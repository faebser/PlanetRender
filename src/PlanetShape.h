/*
 * PlanetShape.h
 *
 *  Created on: Sep 4, 2012
 *      Author: faebser
 */

#ifndef PLANETSHAPE_H_
#define PLANETSHAPE_H_

#define POINTS 6
#define GROWRATE 20
#define UPDATERATE 100
#define ALPHA 140

#include "ofMain.h"

class PlanetShape {
public:
	PlanetShape();
	PlanetShape(float width, float height, float size, string type);
	void updatePoints();
	void updateLines();
	ofVec2f getCenter() const;
	void setCenter(ofVec2f center);
	void grow(int newSize);
	void shrink(int newSize);
	const ofVec2f* getvertexPoints() const;
	ofVec2f getPos() const ;
	void setPos(ofVec2f pos);
	void addToPoint(int pointIndex, ofVec2f toAdd);
	float getSize() const;
	virtual ~PlanetShape();
private:
	ofVec2f pos, center;
	ofVec2f vertexPoints[POINTS];
	float size;
	void growMe();
	void shrinkMe();
};

#endif /* PLANETSHAPE_H_ */
