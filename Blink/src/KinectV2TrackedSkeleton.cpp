#include "KinectV2Trackedskeleton.h"


KinectV2TrackedSkeleton::KinectV2TrackedSkeleton(string bodyId)
{
    this->bodyId = bodyId;

    thumbRightX.set("thumbRightX", 0, -1000, 1000);
    thumbRightY.set("thumbRightY", 0, -1000, 1000);
    thumbRightZ.set("thumbRightZ", 0, -1000, 1000);
    thumbLeftX.set("thumbLeftX", 0, -1000, 1000);
    thumbLeftY.set("thumbLeftY", 0, -1000, 1000);
    thumbLeftZ.set("thumbLeftZ", 0, -1000, 1000);
    handTipRightX.set("handTipRightX", 0, -1000, 1000);
    handTipRightY.set("handTipRightY", 0, -1000, 1000);
    handTipRightZ.set("handTipRightZ", 0, -1000, 1000);
    handTipLeftX.set("handTipLeftX", 0, -1000, 1000);
    handTipLeftY.set("handTipLeftY", 0, -1000, 1000);
    handTipLeftZ.set("handTipLeftZ", 0, -1000, 1000);

    headX.set("headX", 0, -1000, 1000);
    headY.set("headY", 0, -1000, 1000);
    headZ.set("headZ", 0, -1000, 1000);
    neckX.set("neckX", 0, -1000, 1000);
    neckY.set("neckY", 0, -1000, 1000);
    neckZ.set("neckZ", 0, -1000, 1000);
    spineBaseX.set("spineBaseX", 0, -1000, 1000);
    spineBaseY.set("spineBaseY", 0, -1000, 1000);
    spineBaseZ.set("spineBaseZ", 0, -1000, 1000);
    spineMidX.set("spineMidX", 0, -1000, 1000);
    spineMidY.set("spineMidY", 0, -1000, 1000);
    spineMidZ.set("spineMidZ", 0, -1000, 1000);
    spineShoulderX.set("spineShoulderX", 0, -1000, 1000);
    spineShoulderY.set("spineShoulderY", 0, -1000, 1000);
    spineShoulderZ.set("spineShoulderZ", 0, -1000, 1000);
    
    shoulderRightX.set("shoulderRightX", 0, -1000, 1000);
    shoulderRightY.set("shoulderRightY", 0, -1000, 1000);
    shoulderRightZ.set("shoulderRightZ", 0, -1000, 1000);
    elbowRightX.set("elbowRightX", 0, -1000, 1000);
    elbowRightY.set("elbowRightY", 0, -1000, 1000);
    elbowRightZ.set("elbowRightZ", 0, -1000, 1000);
    wristRightX.set("wristRightX", 0, -1000, 1000);
    wristRightY.set("wristRightY", 0, -1000, 1000);
    wristRightZ.set("wristRightZ", 0, -1000, 1000);
    handRightX.set("handRightX", 0, -1000, 1000);
    handRightY.set("handRightY", 0, -1000, 1000);
    handRightZ.set("handRightZ", 0, -1000, 1000);
    shoulderLeftX.set("shoulderLeftX", 0, -1000, 1000);
    shoulderLeftY.set("shoulderLeftY", 0, -1000, 1000);
    shoulderLeftZ.set("shoulderLeftZ", 0, -1000, 1000);
    elbowLeftX.set("elbowLeftX", 0, -1000, 1000);
    elbowLeftY.set("elbowLeftY", 0, -1000, 1000);
    elbowLeftZ.set("elbowLeftZ", 0, -1000, 1000);
    wristLeftX.set("wristLeftX", 0, -1000, 1000);
    wristLeftY.set("wristLeftY", 0, -1000, 1000);
    wristLeftZ.set("wristLeftZ", 0, -1000, 1000);
    handLeftX.set("handLeftX", 0, -1000, 1000);
    handLeftY.set("handLeftY", 0, -1000, 1000);
    handLeftZ.set("handLeftZ", 0, -1000, 1000);
    
    hipRightX.set("hipRightX", 0, -1000, 1000);
    hipRightY.set("hipRightY", 0, -1000, 1000);
    hipRightZ.set("hipRightZ", 0, -1000, 1000);
    kneeRightX.set("kneeRightX", 0, -1000, 1000);
    kneeRightY.set("kneeRightY", 0, -1000, 1000);
    kneeRightZ.set("kneeRightZ", 0, -1000, 1000);
    ankleRightX.set("ankleRightX", 0, -1000, 1000);
    ankleRightY.set("ankleRightY", 0, -1000, 1000);
    ankleRightZ.set("ankleRightZ", 0, -1000, 1000);
    footRightX.set("footRightX", 0, -1000, 1000);
    footRightY.set("footRightY", 0, -1000, 1000);
    footRightZ.set("footRightZ", 0, -1000, 1000);
    hipLeftX.set("hipLeftX", 0, -1000, 1000);
    hipLeftY.set("hipLeftY", 0, -1000, 1000);
    hipLeftZ.set("hipLeftZ", 0, -1000, 1000);
    kneeLeftX.set("kneeLeftX", 0, -1000, 1000);
    kneeLeftY.set("kneeLeftY", 0, -1000, 1000);
    kneeLeftZ.set("kneeLeftZ", 0, -1000, 1000);
    ankleLeftX.set("ankleLeftX", 0, -1000, 1000);
    ankleLeftY.set("ankleLeftY", 0, -1000, 1000);
    ankleLeftZ.set("ankleLeftZ", 0, -1000, 1000);
    footLeftX.set("footLeftX", 0, -1000, 1000);
    footLeftY.set("footLeftY", 0, -1000, 1000);
    footLeftZ.set("footLeftZ", 0, -1000, 1000);
    
    setupJointsUpperBody();
    setupJointsLowerBody();
    setupJointsHands();
    setupJointsGestural();
    setupJointsAll();
    
    for (auto p : getJointsUpperBody())
    {
        ofParameter<float> newParameter;
        newParameter.set("v_"+p.getName(), 0, -100, 100);
        velocities.push_back(newParameter);
    }
    pJoints.resize(velocities.size());

}

