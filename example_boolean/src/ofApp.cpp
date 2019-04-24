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
	auto sphere1P(Converter::mesh_to_poly<Kernel_NT>(sphere1));
	Nef_Polyhedron sphere1NP(sphere1P);
	
	ofMesh sphere2;
	sphere2.load("sphere.ply");
	glm::mat4 m2 = glm::translate(glm::vec3(0., -40, 0));
	for (int i = 0; i < sphere2.getNumVertices(); i++) {
		auto v = sphere2.getVertex(i);
		v = m2 * glm::vec4(v, 1.);
		sphere2.setVertex(i, v);
	}
	auto sphere2P(Converter::mesh_to_poly<Kernel_NT>(sphere2));
	Nef_Polyhedron sphere2NP(sphere2P);
	
	BoolOp b;
	Nef_Polyhedron resNP = b.run(sphere1P, sphere2P, BoolOp::BOOL_OP_INTERSECTION);

	Polyhedron_NT resP;
	resNP.convert_to_polyhedron(resP);

	result = Converter::poly_to_mesh(resP);


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


