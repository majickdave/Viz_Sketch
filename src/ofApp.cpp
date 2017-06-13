#include "ofApp.h"

// called automatically when instance goes
// out of scope
//ofApp::~ofApp(){
//   // delete p_ptr1;
//}

//--------------------------------------------------------------
void ofApp::setup(){
    // if you don't see a delete for this,
    // you definitely have a leak
    ofBackground(0,0,0);
    ofSetColor(255,255, 255, 255);
    // what is being called in the following statements?
    //p1 = MyPoly(100, 6); // assignment operator called
    
    ofDisableArbTex();
    texture.load("of.png");
    texture.getTexture().setTextureWrap( GL_REPEAT, GL_REPEAT );
    vidGrabber.setup(640, 480, true);
//    vidGrabber.draw(0,0);
    bMousePressed   = false;
    bTransit = false;
    mode = 0;
    
    zoom = 1;
    
    
    //    MyPoly p2(p1); // copy constructor called
    //
    //    MyPoly p3 = p2; // copy constructor called
    camWidth 		= 640;	// try to grab at this size.
    camHeight 		= 480;
    
    vidGrabber.setVerbose(true);
    vidGrabber.setup(camWidth,camHeight);
    
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    
    for(int i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }
    
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.initGrabber(camWidth, camHeight);
    
    // exverted
    videoExverted.allocate(camWidth, camHeight, OF_PIXELS_RGB);
    videoTexture2.allocate(videoExverted);
    
    videoExverted2.allocate(camWidth, camHeight, OF_PIXELS_RGB);
    videoTexture3.allocate(videoExverted2);
    
    videoInverted.allocate(camWidth, camHeight, OF_PIXELS_RGB);
    videoTexture.allocate(videoInverted);

    ofSetVerticalSync(false);
    
    sphere.setRadius( ofGetWidth()/9 );
    sphere2.setRadius( ofGetWidth()/6 );
    sphere3.setRadius( ofGetWidth()/3 );
    sphere4.setRadius( ofGetWidth()/4 );
    
    cone.set(0, 0);
    box.set( ofGetWidth()/3 );
    plane.set( ofGetWidth()/6, ofGetHeight()/6 );
    
    cylinder.set(ofGetWidth()/6, ofGetHeight()/2);
    
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    
    pointLight2.setDiffuseColor( ofFloatColor( 212.f/255.f, 63.f/255.f, 135.f/255.f ));
    pointLight2.setSpecularColor(ofFloatColor(.5f, .8f, .2f));
    
    pointLight3.setDiffuseColor( ofFloatColor(85.f/255.f,94.f/255.f,77.f/255.f) );
    pointLight3.setSpecularColor( ofFloatColor(18.f/255.f,111.f/255.f,135.f/255.f) );
    ofSetSphereResolution(24);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    
    pointLight.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight()/2, 500);
    pointLight2.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.15)*(ofGetWidth()*.3),
                            ofGetHeight()*.5 + sin(ofGetElapsedTimef()*.7)*(ofGetHeight()), -300);
    
    pointLight3.setPosition(
                            cos(ofGetElapsedTimef()*1.5) * ofGetWidth()*.5,
                            sin(ofGetElapsedTimef()*1.5f) * ofGetWidth()*.5,
                            cos(ofGetElapsedTimef()*.2) * ofGetWidth()
                            );
    
    

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    // do drawing
    
    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);
    float spinZ = sin(ofGetElapsedTimef()*.075f);
    
    if(bMousePressed) {
        spinX = spinY = 5.0f; spinZ = 0.0f;
    }

    ofEnableLighting();
    pointLight.enable();
    pointLight2.enable();
    pointLight3.enable();
    

    
//    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
//    ofRotate(ofGetFrameNum());
//    p1.draw();
    //ofScale(100, 100);
//    ofTranslate(mouseX, mouseY);
//    p1.draw();
    
    plane.setPosition(ofGetWidth()*.2, ofGetHeight()*.25, 0);
    plane.rotate(spinX, 1.0, 0.0, 0.0);
    plane.rotate(spinY, 0, 1.0, 0.0);
    
    cone.rotate(spinX, 0.0, 0.0, 0.0);
    cone.rotate(spinY, 0, 1.0, 0.0);
    
    box.rotate(spinX, 1.0, 0.0, 0.0);
    box.rotate(spinY, 0, 1.0, 0.0);
    
    cylinder.setPosition(ofGetWidth()*.75, ofGetHeight()*.85, 0);
    cylinder.rotate(spinX, 1.0, 0.0, 0.0);
    cylinder.rotate(spinY, 0, 1.0, 0.0);

