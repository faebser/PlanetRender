#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0,0,0);

	ofSetFrameRate(24);


	int xMax = 1024, yMax = 768;
	fbo.allocate(xMax, yMax, GL_RGBA, 2);
	fbo.setType("line");
	fbo.setColor(ofColor(40, 107, 119));
	fbo.generateShapes(20);
	fbo.paintMe();

	fbo1.allocate(xMax, yMax, GL_RGBA, 2);
	fbo1.setType("line");
	fbo1.setColor(ofColor(123, 155, 160));
	fbo1.generateShapes(35);
	fbo1.paintMe();

	fbo2.allocate(xMax, yMax, GL_RGBA, 2);
	fbo2.setType("line");
	fbo2.setColor(ofColor(67, 140, 142));
	fbo2.generateShapes(15);
	fbo2.paintMe();

	fbo3.allocate(xMax, yMax, GL_RGBA, 2);
	fbo3.setType("line");
	fbo3.setColor(ofColor(73, 103, 104));
	fbo3.generateShapes(10);
	fbo3.paintMe();

	fbo4.allocate(xMax, yMax, GL_RGBA, 2);
	fbo4.setType("line");
	fbo4.setColor(ofColor(3, 117, 165));
	fbo4.generateShapes(20);
	fbo4.paintMe();

	// STARS
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
	ofSetColor(245);
	int rounds = 1000;
	for(int i = 0; i < rounds; i++) {
		for(; it != end; ++it) {
			it->set(it->x + ofRandom(-1.,1.), it->y + ofRandom(-1.1,1.1), 0);
			ofCircle((*it), 1);
		}
		it = stars.begin();
	}

	// Point lights emit light in all directions //
	// set the diffuse color, color reflected from the light source //
	sun.setDiffuseColor( ofColor(249, 245, 224));

	sunPos = ofVec3f(215, 964, 1100);
	sun.setPosition(sunPos);

	// specular color, the highlight/shininess color //
	sun.setSpecularColor( ofColor(255.f, 255.f, 0.f));
	sun.setPointLight();

	ofDisableArbTex(); //needed for textures to work with gluSphere
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	ofEnableAlphaBlending();
	ofEnableLighting();
	sun.enable();

	vector<ofVec3f>::iterator it = stars.begin(), end = stars.end();

	ofSetColor(255);
	for(; it != end; ++it) {
		it->set(it->x + ofRandom(-0.01,0.01), it->y + ofRandom(-0.01,0.01), 0);
		ofCircle(it->x,it->y, 0.8);
	}


	ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);

	//rotate sphere over time
	ofRotateY(ofGetFrameNum()*-0.3); // super idee das mached mir so :D

	glEnable(GL_DEPTH_TEST); //enable depth comparisons and update the depth buffer


	ofSetColor(28, 220, 255);
	ofSphere(70);

	//bind and draw texture
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	ofScale(fbo.getWidth(), fbo.getHeight());
	glMatrixMode(GL_MODELVIEW);

		ofSetColor(255); // IMPORTANT!!!
		fbo.getTextureReference().bind();
		ofRotateY(-20);
		ofSphere(71);
		fbo.getTextureReference().unbind();

		fbo1.getTextureReference().bind();
		ofRotateY(180);
		ofSphere(72);
		fbo1.getTextureReference().unbind();

		fbo2.getTextureReference().bind();
		ofRotateY(25);
		ofSphere(75);
		fbo2.getTextureReference().unbind();

		fbo3.getTextureReference().bind();
		ofRotateY(-10.2);
		ofSphere(77);
		fbo3.getTextureReference().unbind();

		fbo4.getTextureReference().bind();
		ofRotateY(-45);
		ofSphere(80);
		fbo4.getTextureReference().unbind();

	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_DEPTH_TEST);


	ofDisableAlphaBlending();
	ofDisableLighting();

	ofImage screen;
	screen.grabScreen(0,0,ofGetWindowWidth(), ofGetWindowHeight());
	string frame = ofToString(ofGetFrameNum());
	if(frame.length() < 6) {
		int add = 6 - frame.length();
		for(int i = 0; i < add; i++) {
			frame = ofToString(0) + frame;
		}
	}
	screen.saveImage("pod2_" + frame + ".png");
	cout << "saved " << "pod2_" << frame << ".png" << endl;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	 if (key == OF_KEY_UP) {
		sunPos.x += 5;
		sun.setPosition(sunPos);
		cout << "x-> " << sunPos.x << " y-> " << sunPos.y << " z-> " << sunPos.z << endl;
	}
	else if (key == OF_KEY_DOWN) {
		sunPos.x -= 5;
		sun.setPosition(sunPos);
		cout << "x-> " << sunPos.x << " y-> " << sunPos.y << " z-> " << sunPos.z << endl;
	}
	else if (key == OF_KEY_LEFT) {
		sunPos.y += 5;
		sun.setPosition(sunPos);
		cout << "x-> " << sunPos.x << " y-> " << sunPos.y << " z-> " << sunPos.z << endl;
	}
	else if (key == OF_KEY_RIGHT) {
		sunPos.y -= 5;
		sun.setPosition(sunPos);
		cout << "x-> " << sunPos.x << " y-> " << sunPos.y << " z-> " << sunPos.z << endl;
	}
	else if (key == 'o') {
		sunPos.z += 5;
		sun.setPosition(sunPos);
		cout << "x-> " << sunPos.x << " y-> " << sunPos.y << " z-> " << sunPos.z << endl;
	}
	else if (key == 'l') {
		sunPos.z -= 5;
		sun.setPosition(sunPos);
		cout << "x-> " << sunPos.x << " y-> " << sunPos.y << " z-> " << sunPos.z << endl;
	}
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
