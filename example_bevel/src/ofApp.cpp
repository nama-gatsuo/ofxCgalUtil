#include "ofApp.h"
#include "Utils.h"

void ofApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);
	ofEnableDepthTest();

	using namespace ofxCgalUtil;

	ScopedTimer t("creation");

	base = ofMesh::box(200., 200., 200., 1, 1, 1);
	base = mergeDuplicateComponents(base);
	auto p0 = getPolyFromMesh<EPEC>(base);
	auto p1 = bevelEdgesAndVerts(p0, 10., 40.);
	result = getMeshFromPoly(p1);

}

void ofApp::update(){

}

void ofApp::draw(){
	cam.begin();
	ofSetColor(255, 0, 0);
	base.draw(OF_MESH_WIREFRAME);
	ofSetColor(255);
	result.draw(OF_MESH_WIREFRAME);
	cam.end();
}


void ofApp::keyPressed(int key){

}


