#pragma once

#include "ofMain.h"
#include "MyPoly.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{
    
public:
    
    //~ofApp();
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    int mode;
    ofImage texture;
    // camera grabber
    ofVideoGrabber 		vidGrabber;
    int 				camWidth;
    int 				camHeight;
    
    ofAVFoundationPlayer Oav;
    
    ofPixels videoExverted;
    ofTexture videoTexture2;
    
    ofPixels videoExverted2;
    ofTexture videoTexture3;
    
    ofPixels videoInverted;
    ofTexture videoTexture;
    
    // declaring an object
    // invoking the default cstr
    // in C++ declaring an object is
    // instantiation
    MyPoly p1;
    // cstr is not called for pointer declaration
    //MyPoly* p_ptr1;
    
    
    ofIcoSpherePrimitive icoSphere;
    ofPlanePrimitive plane;
    ofCylinderPrimitive cylinder;
    ofConePrimitive cone;
    ofBoxPrimitive box;
    ofLight pointLight;
    ofLight pointLight2;
    ofLight pointLight3;
    
    ofSpherePrimitive sphere;
    ofSpherePrimitive sphere2;
    ofSpherePrimitive sphere3;
    ofSpherePrimitive sphere4;
    
    bool bMousePressed;
    bool bTransit;
    
    int zoom;
    
    
};









