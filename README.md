## Blink

Code for Blink, dance performance piece to be performed later in October. More documentation will be added shortly.

The application trains a gesture classifier including 30 hand-selected gestures, which are collected via KinectV2 skeleton tracker. The gestures are synchronized to a metronome to determine where the initial and final poses are.

The gestures correspond to programming statements, and are performed live in order for a dancer to construct several simple Arduino scripts from body movement alone.


#### Requirements

- [OpenFrameworks](https://www.openframeworks.cc)
- [ofxLearn](https://github.com/genekogan/ofxLearn)
- [ofxControl](https://github.com/genekogan/ofxControl)
- [ofxKinectV2-OSC](https://github.com/microcosm/ofxKinectV2-OSC)
- [ofxSpreadsheet](https://github.com/genekogan/ofxSpreadsheet)

Additionally, the application requires a Microsoft KinectV2, whose data is streamed over OSC from a Windows machine to the machine running this. Follow the [instructions at ofxKinectV2-OSC](https://github.com/microcosm/ofxKinectV2-OSC) to get that setup.

There will be some more documentation shortly.
