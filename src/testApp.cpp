#include "testApp.h"
#define AMOUNT 100

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0,0,0);

	ofSetFrameRate(24);
	ofSetVerticalSync(true);
	ofDisableArbTex(); //needed for textures to work with gluSphere

	int xMax = 1024;
	int yMax = 768;
	res = 10;

	fbo3.allocate(xMax, yMax, GL_RGBA, 4);
	fbo4.allocate(xMax, yMax, GL_RGBA, 4);
	fbo4.setType("line");
	fbo3.setType("line");
	fbo4.setColor(ofColor(0, 255, 56));
	fbo3.setColor(ofColor(255, 141, 68));
	fbo4.generateShapes(20);
	fbo3.generateShapes(20);
	fbo4.paintMe();
	fbo3.paintMe();

	float x = 1, y = 1;
	for(int i = 0; i < 100; i++) {
		x = x + ofGetWindowWidth() / 9;
		if(i % 11 == 0) {
			y = y + ofGetWindowHeight() / 9;
			x = 10;
		}
		stars.push_back(ofVec3f(x, y, ofRandom(0.8, 1)));
	}

	vector<ofVec3f>::iterator it = stars.begin(), end = stars.end();
	ofSetColor(255);
	int rounds = 1000;
	for(int i = 0; i < rounds; i++) {
		for(; it != end; ++it) {
			it->set(it->x + ofRandom(-1.,1.), it->y + ofRandom(-1.1,1.1), 0);
			ofCircle((*it), 1);
		}
		it = stars.begin();
	}

	//anderer planet
	float angle = ofDegToRad(360/10);
	for(int i = 0; i < 10; i++) {
		float x = cos(angle * i) * 25;
		float y = sin(angle * i) * 25;
		vertexPoints[i] = ofPoint(x,y);
	}
	center.set(12,12);

	// Point lights emit light in all directions //
	// set the diffuse color, color reflected from the light source //
	pointLight.setDiffuseColor( ofColor(249, 245, 224));
	lightPos = ofVec3f(800, 34, 545);
	pointLight.setPosition(lightPos);

	// specular color, the highlight/shininess color //
	pointLight.setSpecularColor( ofColor(255.f, 255.f, 0.f));
	pointLight.setPointLight();
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
	vector<ofVec3f>::iterator it = stars.begin(), end = stars.end();
	ofSetColor(255);
	for(; it != end; ++it) {
		it->set(it->x + ofRandom(-0.01,0.01), it->y + ofRandom(-0.01,0.01), 0);
		ofCircle((*it), 0.8);
	}

	fbo3.draw(0, 0);
	ofEnableLighting();
	pointLight.enable();

	//change origin to center
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);

	//rotate sphere over time
	ofRotateY(ofGetFrameNum()*0.1); // super idee das mached mir so :D
	ofEnableAlphaBlending();
	glEnable(GL_DEPTH_TEST); //enable depth comparisons and update the depth buffer

	//bind and draw texture
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	ofScale(fbo3.getWidth(), fbo3.getHeight());
	glMatrixMode(GL_MODELVIEW);
	ofSetColor(184, 114, 32);
	ofFill();
	ofSphere(198);
	ofSetColor(255); // IMPORTANT!!!
	fbo3.getTextureReference().bind();
	ofSphere(200);
	fbo3.getTextureReference().unbind();
	ofSetColor(255);
	fbo4.getTextureReference().bind();
	ofRotateY(90);
	ofSphere(206);
	fbo4.getTextureReference().unbind();
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	//fbo.draw(0,0);
	glDisable(GL_DEPTH_TEST);
	ofDisableAlphaBlending();
	ofDisableLighting();
	/*ofImage screen;
	screen.grabScreen(0,0,ofGetWindowWidth(), ofGetWindowHeight());
	string frame = ofToString(ofGetFrameNum());
	if(frame.length() < 6) {
		int add = 6 - frame.length();
		for(int i = 0; i < add; i++) {
			frame = ofToString(0) + frame;
		}
	}
	screen.saveImage("test_" + frame + ".png");
	cout << "saved " << "test_" << frame << ".png" << endl;*/
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == 'a') {
		fbo3.paintMe();
//		fbo.begin();
//			ofTranslate(fbo.getWidth() / 2, fbo.getHeight() / 2);
//			ofClear(255, 255, 255, 0);
//			//grow
//			for (int r = 0; r < 20; r++) {
//				for(int i = 0; i < res; i++) {
//					vertexPoints[i].set(vertexPoints[i].x + ofRandom(-1, 1), vertexPoints[i].y + ofRandom(-1, 1));
//				}
//			}
//			center.set(center.x + ofRandom(-3,3), center.y + ofRandom(-2, 2));
//			ofSetColor(31, 94, 31, 255);
//			ofBeginShape();
//				ofCurveVertex(vertexPoints[res - 1]);
//				for(int i = 0; i < res; i++) {
//					ofCurveVertex(vertexPoints[i]);
//					//ofSetColor(255, 0 ,0);
//					//ofEllipse(vertexPoints[i], 5, 5);
//				}
//				ofCurveVertex(vertexPoints[1]);
//			ofEndShape();
//			ofNoFill();
//			ofEnableSmoothing();
//				ofBeginShape();
//					ofCurveVertex(vertexPoints[res - 1]);
//					for(int i = 0; i < res; i++) {
//						ofCurveVertex(vertexPoints[i]);
//						//ofSetColor(255, 0 ,0);
//						//ofEllipse(vertexPoints[i], 5, 5);
//					}
//					ofCurveVertex(vertexPoints[1]);
//				ofEndShape();
//			ofDisableSmoothing();
//		fbo.end();
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
	else if (key == OF_KEY_UP) {
		lightPos.x++;
		pointLight.setPosition(lightPos);
		cout << "x-> " << lightPos.x << " y-> " << lightPos.y << " z-> " << lightPos.z << endl;
	}
	else if (key == OF_KEY_DOWN) {
		lightPos.x--;
		pointLight.setPosition(lightPos);
		cout << "x-> " << lightPos.x << " y-> " << lightPos.y << " z-> " << lightPos.z << endl;
	}
	else if (key == OF_KEY_LEFT) {
		lightPos.y++;
		pointLight.setPosition(lightPos);
		cout << "x-> " << lightPos.x << " y-> " << lightPos.y << " z-> " << lightPos.z << endl;
	}
	else if (key == OF_KEY_RIGHT) {
		lightPos.y--;
		pointLight.setPosition(lightPos);
		cout << "x-> " << lightPos.x << " y-> " << lightPos.y << " z-> " << lightPos.z << endl;
	}
	else if (key == 'o') {
		lightPos.z++;
		pointLight.setPosition(lightPos);
		cout << "x-> " << lightPos.x << " y-> " << lightPos.y << " z-> " << lightPos.z << endl;
	}
	else if (key == 'l') {
		lightPos.z--;
		pointLight.setPosition(lightPos);
		cout << "x-> " << lightPos.x << " y-> " << lightPos.y << " z-> " << lightPos.z << endl;
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
