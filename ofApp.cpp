#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(300, 4);
	this->triangle_list.insert(this->triangle_list.end(), ico_sphere.getMesh().getUniqueFaces().begin(), ico_sphere.getMesh().getUniqueFaces().end());

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();
	this->frame.clear();

	for (int radius = 150; radius < 300; radius += 5) {

		for (int i = 0; i < this->triangle_list.size(); i++) {

			glm::vec3 avg = (this->triangle_list[i].getVertex(0) + this->triangle_list[i].getVertex(1) + this->triangle_list[i].getVertex(2)) / 3;
			auto noise_value = ofNoise(avg.y * 0.005 + ofGetFrameNum() * 0.035, avg.x * 0.005, avg.z * 0.005);

			if (noise_value < 0.4 || noise_value > 0.6) { continue; }

			vector<glm::vec3> vertices;

			vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(0)) * radius);
			vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(1)) * radius);
			vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(2)) * radius);

			this->mesh.addVertices(vertices);
			this->frame.addVertices(vertices);

			for (int k = 0; k < vertices.size(); k++) {

				this->mesh.addColor(ofColor(ofMap(radius, 150, 300, 255, 0)));
				this->frame.addColor(ofColor(ofMap(radius, 150, 300, 255, 0)));
			}

			this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 3);

			this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 2);
			this->frame.addIndex(this->frame.getNumVertices() - 2); this->frame.addIndex(this->frame.getNumVertices() - 3);
			this->frame.addIndex(this->frame.getNumVertices() - 3); this->frame.addIndex(this->frame.getNumVertices() - 1);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());

	this->mesh.draw();
	this->frame.drawWireframe();

	ofSetColor(255);
	ofDrawSphere(50);

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}