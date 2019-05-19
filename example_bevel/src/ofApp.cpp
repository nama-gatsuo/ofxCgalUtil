#include "ofApp.h"
#include "Utils.h"

void ofApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);
	
	using namespace ofxCgalUtil;

	//ScopedTimer t("creation");

	ofMesh m0 = ofMesh::box(200., 200., 200., 1, 1, 1);
	m0 = mergeDuplicateComponents(m0);
	auto p0 = getPolyFromMesh<EPEC>(m0);
	auto p1 = bevelAllVertices(p0, 40., true);
	result = getMeshFromPoly(bevelEdges(p0, 10.));
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


