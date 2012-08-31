#pragma once
#define POINTS 6
#define RADIUS 250
#define GROWRATE 20
#define UPDATERATE 100
#define ALPHA 128
#include "ofMain.h"

class planetShape {
	public:
		planetShape(float width, float height, float size, string type) {
			if(type == "shape") {
				center = ofVec2f(ofRandom(0, width), ofRandom(0, height));
				float angle = ofDegToRad(360 / POINTS);
				for(int i = 0; i < POINTS; i++) {
						float x = cos(angle * i) * 25;
						float y = sin(angle * i) * 25;
						ofVec2f newPoint = ofVec2f(x,y) + center;
						vertexPoints[i] = newPoint;
						this->size = size;
						for(int i = 0; i <= size; i++) {
							growMe();
						}
				}
			}
			else if(type == "line") {
				float step = (float)1 / (POINTS/2);
				ofVec2f start = ofVec2f(0, ofRandom(0, height));
				ofVec2f end = ofVec2f(width, start.y);
				vertexPoints[0] = start;
				for(int i = 1; i < POINTS-1; i++) {
					ofVec2f newPoint = start.interpolate(end, step);
					vertexPoints[i] = newPoint;
				}
				vertexPoints[POINTS-1] = end;
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
		void updateLines() {
			for (int change = 0; change < UPDATERATE; change++) {
				for(int i = 0; i < POINTS; i++) {
					vertexPoints[i].set(vertexPoints[i].x, vertexPoints[i].y + ofRandom(-3, 3));
				}
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
				shrinkMe();
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
			if(type == "shape") {
				for (; it < end; it++) {
					it->updatePoints();
				}
			}
			else if(type == "line") {
				for (; it < end; it++) {
					it->updateLines();
				}
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
			if (type == "shape") {
				paintMeShapes();
			}
			else if(type == "line") {
				paintMeLines();
			}
		}
		void paintMeShapes() {
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
		void paintMeLines() {
			vector<planetShape>::iterator it = shapes.begin(), end = shapes.end();
			ofSetColor(255);
			ofClear(0,0,0,0);
			updatePoints();
			this->begin();
			for(;it < end; ++it) {
				ofPushStyle();
				ofPushMatrix();
					const ofVec2f* vertexPoints = it->getvertexPoints();
					float randomX = 0;
					if(ofRandom(1) > 0.5) {
						randomX = ofRandom(-10, this->getWidth()-vertexPoints[POINTS-2].x);
					}
					else {
						randomX = ofRandom(-10, vertexPoints[1].x)*-1;
					}
					ofTranslate(randomX, 0);
					ofEnableSmoothing();
					ofSetColor(color);
					ofBeginShape();
						for(int i = 0; i < POINTS; i++) {
							ofCurveVertex(vertexPoints[i].x, vertexPoints[i].y);
						}
					ofEndShape();
					ofDisableSmoothing();
				ofPopMatrix();
				ofPopStyle();
			}
			this->end();
		}
		void generateShapes(int size) {
			if(type == "shape") {
				if(size > 5) {
					float left = size - ofRandom(size * 0.25,size);
					shapes.push_back(planetShape(getWidth(), getHeight(), left, type));
					generateShapes(left);
				}
				else {
					shapes.push_back(planetShape(getWidth(), getHeight(), size, type));
				}
			}
			else if(type == "line") {
				for(int i = 0; i < size; i++) {
					shapes.push_back(planetShape(getWidth(), getHeight(), size, type));
				}
			}
		}
		string getType() const {
			return type;
		}

		void setType(string type) {
			this->type = type;
		}
		ofColor getColor() const {
			return color;
		}
		ofColor getColorWithMaxAlpha() const {
			return colorWithMaxAlpha;
		}
		void setColor(ofColor color) {
			this->color = color;
			this->colorWithMaxAlpha = color;
			this->colorWithMaxAlpha.a = 255;
			this->color.a = ALPHA;
		}
	private:
		vector<planetShape> shapes;
		string type;
		ofColor colorWithMaxAlpha, color;
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
		ofTexture text;
		ofPoint vertexPoints[10];
		ofPoint center;
		planetFbo fbo3, fbo4;
		int res;
		ofLight pointLight;
		ofVec3f lightPos;
};
