#include "ofApp.h"

void ofApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);
	//cam.enableOrtho();

	using namespace ofxCgalUtil;

	/// * Get Box as Primitive is triangle
	// ofMesh m0 = mergeDuplicateComponents(ofMesh::box(80., 80., 80, 1, 1, 1));
	// auto& p = getPolyFromMesh<EPIC>(m0);
	/// * Get Box as Primitive is quadrilateral
	// auto& p = getPlatonicSolid<EPIC>(PolyhedronData::BOX, 80);
	
	polys.assign(3, std::vector<Polyhedron<EPIC>>());
	results.assign(3, std::vector<ofVboMesh>());

	for (int i = 0; i < 3; i++) {
		int depth = i + 1;

		auto& p0 = getPlatonicSolid<EPIC>(PolyhedronData::BOX, 80);
		auto& p1 = getPlatonicSolid<EPIC>(PolyhedronData::BOX, 80);
		auto& p2 = getPlatonicSolid<EPIC>(PolyhedronData::BOX, 80);

		subdivide(p0, CATMULL_CLARK, depth);
		subdivide(p1, DOOSABIN, depth);
		subdivide(p2, SQRT3, depth);

		polys[i].push_back(p0);
		polys[i].push_back(p1);
		polys[i].push_back(p2);

		results[i].push_back(getMeshFromPoly(p0));
		results[i].push_back(getMeshFromPoly(p1));
		results[i].push_back(getMeshFromPoly(p2));
	}
	
}

void ofApp::update(){

}

void ofApp::draw(){

	ofEnableDepthTest();
	
	cam.begin();
	for (int d = 0; d < 3; d++) {
		for (int i = 0; i < 3; i++) {
			ofPushMatrix();
			ofTranslate(100. * (i - 1), 100 * (1 - d), 0);

			ofSetColor(255);
			results[d][i].draw();

			ofScale(1.001);
			ofSetColor(0);
			ofxCgalUtil::drawEdges(polys[d][i]);
			ofPopMatrix();
		}
	}
	cam.end();

	ofDisableDepthTest();
}

void ofApp::keyPressed(int key){

}


