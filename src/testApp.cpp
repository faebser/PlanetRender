#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0,0,0);

	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofDisableArbTex(); //needed for textures to work with gluSphere
	earth.loadImage("earth.jpg");
	//text = earth.getTextureReference();

	int xMax = 800;
	int yMax = 600;

	fbo.allocate(xMax, yMax, GL_RGBA, 4);
	fbo1.allocate(xMax, yMax, GL_RGBA, 4);
	fbo2.allocate(xMax, yMax, GL_RGBA, 4);
	//map.allocate(2048, 1024, OF_IMAGE_GRAYSCALE);



	int max = xMax * yMax;
	float xNoise = 0, yNoise = 0;
	// gas planet = yInc = 0.1 xInc = 0.0001
	brighntess = new int[max];
	yIncrement = 0.0005, xIncrement = 0.008;

	/*fbo.begin();
		for(int y = 0; y < yMax; y++) {
			yNoise = 0;
			xNoise += xIncrement;
			for(int x = 0 ; x < xMax; x++) {
				yNoise += yIncrement;
				//brighntess[x+y] = (int)(255 * ofRandomuf());
				ofSetColor(ofNoise(xNoise, yNoise)*240);
				ofRect(x, y, 1, 1);
			}
		}
	fbo.end();*/


	//gasplanet
	fbo.begin();
		for(int y = 0; y < yMax; y++) {
			yNoise = 0;
			xNoise += xIncrement;
			for(int x = 0 ; x < xMax; x++) {
				yNoise += yIncrement;
				float brig = ofNoise(xNoise, yNoise)*240;
				if(brig > 100 && brig < 150) {
					ofSetColor(142, 109, 86, 240);
				}
				/*else if(brig < 100) {
					ofSetColor(99, 69, 39, 5);
				}
				else if(brig > 150) {
					ofSetColor(51, 41, 32, 5);
				}*/
				else {
					ofSetColor(0, 0, 0, 0);
				}
				ofRect(x, y, 150, 150);
			}
		}
	fbo.end();
	fbo1.begin();
			for(int y = 0; y < yMax; y++) {
				yNoise = 0;
				xNoise += xIncrement;
				for(int x = 0 ; x < xMax; x++) {
					yNoise += yIncrement;
					float brig = ofNoise(xNoise, yNoise)*240;
					if(brig < 100) {
						ofSetColor(99, 69, 39, 240);
						ofRect(x, y, 1, 1);
					}

				}
			}
	fbo1.end();
	fbo2.begin();
				for(int y = 0; y < yMax; y++) {
					yNoise = 0;
					xNoise += xIncrement;
					for(int x = 0 ; x < xMax; x++) {
						yNoise += yIncrement;
						float brig = ofNoise(xNoise, yNoise)*240;
						if(brig > 150) {
							ofSetColor(51, 41, 32, 255);
							ofRect(x, y, 1, 1);
						}

					}
				}
	fbo2.end();
}
//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255);
	//ofRect(0, 0, 1024, 768);
	//fbo.draw(0,0);

	//fbo.draw(0,0);
	//change origin to center
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);

	//rotate sphere over time
	ofRotateY(ofGetFrameNum()*0.1);
	//ofRotateX(); //north pole facing up
	ofEnableAlphaBlending();
	glEnable(GL_DEPTH_TEST); //enable depth comparisons and update the depth buffer

	//bind and draw texture
	//texta.draw(0,0);
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	ofScale(fbo.getWidth(), fbo.getHeight());
	glMatrixMode(GL_MODELVIEW);
	fbo2.getTextureReference().bind();
	ofSphere(198);
	fbo2.getTextureReference().unbind();
	fbo.getTextureReference().bind();
	ofSphere( 200);
	fbo.getTextureReference().unbind();
	fbo1.getTextureReference().bind();
	ofSphere( 202);
	fbo1.getTextureReference().unbind();
	ofEnableAlphaBlending();
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	//fbo.draw(0,0);
	glDisable(GL_DEPTH_TEST);
	ofDisableAlphaBlending();
	/*ofEnableAlphaBlending();
	ofSetColor(255, 0, 0, 75);
	ofRect(100, 100, 150, 150);
	ofSetColor(0, 255, 0, 128);
	ofRect(200, 200, 150, 150);
	ofDisableAlphaBlending();*/
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == 'a') {
		yIncrement += 0.0001;
		cout << ofToString(yIncrement) << endl;
	}
	else if(key == 's') {
		yIncrement -= 0.0001;
		cout << ofToString(yIncrement) << endl;
	}
	else if(key == 'q') {
		xIncrement += 0.0001;
		cout << ofToString(xIncrement) << endl;
	}
	else if(key == 'w') {
		xIncrement -= 0.0001;
		cout << ofToString(xIncrement) << endl;
	}

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
