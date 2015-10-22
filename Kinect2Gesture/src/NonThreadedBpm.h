#pragma once
#include "ofMain.h"

class NonThreadedBpm
{
public:
    void setup(int bpm) {
        soundActive = false;
        active = true;
        setBpm(bpm);
    }
    void setupSound(string filename) {
        sound.loadSound(filename);
        sound.setVolume(1.0);
        soundActive = true;
    }
    void update() {
        if (!active) return;
        float t = ofGetElapsedTimef() - lastTime;
        if (t > interval) {
            lastTime = ofGetElapsedTimef();// - (t - interval);
            tick++;
            if (soundActive) {
                sound.play();
            }
            ofNotifyEvent(beatEvent);
        }
    }
    void setBpm(float bpm) {
        this->bpm = (float) bpm;
        lastTime = ofGetElapsedTimef();
        interval = 60.0 / bpm;
    }
    void start() {this->active = true;}
    void stop() {this->active = false;}
    void toggle() {this->active = !active;}
    int getTick() {return tick;}
    bool getActive() {return active;}
    
    float bpm;
    int tick;
    float lastTime;
    float interval;
    bool active;
    bool soundActive;
    ofSoundPlayer sound;
    ofEvent<void> beatEvent;
};

