#include "KinectV2Classifier.h"

void KinectV2Classifier::setup(KinectV2 *kinect)
{
    this->kinect = kinect;
    trained = false;
    kinect->setToTrackFirstFoundUser(this, &KinectV2Classifier::receiveFirstUser);
    data.setup(205, 0, 32, 8);
    countdownLength = COUNTDOWN_LENGTH;
    twoPhase = USE_TWO_PHASE;
    countFont.loadFont("verdana.ttf", 156);
    
    osc.setup(7000);
    
    clock.setup(30);
    clock.setupSound("perc2.wav");
    ofAddListener(clock.beatEvent, this, &KinectV2Classifier::beatEvent);
    clock.stop();

    gui.setName("Kinect2Gesture");
    gui.addButton("save preset", this, &KinectV2Classifier::eventSave);
    gui.addButton("load preset", this, &KinectV2Classifier::eventLoad);
    gui.addToggle("calibrating", &calibrating, this, &KinectV2Classifier::eventSetCalibrating);
    gui.addButton("reset calibration", this, &KinectV2Classifier::eventSetResetCalibration);
    gui.addToggle("recording", this, &KinectV2Classifier::eventSetRecording);
    gui.addButton("train", this, &KinectV2Classifier::eventSetTrain);
    gui.addToggle("predicting", this, &KinectV2Classifier::eventSetPredicting);
    gui.addSlider("bpm", new int(30), 0, 200, this, &KinectV2Classifier::eventSetBpm);
    //gui.addToggle("capturing", new bool(false), this, &KinectV2Classifier::eventSetCapturing);
    gui.addButton("add class", this, &KinectV2Classifier::eventAddClass);
    menu = gui.addMenu("training label", this, &KinectV2Classifier::eventSetTrainingLabel);
    setTrainingLabel(1);
}

void KinectV2Classifier::eventAddClass(ofxControlButtonEventArgs & evt)
{
    string newClassName = ofSystemTextBoxDialog("Name of new class");
    addClass(newClassName);
}

void KinectV2Classifier::eventSave(ofxControlButtonEventArgs & evt)
{
    string filename = ofSystemTextBoxDialog("Name of your preset");
    if (filename != "") {
        savePreset(filename+".xml");
    }
}

void KinectV2Classifier::eventLoad(ofxControlButtonEventArgs & evt)
{
    ofFileDialogResult result = ofSystemLoadDialog("Select preset", false, ofToDataPath(""));
    if (result.bSuccess) {
        loadPreset(result.filePath);
    }
}

void KinectV2Classifier::receiveFirstUser(KinectV2TrackedSkeleton* & skeleton)
{
    this->skeleton = skeleton;
    
    vector<string> headers;
    headers.push_back("label");
    
    if (twoPhase) {
        for (auto p : skeleton->getJointsGestural()) {
            headers.push_back("p_"+p.getName()+"_(1)");
            headers.push_back("v_"+p.getName()+"_(1)");
            headers.push_back("p_s_"+p.getName()+"_(1)");
            headers.push_back("v_s_"+p.getName()+"_(1)");
            headers.push_back("p_"+p.getName()+"_(2)");
            headers.push_back("v_"+p.getName()+"_(2)");
            headers.push_back("p_s_"+p.getName()+"_(2)");
            headers.push_back("v_s_"+p.getName()+"_(2)");
        }
    }
    else {
        for (auto p : skeleton->getJointsGestural()) {
            headers.push_back("p_"+p.getName());
            headers.push_back("v_"+p.getName());
            headers.push_back("p_s_"+p.getName());
            headers.push_back("v_s_"+p.getName());
        }
    }
    
    data.setHeaders(headers);
    
    min.resize(headers.size()-1);
    max.resize(headers.size()-1);
    resetMinMaxRange();
}

void KinectV2Classifier::update()
{
    checkOscMessages();
    
    if (toPredict || toRecord) {
        countdown();
    }
    else {
        clock.update();
    }

    if (skeleton != NULL) {
        if (calibrating) {
            calibrate();
        }
        
        if (capturing) {
            captureGesture();
        }
    }
}

