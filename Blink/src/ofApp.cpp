#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    font.loadFont("/Users/gene/Code/of_v0.8-4.4_osx_release/apps/SteveDocUMusical/Steve_A_Docu_Musical2/bin/data/verdana.ttf", 48);
    
    kinect.setup();
    //kinect.setReceiveFromFile("/Users/gene/Code/of_v0.8-4.4_osx_release/addons/ofxKinectV2-OSC/example/bin/data/gestures1.txt");
    ofAddListener(classifier.predictionE, this, &ofApp::labelPredicted);
    classifier.setup(&kinect);
    
    classifier.addClass("HIGH");
    classifier.addClass(",");
    classifier.addClass("LOW");
    classifier.addClass("output");
    classifier.addClass("void setup");
    classifier.addClass("=");
    classifier.addClass("()");
    classifier.addClass("digitalWrite");
    classifier.addClass("for");
    classifier.addClass("pinMode");
    classifier.addClass("[");
    classifier.addClass("]");
    classifier.addClass("int");
    classifier.addClass("x");
    classifier.addClass("0");
    classifier.addClass("(");
    classifier.addClass(";");
    classifier.addClass("void loop");
    classifier.addClass("delay");
    classifier.addClass("<");
    classifier.addClass("+");
    classifier.addClass("5");
    classifier.addClass("3");
    classifier.addClass("1");
    classifier.addClass("rest");
    classifier.addClass("led");
    classifier.addClass("BACKSPACE");
    classifier.addClass("SPACEBAR");
    classifier.addClass("VERIFY");
    classifier.addClass("UPLOAD");
    
    lastMsg = "predicted: ";
    
    savingFrames = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
    classifier.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    classifier.draw();
    kinect.draw();
    
    if (classifier.getCapturing()) {
        ofSetColor(255, 0, 0);
        ofCircle(100, ofGetHeight()-100, 100, 100);
        ofSetColor(255);
    }
    
    ofSetColor(0, 100, 0);
    font.drawString(lastMsg, ofGetWidth()-720, ofGetHeight()-130);
    ofSetColor(255);
    
    if (savingFrames) {
        ofSaveFrame();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key=='1') {
        classifier.setCapturing(true);
    }
    if (key=='2') {
        classifier.setCapturing(false);
    }
    
    if (key=='3') {
        classifier.toggleClock();
    }
    
    if (key=='s') {
        classifier.savePreset("thisPreset.xml");
    }
    if (key=='l') {
        classifier.loadPreset("thisPreset.xml");
    }
    if (key=='r') {
        savingFrames = !savingFrames;
    }
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
