#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    //--------------- kinect ------------
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // enable depth->video image calibration
    kinect.setRegistration(true);
    
    kinect.init();
    //kinect.init(true); // shows infrared instead of RGB video image
    //kinect.init(false, false); // disable video image (faster fps)
    
    kinect.open();		// opens first available kinect
    //kinect.open(1);	// open a kinect by id, starting with 0 (sorted by serial # lexicographically))
    //kinect.open("A00362A08602047A");	// open a kinect using it's unique serial #
    
    // print the intrinsic IR sensor values
    if(kinect.isConnected()) {
        ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
        ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
        ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
        ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
    }
    colorImg.allocate(kinect.width, kinect.height);
    grayImage.allocate(kinect.width, kinect.height);
    grayThreshNear.allocate(kinect.width, kinect.height);
    grayThreshFar.allocate(kinect.width, kinect.height);
    
//    nearThreshold = 230;
//    farThreshold = 132;
    nearThreshold = 255;
    farThreshold = 248;
    bThreshWithOpenCV = true;
    
    ofSetFrameRate(60);
    
    // zero the tilt on startup
    angle = 10;
    kinect.setCameraTiltAngle(angle);
    //--------------- kinect ------------

    
    prevNumBlobs = 0;
    cout << "initial stroke size " << strokes.size() << endl;
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //--------------- kinect ------------
    ofBackground(255, 255, 255);
    
    kinect.update();
    
    // there is a new frame and we are connected
    if(kinect.isFrameNew()) {
        
        // load grayscale depth image from the kinect source
        grayImage.setFromPixels(kinect.getDepthPixels());
        
        // we do two thresholds - one for the far plane and one for the near plane
        // we then do a cvAnd to get the pixels which are a union of the two thresholds
        if(bThreshWithOpenCV) {
            grayThreshNear = grayImage;
            grayThreshFar = grayImage;
            grayThreshNear.threshold(nearThreshold, true);
            grayThreshFar.threshold(farThreshold);
            cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
        }
        
        // update the cv images
        grayImage.flagImageChanged();
        
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // also, find holes is set to true so we will get interior contours as well....
        //contourFinder.findContours(grayImage, 5000, (kinect.width*kinect.height)/3, 20,false);
        contourFinder.findContours(grayImage, 1000, (kinect.width*kinect.height)/3, 20,false);

    }
    //---------------------------
    
    //check when new blobs appear, check when blobs disappear
    //create strokes for every new blob

    ////////////////////////// check if the blob is the same blob /////////////////////////////
//    for(int j=0; contourFinder.blobs.size(); j++){
//        for(int i=0; i< strokes.size(); i++){
//            int lastPoint = strokes[i].lines.size();
//                ofDist(contourFinder.blobs[j].centroid.x, contourFinder.blobs[j].centroid.y, strokes[i].lines[lastPoint].posEnd.x, strokes[i].lines[lastPoint].posEnd.y );//check dist tween each blob and the points on each line of the stroke
//                //take the blob with the
//            
//        }
//    }
    
    
    


    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //--------------- kinect ------------
   

   // grayImage.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
//    contourFinder.draw(10, 320, 400, 300);
  
    
   
    
    //draw the points
    ofPushMatrix();
    ofScale(1.6 , 1.6, 0.0 );
//    ofTranslate( x, y, 0.0 );
    for( int i=0; i<strokes.size(); i++ ) {

        strokes[i].draw();
    }
   
    ofPopMatrix();;
    
    
    stringstream data;
    data << "# blobs: " << contourFinder.nBlobs << " # strokes: " << strokes.size() << endl;
    ofPushStyle();
    ofSetColor(255,0,0);
    ofDrawBitmapString(data.str(), 20, 652);
    ofPopStyle();

    //--------------- kinect ------------
        
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ':
            bThreshWithOpenCV = !bThreshWithOpenCV;
            break;
            
            
        case '>':
        case '.':
            farThreshold ++;
            if (farThreshold > 255) farThreshold = 255;
            break;
            
        case '<':
        case ',':
            farThreshold --;
            if (farThreshold < 0) farThreshold = 0;
            break;
            
        case '+':
        case '=':
            nearThreshold ++;
            if (nearThreshold > 255) nearThreshold = 255;
            break;
            
        case '-':
            nearThreshold --;
            if (nearThreshold < 0) nearThreshold = 0;
            break;
    }
     

    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
        
    
}

//--------------------------------------------------------------
void ofApp::exit() {
    kinect.close();
    
}

