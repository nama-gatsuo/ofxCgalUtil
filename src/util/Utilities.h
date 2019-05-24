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
			return lhs.x * 1e15 + lhs.y * 1e16 + lhs.z * 1e18;
		}
	};
}

namespace ofxCgalUtil {
	
	static ofMesh transform(const ofMesh& mesh, const glm::mat4& mat) {
		ofMesh result(mesh);
		for (int i = 0; i < result.getNumVertices(); i++) {
			auto v = result.getVertex(i);
			v = mat * glm::vec4(v, 1.);
			result.setVertex(i, v);
		}
		return result;
	}

	static double areaOfTriangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2) {
		glm::vec3 a(v2 - v0), b(v1 - v0);
		float area = 0.5 * std::sqrt(glm::length2(a) * glm::length2(b) - glm::pow(glm::dot(a, b), 2.));
		return area;
	}

	static ofMesh mergeDuplicateComponents(const ofMesh& mesh) {
		
		ofLogVerbose("ofxCgalUtil::mergeDuplicateComponents") << "input_vert_num: " << mesh.getNumVertices();

		std::unordered_map<Vec, size_t> uniquePoints;
		ofMesh result;
		auto align = [](const glm::vec3& key) {
			return glm::ivec3(key * 1e3) / int(1e3);
		};

		if (mesh.getMode() == OF_PRIMITIVE_TRIANGLES) {
			int count = 0;
			for (const glm::vec3& v : mesh.getVertices()) {
				Vec cv(v);
				if (uniquePoints.find(cv) == uniquePoints.end()) {
					uniquePoints[cv] = count++;
					result.addVertex(v);
				}
			}
			for (int i : mesh.getIndices()) {
				result.addIndex(uniquePoints[Vec(mesh.getVertex(i))]);
			}
		} else if (mesh.getMode() == OF_PRIMITIVE_TRIANGLE_STRIP) {
			int count = 0;
			for (const glm::vec3& v : mesh.getVertices()) {
				
				Vec cv(align(v));
				if (uniquePoints.find(cv) == uniquePoints.end()) {
					uniquePoints[cv] = count++;
					result.addVertex(v);
				}
			}

			auto ind = mesh.getIndices();		
			
			for (auto it = ind.begin(); it != ind.end() - 2; it += 2) {
				auto v0 = Vec(align(mesh.getVertex(*(it + 0))));
				auto v1 = Vec(align(mesh.getVertex(*(it + 1))));
				auto v2 = Vec(align(mesh.getVertex(*(it + 2))));
				auto v3 = Vec(align(mesh.getVertex(*(it + 3))));

				if (areaOfTriangle(v0, v1, v2) > 1e-2) {
					result.addIndex(uniquePoints[v0]);
					result.addIndex(uniquePoints[v1]);
					result.addIndex(uniquePoints[v2]);
				}

				if (areaOfTriangle(v1, v3, v2) > 1e-2) {
					result.addIndex(uniquePoints[v1]);
					result.addIndex(uniquePoints[v3]);
					result.addIndex(uniquePoints[v2]);
				}
			}
		} else {
			ofLogWarning("ofxCgalUtil") << "Unsupported PrimitiveType";
		}

		ofLogVerbose("ofxCgalUtil::mergeDuplicateComponents") << "output_vert_num: " << result.getNumVertices();

		return result;
	}
	
	

};
