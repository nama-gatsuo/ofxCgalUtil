#include "ofApp.h"

void ofApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);

	ofMesh m0 = ofMesh::box(200., 200., 200., 1, 1, 1);
	m0 = ofxCgalUtil::mergeDuplicateComponents(m0);
	auto p0 = ofxCgalUtil::getPolyFromMesh<ofxCgalUtil::EPEC>(m0);
	result = ofxCgalUtil::getMeshFromPoly(ofxCgalUtil::bevelAllEdges(p0, 40.));
	
	ofEnableDepthTest();
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


