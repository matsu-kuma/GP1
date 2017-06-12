#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    aflag = 0;
    FR = 60.0;
    
    
    //----------------------Draw Circle Config---------------------------------------
    
    n = 8;// the number of circle
    
    Fn = (float)FR / n;
    
    //-------------------display config------------------------
    ofSetVerticalSync(true);
    ofSetFrameRate(FR);
    //ofSetBackgroundAuto(false);
    ofBackground(255,255,255);
    
        pos1.x = 50;   // radius of Main circle
        pos1.y = 0;
        
        pos2.x = 100;
        pos2.y = 0;
        
        pos3.x = 200;
        pos3.y= 0;
    
        pos4.x = 300;
        pos4.y = 0;
        
    //--------------------circle config-------------------------
        
        frame = 0;
    
    //---------------------serial start------------------------
    
    //    serial.setup("/dev/cu.usbmodem1411",57600);
    
    //-------------------sound player---------------------
   // ofSoundStreamSetup(4, 0, 44100, , <#int nBuffers#>)
    
    kick.load("sounds/Kick.wav");
    snare.load("sounds/Snare.wav");
    hihat.load("sounds/HiHat.wav");
    crash.load("sounds/Crash.wav");
    kick.setVolume(1.00f);
    snare.setVolume(0.75f);
    hihat.setVolume(0.75f);
    crash.setVolume(0.75f);
    font.load("Sudbury_Basin_3D.ttf", 32);
    //beats.setMultiPlay(false);
    //vocals.setMultiPlay(true);
    
    //-------------------arduino settings---------------------
    buttonState = "digital pin:";
    potValue = "analog pin:";
    
    bgImage.load("background.png");
    font.load("franklinGothic.otf", 20);
    smallFont.load("franklinGothic.otf", 14);
    
    // replace the string below with the serial port for your Arduino board
    // you can get this from the Arduino application or via command line
    // for OSX, in your terminal type "ls /dev/tty.*" to get a list of serial devices
    ard.connect("/dev/cu.usbmodem1461", 57600);
    
    // listen for EInitialized notification. this indicates that
    // the arduino is ready to receive commands and it is safe to
    // call setupArduino()
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)


    
}
//--------------------------------------------------------------