void KinectV2TrackedSkeleton::update(Skeleton * skeleton)
{
    // save previous joint states
    for (int i = 0; i <jointsUpperBody.size(); i++) {
        pJoints[i] = jointsUpperBody[i];
    }
    
    thumbRightX.set(skeleton->getThumbRight().getPoint().x);
    thumbRightY.set(skeleton->getThumbRight().getPoint().y);
    thumbRightZ.set(skeleton->getThumbRight().getPoint().z);
    thumbLeftX.set(skeleton->getThumbLeft().getPoint().x);
    thumbLeftY.set(skeleton->getThumbLeft().getPoint().y);
    thumbLeftZ.set(skeleton->getThumbLeft().getPoint().z);
    handTipRightX.set(skeleton->getHandTipRight().getPoint().x);
    handTipRightY.set(skeleton->getHandTipRight().getPoint().y);
    handTipRightZ.set(skeleton->getHandTipRight().getPoint().z);
    handTipLeftX.set(skeleton->getHandTipLeft().getPoint().x);
    handTipLeftY.set(skeleton->getHandTipLeft().getPoint().y);
    handTipLeftZ.set(skeleton->getHandTipLeft().getPoint().z);
    headX.set(skeleton->getHead().getPoint().x);
    headY.set(skeleton->getHead().getPoint().y);
    headZ.set(skeleton->getHead().getPoint().z);
    neckX.set(skeleton->getNeck().getPoint().x);
    neckY.set(skeleton->getNeck().getPoint().y);
    neckZ.set(skeleton->getNeck().getPoint().z);
    spineBaseX.set(skeleton->getSpineBase().getPoint().x);
    spineBaseY.set(skeleton->getSpineBase().getPoint().y);
    spineBaseZ.set(skeleton->getSpineBase().getPoint().z);
    spineMidX.set(skeleton->getSpineMid().getPoint().x);
    spineMidY.set(skeleton->getSpineMid().getPoint().y);
    spineMidZ.set(skeleton->getSpineMid().getPoint().z);
    spineShoulderX.set(skeleton->getSpineShoulder().getPoint().x);
    spineShoulderY.set(skeleton->getSpineShoulder().getPoint().y);
    spineShoulderZ.set(skeleton->getSpineShoulder().getPoint().z);
    shoulderRightX.set(skeleton->getShoulderRight().getPoint().x);
    shoulderRightY.set(skeleton->getShoulderRight().getPoint().y);
    shoulderRightZ.set(skeleton->getShoulderRight().getPoint().z);
    elbowRightX.set(skeleton->getElbowRight().getPoint().x);
    elbowRightY.set(skeleton->getElbowRight().getPoint().y);
    elbowRightZ.set(skeleton->getElbowRight().getPoint().z);
    wristRightX.set(skeleton->getWristRight().getPoint().x);
    wristRightY.set(skeleton->getWristRight().getPoint().y);
    wristRightZ.set(skeleton->getWristRight().getPoint().z);
    handRightX.set(skeleton->getHandRight().getPoint().x);
    handRightY.set(skeleton->getHandRight().getPoint().y);
    handRightZ.set(skeleton->getHandRight().getPoint().z);
    shoulderLeftX.set(skeleton->getShoulderLeft().getPoint().x);
    shoulderLeftY.set(skeleton->getShoulderLeft().getPoint().y);
    shoulderLeftZ.set(skeleton->getShoulderLeft().getPoint().z);
    elbowLeftX.set(skeleton->getElbowLeft().getPoint().x);
    elbowLeftY.set(skeleton->getElbowLeft().getPoint().y);
    elbowLeftZ.set(skeleton->getElbowLeft().getPoint().z);
    wristLeftX.set(skeleton->getWristLeft().getPoint().x);
    wristLeftY.set(skeleton->getWristLeft().getPoint().y);
    wristLeftZ.set(skeleton->getWristLeft().getPoint().z);
    handLeftX.set(skeleton->getHandLeft().getPoint().x);
    handLeftY.set(skeleton->getHandLeft().getPoint().y);
    handLeftZ.set(skeleton->getHandLeft().getPoint().z);
    hipRightX.set(skeleton->getHipRight().getPoint().x);
    hipRightY.set(skeleton->getHipRight().getPoint().y);
    hipRightZ.set(skeleton->getHipRight().getPoint().z);
    kneeRightX.set(skeleton->getKneeRight().getPoint().x);
    kneeRightY.set(skeleton->getKneeRight().getPoint().y);
    kneeRightZ.set(skeleton->getKneeRight().getPoint().z);
    ankleRightX.set(skeleton->getAnkleRight().getPoint().x);
    ankleRightY.set(skeleton->getAnkleRight().getPoint().y);
    ankleRightZ.set(skeleton->getAnkleRight().getPoint().z);
    footRightX.set(skeleton->getFootRight().getPoint().x);
    footRightY.set(skeleton->getFootRight().getPoint().y);
    footRightZ.set(skeleton->getFootRight().getPoint().z);
    hipLeftX.set(skeleton->getHipLeft().getPoint().x);
    hipLeftY.set(skeleton->getHipLeft().getPoint().y);
    hipLeftZ.set(skeleton->getHipLeft().getPoint().z);
    kneeLeftX.set(skeleton->getKneeLeft().getPoint().x);
    kneeLeftY.set(skeleton->getKneeLeft().getPoint().y);
    kneeLeftZ.set(skeleton->getKneeLeft().getPoint().z);
    ankleLeftX.set(skeleton->getAnkleLeft().getPoint().x);
    ankleLeftY.set(skeleton->getAnkleLeft().getPoint().y);
    ankleLeftZ.set(skeleton->getAnkleLeft().getPoint().z);
    footLeftX.set(skeleton->getFootLeft().getPoint().x);
    footLeftY.set(skeleton->getFootLeft().getPoint().y);
    footLeftZ.set(skeleton->getFootLeft().getPoint().z);
    
    
    // update velocities
    for (int i = 0; i <jointsUpperBody.size(); i++) {
        velocities[i] = ofLerp(velocities[i], jointsUpperBody[i] - pJoints[i], 0.1);
    }
}

