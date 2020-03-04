#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Triangle {
public:
	
	void draw();

	bool inside(glm::vec3 p);

	glm::mat4 getMatrix();

	glm::vec3 curveEval(float x, float scale, float cycles);

	// triangle data
	vector<glm::vec3> verts;
	glm::vec3 pos;
	float angel = 0;
	bool bSelected = false;
	bool useImage = false;


};



class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	



	// application data

	glm::vec3 lastMouse;   // location of where mouse moved last (when dragging)
	glm::vec3 mouseDown;
	glm::vec3 orientation;

	// UI control data
	//
	bool bFullscreen = false;
	bool bCtrlKeyDown = false;
	bool bInDrag = false;


	// create one triangle
	//
	Triangle tri;

	bool startAnim = false;

	int step = 0;
	int v;

	bool bHide;

	ofxFloatSlider Scale;
	ofxFloatSlider Cycles;
	ofxIntSlider Speed;
	ofxToggle UseImage;
	ofxToggle DrawPath;
	ofxLabel screenSize;
	ofxPanel gui;
	ofImage image;
	glm::vec3 posOfImage;


};
