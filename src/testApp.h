#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofImage earth;
		float yIncrement, xIncrement;
		int* brighntess;
		//ofImage_<ofPixels_<unsigned char> > map;
		//GLUquadricObj *quadric;
		ofTexture text;
		ofFbo fbo, fbo1, fbo2;
};
