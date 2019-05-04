#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);

	ofMesh m0 = ofMesh::sphere(80.);
	m0 = ofxCgalUtil::mergeDuplicateComponents(m0);
	
	ofMesh m1 = ofMesh::cylinder(30., 300., 12, 1);
	m1 = ofxCgalUtil::mergeDuplicateComponents(m1);
	m1 = ofxCgalUtil::transform(m1, glm::rotate(float(HALF_PI), glm::vec3(0., 0., 1.)));

	result = ofxCgalUtil::booleanOperation(m0, m1, ofxCgalUtil::BOOL_OP_DIFFERENCE);
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();
	result.draw(OF_MESH_WIREFRAME);
	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}


