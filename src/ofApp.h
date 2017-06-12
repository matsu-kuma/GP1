#pragma once

#include "ofMain.h"
#include "ofEvents.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void rhythmArduino();
        void aflagArduino();
        void buttonArduino();
        void clickArduino();
    
    int aflag;
    int flag[9] = {0,0,0,0,0,0,0,0,0};
    int flag2[8] = {0,0,0,0,0,0,0,0};
    int flag3[8] = {0,0,0,0,0,0,0,0};
    int inputPin[8] = {0,1};
    int inputPinA = 16;
    int outputPin[12] = {13,2,3,4,5,6,7,8,9,11,10,12};
    
    int repair[8] = {0};
    int repair2[8] = {0};
    int repair3[8] = {0};

    
    //------------------------circle pos--------------------------
    ofPoint pos1;
    ofPoint pos2;
    ofPoint pos3;
    ofPoint pos4;

    //-----------------------time(frame)--------------------------
    float frame;
    float FR;  //Frame Rate
    
    //-----------------------Draw Circle Config--------------------------
    int n;// the number of circle
    float Fn;
    
    //-----------------------sound--------------------------
    ofSoundPlayer  kick;
    ofSoundPlayer  snare;
    ofSoundPlayer  hihat;
    ofSoundPlayer  crash;
    ofTrueTypeFont	font;
    float 			synthPosition;
    //double t;
    bool bKick;
    bool bSnare;
    bool bHiHat;
    bool bCrash;
    ofImage				bgImage;
    ofTrueTypeFont      smallFont;
    ofArduino	ard;
    bool		bSetupArduino;

    
private:
    
    void setupArduino(const int & version);
    void digitalPinChanged(const int & pinNum);
    void analogPinChanged(const int & pinNum);
    void updateArduino();
    
    string buttonState;
    string potValue;

		
};


