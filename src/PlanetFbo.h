/*
 * PlanetFbo.h
 *
 *  Created on: Sep 4, 2012
 *      Author: faebser
 */



#ifndef PLANETFBO_H_
#define PLANETFBO_H_

#define GROWRATE 20
#define UPDATERATE 100
#define ALPHA 140
#define RADIUS 250

#include "ofMain.h"
#include "PlanetShape.h"

class PlanetFbo : public ofFbo {
public:
	PlanetFbo();
	float getRealXPos(float input);
	void updatePoints();
	void generateAttraction();
	void paintMe();
	void paintMeShapes();
	void paintMeLines();
	void generateShapes(int size);
	string getType() const;
	void setType(string type);
	ofColor getColor() const;
	ofColor getColorWithMaxAlpha() const;
	void setColor(ofColor color);
	virtual ~PlanetFbo();
private:
	vector<PlanetShape> shapes;
	string type;
	ofColor colorWithMaxAlpha, color;
};

#endif /* PLANETFBO_H_ */
