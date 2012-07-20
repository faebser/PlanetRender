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
	res = 10;

	fbo.allocate(xMax, yMax, GL_RGBA, 4);


	//anderer planet
	float angle = ofDegToRad(360/10);
	for(int i = 0; i < 10; i++) {
		float x = cos(angle * i) * 100;
		float y = sin(angle * i) * 100;
		vertexPoints[i] = ofPoint(x,y);
	}
	center.set(50,50);

	fbo.begin();
		ofTranslate(fbo.getWidth() / 2, fbo.getHeight() / 2);
		for (int r = 0; r < 20; r++) {
			for(int i = 0; i < res; i++) {
				vertexPoints[i].set(vertexPoints[i].x + ofRandom(-1, 3), vertexPoints[i].y + ofRandom(-1, 3));
			}
		}
		ofBeginShape();
			ofCurveVertex(vertexPoints[res - 1]);
			for(int i = 0; i < res; i++) {
				ofCurveVertex(vertexPoints[i]);
				ofSetColor(255, 0 ,0);
				ofEllipse(vertexPoints[i], 5, 5);
				ofSetColor(255, 255, 255);
			}
			ofCurveVertex(vertexPoints[1]);
		ofEndShape();
		ofSetColor(255, 0, 0);
		ofEllipse(center, 5,5);
	fbo.end();

	/*fbo1.allocate(xMax, yMax, GL_RGBA, 4);
	fbo2.allocate(xMax, yMax, GL_RGBA, 4);
	//map.allocate(2048, 1024, OF_IMAGE_GRAYSCALE);

	//gasplanet
	int max = xMax * yMax;
	float xNoise = 0, yNoise = 0;
	// gas planet = yInc = 0.1 xInc = 0.0001
	brighntess = new int[max];
	yIncrement = 0.008, xIncrement = 0.008;*/

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



	/*
	fbo.begin();
		for(int y = 0; y < yMax; y++) {
			yNoise = 0;
			xNoise += xIncrement;
			for(int x = 0 ; x < xMax; x++) {
				yNoise += yIncrement;
				float brig = ofNoise(xNoise, yNoise)*240;
				if(brig > 100 && brig < 150) {
					ofSetColor(142, 109, 86, 100);
				}
				else {
					ofSetColor(0, 0, 0, 0);
				}
				ofRect(x, y, 1, 1);
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
						ofSetColor(99, 69, 39, 100);
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
							ofSetColor(51, 41, 32, 100);
							ofRect(x, y, 1, 1);
						}

					}
				}
	fbo2.end();*/
}
//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255);
	//ofRect(0, 0, 1024, 768);
	fbo.draw(0,0);

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
	//ofSetColor(181, 133, 85);
	//ofSphere(195);
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	ofScale(fbo.getWidth(), fbo.getHeight());
	glMatrixMode(GL_MODELVIEW);
	/*fbo2.getTextureReference().bind();
	ofSphere(198);
	fbo2.getTextureReference().unbind();*/
	fbo.getTextureReference().bind();
	//ofSphere(200);
	fbo.getTextureReference().unbind();
	/*fbo1.getTextureReference().bind();
	ofSphere( 202);
	fbo1.getTextureReference().unbind();*/
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
		fbo.begin();
			ofSetColor(0);
			ofRect(0,0, fbo.getWidth(), fbo.getHeight());
			ofTranslate(fbo.getWidth() / 2, fbo.getHeight() / 2);
			//grow
			ofSetColor(255);
			for (int r = 0; r < 20; r++) {
				for(int i = 0; i < res; i++) {
					vertexPoints[i].set(vertexPoints[i].x + ofRandom(-3, 3), vertexPoints[i].y + ofRandom(-3, 3));
				}
			}
			center.set(center.x + ofRandom(-3,3), center.y + ofRandom(-3, 3));
			ofBeginShape();
				ofCurveVertex(vertexPoints[res - 1]);
				for(int i = 0; i < res; i++) {
					ofCurveVertex(vertexPoints[i]);
					ofSetColor(255, 0 ,0);
					ofEllipse(vertexPoints[i], 5, 5);
					ofSetColor(255);
				}
				ofCurveVertex(vertexPoints[1]);
			ofEndShape();
			ofSetColor(255, 0, 0);
			ofEllipse(center, 5,5);
		fbo.end();
	}
	else if(key == 's') {
		for (int r = 0; r < 20; r++) {
			for(int i = 0; i < res; i++) {
				ofPoint growVec;
				growVec =  vertexPoints[i] - center;
				vertexPoints[i] += growVec.normalized()*0.5;
			}
		}
	}
	else if(key == 'q') {
		for (int r = 0; r < 20; r++) {
			for(int i = 0; i < res; i++) {
				ofPoint growVec;
				growVec =  vertexPoints[i] - center;
				vertexPoints[i] -= growVec.normalized()*0.5;
			}
		}
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
