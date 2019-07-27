#pragma once

#include "ofMain.h"
#include "ofxCgalUtil.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
public:
	ofEasyCam cam;
	std::vector<std::vector<ofVboMesh>> results;
	std::vector<std::vector<ofxCgalUtil::Polyhedron<ofxCgalUtil::EPIC>>> polys;
};
