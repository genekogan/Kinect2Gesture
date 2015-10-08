#pragma once

#include "ofMain.h"
#include "KinectV2.h"
#include "KinectV2Classifier.h"



// x fix fbo spreadsheet bug + framecount metro
// feature set: gesture in 2 overlapping halves
// fix bpm bug

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void labelPredicted(int & prediction) {
        cout << "ofapp got prediction " << prediction << endl;
        lastMsg = "predicted: " + classifier.getClassLabel((int) prediction);
    }
    
    KinectV2 kinect;
    KinectV2Classifier classifier;
    
    ofTrueTypeFont font;
    string lastMsg;
    
    bool savingFrames;
};
