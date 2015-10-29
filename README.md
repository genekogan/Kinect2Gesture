## Kinect2Gesture + Blink

**Kinect2Gesture** is an application which trains a classifier to recognize custom gestures, which are collected via KinectV2 skeleton tracker. The gestures are synchronized to a metronome to determine the initial and final poses. Once trained, the classifier predicts gestures and sends the predictions over OSC. See the [tutorial video](https://vimeo.com/143963394) and [instructions](https://github.com/genekogan/Kinect2Gesture/blob/master/Instructions.md) to set it up.

**Blink** is the specific version of Kinect2Gesture which was used in a performance piece made with Nancy Nowacek, Morgan Hille Refakis, and Dave Scheinkopf. In the piece, we used the gesture classifier to turn choreographed dance poses into Arduino code statements, which were then fed to a computer to generate the Arduino blinky script. The piece was performed live at [Debaun Performing Arts Center](http://ugstudentlife.stevens.edu/org/debauncenter) in Hoboken, NJ, October 2015. 

#### Requirements

- [openFrameworks](http://www.openframeworks.cc) (tested on 0.8.4)
- [ofxLearn](https://github.com/genekogan/ofxLearn)
- [ofxControl](https://github.com/genekogan/ofxControl)
- [ofxKinectV2-OSC](https://github.com/microcosm/ofxKinectV2-OSC)
- [ofxSpreadsheet](https://github.com/genekogan/ofxSpreadsheet)

Additionally, the application requires a Microsoft KinectV2, whose data is streamed over OSC from a Windows machine to the machine running this. Follow the [instructions at ofxKinectV2-OSC](https://github.com/microcosm/ofxKinectV2-OSC) to get that setup.
