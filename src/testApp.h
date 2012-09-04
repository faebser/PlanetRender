#pragma once

#include "ofMain.h"
#include "PlanetShape.h"
#include "PlanetFbo.h"

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

		ofImage test, fboI, fbo1I, fbo2I, fbo3I, fbo4I;
		PlanetFbo fbo, fbo1, fbo2, fbo3, fbo4;
		ofPixels fboPixels, fbo1P, fbo2P, fbo3P, fbo4P;

		vector<ofVec3f> stars;
		ofVec3f sunPos;
		ofLight sun;
};
