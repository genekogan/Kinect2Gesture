#pragma once

#include "ofMain.h"
#include "ofxKinectV2OSC.h"
#include "KinectV2TrackedSkeleton.h"


class KinectV2TrackedSkeleton;


class KinectV2 {
public:
    void setup();
    virtual void update();
    void draw();

    void setReceiveFromFile(string filename);
    
    template <typename L, typename M>
    void setToTrackFirstFoundUser(L *listener, M method);

    ofxKinectV2OSC & getKinect() {return kinect;}
protected:
    
    void updateTrackedSkeletons();
    void assignFirst();
    KinectV2TrackedSkeleton * trackSkeleton(string bodyId);
    
    ofxKinectV2OSC kinect;
    map<string, KinectV2TrackedSkeleton*> trackedSkeletons;
    vector<Skeleton>* skeletons;
    BodyRenderer renderer;

    bool toAssignFirst;
    ofEvent<KinectV2TrackedSkeleton*> foundUserE;
    KinectV2TrackedSkeleton *primaryTrackedSkeleton;
    KinectV2TrackedSkeleton *trackedUserArchetype;
};


template <typename L, typename M>
void KinectV2::setToTrackFirstFoundUser(L *listener, M method)
{
    toAssignFirst = true;
    ofAddListener(foundUserE, listener, method);
}