void KinectV2TrackedSkeleton::setupJointsUpperBody()
{
    jointsUpperBody.clear();
    jointsUpperBody.push_back(headX);
    jointsUpperBody.push_back(headY);
    jointsUpperBody.push_back(headZ);
    jointsUpperBody.push_back(neckX);
    jointsUpperBody.push_back(neckY);
    jointsUpperBody.push_back(neckZ);
    jointsUpperBody.push_back(spineBaseX);
    jointsUpperBody.push_back(spineBaseY);
    jointsUpperBody.push_back(spineBaseZ);
    jointsUpperBody.push_back(spineMidX);
    jointsUpperBody.push_back(spineMidY);
    jointsUpperBody.push_back(spineMidZ);
    jointsUpperBody.push_back(spineShoulderX);
    jointsUpperBody.push_back(spineShoulderY);
    jointsUpperBody.push_back(spineShoulderZ);
    jointsUpperBody.push_back(shoulderRightX);
    jointsUpperBody.push_back(shoulderRightY);
    jointsUpperBody.push_back(shoulderRightZ);
    jointsUpperBody.push_back(elbowRightX);
    jointsUpperBody.push_back(elbowRightY);
    jointsUpperBody.push_back(elbowRightZ);
    jointsUpperBody.push_back(wristRightX);
    jointsUpperBody.push_back(wristRightY);
    jointsUpperBody.push_back(wristRightZ);
    jointsUpperBody.push_back(handRightX);
    jointsUpperBody.push_back(handRightY);
    jointsUpperBody.push_back(handRightZ);
    jointsUpperBody.push_back(shoulderLeftX);
    jointsUpperBody.push_back(shoulderLeftY);
    jointsUpperBody.push_back(shoulderLeftZ);
    jointsUpperBody.push_back(elbowLeftX);
    jointsUpperBody.push_back(elbowLeftY);
    jointsUpperBody.push_back(elbowLeftZ);
    jointsUpperBody.push_back(wristLeftX);
    jointsUpperBody.push_back(wristLeftY);
    jointsUpperBody.push_back(wristLeftZ);
    jointsUpperBody.push_back(handLeftX);
    jointsUpperBody.push_back(handLeftY);
    jointsUpperBody.push_back(handLeftZ);
}

