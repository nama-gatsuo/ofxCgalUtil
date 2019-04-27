#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofMesh m0 = ofMesh::cylinder(100., 100);
	m0 = ofxCgalUtil::mergeDuplicateComponents(m0);
	m0 = ofxCgalUtil::transform(m0, glm::translate(glm::vec3(0., 40, 0)));
	
	ofMesh m1 = ofMesh::box(120., 500, 40);
	m1 = ofxCgalUtil::mergeDuplicateComponents(m1);
	m1 = ofxCgalUtil::transform(m1, glm::translate(glm::vec3(0., -40, 0)));

	result = ofxCgalUtil::booleanOperation(m0, m1, ofxCgalUtil::BOOL_OP_UNION);
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


