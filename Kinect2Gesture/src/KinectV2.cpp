#include "KinectV2.h"


void KinectV2::setup()
{
    kinect.setup(12345);
    skeletons = kinect.getSkeletons();
    renderer.setup(skeletons);
    toAssignFirst = false;
    trackedUserArchetype = NULL;
}

void KinectV2::setReceiveFromFile(string filename)
{
    kinect.setReceiveFromFile(filename);
}

void KinectV2::update()
{
    kinect.update();
    if (toAssignFirst) {
        assignFirst();
    }
    updateTrackedSkeletons();
}

void KinectV2::draw() {
    kinect.drawDebug();
    renderer.draw();
}

void KinectV2::updateTrackedSkeletons()
{
    /*
    for (int i=0; i<skeletons->size(); i++)
    {
        if (trackedSkeletons.count(skeletons->at(i).getBodyId()) > 0) {
            trackedSkeletons[skeletons->at(i).getBodyId()]->update(&skeletons->at(i));
        }
    }
     */
    if (skeletons->size() > 0 && primaryTrackedSkeleton != NULL) {
        primaryTrackedSkeleton->update(&skeletons->at(0));
    }
}

void KinectV2::assignFirst()
{
    if (trackedSkeletons.size() == 0 && skeletons->size() > 0)
    {
        KinectV2TrackedSkeleton *newTrackedSkeleton = trackSkeleton(skeletons->at(0).getBodyId());
        primaryTrackedSkeleton = newTrackedSkeleton;
        ofNotifyEvent(foundUserE, newTrackedSkeleton);
    }
}

KinectV2TrackedSkeleton * KinectV2::trackSkeleton(string bodyId)
{
    KinectV2TrackedSkeleton *newTrackedSkeleton = new KinectV2TrackedSkeleton(bodyId);
    if (trackedUserArchetype != NULL)
    {
        vector<ofParameter<float> > & newUserJoints = newTrackedSkeleton->getJointsAll();
        vector<ofParameter<float> > & archetypeJoints = trackedUserArchetype->getJointsAll();
        for (int i=0; i<newTrackedSkeleton->getJointsAll().size(); i++) {
            newUserJoints[i].setMin(archetypeJoints[i].getMin());
            newUserJoints[i].setMax(archetypeJoints[i].getMax());
        }
    }
    trackedSkeletons[bodyId] = newTrackedSkeleton;
    return newTrackedSkeleton;
}