void KinectV2TrackedSkeleton::setupJointsLowerBody()
{
    jointsLowerBody.clear();
    jointsLowerBody.push_back(hipRightX);
    jointsLowerBody.push_back(hipRightY);
    jointsLowerBody.push_back(hipRightZ);
    jointsLowerBody.push_back(kneeRightX);
    jointsLowerBody.push_back(kneeRightY);
    jointsLowerBody.push_back(kneeRightZ);
    jointsLowerBody.push_back(ankleRightX);
    jointsLowerBody.push_back(ankleRightY);
    jointsLowerBody.push_back(ankleRightZ);
    jointsLowerBody.push_back(footRightX);
    jointsLowerBody.push_back(footRightY);
    jointsLowerBody.push_back(footRightZ);
    jointsLowerBody.push_back(hipLeftX);
    jointsLowerBody.push_back(hipLeftY);
    jointsLowerBody.push_back(hipLeftZ);
    jointsLowerBody.push_back(kneeLeftX);
    jointsLowerBody.push_back(kneeLeftY);
    jointsLowerBody.push_back(kneeLeftZ);
    jointsLowerBody.push_back(ankleLeftX);
    jointsLowerBody.push_back(ankleLeftY);
    jointsLowerBody.push_back(ankleLeftZ);
    jointsLowerBody.push_back(footLeftX);
    jointsLowerBody.push_back(footLeftY);
    jointsLowerBody.push_back(footLeftZ);
}

void KinectV2TrackedSkeleton::setupJointsHands()
{
    jointsHands.clear();
    jointsHands.push_back(thumbRightX);
    jointsHands.push_back(thumbRightY);
    jointsHands.push_back(thumbRightZ);
    jointsHands.push_back(thumbLeftX);
    jointsHands.push_back(thumbLeftY);
    jointsHands.push_back(thumbLeftZ);
    jointsHands.push_back(handTipRightX);
    jointsHands.push_back(handTipRightY);
    jointsHands.push_back(handTipRightZ);
    jointsHands.push_back(handTipLeftX);
    jointsHands.push_back(handTipLeftY);
    jointsHands.push_back(handTipLeftZ);
}

void KinectV2TrackedSkeleton::setupJointsGestural()
{
    jointsGestural.clear();
    jointsGestural.push_back(handLeftX);
    jointsGestural.push_back(handLeftY);
    jointsGestural.push_back(handLeftZ);
    jointsGestural.push_back(elbowLeftX);
    jointsGestural.push_back(elbowLeftY);
    jointsGestural.push_back(elbowLeftZ);
    jointsGestural.push_back(handRightX);
    jointsGestural.push_back(handRightY);
    jointsGestural.push_back(handRightZ);
    jointsGestural.push_back(elbowRightX);
    jointsGestural.push_back(elbowRightY);
    jointsGestural.push_back(elbowRightZ);    
    jointsGestural.push_back(kneeLeftX);
    jointsGestural.push_back(kneeLeftY);
    jointsGestural.push_back(kneeLeftZ);
    jointsGestural.push_back(footLeftX);
    jointsGestural.push_back(footLeftY);
    jointsGestural.push_back(footLeftZ);
    jointsGestural.push_back(kneeRightX);
    jointsGestural.push_back(kneeRightY);
    jointsGestural.push_back(kneeRightZ);
    jointsGestural.push_back(footRightX);
    jointsGestural.push_back(footRightY);
    jointsGestural.push_back(footRightZ);
}

void KinectV2TrackedSkeleton::setupJointsAll()
{
    jointsAll.clear();
    for (auto p : getJointsUpperBody())   jointsAll.push_back(p);
    for (auto p : getJointsLowerBody())   jointsAll.push_back(p);
    for (auto p : getJointsHands())       jointsAll.push_back(p);
}