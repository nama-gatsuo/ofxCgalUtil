#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofMesh sphere1;
	sphere1.load("sphere.ply");
	glm::mat4 m = glm::translate(glm::vec3(0., 40, 0));
	for (int i = 0; i < sphere1.getNumVertices(); i++) {
		auto v = sphere1.getVertex(i);
		v = m * glm::vec4(v, 1.);
		sphere1.setVertex(i, v);
	}
	
	ofMesh aa = ofMesh::icosahedron(10.);
	glm::mat4 m2 = glm::translate(glm::vec3(0., -80, 0));
	for (int i = 0; i < aa.getNumVertices(); i++) {
		auto v = aa.getVertex(i);
		v = m2 * glm::vec4(v, 1.);
		aa.setVertex(i, v);
	}

	result = ofxCgalUtil::booleanOperation(sphere1, aa, ofxCgalUtil::BOOL_OP_COMPLEMENT);

	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();
	result.draw(OF_MESH_WIREFRAME);
	base.draw(OF_MESH_WIREFRAME);
	cam.end();


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}


