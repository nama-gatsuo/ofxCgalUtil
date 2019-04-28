#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);

	ofMesh m0 = ofMesh::sphere(80.);
	m0 = ofxCgalUtil::mergeDuplicateComponents(m0);
	//m0 = ofxCgalUtil::transform(m0, glm::translate(glm::vec3(0., 40, 0)));
	
	ofMesh m1 = ofMesh::cylinder(10., 300., 12, 1);
	m1 = ofxCgalUtil::mergeDuplicateComponents(m1);
	m1 = ofxCgalUtil::transform(m1, glm::rotate(float(HALF_PI), glm::vec3(0., 0., 1.)));

	ofMesh m2 = ofMesh::cylinder(10., 300., 12, 1);
	m2 = ofxCgalUtil::mergeDuplicateComponents(m2);

	ofMesh m3 = ofMesh::cylinder(10., 300., 12, 1);
	m3 = ofxCgalUtil::mergeDuplicateComponents(m1);
	m3 = ofxCgalUtil::transform(m1, glm::rotate(float(HALF_PI), glm::vec3(0., 0., 1.)));

	result = ofxCgalUtil::booleanOperation(m0, m1, ofxCgalUtil::BOOL_OP_DIFFERENCE);
	//result = ofxCgalUtil::booleanOperation(result, m2, ofxCgalUtil::BOOL_OP_DIFFERENCE);
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


