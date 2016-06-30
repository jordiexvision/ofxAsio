#include "Socket.h"

namespace ofxAsio {
	namespace UDP {
		//----------
		// call used in Server
		Socket::Socket()
			: socket(this->ioService)
			, work(this->ioService)
		{
			socket.open(asio::ip::udp::v4());

			// Allow other processes to reuse the address, permitting other processes on 
			// the same machine to use the multicast address. 
			socket.set_option(asio::ip::udp::socket::reuse_address(true));
			// do this before binding 
			socket.set_option(asio::socket_base::broadcast(true));
			cout << "server socket initialized" << endl;

			this->asyncThread = thread([this]() {
				this->ioService.run();
			});
		}

		//----------
		// call used in Client
		Socket::Socket(int port)
			// exception handling in initializer list // http://stackoverflow.com/questions/697026/exception-handling-in-constructor-s-initializer-list
			try
			: socket(this->ioService, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
			, work(this->ioService)
		{
			//constructor function body  
			cout << "client socket initialized" << endl;
			this->asyncThread = thread([this]() {
				this->ioService.run();
			});
		}
		//handles exceptions thrown from the ctor-initializer  
		//and from the constructor functionbody  
		catch (std::exception & e)
		{
			ofLogError() << "Failed to open Receiver on port " << port << " : " << e.what();
		}

		//----------
		Socket::Socket(string ipAddress, int port)
			: socket(this->ioService, asio::ip::udp::endpoint(asio::ip::address::from_string(ipAddress), port))
			, work(this->ioService)
		{
			this->asyncThread = thread([this]() {
				this->ioService.run();
			});
		}

		//----------
		Socket::~Socket() {
			this->close();
		}

		//----------
		shared_ptr<DataGram> Socket::receive(size_t bufferSize) {
			asio::error_code errorCode;
			auto dataGram = make_shared<DataGram>();
			auto & message = dataGram->getMessage();
			message.resize(bufferSize);

			auto mutableBuffer = asio::buffer(message.data(), message.size());

			auto receivedSize = this->socket.receive_from(mutableBuffer, dataGram->getEndPoint().getEndPoint(), 0, errorCode);

			if (errorCode) {
				//return empty pointer if we failed to receive
				ofLogError("ofxAsio::UDP::Socket::receive") << "Cannot receive data. " << asio::system_error(errorCode).what();
				return shared_ptr<DataGram>();
			}
			else {
				//return pointer to a DataGram object if succeed
				message.resize(receivedSize);
				return dataGram;
			}
		}

		//----------
		void Socket::asyncReceiveOnce(const function<void(AsyncArguments)> & callback, size_t bufferSize) {
			this->asyncIncoming.buffer.resize(bufferSize);
			this->socket.async_receive_from(
				asio::buffer(this->asyncIncoming.buffer),
				this->asyncIncoming.endpoint,
				[this, callback](asio::error_code errorCode,
					size_t size) {
				if (errorCode) {
					AsyncArguments args = {
						false,
						asio::system_error(errorCode).what(),
						shared_ptr<DataGram>()
					};
					callback(args);
				}
				else {
					auto dataGram = make_shared<DataGram>();
					dataGram->getMessage().set(this->asyncIncoming.buffer);
					dataGram->setEndPoint(this->asyncIncoming.endpoint);

					AsyncArguments args = {
						true,
						asio::system_error(errorCode).what(),
						dataGram
					};
					callback(args);
				}
			});
		}

		//----------
		void Socket::asyncReceiveAll(const function<void(AsyncArguments)> & callback, size_t bufferSize) {
			this->asyncReceiveOnce([this, callback, bufferSize](AsyncArguments args) {
				asyncReceiveAll(callback, bufferSize);
				callback(args);
			});
		}

		//----------
		bool Socket::send(shared_ptr<DataGram> dataGram) {
			asio::error_code errorCode;
			const auto & message = dataGram->getMessage();
			const auto & endPoint = dataGram->getEndPoint().getEndPoint();

			//this is a wrapper not a copy
			auto buffer = asio::buffer(message.data(), message.size());

			this->socket.send_to(buffer, endPoint, 0, errorCode);

			if (errorCode) {
				ofLogError("ofxAsio::UDP::Socket::send") << "Cannot send data. " << asio::system_error(errorCode).what();
				return false;
			}
			else {
				return true;
			}
		}

		asio::ip::udp::socket & Socket::getSocket()
		{
			return this->socket;
		}

		//----------
		void Socket::close() {
			this->socket.cancel();
			this->ioService.stop();
			if (this->asyncThread.joinable()) {
				this->asyncThread.join();
			}
		}
	}
}