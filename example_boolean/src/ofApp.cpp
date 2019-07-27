#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);

	using namespace ofxCgalUtil;
	// Boolean operaion is only available on NefPolyhedron objects
	// For more detail, see API specification https://doc.cgal.org/latest/Nef_3/index.html
	//
	// Since boolean op need NefPolyhedron, we have to convert ofMesh into NefPolyhedron object.
	// What is annoying is that NefPolyhedron and Polyhedon in CGAL can't be apply boolean operation
	// when mesh has duplicated components and crossed faces or edges.
	// So we need pre-process to avoid above.
	
	// Prepare meshes which have no duplicate components (vertices)
	ofMesh m0, m1, m2, m3;
	m0 = mergeDuplicateComponents(ofMesh::sphere(80., 12));
	
	m1 = mergeDuplicateComponents(ofMesh::cylinder(50., 200., 12, 1));
	m1 = transform(m1, glm::rotate(float(HALF_PI), glm::vec3(1., 0., 0.)));
	
	m2 = mergeDuplicateComponents(ofMesh::cylinder(50., 200., 12, 1));
	
	m3 = mergeDuplicateComponents(ofMesh::cylinder(50., 200., 12, 1));
	m3 = transform(m3, glm::rotate(float(HALF_PI), glm::vec3(0., 0., 1.)));

	// Convert mesh to NefPolyhdeon object
	auto np0 = getNefPolyFromMesh(m0);
	auto np1 = getNefPolyFromMesh(m1);
	auto np2 = getNefPolyFromMesh(m2);
	auto np3 = getNefPolyFromMesh(m3);

	// Fun part is here!
	// We can use math operators which stand for boolean operaton
	auto result0 = np0 - (np1 + np2 + np3);
	auto result1 = (np1 + np2 + np3) * np0;

	// Store both ofMesh and Polyhedron to draw edges
	results.push_back(getMeshFromNefPoly(result0));
	edges.push_back(getPolyFromMesh<EPIC>(results[0]));
	
	results.push_back(getMeshFromNefPoly(result1));
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


