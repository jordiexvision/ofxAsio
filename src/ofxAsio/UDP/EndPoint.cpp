#include "EndPoint.h"

namespace ofxAsio {
	namespace UDP {
		//----------
		EndPoint::EndPoint() {

		}

		//----------
		EndPoint::EndPoint(asio::ip::udp::endpoint & endPoint) :
		endPoint(endPoint) {

		}

		//----------
		EndPoint::EndPoint(string ipAddressString, int port, bool bBroadcast) {
			if (bBroadcast) {
//				auto ipAddress = asio::ip::address::from_string(ipAddressString);
//				auto endPoint = asio::ip::udp::endpoint(ipAddress, port);
				auto endPoint = asio::ip::udp::endpoint(asio::ip::address_v4::broadcast(), port);
				this->endPoint = endPoint;
			}
			else {
				auto ipAddress = asio::ip::address::from_string(ipAddressString);
				auto endPoint = asio::ip::udp::endpoint(ipAddress, port);
				this->endPoint = endPoint;
			}
		}

		//----------
		asio::ip::udp::endpoint & EndPoint::getEndPoint() {
			return this->endPoint;
		}

		//----------
		const asio::ip::udp::endpoint & EndPoint::getEndPoint() const {
			return this->endPoint;
		}

		//----------
		ostream & operator<<(ostream & os, const EndPoint & endPoint) {
			os << endPoint.getEndPoint();
			return os;
		}
	}
}