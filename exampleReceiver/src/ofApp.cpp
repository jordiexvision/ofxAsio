#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Receiver");

	// When binding a server, we must use the server's constructor
	// We use an empty pointer to represent that no server is bound.

	this->receiver = make_shared<ofxAsio::UDP::Socket>(4444);

}

//--------------------------------------------------------------
void ofApp::update(){

	//try to receive data
	{
		//receive a DataGram
		auto dataGram = this->receiver->receive();
		const auto & message = dataGram->getMessage();
		msg_str = message.getMessageString();
///		cout << message.getMessageString() << endl;
///		cout << "Arrived from : " << dataGram->getEndPoint() << endl;
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDrawBitmapStringHighlight(msg_str, 100, 100);
}

//--------------------------------------------------------------
void ofApp::exit() {
//	receiver.reset();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
