#pragma once
#include "ofMesh.h"
#include <map>

namespace ofxCgalUtil {
	class Vec : public glm::vec3 {
	public:
		Vec() : glm::vec3() {}
		Vec(float x, float y, float z) : glm::vec3(x, y, z) {}
		Vec(const glm::vec3& p) : glm::vec3(p) {}
		bool operator==(const glm::vec3& lhs) {
			return glm::all(glm::equal(*this, lhs));
		}
	};
}

namespace std {
	template<>
	class hash<ofxCgalUtil::Vec> {
	public:
		size_t operator()(const ofxCgalUtil::Vec& lhs) const {
			return lhs.x * 10000 + lhs.y * 100000 + lhs.z * 1000000;
		}
	};
}

namespace ofxCgalUtil {
	
	static ofMesh mergeDuplicateComponets(const ofMesh& mesh) {
		
		std::unordered_map<Vec, int> uniquePoints;
		
		ofMesh result;

		int count = 0;
		for (const glm::vec3& v : mesh.getVertices()) {
			Vec cv(v);
			if (uniquePoints.find(cv) == uniquePoints.end()) {
				uniquePoints[cv] = count;
				result.addVertex(cv);
				count++;
			}
		}

		std::vector<int> newIndices;
		for (int i : mesh.getIndices()) {
			const glm::vec3& v = mesh.getVertex(i);
			result.addIndex(uniquePoints[Vec(v)]);
		}

		return result;
	}

	static ofMesh transform(const ofMesh& mesh, const glm::mat4& mat) {
		ofMesh result(mesh);
		for (int i = 0; i < result.getNumVertices(); i++) {
			auto v = result.getVertex(i);
			v = mat * glm::vec4(v, 1.);
			result.setVertex(i, v);
		}
		return result;
	}

};
