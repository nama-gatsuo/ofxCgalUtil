#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);

	using namespace ofxCgalUtil;

	ofMesh m0 = mergeDuplicateComponents(ofMesh::sphere(80., 12));
	auto np0 = getNefPolyFromMesh(m0);

	ofMesh m1 = mergeDuplicateComponents(ofMesh::cylinder(50., 200., 12, 1));
	m1 = transform(m1, glm::rotate(float(HALF_PI), glm::vec3(1., 0., 0.)));
	auto np1 = getNefPolyFromMesh(m1);

	ofMesh m2 = mergeDuplicateComponents(ofMesh::cylinder(50., 200., 12, 1));
	auto np2 = getNefPolyFromMesh(m2);

	ofMesh m3 = mergeDuplicateComponents(ofMesh::cylinder(50., 200., 12, 1));
	m3 = transform(m3, glm::rotate(float(HALF_PI), glm::vec3(0., 0., 1.)));
	auto np3 = getNefPolyFromMesh(m3);

	auto resultNp = np0 - (np1 + np2 + np3);
	results.push_back(getMeshFromNefPoly(resultNp));
	edges.push_back(getPolyFromMesh<EPIC>(results[0]));
	
	resultNp = (np1 + np2 + np3) * np0;
	results.push_back(getMeshFromNefPoly(resultNp));
	edges.push_back(getPolyFromMesh<EPIC>(results[1]));
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofEnableDepthTest();

	cam.begin();
	for (int i = 0; i < results.size(); i++) {
		ofPushMatrix();
		ofTranslate((float(i) - 0.5) * 200., 0, 0);

		ofSetColor(255);
		results[i].draw();

		ofScale(1.001);
		ofSetColor(0);
		ofxCgalUtil::drawEdges(edges[i]);
		
		ofPopMatrix();
	}
	cam.end();
	
	ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}


