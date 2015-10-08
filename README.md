## Blink

Code for **Blink**, upcoming dance performance piece to be performed later in October, along with Nancy Nowacek and Morgan Hille Refakis. More documentation will be added shortly.

The application trains a gesture classifier containing 30 hand-selected gestures, which are collected via KinectV2 skeleton tracker. The gestures are synchronized to a metronome to determine where the initial and final poses are, and correspond to programming statements. They are to be performed live in order for a dancer to construct several simple Arduino scripts from body movement alone.


#### Requirements

- [openFrameworks](http://www.openframeworks.cc) (tested on 0.8.4)
- [ofxLearn](https://github.com/genekogan/ofxLearn)
- [ofxControl](https://github.com/genekogan/ofxControl)
- [ofxKinectV2-OSC](https://github.com/microcosm/ofxKinectV2-OSC)
- [ofxSpreadsheet](https://github.com/genekogan/ofxSpreadsheet)

Additionally, the application requires a Microsoft KinectV2, whose data is streamed over OSC from a Windows machine to the machine running this. Follow the [instructions at ofxKinectV2-OSC](https://github.com/microcosm/ofxKinectV2-OSC) to get that setup.

There will be some more documentation shortly.
