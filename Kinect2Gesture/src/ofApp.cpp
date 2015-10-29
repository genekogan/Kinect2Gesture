#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowPosition(0, 0);
    font.loadFont("verdana.ttf", 48);
    lastMsg = "";
    
    kinect.setup();
    //kinect.setReceiveFromFile("/Users/gene/Code/of_v0.8-4.4_osx_release/addons/ofxKinectV2-OSC/example/bin/data/gestures1.txt");
    ofAddListener(classifier.predictionE, this, &ofApp::labelPredicted);
    classifier.setup(&kinect);
 
    ofBuffer buffer = ofBufferFromFile(ofToDataPath("ip.txt")); // reading into the buffer
    string address = buffer.getText();
    send.setup(address, 1357);
}

//--------------------------------------------------------------
void ofApp::labelPredicted(int & prediction) {
    lastMsg = classifier.getClassLabel((int) prediction);

    ofxOscMessage msg;
    msg.setAddress("/prediction");
    msg.addIntArg((int) prediction);
    send.sendMessage(msg);
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
    classifier.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::black, ofColor::darkGrey);
    
    classifier.draw();
    kinect.draw();
    
    if (classifier.getPredicting()) {
        ofSetColor(0, 120);
        ofRect(240, 448, 764, 85);
        ofSetColor(0, 230, 0);
        //font.drawString(lastMsg, ofGetWidth()-720, ofGetHeight()-130);
        font.drawString(lastMsg, 304, 516);
    }
    
    if (classifier.getCapturing()) {
        ofSetColor(255, 0, 0, 200);
        ofCircle(895, 488, 120);
        ofSetColor(255);
    }
    
    classifier.drawCounter();
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
