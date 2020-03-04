//--------------------------------------------------------------
//
// This is a simple first OpenFrameworks lab to practice how to draw
// a primitive (such as a triangle), select it and drag/rotate it
// around in the viewport with the mouse.  The exercise illustrates
// a few key concepts that will prove to be useful later in our 
// journey
// (1) How to do simple 2D intersection testing on triangles.
// (2) How to compute a 2D rotation transformation manually using 
//     trig functions (the rotation matrix).
// (3) How to use the glm::vec3 class for simple point/vector ops
// (4) The concept of a local coordinate system around a shape (triangle) 
//     which can translated to any arbitrary position and rotated
//     about it's origin.
// (5) Using basic callbacks in OF.
//   
//  (c) Kevin M. Smith - 2019 

#include "ofApp.h"

void Triangle::draw() {

		//if (bSelected) ofSetColor(ofColor::lightGray);
		//else ofSetColor(ofColor::blue);
		//ofSetColor(ofColor::blue);
		//ofPushMatrix();

		//ofMultMatrix(getMatrix());
		//ofDrawTriangle(verts[0], verts[1], verts[2]);
		//ofPopMatrix();
	
	
}

//    Given x in pixel coordinates, return (x, y, z) on the sin wave
//    Note that "z" is not used, so it is set to "0".
//    scale - scales the curve in Y  (the amplitude)
//    cycles - number of cycles in sin wave.
//
	glm::vec3 Triangle::curveEval(float x, float scale, float cycles){
		// x is in screen coordinates and his in [0, WindowWidth]
		float u = (cycles * x * PI) / ofGetWidth();
		return (glm::vec3(x, -scale * sin(u) + (ofGetHeight() / 2), 0));
	}


glm::mat4 Triangle::getMatrix() {
	glm::mat4 m = glm::translate(glm::mat4(1.0), glm::vec3(pos));
	glm::mat4 M = glm::rotate(m, glm::radians(angel), glm::vec3(0, 0, 1));
	return M;
}


// Determine if point p is inside the triangle shape. Method is the simplest 
// way but not necessarily the most efficent.  We look at the sign of the angles
// between the vectors connecting p and the three triangle vertices. They each
// have to be ( < 0 ) for the point to be inside.  Note: glm::orientedAngle
// will provide a signed angle if you supply an orientation vector (in this case Z axis).
//
bool Triangle::inside(glm::vec3 p) {
	//p2 is new postion after rotate.
	glm::vec3 p2 = glm::inverse(getMatrix()) * glm::vec4(p, 1);

	glm::vec3 v1 = glm::normalize(verts[0] - p2);
	glm::vec3 v2 = glm::normalize(verts[1] - p2);
	glm::vec3 v3 = glm::normalize(verts[2] - p2);
	float a1 = glm::orientedAngle(v1, v2, glm::vec3(0, 0, -1));
	float a2 = glm::orientedAngle(v2, v3, glm::vec3(0, 0, -1));
	float a3 = glm::orientedAngle(v3, v1, glm::vec3(0, 0, -1));
	if (a1 < 0 && a2 < 0 && a3 < 0) return true;
	else return false;
}

//--------------------------------------------------------------
void ofApp::setup() {
	tri.pos = glm::vec3(ofGetWidth() / 2.0, ofGetHeight() / 2.0, 0);

	// Exam;ple on how to add elements to a vector<>
	// Store the vertices to the triangle relative to origin (0, 0, 0);
	// The triangle is moveable in that we add these vertices to it's
	// position to get screen space coordinates (for drawing).
	//
	tri.verts.push_back(glm::vec3(-25, -25, 0));
	tri.verts.push_back(glm::vec3(0, 50, 0));
	tri.verts.push_back(glm::vec3(25, -25, 0));

	ofSetBackgroundColor(ofColor::black);

	image.load("dog5.png");

	ofSetVerticalSync(true);

	// we add this listener before setting up so the initial circle resolution is correct
	//Scale.addListener(this, &Triangle::curveEval);
	//Cycles.addListener(this, &Triangle::curveEval);
	//Speed.addListener
	gui.setup(); // most of the time you don't need a name
	
	gui.add(Scale.setup("Scale", 140, 10, 300));
	gui.add(Cycles.setup("Cycles",4, 2, 12));
	gui.add(Speed.setup("Speed", 100, 10, 150));
	gui.add(UseImage.setup("Use Image", false));
	gui.add(DrawPath.setup("Draw Path", true));
	gui.add(screenSize.setup("screen size", ofToString(ofGetWidth()) + "x" + ofToString(ofGetHeight())));


	bHide = false;

}

//--------------------------------------------------------------
void ofApp::update() {
 	if (startAnim) {
		v = Speed*0.1;
		step += v;
		if (step > ofGetWidth()) {
			step = 0;
		}
		glm::vec3 cur = tri.curveEval(step,Scale, Cycles);
		orientation = glm::vec3(0, tri.pos.y, 0);
		
		glm::vec3 heading = cur - tri.pos;
		
		float dot = glm::dot(heading, orientation);
		float nor = glm::length(heading) * glm::length(orientation);
		float rot = glm::acos(dot / nor);

		tri.angel = -glm::degrees(rot);
		cout << rot << endl;
		tri.pos = cur;
		
		
	}
	
}

//--------------------------------------------------------------
void ofApp::draw() {
	

	if (UseImage) {
		ofPushMatrix();
		ofMultMatrix(tri.getMatrix());
		image.draw(0,0 ,80, 80);
		ofPopMatrix();
		
	}
	else {
		ofPushMatrix();
		ofMultMatrix(tri.getMatrix());
		ofDrawTriangle(tri.verts[0], tri.verts[1], tri.verts[2]);
		ofPopMatrix();
		tri.draw();
	}
	
	//  Test curveEval() Function
	//
	if (DrawPath) {
		for (int i = 0; i < ofGetWidth(); i++) {
			glm::vec3 p = tri.curveEval(i, Scale, Cycles);
			ofDrawCircle(p.x, p.y, 1);
			//ofSetColor(ofColor::purple);
		}
	}
	
	if (!bHide) {
		gui.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	switch (key) {
	case 'f':
		bFullscreen = !bFullscreen;
		ofSetFullscreen(bFullscreen);
		break;
	case OF_KEY_CONTROL:
		bCtrlKeyDown = true;
		break;
	case ' ':
		startAnim = !startAnim;
		break;
	case 'h':
		bHide = !bHide;
		break;
	default:
		break;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key) {
	case OF_KEY_CONTROL:
		bCtrlKeyDown = false;
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

	if (!tri.bSelected) {
		return;
	}
	glm::vec3 mousePoint = glm::vec3(x, y, 0);

	if (bCtrlKeyDown) {
		tri.angel += x - lastMouse.x;
	}
	else {
		tri.pos += mousePoint - lastMouse;
	}

	lastMouse = mousePoint;

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (tri.inside(glm::vec3(x, y, 0))) {
		tri.bSelected = true;
		bInDrag = true;
		mouseDown = glm::vec3(x, y, 0);
		lastMouse = mouseDown;
	}
	else {
		tri.bSelected = false;
		bInDrag = false;
	}

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	tri.bSelected = false;
	bInDrag = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}