//    sphere.setPosition(ofGetWidth()*.5, ofGetHeight()*.5, 1);
    sphere.rotate(spinX, 1.0, 0.0, 0.0);
    sphere.rotate(spinY, 0, 1.0, 0.0);
//    sphere.rotate(spinZ, 0, 0, 1.0);
    

    sphere.setPosition(mouseX, mouseY, 0);
    box.setPosition(mouseX-500, mouseY, 0);
    
    if(bMousePressed) {
       if(vidGrabber.isFrameNew()){
        ofPixels & pixels = vidGrabber.getPixels();
        for(int i = 0; i < pixels.size(); i++){
            videoInverted[i] = 255*cos(ofGetFrameNum()/(100*PI)) + pixels[i];
            videoExverted[i] = 255*sin(ofGetFrameNum()/(10*PI)) - pixels[i];
            videoExverted2[i] = 255*sin(ofGetFrameNum()/(100*PI)) + pixels[i];
            }
            videoTexture.loadData(videoInverted);
            videoTexture2.loadData(videoExverted);
            videoTexture3.loadData(videoExverted2);
        }
        int posx = mouseX;
        int posy = mouseY;
        
        
//        sphere.setPosition(ofGetWidth()/2, ofGetHeight()/4, 0);
//        box.setPosition(ofGetWidth()/2, 3*ofGetHeight()/4, 0);
        
        sphere.setPosition(mouseX, mouseY, 0);
        sphere2.setPosition(mouseX-camWidth, mouseY, 0);
        sphere3.setPosition(mouseX-2*camWidth, mouseY, 0);
        sphere4.setPosition(mouseX-3*camWidth, mouseY, 0);
        box.setPosition(mouseX+300, mouseY, 0);

        cone.setPosition(mouseX, mouseY+300, 0);
        plane.setPosition(mouseX, mouseY+300, 0);
        cylinder.setPosition(mouseX, mouseY+600, 0);
//        cone.draw();
//        
////        plane.setPosition(ofGetWidth()*.33, ofGetHeight()*.75, 0);
////        plane.draw();
//        box.draw();
        

        
        videoTexture.draw(camWidth, 0, camWidth*zoom, camHeight*zoom);
        videoTexture2.draw(0, camHeight, camWidth*zoom, camHeight*zoom);
        videoTexture3.draw(camWidth, camHeight, camWidth, camHeight);
        vidGrabber.draw(0, 0, camWidth*zoom, camHeight*zoom);

//        videoTexture.draw(0,0, camWidth/2, camHeight/2);
//        videoTexture.draw(ofGetWidth()-camWidth, 0, camWidth/2, camHeight/2);
//        videoTexture.draw(0, ofGetHeight()-camHeight, camWidth/2, camHeight/2);
//        videoTexture.draw(ofGetWidth()-camWidth, ofGetHeight()-camHeight, camWidth/2, camHeight/2);
        
//        videoTexture.draw(posx, posy, camWidth*zoom, camHeight*zoom);
  
        
//        sphere.setRadius( ofGetWidth()/8 );
        
        
    }
    
    vidGrabber.getTexture().bind();
    videoTexture.bind();
    videoTexture2.bind();
    videoTexture3.bind();
    
    //vidGrabber.draw(ofGetWidth()-camWidth,ofGetHeight()-camHeight);

    ofPixelsRef pixelsRef = vidGrabber.getPixels();
    sphere.mapTexCoordsFromTexture( videoTexture3 );sphere.draw();
//    sphere2.mapTexCoordsFromTexture( videoTexture3 );sphere2.draw();
//    sphere3.mapTexCoordsFromTexture( videoTexture3 );sphere3.draw();
//    sphere4.mapTexCoordsFromTexture( vidGrabber.getTexture() );sphere4.draw();
    cylinder.mapTexCoordsFromTexture( vidGrabber.getTexture() );cylinder.draw();
    box.mapTexCoordsFromTexture( vidGrabber.getTexture() );box.draw();
    
    cone.mapTexCoordsFromTexture( vidGrabber.getTexture() );cone.draw();
    plane.mapTexCoordsFromTexture( vidGrabber.getTexture() );plane.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    key = 1;
    bMousePressed = true;
    
    key = 2;
    if (zoom<5){
    zoom += 1;
    } else{
        zoom = 1;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    


    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    sphere.setRadius(ofGetWidth() * mouseX/ofGetWidth());
    box.set(ofGetHeight() * mouseY/ofGetHeight());
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    bMousePressed = true;

    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    bMousePressed = false;
    
    sphere.setRadius(ofGetWidth()/16);
    box.set(ofGetWidth()/16);
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
