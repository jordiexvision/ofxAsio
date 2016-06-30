#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Sender");
}

//--------------------------------------------------------------
void ofApp::update(){

	//send a DataGram (i.e. a message)
	{
		//make the DataGram
		auto dataGram = make_shared<ofxAsio::UDP::DataGram>();

//		dataGram->setEndPoint(ofxAsio::UDP::EndPoint(MYIPADDRESS_1, MYPORT));		

		//enable broadcast
		dataGram->setEndPoint(ofxAsio::UDP::EndPoint(MYIPADDRESS_3, MYPORT, true));		

		auto & message = dataGram->getMessage();
		msg_str = "mouse x " + ofToString(ofGetMouseX()) + " mouse y " + ofToString(ofGetMouseY());
		message.set(msg_str); //--set the message content

		//send the DataGram
		this->sender.send(dataGram);

		auto & m = dataGram->getMessage();
///		cout << m.getMessageString() << endl;
///		cout << "Sent to : " << dataGram->getEndPoint() << endl;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDrawBitmapStringHighlight(msg_str, 100, 100);
}

//--------------------------------------------------------------
void ofApp::exit(){
//	sender.close();
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