void KinectV2Classifier::checkOscMessages()
{
    while (osc.hasWaitingMessages()) {
        ofxOscMessage msg;
        osc.getNextMessage(&msg);
        if (msg.getAddress() == "/metro") {
            msg.getArgAsInt32(0) == 1 ? clock.start() : clock.stop();
        }
        else if (msg.getAddress() == "/metroSpeed") {
            int bpm = 120 * msg.getArgAsFloat(0);
            clock.setBpm(bpm);
        }
        else if (msg.getAddress() == "/calibrating") {
            setCalibrating(msg.getArgAsInt32(0));
        }
        else if (msg.getAddress() == "/recording") {
            //setRecording(msg.getArgAsInt32(0) == 1);
            this->recording = msg.getArgAsInt32(0) == 1;
        }
        else if (msg.getAddress() == "/predicting") {
            setPredicting(msg.getArgAsInt32(0) == 1);
        }
        else {
            for (int i=1; i<9; i++) {
                if (msg.getAddress() == "/trainingLabel/"+ofToString(i)+"/1") {
                    setTrainingLabel(i);
                }
            }
        }
    }
}

void KinectV2Classifier::setCapturing(bool capturing)
{
    if (capturing)
    {
        this->capturing = true;
        beginCaptureGesture();
    }
    else
    {
        this->capturing = false;
        endCaptureGesture();
    }
}

void KinectV2Classifier::setPredicting(bool predicting)
{
    this->predicting = predicting;
    if (predicting) {
        recording = false;
    }
    else {
    
    }
    cout << "set pred " << predicting << endl;

}

void KinectV2Classifier::getStateVector(vector<float> & currentState)
{
    vector<ofParameter<float> > & joints = skeleton->getJointsGestural();
    for (int i = 0; i < joints.size()/3; i++) {
        float px = joints[3*i+0] - skeleton->spineMidX;
        float py = joints[3*i+1] - skeleton->spineMidY;
        float pz = joints[3*i+2] - skeleton->spineMidZ;
        currentState.push_back(px);
        currentState.push_back(py);
        currentState.push_back(pz);
    }
}

void KinectV2Classifier::resetMinMaxRange()
{
    for (int i = 0; i < min.size(); i++) {
        min[i] = +std::numeric_limits<float>::max();
        max[i] = -std::numeric_limits<float>::max();
    }
}

void KinectV2Classifier::setCalibrating(bool calibrating)
{
    this->calibrating = calibrating;
    if (!calibrated && calibrating) {
        resetMinMaxRange();
    }
    calibrated = true;
}

void KinectV2Classifier::calibrate()
{
    vector<float> features;
    if (twoPhase) {
        createFeatureVectorTwoPhase(features);
    }
    else {
        createFeatureVector(features);
    }
    for (int k = 0; k < features.size(); k++) {
        if (features[k] < min[k])   min[k] = features[k];
        if (features[k] > max[k])   max[k] = features[k];
        
        
    }
}

void KinectV2Classifier::beginCaptureGesture()
{
    poses.clear();
}

void KinectV2Classifier::captureGesture()
{
    vector<float> currentState;
    getStateVector(currentState);
    poses.push_back(currentState);
}

void KinectV2Classifier::endCaptureGesture()
{
    cout << "GO!!!" << endl;
    if (poses.size() == 0) return;
    cout << "GO 2!!! "<< predicting <<" " << recording << endl;
    
    vector<float> features;
    if (twoPhase) {
        createFeatureVectorTwoPhase(features);
    }
    else {
        createFeatureVector(features);
    }
    
    if (recording)
    {
        vector<float> entry;
        entry.push_back(trainingLabel);
        for (int i = 0; i < features.size(); i++) {
            entry.push_back(features[i]);
        }
        data.addEntry(entry);
    }
    else if (predicting)
    {
        cout << "is pred " << endl;
        vector<double> featureVector;
        for (int i = 0; i < features.size(); i++) {
            float featureValue = (double)(features[i] - min[i]) / (max[i] - min[i]);
            featureVector.push_back(featureValue);
        }
        int predictedLabel = svm.predict(featureVector);
        predictLabel(predictedLabel);
    }
}

