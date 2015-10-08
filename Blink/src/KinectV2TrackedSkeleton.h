#pragma once

#include "ofMain.h"
#include "KinectV2.h"

class Skeleton;

class KinectV2TrackedSkeleton{
    friend class KinectV2;
    friend class KinectV2Input;
public:
    KinectV2TrackedSkeleton(string bodyId);
    
    void update(Skeleton * skeleton);
    
    vector<ofParameter<float> > & getJointsUpperBody() {return jointsUpperBody;}
    vector<ofParameter<float> > & getJointsLowerBody() {return jointsLowerBody;}
    vector<ofParameter<float> > & getJointsAll() {return jointsAll;}
    vector<ofParameter<float> > & getJointsHands() {return jointsHands;}
    vector<ofParameter<float> > & getJointsGestural() {return jointsGestural;}
    vector<ofParameter<float> > & getVelocityJointsUpperBody() {return velocities;}
    
    // torso
    ofParameter<float> headX, headY, headZ;
    ofParameter<float> neckX, neckY, neckZ;
    ofParameter<float> spineBaseX, spineBaseY, spineBaseZ;
    ofParameter<float> spineMidX, spineMidY, spineMidZ;
    ofParameter<float> spineShoulderX, spineShoulderY, spineShoulderZ;
    
    // arms
    ofParameter<float> shoulderRightX, shoulderRightY, shoulderRightZ;
    ofParameter<float> elbowRightX, elbowRightY, elbowRightZ;
    ofParameter<float> wristRightX, wristRightY, wristRightZ;
    ofParameter<float> handRightX, handRightY, handRightZ;
    ofParameter<float> shoulderLeftX, shoulderLeftY, shoulderLeftZ;
    ofParameter<float> elbowLeftX, elbowLeftY, elbowLeftZ;
    ofParameter<float> wristLeftX, wristLeftY, wristLeftZ;
    ofParameter<float> handLeftX, handLeftY, handLeftZ;
    
    // legs
    ofParameter<float> hipRightX, hipRightY, hipRightZ;
    ofParameter<float> kneeRightX, kneeRightY, kneeRightZ;
    ofParameter<float> ankleRightX, ankleRightY, ankleRightZ;
    ofParameter<float> footRightX, footRightY, footRightZ;
    ofParameter<float> hipLeftX, hipLeftY, hipLeftZ;
    ofParameter<float> kneeLeftX, kneeLeftY, kneeLeftZ;
    ofParameter<float> ankleLeftX, ankleLeftY, ankleLeftZ;
    ofParameter<float> footLeftX, footLeftY, footLeftZ;
    
    // hands
    ofParameter<float> thumbRightX, thumbRightY, thumbRightZ;
    ofParameter<float> thumbLeftX, thumbLeftY, thumbLeftZ;
    ofParameter<float> handTipRightX, handTipRightY, handTipRightZ;
    ofParameter<float> handTipLeftX, handTipLeftY, handTipLeftZ;
    

protected:
    
    void setupJointsUpperBody();
    void setupJointsLowerBody();
    void setupJointsHands();
    void setupJointsGestural();
    void setupJointsAll();

    string bodyId;
    
    // collections
    vector<ofParameter<float> > jointsUpperBody;
    vector<ofParameter<float> > jointsLowerBody;
    vector<ofParameter<float> > jointsAll;
    vector<ofParameter<float> > jointsHands;
    vector<ofParameter<float> > jointsGestural;
    vector<ofParameter<float> > velocities;
    
    vector<float> pJoints;
};
