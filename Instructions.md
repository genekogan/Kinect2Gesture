## Kinect2Gesture instructions

This is a tutorial for how to use Kinect2Gesture, an application which is trained to recognize and classify custom choreographed gestures tracked by a KinectV2 timed to a metronome, and to send the class predictions over OSC for further processing.

#### [A companion tutorial video can be viewed here](https://vimeo.com/143963394).


### Setup

#### Skeleton tracking application

You need a [KinectV2](http://www.microsoft.com/en-us/kinectforwindows/purchase/) and a PC with USB3 and Windows 8.1 to run [KinectV2-OSC](https://github.com/microcosm/KinectV2-OSC). Follow the instructions in there to set up the skeleton tracking.


#### Classifier application

The classifier application receives data from KinectV2-OSC. The current release is built as an OSX application to be run on a Mac and receiving the skeleton data from the Windows machine through OSC. If you want to run it on just one laptop, you can build the application for Windows instead and run it on the same computer as the kinect, changing the ip.txt file in KinectV2-OSC (not to be confused with the other ip.txt file in Kinect2Gesture) to send the data to `localhost`.

#### Specify OSC address

After the application is trained (instructions in the next section), predictions are sent over OSC for further processing. Open the file `ip.txt` in Kinect2Gesture's data folder (not to be confused with ip.txt in KinectV2-OSC) and change the ip address to whatever address you like. In most cases this will just be the same computer, so you can make it "localhost" if you wish.  


### Training

#### Creating gesture classes and adding data

Once you are transmitting the skeleton data from the Kinect to Kinect2Gesture, you are ready to begin training it. See the tutorial video for a [demonstration](https://vimeo.com/143963394).

**Please note: the calibration step is no longer necessary, as it is now taken care of automatically when you train. Ignore the calibration toggles in the GUI in the video.**

1) Add a class to the application and name it.

2) Toggle on 'recording'. After a 5-sec countdown, a metronome will begin pulsing at the desired BPM, controllable by the slider. 

Gestures are recorded between the moment the red light goes and on and when it goes off, and the feature vector represents the mean and standard deviations of arm and leg joints, in two time-overlapping halves. Fingers and head position is not included in the features.

You must record at least 10 examples for each class, but the more you record, the more accurate the classifier will be.

3) Repeat #2 for as many classes as you like. Best gesture categories avoid occlusion of Kinect skeleton joints (think front-facing). To avoid confusion between pairs of classes, it's best to select a set of classes which are as mutually dissimilar from each other as possible.


#### Train the SVM

Once you have collected sufficient data, hit the "train" button in the GUI. At this point the app will freeze and begin the process of training a [multi-class SVM](https://en.wikipedia.org/wiki/Support_vector_machine) to discriminate among the classes. This can take anywhere from a few minutes for a small number of classes, to a few hours if you have several dozen classes, so be patient! Unfortunately there's no progress indicator so you just have to let it run until it becomes responsive again.


### Use it!

#### Prediction and sending OSC

Once the app is finished training, you can toggle on "predicting" at which point the app will begin recording gestures again, timed to the metronome as before, except now it will predict which of the previously trained classes each gesture belongs to and output its prediction on the screen.

As it generates predictions, it will output them over OSC. Make sure you've edited ip.txt so that it's sending them to the right place. The class predictions will be sent via port 1357 to the address "/predicting" and it will contain a single integer, corresponding to the class of the predictions (in the order they were added to the classifier).


#### Saving and loading presets

You may save the state of your application at any time, trained or untrained, by clicking "Save preset", and giving it a name. The preset will contain all collected examples, as well as the trained SVM classifier if it has been generated. Thus you can use it to save pre-training in the middle of data collection, or you can save the classifier for future use.

To load a preset, click "load preset" and find the xml file you saved previously. **Note: you must have detected a skeleton first before loading the preset**. Otherwise it has no user to bind the features too. 


