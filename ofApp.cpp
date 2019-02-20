#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofNoFill();
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());

	float radius = 180;
	auto ico_sphere = ofIcoSpherePrimitive(radius, 2);
	auto triangles = ico_sphere.getMesh().getUniqueFaces();

	for (int index = 0; index < triangles.size(); index++) {

		auto avg = glm::vec3();
		vector<glm::vec3> vertices;
		for (int j = 0; j < 3; j++) {

			glm::vec3 location(triangles[index].getVertex(j).x, triangles[index].getVertex(j).y, triangles[index].getVertex(j).z);
			vertices.push_back(location);

			avg += location;
		}
		avg /= 3;

		int noise_value = ofMap(ofNoise(avg.x * 0.002, avg.y * 0.002, avg.z * 0.002, ofGetFrameNum() * 0.01), 0, 1, 0, 9);
		float x = 400 * (noise_value % 3) + 200 - 600;
		float y = 400 * (noise_value / 3) + 200 - 600;

		ofPushMatrix();
		ofTranslate(x, y);

		ofFill();
		ofSetColor(39);

		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);

		ofNoFill();
		ofSetColor(255);

		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);

		ofPopMatrix();
	}
	
	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}