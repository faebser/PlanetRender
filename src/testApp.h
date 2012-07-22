#pragma once
#define POINTS 10
#include "ofMain.h"

class planetShape {
	public:
		void updatePoints() {
			for(int i = 0; i < POINTS; i++) {
				vertexPoints[i].set(vertexPoints[i].x + ofRandom(-1, 1), vertexPoints[i].y + ofRandom(-1, 1));
			}
			center.set(center.x + ofRandom(-1.5,1.5), center.y + ofRandom(-1.5, 1.5));
		}
		ofVec2f getCenter() const {
				return center;
		}

		void setCenter(ofVec2f center) {
			this->center = center;
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
	private:
		ofVec2f pos, center;
		ofVec2f vertexPoints[POINTS];
};

class planetFbo : public ofFbo {
	public:
		float getRealXPos(float input) {
			float width = input / getWidth();
			return (width - (int)width) * getWidth();
		}
		void updatePoints() {
			vector<planetShape>::iterator it = shapes.begin(), end = shapes.end();
			for (; it < end; it++) {
			}
		}
		void generateAttraction() {
			vector<planetShape>::iterator it = shapes.begin(), end = shapes.end();
			for (; it < end; it++) {

			}
		}
		void paintMe() {
			updatePoints();
			generateAttraction();
			begin();

			end();
		}
		void generateShapes(int size) {

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
};
