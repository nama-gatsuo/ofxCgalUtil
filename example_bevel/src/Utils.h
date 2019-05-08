#pragma once
#include "ofLog.h"
#include "ofUtils.h"
class ScopedTimer {
public:
	ScopedTimer(const std::string name = "") : name(name) {
		start = ofGetElapsedTimef();
		ofLogNotice(name) << "start";
	}
	~ScopedTimer() {
		float duration = ofGetElapsedTimef() - start;
		ofLogNotice(name) << "end after " << duration << " sec.";
	}
private:
	const std::string name;
	float start;
};