#pragma once
#define POINTS 6
#define RADIUS 250
#define GROWRATE 20
#define UPDATERATE 100
#include "ofMain.h"

class planetShape {
	public:
		planetShape(float width, float height, float size) {
			center = ofVec2f(ofRandom(0, width), ofRandom(0, height));
			float angle = ofDegToRad(360 / POINTS);
			for(int i = 0; i < POINTS; i++) {
					float x = cos(angle * i) * 25;
					float y = sin(angle * i) * 25;
					ofVec2f newPoint = ofVec2f(x,y) + center;
					vertexPoints[i] = newPoint;
					this->size = size;
			}
			for(int i = 0; i <= size; i++) {
				growMe();
			}
		}
		void updatePoints() {
			for (int change = 0; change < UPDATERATE; change++) {
				for(int i = 0; i < POINTS; i++) {
					vertexPoints[i].set(vertexPoints[i].x + ofRandom(-3, 3), vertexPoints[i].y + ofRandom(-3, 3));
				}
				center.set(center.x + ofRandom(-3.5,3.5), center.y + ofRandom(-3.5, 3.5));
			}
		}
		ofVec2f getCenter() const {
				return center;
		}
		void setCenter(ofVec2f center) {
			this->center = center;
		}
		void grow(int newSize) {
			int change  = newSize - size;
			for(int i = 0; i <= change; i++) {
				growMe();
			}
		}
		void shrink(int newSize) {
			int change  = size - newSize;
			for(int i = 0; i <= change; i++) {
				growMe();
			}
		}
		const ofVec2f* getvertexPoints() const {
			return vertexPoints;
		}

		ofVec2f getPos() const {
			return pos;
		}

		void setPos(ofVec2f pos) {
			this->pos = pos;
		}
		void addToPoint(int pointIndex, ofVec2f toAdd) {
			vertexPoints[pointIndex] += toAdd;
		}
		float getSize() const {
				return size;
		}
	private:
		ofVec2f pos, center;
		ofVec2f vertexPoints[POINTS];
		float size;
		void growMe() {
			for (int r = 0; r < GROWRATE; r++) {
				for(int i = 0; i < POINTS; i++) {
					ofPoint growVec;
					growVec =  vertexPoints[i] - center;
					vertexPoints[i] += growVec.normalized()*0.5;
				}
			}
		}
		void shrinkMe() {
			for (int r = 0; r < GROWRATE; r++) {
				for(int i = 0; i < POINTS; i++) {
					ofPoint growVec;
					growVec =  vertexPoints[i] - center;
					vertexPoints[i] -= growVec.normalized()*0.5;
				}
			}
		}
};

class planetFbo : public ofFbo {
	public:
		float getRealXPos(float input) {
			float width = input / getWidth();
			float returning = (width - (int)width) * getWidth();
			if(returning < 0) {
				returning *= -1;
			}
			return returning;
		}
		void updatePoints() {
			vector<planetShape>::iterator it = shapes.begin(), end = shapes.end();
			for (; it < end; it++) {
				it->updatePoints();
			}
		}
		void generateAttraction() {
			vector<planetShape>::iterator it = shapes.begin(), end = shapes.end();
			for (; it < end; it++) {
				const ofVec2f* points = it->getvertexPoints();
				for(int iP = 0; iP < POINTS; iP++) {
					vector<planetShape>::iterator innerIt = shapes.begin(), innerEnd = shapes.end();
					for(;innerIt < innerEnd; ++innerIt) {
						if(innerIt == it) {
							continue;
						}
						ofVec2f distVec = innerIt->getCenter() - points[iP];
						float dist = distVec.length();
						if( dist > 0 && dist < RADIUS) {
							float s = dist / RADIUS;
							float force = 1 / pow(s, .5f) -1;
							force = force / RADIUS;
							it->addToPoint(iP, distVec * force);
						}
					}
				}
			}
		}
		void paintMe() {
			vector<planetShape>::iterator it = shapes.begin(), end = shapes.end();
			updatePoints();
			generateAttraction();
			this->begin();
			ofClear(0, 0, 0, 0);
			for(;it < end; ++it) {
				ofPushStyle();
					ofSetColor(66, 154, 66);
					ofFill();
					const ofVec2f* vertexPoints = it->getvertexPoints();
					ofBeginShape();
					ofVertex(getRealXPos(vertexPoints[POINTS - 1].x), vertexPoints[POINTS - 1].y);
						for(int i = 0; i < POINTS; i++) {
							ofVertex(getRealXPos(vertexPoints[i].x), vertexPoints[i].y);
						}
						ofVertex(getRealXPos(vertexPoints[1].x), vertexPoints[1].y);
					ofEndShape();
					ofNoFill();
					ofEnableSmoothing();
						ofBeginShape();
							ofVertex(getRealXPos(vertexPoints[POINTS - 1].x), vertexPoints[POINTS - 1].y);
							for(int i = 0; i < POINTS; i++) {
								ofVertex(getRealXPos(vertexPoints[i].x), vertexPoints[i].y);
							}
							ofVertex(getRealXPos(vertexPoints[1].x), vertexPoints[1].y);
						ofEndShape();
					ofDisableSmoothing();
				ofPopStyle();
			}
			this->end();
		}
		void generateShapes(int size) {
			if(size > 5) {
				float left = size - ofRandom(size * 0.25,size);
				shapes.push_back(planetShape(getWidth(), getHeight(), left));
				generateShapes(left);
			}
			else {
				shapes.push_back(planetShape(getWidth(), getHeight(), size));
			}
		}
	private:
		vector<planetShape> shapes;
};


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
		ofPoint vertexPoints[10];
		ofPoint center;
		ofFbo fbo, fbo1, fbo2;
		planetFbo fbo3;
		int res;
		ofLight pointLight;
		ofVec3f lightPos;
};