void KinectV2Classifier::predictLabel(int predictedLabel)
{
    cout << "LABEL !" <<endl;
    ofNotifyEvent(predictionE, predictedLabel, this);
}

void KinectV2Classifier::setTrainingLabel(int trainingLabel)
{
    this->trainingLabel = trainingLabel;
}

void KinectV2Classifier::train()
{
    vector<vector<float> > entries = data.getEntries();
    for (int i = 0; i < entries.size(); i++) {
        int label = entries[i][0];
        vector<double> featureVector;
        for (int f = 1; f < entries[i].size(); f++) {
            float featureValue = (double)(entries[i][f] - min[f-1]) / (max[f-1] - min[f-1]);
            featureVector.push_back(featureValue);
        }
        svm.addTrainingInstance(featureVector, label);
    }
    
    svm.train();
//    svm.trainWithGridParameterSearch();
    trained = true;
    ofLog(OF_LOG_NOTICE, "Finished training");
}

void KinectV2Classifier::savePreset(string filename) {
    ofXml xml;
    setLearnXml(xml);
    xml.save(filename);
}

void KinectV2Classifier::loadPreset(string filename) {
    ofXml xml;
    xml.load(filename);
    setFromLearnXml(xml);
    xml.setToParent();
}

void KinectV2Classifier::draw()
{
    data.draw();
    gui.draw();
}

void KinectV2Classifier::drawCounter()
{
    if (toPredict || toRecord) {
        ofSetColor(0, 190);
        ofRect(ofGetWidth()/2 - 200, ofGetHeight()/2 - 200, 400, 200);
        ofSetColor(255, 190);
        countFont.drawString(ofToString(countdownLength-count, 1), ofGetWidth()/2 - 185, ofGetHeight()/2 - 15);
        ofSetColor(255);
    }
}

void KinectV2Classifier::addClass(string name) {
    menu->addToggle(name);
    classes.push_back(name);
}

void KinectV2Classifier::startCountdown() {
    countStart = ofGetElapsedTimef();
}

void KinectV2Classifier::countdown() {
    count = ofGetElapsedTimef() - countStart;
    if (count > countdownLength) {
        if (toRecord) {
            recording = true;
            predicting = false;
        }
        else if (toPredict) {
            predicting = true;
            recording = false;
        }
        toRecord = false;
        toPredict = false;
        clock.start();
    }
}

void KinectV2Classifier::eventSetRecording(ofxControlButtonEventArgs & evt)
{
    if (evt.value) {
        toRecord = true;
        toPredict = false;
        capturing = false;
        clock.stop();
        startCountdown();
    }
    else if (!evt.value && !predicting) {
        clock.stop();
    }
}

void KinectV2Classifier::eventSetPredicting(ofxControlButtonEventArgs & evt) {
    if (evt.value) {
        toRecord = false;
        toPredict = true;
        capturing = false;
        clock.stop();
        startCountdown();
    }
    else if (!evt.value && !recording) {
        clock.stop();
    }
}

void KinectV2Classifier::setLearnXml(ofXml &xml)
{
    // first save the classifier
    if (trained) {
        svm.saveModel(ofToDataPath("svmModel.dat"));
    }
    
    // event-parameter mappings
    xml.addChild("LearnInfo");
    xml.setTo("LearnInfo");
    
    // classes
    xml.addChild("Classes");
    xml.setTo("Classes");
    for (int i=0; i<classes.size(); i++) {
        ofXml xml_;
        xml_.addChild("Class");
        xml_.setTo("Class");
        xml_.addValue("Name", classes[i]);
        xml.addXml(xml_);
    }
    xml.setToParent();
    
    // ranges
    xml.addChild("Ranges");
    xml.setTo("Ranges");
    for (int i=0; i<min.size(); i++) {
        ofXml xml_;
        xml_.addChild("Joint");
        xml_.setTo("Joint");
        xml_.addValue("Min", min[i]);
        xml_.addValue("Max", max[i]);
        xml.addXml(xml_);
    }
    xml.setToParent();
    
    vector<vector<float> > & entries = data.getEntries();
    if (entries.size() > 0) {
        xml.addChild("Training");
        xml.setTo("Training");
        for (int i = 0; i < entries.size(); i++) {
            vector<string> featureStringV;
            for (int f=1; f<entries[i].size(); f++) {
                featureStringV.push_back(ofToString(entries[i][f]));
            }
            string featureString = ofJoinString(featureStringV, ",");
            double label = entries[i][0];
            ofXml xml_;
            xml_.addChild("Entry");
            xml_.setTo("Entry");
            xml_.addValue("Label", label);
            xml_.addValue("Features", featureString);
            xml.addXml(xml_);
        }
        xml.setToParent();
    }
    
    if (trained) {
        xml.addChild("Model");
        xml.setTo("Model");
        xml.addValue("Path", ofToDataPath("svmModel.dat"));
        xml.setToParent();
    }
    
    xml.setToParent();
}

