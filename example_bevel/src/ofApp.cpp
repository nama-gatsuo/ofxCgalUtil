#include "ofApp.h"

void ofApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);

	ofMesh m0 = ofMesh::box(200., 200., 200.);
	m0 = ofxCgalUtil::mergeDuplicateComponents(m0);
	
	auto p0 = ofxCgalUtil::getPolyFromMesh<ofxCgalUtil::EPIC>(m0);
	
	//ofxCgalUtil::bevelEdge(p0, p0.vertices_begin(), 20.);

	result = ofxCgalUtil::getMeshFromNefPoly(p0);
	
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


