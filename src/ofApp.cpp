#include "ofApp.h"
//#include "ofxMIDI.h"

int pix0[1024][1024];
int pix1[1024][1024];
//int pix0hue[1024][1024];
//int pix1hue[1024][1024];
float saten=0;
int mp;
float ss=.95;
float dd=.5;
float ff=1;
float hh=1;
float jj=5.8;
float kk=5.9;
float ll=5.7;
float gg=5;
int sw0=0;
int sw1=0;
int sw2=0;
float hue=0;
float sat=0;

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0,0,0);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
	ofSetWindowTitle("color example");
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    
	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
    
    // initialise member variables to the centre of the screen
    mouseXPercent = 0.5f;
    mouseYPercent = 0.5f;
    
    /*
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // print input ports to console
    midiIn.listInPorts();
    
    // open port by number (you may need to change this)
    midiIn.openPort(1);
    //midiIn.openPort("IAC Pure Data In");	// by name
    //midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
    
    // don't ignore sysex, timing, & active sense messages,
    // these are ignored by default
    midiIn.ignoreTypes(false, false, false);
    
    // add ofApp as a listener
    midiIn.addListener(this);
    
    // print received messages to the console
    midiIn.setVerbose(true);
     */
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    
   
	//float hue = 0;
   
    int step = 6;
    int x=0;
    int y=0;
    // step through horizontally
    for ( int i=1; i<ofGetWidth()-1; i+=step )
    {
        // step through vertically
        for ( int j=1; j<ofGetHeight()-10; j+=step )
        {
             float bright=0;
            float bright0=0;
            int count=0;
            bright=pix0[i/step][j/step];
            
           // float sat=0;
            
            
            if(j<=(mouseY+step)&&j>=(mouseY-step)){
                if(i<=(mouseX+step)&&i>=(mouseX-step)){
                    bright=255;
                }//endifi
            }//endifj

            
            
           // int up=ofClamp((j-ff)/step,0,ofGetHeight()/step);
           // int down=ofClamp((j+ff)/step,0,ofGetHeight()/step);
           //  int left=ofClamp((i+ff)/step,0,ofGetHeight()/step);
          //  int right=ofClamp((i-ff)/step,0,ofGetHeight()/step);
            
            int up=ofClamp((j-ff)/step,-ofGetHeight()/step,ofGetHeight()/step);
            int down=ofClamp((j+jj)/step,-ofGetHeight()/step,ofGetHeight()/step);
            int left=ofClamp((i+kk)/step,-ofGetWidth()/step,ofGetWidth()/step);
            int right=ofClamp((i-ll)/step,-ofGetWidth()/step,ofGetWidth()/step);

            if(bright<=pix0[i/step][up]){
                bright=(bright+2*dd*pix0[i/step][up])/2;
                count++;
            }
            if(bright<=pix0[i/step][down]){
                bright=(bright+2*dd*pix0[i/step][down])/2;
                count++;
            }
                      if(bright<=pix0[left][j/step]){
                bright=(bright+2*dd*pix0[left][j/step])/2;
                count++;
            }
            if(bright<=pix0[right][up]){
                bright0=(bright+2*dd*pix0[right][up])/2;
                count++;
            }
            if(bright<=pix0[right][down]){
                bright=(bright+2*dd*pix0[right][down])/2;
                count++;
            }
            if(bright<=pix0[left][down]){
                bright=(bright+2*dd*pix0[left][down])/2;
                count++;
            }
            if(bright<=pix0[right][down]){
                bright=(bright+2*dd*pix0[right][down])/2;
                count++;
            }
            if(bright<=pix0[i/step][up]){
                bright=(bright+2*dd*pix0[i/step][up])/2;
                count++;
            }
            if(bright<=pix0[right][j/step]){
                bright=(bright+2*dd*pix0[right][j/step])/2;
                count++;
            }

            
          ////  if(count>0){
           // bright=bright0/count;
          //  }
            if(sw1==1){
                bright=(pix0[right][down]+pix0[left][down]+pix0[i/step][up]+pix0[right][up]
                        +pix0[left][j/step]+pix0[right][j/step]+pix0[i/step][down]+255*hh)/8;
                
                if(bright>255){
                    bright=fmod(bright,255);
                   // bright=255-bright;
                }
            }
         
            
            
            
           // if(mp==1){
               // hue=ofRandom(0,1)*255;
                sat=255;
            //}
            /*
            if(mp==0&&hue>0){
                hue=hue*(.91);
                sat=sat*.99;
            }
            */
            
            if(bright>=pix0[i/step][j/step]){
            
                bright=bright*(.0001+ss);
                sat=sat*(.0001+ss);
            }
            
            //rug rule switch
           if(sw2==1){bright=abs(bright);}
            
            if(sw0==1){bright=fmod(bright,255);}
            
            
         //  hue=hue*(1+gg*(bright/255));
            //sat=sat*(255-bright);
            float alph=bright;
            ofColor c;
            // the range of each of the arguments here is 0..255 so we map i and j to that range.
            c.setHsb( fmod(abs((bright*gg)),255), sat, bright,alph );

            
            
           /*
            
            // set HSB using our hue value that changes over time, saturation from the X position (i), 
            // and brightness from the Y position (j). we also invert the Y value since it looks
            // nicer if the dark/black colors are along the bottom.
            ofColor c;
            // the range of each of the arguments here is 0..255 so we map i and j to that range.
            c.setHsb( hue, ofMap(i, 0,ofGetWidth(), 0,255), ofMap(j, ofGetHeight(),0, 0,255 ) );
            */
            
            
            
            // assign the color and draw a rectangle
            ofSetColor( c );
            ofDrawRectangle( i, j, step, step );
            
            pix1[i/step][j/step]=int(bright);
            
        }//endj
        
    }//endi
    
    for ( int i=0; i<ofGetWidth(); i+=step)
    {
        // step through vertically
        for ( int j=0; j<ofGetHeight(); j+=step )
        {
            pix0[i/step][j/step]=pix1[i/step][j/step];
        }//endj
    }//endi
    
    
    
    
     ofSetHexColor(0xFFFFFF);
     ofDrawBitmapString("ff: "+ofToString(ff)+" dd: "+ofToString(dd)+" ss: "+ofToString(ss)
                        +" hh: "+ofToString(hh)+"jjh: "+ofToString(jj)+" kk: "+ofToString(kk)
                        +" ll: "+ofToString(ll),
      10, ofGetHeight()-13 );
  

}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    if(key=='s'){ss+=.001;}
    if(key=='x'){ss-=.001;}
    if(key=='d'){dd+=.01;}
    if(key=='c'){dd-=.01;}
    if(key=='f'){ff+=.1;}
    if(key=='v'){ff-=.1;}
    if(key=='g'){gg+=.01;}
    if(key=='b'){gg-=.01;}
    if(key=='h'){hh+=.005;}
    if(key=='n'){hh-=.005;}
    
    if(key=='j'){jj+=.1;}
    if(key=='m'){jj-=.1;}
    if(key=='k'){kk+=.1;}
    if(key==','){kk-=.1;}
    if(key=='l'){ll+=.1;}
    if(key=='.'){ll-=.1;}



    
     if(key=='`'){hh=ss=dd=ff=gg=1;}
    
}

//--------------------------------------------------------------
void ofApp::keyReleased  (int key){

    if(key=='0'){sw0=1;}
    if(key=='p'){sw0=0;}
    if(key=='2'){sw2=1;}
    if(key=='w'){sw2=0;}

    if(key=='1'){sw1=1;}
    if(key=='q'){sw1=0;}


}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    // update mouse x and y percent when the mouse moves
    mouseXPercent = float(x) / ofGetWidth();
    mouseYPercent = float(y) / ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mp=1;

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    mp=0;
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