void KinectV2Classifier::setFromLearnXml(ofXml &xml)
{
    xml.setTo("LearnInfo");
    
    if (xml.exists("Classes")) {
        xml.setTo("Classes");
        if (xml.exists("Class[0]"))
        {
            xml.setTo("Class[0]");
            do {
                addClass(xml.getValue<string>("Name"));
            }
            while(xml.setToSibling());
            xml.setToParent();
        }
        xml.setToParent();
    }
    
    if (xml.exists("Ranges")) {
        xml.setTo("Ranges");
        if (xml.exists("Joint[0]"))
        {
            int idx = 0;
            xml.setTo("Joint[0]");
            do {
                min[idx] = xml.getValue<float>("Min");
                max[idx] = xml.getValue<float>("Max");
                idx++;
            }
            while(xml.setToSibling());
            xml.setToParent();
        }
        xml.setToParent();
    }
    
    if (xml.exists("Training")) {
        xml.setTo("Training");
        if (xml.exists("Entry[0]"))
        {
            xml.setTo("Entry[0]");
            do {
                double label = xml.getValue<double>("Label");
                vector<string> featureVectorS = ofSplitString(xml.getValue<string>("Features"), ",");
                vector<float> entry;
                entry.push_back(label);
                for (auto f : featureVectorS) {
                    entry.push_back(ofToFloat(f));
                }
                data.addEntry(entry);
            }
            while(xml.setToSibling());
            xml.setToParent();
        }
        xml.setToParent();
    }
    
    if (xml.exists("Model")) {
        xml.setTo("Model");
        string path = xml.getValue<string>("Path");
        svm.loadModel(path);
        trained = true;
        xml.setToParent();
    }
    xml.setToParent();
}

void KinectV2Classifier::createFeatureVector(vector<float> & features)
{
    vector<float> meanPosition, meanVelocity, stdPosition, stdVelocity;
    meanPosition.resize(poses[0].size());
    meanVelocity.resize(poses[0].size());
    stdPosition.resize(poses[0].size());
    stdVelocity.resize(poses[0].size());
    
    // calculate mean position and mean velocity
    for (int k = 0; k < poses.size(); k++) {
        for (int i = 0; i < poses[k].size(); i++) {
            meanPosition[i] += (1.0f / poses.size()) * poses[k][i];
            if (k > 0) {
                meanVelocity[i] += (1.0f / (poses.size()-1)) * (poses[k][i] - poses[k-1][i]);
            }
        }
    }
    
    // calculate std position + std velocity
    for (int k = 0; k < poses.size(); k++) {
        for (int i = 0; i < poses[k].size(); i++) {
            stdPosition[i] += pow(poses[k][i] - meanPosition[i], 2.0f);
            if (k > 0) {
                stdVelocity[i] += pow((poses[k][i] - poses[k-1][i]) - meanVelocity[i], 2.0f);
            }
        }
    }
    
    for (int i = 0; i < stdPosition.size(); i++) {
        stdPosition[i] = (1.0f / poses[0].size()) * sqrt(stdPosition[i]);
        stdVelocity[i] = (1.0f / (poses[0].size() - 1)) * sqrt(stdVelocity[i]);
    }
    
    for (int i = 0; i < meanPosition.size(); i++) {
        features.push_back(meanPosition[i]);
        features.push_back(meanVelocity[i]);
        features.push_back(stdPosition[i]);
        features.push_back(stdVelocity[i]);
    }
}

