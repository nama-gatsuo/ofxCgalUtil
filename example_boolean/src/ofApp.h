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
	std::vector<ofMesh> results;
	std::vector<ofxCgalUtil::Polyhedron<ofxCgalUtil::EPIC>> edges;
};
