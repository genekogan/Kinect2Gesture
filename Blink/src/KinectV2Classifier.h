#pragma once

#include "ofMain.h"
#include "ofxControl.h"
#include "ofxOsc.h"
#include "ofxSpreadsheet.h"
#include "ofxLearn.h"
#include "KinectV2.h"
#include "NonThreadedBpm.h"


#define USE_TWO_PHASE true


class KinectV2Classifier
{
public:
    void setup(KinectV2 *kinect);
    void update();
    void draw();
    
    void receiveFirstUser(KinectV2TrackedSkeleton* & skeleton);

    void toggleClock() {clock.toggle();}
    
    void setCapturing(bool capturing);
    void beginCaptureGesture();
    void endCaptureGesture();
    
    void setCalibrating(bool calibrating);
    void calibrate();
    void resetMinMaxRange();
    
    void setPredicting(bool predicting);
    void setTrainingLabel(int trainingLabel);
    void train();
    void predictLabel(int predictedLabel);
    
    bool getCapturing() {return capturing;}
    bool getRecording() {return recording;}
    bool getPredicting() {return predicting;}
    
    void savePreset(string filename);
    void loadPreset(string filename);
    
    void addClass(string name);
    string getClassLabel(int index) {return classes[index-1];}
    
    ofEvent<int> predictionE;
    
private:
    void createFeatureVector(vector<float> & features);
    void createFeatureVectorTwoPhase(vector<float> & features);
    
    void beatEvent() {setCapturing(clock.getTick() % 2 != 0);}

    void captureGesture();
    void checkOscMessages();
    
    void eventSetBpm(ofxControlSliderEventArgs<int> & evt) {clock.setBpm(evt.value);}
    void eventSetCalibrating(ofxControlButtonEventArgs & evt) {setCalibrating(evt.value);}
    void eventSetResetCalibration(ofxControlButtonEventArgs & evt) {resetMinMaxRange();}
    void eventSetCapturing(ofxControlButtonEventArgs & evt) {setCapturing(evt.value);}
    void eventSetPredicting(ofxControlButtonEventArgs & evt) {setPredicting(evt.value);}
    void eventSetTrainingLabel(ofxControlMenuEventArgs & evt) {setTrainingLabel(trainingLabel = 1 + evt.index);}
    void eventSetTrain(ofxControlButtonEventArgs & evt) {train();}
    void getStateVector(vector<float> & currentState);
    
    void setLearnXml(ofXml &xml);
    void setFromLearnXml(ofXml &xml);
    
    bool twoPhase = USE_TWO_PHASE;
    
    NonThreadedBpm clock;
    
    KinectV2 *kinect;
    KinectV2TrackedSkeleton *skeleton;
    vector<vector<float> > poses;
    vector<float> min, max;
    int trainingLabel;
    ofxSpreadsheet data;
    
    bool recording;
    bool capturing;
    bool predicting;
    bool calibrating;
    bool calibrated;
    bool trained;
    
    ofxControlWidget gui;
    ofxOscReceiver osc;
    
    ofxLearnSVM svm;
    int numLayers;
    
    ofxControlMenu *menu;
    vector<string> classes;
  
};