void KinectV2Classifier::createFeatureVectorTwoPhase(vector<float> & features)
{
    vector<float> meanPosition1, meanVelocity1, stdPosition1, stdVelocity1;
    vector<float> meanPosition2, meanVelocity2, stdPosition2, stdVelocity2;
    
    meanPosition1.resize(poses[0].size());
    meanVelocity1.resize(poses[0].size());
    stdPosition1.resize(poses[0].size());
    stdVelocity1.resize(poses[0].size());
    
    meanPosition2.resize(poses[0].size());
    meanVelocity2.resize(poses[0].size());
    stdPosition2.resize(poses[0].size());
    stdVelocity2.resize(poses[0].size());
    
    int range11 = floor(poses.size() * 0.1);
    int range12 = floor(poses.size() * 0.6);
    int range21 = floor(poses.size() * 0.4);
    int range22 = floor(poses.size() * 0.9);
    
    
    // calculate mean position and mean velocity
    for (int k = range11; k < range12; k++) {
        for (int i = 0; i < poses[k].size(); i++) {
            meanPosition1[i] += (1.0f / (range12 - range11)) * poses[k][i];
            if (k > 0) {
                meanVelocity1[i] += (1.0f / (range12 - range11 - 1)) * (poses[k][i] - poses[k-1][i]);
            }
        }
    }
    
    // calculate std position + std velocity
    for (int k = range11; k < range12; k++) {
        for (int i = 0; i < poses[k].size(); i++) {
            stdPosition1[i] += pow(poses[k][i] - meanPosition1[i], 2.0f);
            if (k > 0) {
                stdVelocity1[i] += pow((poses[k][i] - poses[k-1][i]) - meanVelocity1[i], 2.0f);
            }
        }
    }
    
    for (int i = 0; i < stdPosition1.size(); i++) {
        stdPosition1[i] = (1.0f / poses[0].size()) * sqrt(stdPosition1[i]);
        stdVelocity1[i] = (1.0f / (poses[0].size() - 1)) * sqrt(stdVelocity1[i]);
    }
    
    
    /////////////////////
    // second phase
    
    // calculate mean position and mean velocity
    for (int k = range21; k < range22; k++) {
        for (int i = 0; i < poses[k].size(); i++) {
            meanPosition2[i] += (1.0f / (range22 - range21)) * poses[k][i];
            if (k > 0) {
                meanVelocity2[i] += (1.0f / (range22 - range21 - 1)) * (poses[k][i] - poses[k-1][i]);
            }
        }
    }
    
    // calculate std position + std velocity
    for (int k = range21; k < range22; k++) {
        for (int i = 0; i < poses[k].size(); i++) {
            stdPosition2[i] += pow(poses[k][i] - meanPosition2[i], 2.0f);
            if (k > 0) {
                stdVelocity2[i] += pow((poses[k][i] - poses[k-1][i]) - meanVelocity2[i], 2.0f);
            }
        }
    }
    
    for (int i = 0; i < stdPosition2.size(); i++) {
        stdPosition2[i] = (1.0f / poses[0].size()) * sqrt(stdPosition2[i]);
        stdVelocity2[i] = (1.0f / (poses[0].size() - 1)) * sqrt(stdVelocity2[i]);
    }
    
    
    
    for (int i = 0; i < meanPosition1.size(); i++) {
        features.push_back(meanPosition1[i]);
        features.push_back(meanVelocity1[i]);
        features.push_back(stdPosition1[i]);
        features.push_back(stdVelocity1[i]);
    }
    for (int i = 0; i < meanPosition2.size(); i++) {
        features.push_back(meanPosition2[i]);
        features.push_back(meanVelocity2[i]);
        features.push_back(stdPosition2[i]);
        features.push_back(stdVelocity2[i]);
    }
}
