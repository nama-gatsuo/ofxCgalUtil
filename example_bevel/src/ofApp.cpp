#include "ofApp.h"

void ofApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);
	using namespace ofxCgalUtil;

	ofMesh m0 = ofMesh::box(200., 200., 200., 1, 1, 1);
	m0 = mergeDuplicateComponents(m0);
	auto p0 = getPolyFromMesh<EPEC>(m0);	
	result = getMeshFromPoly(bevelAllVertices(p0, 40., true));
	
}

void ofApp::update(){

}

void ofApp::draw(){
	cam.begin();
	result.draw(OF_MESH_WIREFRAME);
	cam.end();
}


void ofApp::keyPressed(int key){

}