void ofApp::setupArduino(const int & version) {
    
    // remove listener because we don't need it anymore
    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    // Note: pins A0 - A5 can be used as digital input and output.
    // Refer to them as pins 14 - 19 if using StandardFirmata from Arduino 1.0.
    // If using Arduino 0022 or older, then use 16 - 21.
    // Firmata pin numbering changed in version 2.3 (which is included in Arduino 1.0)
    
    // set pins A0 to A2 to input
    ard.sendAnalogPinReporting(inputPin[0], ARD_ANALOG);
    ard.sendAnalogPinReporting(inputPin[1], ARD_ANALOG);
    //ard.sendDigitalPinMode(inputPinA, ARD_INPUT);
    
    // set pin D1 toD12 as digital output
    for(int i=0; i<12; i++){
        ard.sendDigitalPinMode(inputPin[i], ARD_OUTPUT); //ÊåáÂÆö„Åó„Åü„Éá„Ç∏„Çø„É´„Éî„É≥„ÇíÊúâÂäπÂåñ
    }
    ard.sendDigitalPinMode(inputPinA, ARD_INPUT);
    
    // Listen for changes on the digital and analog pins
    ofAddListener(ard.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
    ofAddListener(ard.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

//--------------------------------Arduino------------------------------

void ofApp::updateArduino(){
    
    // update the arduino, get any data or messages.
    // the call to ard.update() is required
    ard.update();
    
}

// digital pin event handler, called whenever a digital pin value has changed
// note: if an analog pin has been set as a digital pin, it will be handled
// by the digitalPinChanged function rather than the analogPinChanged function.

//--------------------------------------------------------------
void ofApp::digitalPinChanged(const int & pinNum) {
    // do something with the digital input. here we're simply going to print the pin number and
    // value to the screen each time it changes
    buttonState = "digital pin: " + ofToString(pinNum) + " = " + ofToString(ard.getDigital(pinNum));
}

// analog pin event handler, called whenever an analog pin value has changed

//--------------------------------------------------------------
void ofApp::analogPinChanged(const int & pinNum) {
    // do something with the analog input. here we're simply going to print the pin number and
    // value to the screen each time it changes
    potValue = "analog pin: " + ofToString(pinNum) + " = " + ofToString(ard.getAnalog(pinNum));
}


void ofApp::update(){
    
    if(frame >= FR){
        frame = 0;
    }
    
    frame += 1;
    
    updateArduino();
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    
    //------------------------print FR--------------------------------
    string FRMsg = "FrameRate: " + ofToString((float)FR);
    ofDrawBitmapString(FRMsg, 10, 10);
    
    //------------------------------------------------------------------------------
      for(int j = 0;j < n;j++){
          
          //-----------------------Draw Main Circle  -------------------------------------------
          float Fn = (float)FR / n;
          
          if(Fn * j <= frame && frame < Fn * (j + 1)){//-------change color(blue)------
              
              ofPushMatrix();
              ofSetColor(0,127,255);
              ofFill();
              ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
              ofRotate(j * 360 / n - 90);
              ofDrawCircle(pos1.x,pos1.y,15.0);
              ofPopMatrix();
              
              //------------sound kick--------------
              
              if(flag[j] == 1){
                  
                  kick.play();
                  
                  flag[j] = 0;
                  
                  repair[j] = 1;
              }
              //------------------------------------
              
              //------------sound snare-----------
              
              if(flag2[j] == 1){
                  
                  snare.play();
                  
                  flag2[j] = 0;
                  
                  repair2[j] = 1;
                  
              }
              //-------------------------------------
              
              //------------sound highhat-----------
              
              if(flag3[j] == 1){
                  
                  hihat.play();
                  
                  flag3[j] = 0;
                  
                  repair3[j] = 1;
                  
              }
              //-------------------------------------
              
              
              if(j != 0 && repair[j - 1] == 1){
                  
                  flag[j - 1] = 1;
                  repair[j - 1] = 0;
                  
              }else if(j == 0 && repair[7] == 1){
                  
                  flag[7] = 1;
                  repair[7] = 0;
                  
              }
              
              
              if(j != 0 && repair2[j - 1] == 1){
                  
                  flag2[j - 1] = 1;
                  repair2[j - 1] = 0;
                  
              }else if(j == 0 && repair2[7] == 1){
                  
                  flag2[7] = 1;
                  repair2[7] = 0;
                  
              }
              
              
              if(j != 0 && repair3[j - 1] == 1){
                  
                  flag3[j - 1] = 1;
                  repair3[j - 1] = 0;
                  
              }else if(j == 0 && repair3[7] == 1){
                  
                  flag3[7] = 1;
                  repair3[7] = 0;
                  
              }
              
          }
          
          else {//------------change color(red)-----------------
              ofPushMatrix();
              ofSetColor(125,125,125);
              ofFill();
              ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
              ofRotate(j * 360 / n - 90);
              ofDrawCircle(pos1.x,pos1.y,15.0);
              ofPopMatrix();
          }
    //-----------------------Draw Circle 1
        
       if(flag[(j)] == 1){//----------red--------------
           ofPushMatrix();
            ofSetColor(255,0,0);
            ofFill();
            ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
            ofRotate(j * 360 / n - 90);
            ofDrawCircle(pos2.x,pos2.y,20.0);
            ofPopMatrix();
        }
        
       else {//--------------gray-------------
            ofPushMatrix();
            ofSetColor(125,125,125);
            ofFill();
            ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
            ofRotate(j * 360 / n - 90);
            ofDrawCircle(pos2.x,pos2.y,20.0);
            ofPopMatrix();
        }
    //-----------------------Draw Circle 2
    
        if(flag2[j] == 1){//----------red--------------
            ofPushMatrix();
            ofSetColor(255,0,0);
            ofFill();
            ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
            ofRotate(j * 360 / n - 90);
            ofDrawCircle(pos3.x,pos3.y,25.0);
            ofPopMatrix();
        }
        
        else {//--------------gray--------------
            ofPushMatrix();
            ofSetColor(125,125,125);
            ofFill();
            ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
            ofRotate(j * 360 / n - 90);
            ofDrawCircle(pos3.x,pos3.y,25.0);
            ofPopMatrix();
        }
          
    //-----------------------Draw Circle 3
          
          
          if(flag3[j] == 1){//----------red--------------
              ofPushMatrix();
              ofSetColor(255,0,0);
              ofFill();
              ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
              ofRotate(j * 360 / n - 90);
              ofDrawCircle(pos4.x,pos4.y,30.0);
              ofPopMatrix();
          }
          
          else {//--------------gray--------------
              ofPushMatrix();
              ofSetColor(125,125,125);
              ofFill();
              ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
              ofRotate(j * 360 / n - 90);
              ofDrawCircle(pos4.x,pos4.y,30.0);
              ofPopMatrix();
          }
    }
    
    clickArduino();
    aflagArduino();
    rhythmArduino();
    buttonArduino();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == '0'){
        if(aflag <2){
            aflag += 1;
        }
        
        else if(aflag == 2){
            aflag = 0;
        }
    }
    
    //------------------- circle 2--------------------------------
    
    if(aflag == 0){
    
    if(key == '1'){
        if(flag[0] == 0){
        flag[0] = 1;
        }
        
       else if(flag[0] == 1){
            flag[0] = 0;
        }
    }
    
    if(key == '2'){
        if(flag[1] == 0){
            flag[1] = 1;
        }
        
        else if(flag[1] == 1){
            flag[1] = 0;
        }
    }
    if(key == '3'){
        if(flag[2] == 0){
            flag[2] = 1;
        }
        
        else if(flag[2] == 1){
            flag[2] = 0;
        }
    }
    
    if(key == '4'){
        if(flag[3] == 0){
            flag[3] = 1;
        }
        
        else if(flag[3] == 1){
            flag[3] = 0;
        }
    }
    if(key == '5'){
        if(flag[4] == 0){
            flag[4] = 1;
        }
        
        else if(flag[4] == 1){
            flag[4] = 0;
        }
    }
    
    if(key == '6'){
        if(flag[5] == 0){
            flag[5] = 1;
        }
        
        else if(flag[5] == 1){
            flag[5] = 0;
        }
    }
    if(key == '7'){
        if(flag[6] == 0){
            flag[6] = 1;
        }
        
        else if(flag[6] == 1){
            flag[6] = 0;
        }
    }
    
    if(key == '8'){
        if(flag[7] == 0){
            flag[7] = 1;
        }
        
        else if(flag[7] == 1){
            flag[7] = 0;
        }
    }
    }
    //--------------------------------------------------------------
    
    //----------circle 3---------------------------------

    if(aflag == 1){
        
        if(key == '1'){
            if(flag2[0] == 0){
                flag2[0] = 1;
            }
            
            else if(flag2[0] == 1){
                flag2[0] = 0;
            }
        }
        
        if(key == '2'){
            if(flag2[1] == 0){
                flag2[1] = 1;
            }
            
            else if(flag2[1] == 1){
                flag2[1] = 0;
            }
        }
        
        if(key == '3'){
            if(flag2[2] == 0){
                flag2[2] = 1;
            }
            
            else if(flag2[2] == 1){
                flag2[2] = 0;
            }
        }
        if(key == '4'){
            if(flag2[3] == 0){
                flag2[3] = 1;
            }
            
            else if(flag2[3] == 1){
                flag2[3] = 0;
            }
        }
        
        if(key == '5'){
            if(flag2[4] == 0){
                flag2[4] = 1;
            }
            
            else if(flag2[4] == 1){
                flag2[4] = 0;
            }
        }
        if(key == '6'){
            if(flag2[5] == 0){
                flag2[5] = 1;
            }
            
            else if(flag2[5] == 1){
                flag2[5] = 0;
            }
        }
        
        if(key == '7'){
            if(flag2[6] == 0){
                flag2[6] = 1;
            }
            
            else if(flag2[6] == 1){
                flag2[6] = 0;
            }
        }
        if(key == '8'){
            if(flag2[7] == 0){
                flag2[7] = 1;
            }
            
            else if(flag2[7] == 1){
                flag2[7] = 0;
            }
        }
        
    
        
    }
    
    //----------circle 4---------------------------------
    
    if(aflag == 2){
        
        if(key == '1'){
            if(flag3[0] == 0){
                flag3[0] = 1;
            }
            
            else if(flag3[0] == 1){
                flag3[0] = 0;
            }
        }
        
        if(key == '2'){
            if(flag3[1] == 0){
                flag3[1] = 1;
            }
            
            else if(flag3[1] == 1){
                flag3[1] = 0;
            }
        }
        
        if(key == '3'){
            if(flag3[2] == 0){
                flag3[2] = 1;
            }
            
            else if(flag3[2] == 1){
                flag3[2] = 0;
            }
        }
        if(key == '4'){
            if(flag3[3] == 0){
                flag3[3] = 1;
            }
            
            else if(flag3[3] == 1){
                flag3[3] = 0;
            }
        }
        
        if(key == '5'){
            if(flag3[4] == 0){
                flag3[4] = 1;
            }
            
            else if(flag3[4] == 1){
                flag3[4] = 0;
            }
        }
        if(key == '6'){
            if(flag3[5] == 0){
                flag3[5] = 1;
            }
            
            else if(flag3[5] == 1){
                flag3[5] = 0;
            }
        }
        
        if(key == '7'){
            if(flag3[6] == 0){
                flag3[6] = 1;
            }
            
            else if(flag3[6] == 1){
                flag3[6] = 0;
            }
        }
        if(key == '8'){
            if(flag3[7] == 0){
                flag3[7] = 1;
            }
            
            else if(flag3[7] == 1){
                flag3[7] = 0;
            }
            
        }
        
    }
    
}

//--------------------------------------------------------------
void ofApp::buttonArduino(){
    //抵抗値によって変わるようにしたいので、実験が必要
    int pin0 = 0,pin1 = 0;
    pin0 = ard.getAnalog(inputPin[0]);
    pin1 = ard.getAnalog(inputPin[1]);
    
    //aflagでまず分岐、そこから各フラグを書き換えてく
    switch(aflag){
        case 0:
            if(800 < pin0 && pin0 <= 1023){
                if(!(prev_flag==0)){
                    prev_flag=0;
                    if(flag[0]==0){
                        flag[0]=1;
                        break;
                    }
                    else if(flag[0]==1){
                        flag[0]=0;
                        break;
                    }
                }
                else{break;}
            }
            else if(600 < pin0 && pin0 <= 650){
                if(!(prev_flag==1)){
                    prev_flag=1;
                    if(flag[1]==0){
                        flag[1]=1;
                        break;
                    }
                    else if(flag[1]==1){
                        flag[1]=0;
                        break;
                    }
                }
                else{break;}
            }
            else if(350 < pin0 && pin0 <= 420){
                if(!(prev_flag==2)){
                    prev_flag=2;
                    if(flag[2]==0){
                        flag[2]=1;
                        break;
                    }
                    else if(flag[2]==1){
                        flag[2]=0;
                        break;
                    }
                }
                else{break;}
            }
            else if(180 < pin0 && pin0 <= 250){
                if(!(prev_flag==3)){
                    prev_flag=3;
                    if(flag[3]==0){
                        flag[3]=1;
                        break;
                    }
                    else if(flag[3]==1){
                        flag[3]=0;
                        break;
                    }
                }
                else{break;}
            }
            if(800 < pin1 && pin1 <= 1023){
                if(!(prev_flag==4)){
                    prev_flag=0;
                    if(flag[4]==4){
                        flag[4]=1;
                        break;
                    }
                    else if(flag[4]==1){
                        flag[4]=0;
                        break;
                    }
                }
                else{break;}
                    }
            else if(600 < pin1 && pin1 <= 650){
                if(!(prev_flag==5)){
                    prev_flag=5;
                    if(flag[5]==0){
                        flag[5]=1;
                        break;
                    }
                    else if(flag[5]==1){
                        flag[5]=0;
                        break;
                    }
                }
                else{break;}
            }
            else if(350 < pin1 && pin1 <= 420){
                if(!(prev_flag==6)){
                    prev_flag=6;
                    if(flag[6]==0){
                        flag[6]=1;
                        break;
                    }
                    else if(flag[6]==1){
                        flag[6]=0;
                        break;
                    }
                }
                else{break;}
            }
            else if(180 < pin1 && pin1 <= 250){
                if(!(prev_flag==7)){
                    prev_flag=7;
                    if(flag[7]==0){
                        flag[7]=1;
                        break;
                    }
                    else if(flag[7]==1){
                        flag[7]=0;
                        break;
                    }
                }
                else{break;}
            }
            else{prev_flag=10;}
            
        case 1:
            if(800 < pin0 && pin0 <= 1023){
                if(!(prev_flag==0)){
                    prev_flag=0;
                    if(flag2[0]==0){
                        flag2[0]=1;
                        break;
                    }
                    else if(flag2[0]==1){
                        flag2[0]=0;
                        break;
                    }
                }
                else{break;}
            }
            else if(600 < pin0 && pin0 <= 650){
                if(!(prev_flag==1)){
                    prev_flag=1;
                    if(flag2[1]==1){
                        flag2[1]=1;
                        break;
                    }
                    else if(flag2[1]==1){
                        flag2[1]=0;
                        break;
                    }
                }
                else{break;}
            }
            else if(350 < pin0 && pin0 <= 420){
                if(!(prev_flag==2)){
                    prev_flag=2;
                    if(flag2[2]==0){
                        flag2[2]=1;
                        break;
                    }
                    else if(flag2[2]==1){
                        flag2[2]=0;
                        break;
                    }
                }
                else{break;}
            }
            else if(180 < pin0 && pin0 <= 250){
                if(!(prev_flag==3)){
                    prev_flag=3;
                    if(flag2[3]==0){
                        flag2[3]=1;
                        break;
                    }
                    else if(flag2[3]==1){
                        flag2[3]=0;
                        break;
                    }
                }
                else{break;}
            }
            if(800 < pin1 && pin1 <= 1023){
                if(!(prev_flag==4)){
                    prev_flag=4;
                    if(flag2[4]==0){
                        flag2[4]=1;
                        break;
                    }
                    else if(flag2[4]==1){
                        flag2[4]=0;
                        break;
                    }
                }
                else{break;}
            }
            else if(600 < pin1 && pin1 <= 650){
                if(!(prev_flag==5)){
                    prev_flag=5;
                    if(flag2[5]==0){
                        flag2[5]=1;
                        break;
                    }
                    else if(flag[5]==1){
                        flag[5]=0;
                        break;
                    }
                }
                else{break;}
            }
            else if(350 < pin1 && pin1 <= 420){
                if(!(prev_flag==6)){
                    prev_flag=6;
                    if(flag2[6]==0){
                        flag2[6]=1;
                        break;
                    }
                    else if(flag2[6]==1){
                        flag2[6]=0;
                        break;
                    }
                }
                else{break;}
            }
            else if(180 < pin1 && pin1 <= 250){
                if(!(prev_flag==7)){
                    prev_flag=7;
                    if(flag2[7]==0){
                        flag2[7]=1;
                        break;
                    }
                    else if(flag2[7]==1){
                        flag2[7]=0;
                        break;
                    }
                }
                else{break;}
            }
            else{prev_flag=10;}
            
        case 2:
            if(800 < pin0 && pin0 <= 1023){
                if(!(prev_flag==0)){
                    prev_flag=0;
                    if(flag3[0]==0){
                        flag3[0]=1;
                        break;
                    }
                    else if(flag3[0]==1){
                        flag3[0]=0;
                        break;
                    }
                }
                else{break;}
            }
            else if(600 < pin0 && pin0 <= 650){
                if(!(prev_flag==1)){
                    prev_flag=1;
                    if(flag3[1]==0){
                        flag3[1]=1;
                        break;
                    }
                    else if(flag3[1]==1){
                        flag3[1]=0;
                        break;
                    }
                }
                else{break;}
            }
            else if(350 < pin0 && pin0 <= 420){
                if(!(prev_flag==2)){
                    prev_flag=2;
                    if(flag3[2]==0){
                        flag3[2]=1;
                        break;
                    }
                    else if(flag3[2]==1){
                        flag3[2]=0;
                        break;
                    }
                }
                else{break;}
            }
            else if(180 < pin0 && pin0 <= 250){
                if(!(prev_flag==3)){
                    prev_flag=3;
                    if(flag3[3]==0){
                        flag3[3]=1;
                        break;
                    }
                    else if(flag3[3]==1){
                        flag3[3]=0;
                        break;
                    }
                }
                else{break;}
            }
            if(716 < pin1 && pin1 <= 1023){
                if(!(prev_flag==4)){
                    prev_flag=4;
                    if(flag3[4]==0){
                        flag3[4]=1;
                        break;
                    }
                    else if(flag3[4]==1){
                        flag3[4]=0;
                        break;
                    }
                }
                else{break;}
            }
            else if(512 < pin1 && pin1 <= 716){
                if(!(prev_flag==5)){
                    prev_flag=5;
                    if(flag3[5]==0){
                        flag3[5]=1;
                        break;
                    }
                    else if(flag3[5]==1){
                        flag3[5]=0;
                        break;
                    }
                }
                else{break;}
            }
            else if(307 < pin1 && pin1 <= 512){
                if(!(prev_flag==6)){
                    prev_flag=6;
                    if(flag3[6]==0){
                        flag3[6]=1;
                        break;
                    }
                    else if(flag3[6]==1){
                        flag3[6]=0;
                        break;
                    }
                }
                else{break;}
            }
            else if(102 < pin1 && pin1 <= 307){
                if(!(prev_flag==7)){
                    prev_flag=7;
                    if(flag3[7]==0){
                        flag3[7]=1;
                        break;
                    }
                    else if(flag3[7]==1){
                        flag3[7]=0;
                        break;
                    }
                }
                else{break;}
            }
            else{prev_flag=10;}
            
    }
    
}

//--------------------------------------------------------------
void ofApp::clickArduino(){
    //常に回り続けるやつ、フレームで管理する
    if(0<=frame && frame<=15){
        ard.sendDigital(outputPin[8], ARD_HIGH);
        ard.sendDigital(outputPin[9], ARD_LOW);
        ard.sendDigital(outputPin[10], ARD_LOW);
        ard.sendDigital(outputPin[11], ARD_LOW);
    }
    else if(15<=frame && frame<=30){
        ard.sendDigital(outputPin[8], ARD_LOW);
        ard.sendDigital(outputPin[9], ARD_HIGH);
        ard.sendDigital(outputPin[10], ARD_LOW);
        ard.sendDigital(outputPin[11], ARD_LOW);
    }
    else if(30<=frame && frame<=45){
        ard.sendDigital(outputPin[8], ARD_LOW);
        ard.sendDigital(outputPin[9], ARD_LOW);
        ard.sendDigital(outputPin[10], ARD_HIGH);
        ard.sendDigital(outputPin[11], ARD_LOW);
    }
    else if(45<=frame && frame<=55){
        ard.sendDigital(outputPin[8], ARD_LOW);
        ard.sendDigital(outputPin[9], ARD_LOW);
        ard.sendDigital(outputPin[10], ARD_LOW);
        ard.sendDigital(outputPin[11], ARD_HIGH);
    }
    else {
        ard.sendDigital(outputPin[8], ARD_LOW);
        ard.sendDigital(outputPin[9], ARD_LOW);
        ard.sendDigital(outputPin[10], ARD_LOW);
        ard.sendDigital(outputPin[11], ARD_LOW);
    }
    
}

//--------------------------------------------------------------
void ofApp::rhythmArduino(){
    switch (aflag){
        case 0:
            for(int p=0; p<8; p++){
                if(flag[p]==0)ard.sendDigital(outputPin[p],ARD_LOW);
                else if(flag[p]==1)ard.sendDigital(outputPin[p],ARD_HIGH);
            }
            break;
            
        case 1:
            for(int p=0; p<8; p++){
                if(flag2[p]==0)ard.sendDigital(outputPin[p],ARD_LOW);
                else if(flag2[p]==1)ard.sendDigital(outputPin[p],ARD_HIGH);
            }
            break;
            
        case 2:
            for(int p=0; p<8; p++){
                if(flag3[p]==0)ard.sendDigital(outputPin[p],ARD_LOW);
                else if(flag3[p]==1)ard.sendDigital(outputPin[p],ARD_HIGH);
            }
            break;
    }
}

//--------------------------------------------------------------
void ofApp::aflagArduino(){
    if(ard.getDigital(inputPinA) == 1){
        if(aflag <2){
            aflag += 1;
        }
        
        else if(aflag == 2){
            aflag = 0;
        }
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
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
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
