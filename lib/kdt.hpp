#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "vectors.hpp"

namespace kdt
{
	struct KDTree
	{
		KDTree();
		vecs::Vec3 position;
		int axis; // 0 pour X, 1 pour Y et 2 pour Z
		KDTree *left;
		KDTree *right;
	};
	KDTree *buildKDTree(const std::vector<vecs::Vec3> &points);
	bool compareX(vecs::Vec3 &a, vecs::Vec3 &b);
	bool compareY(vecs::Vec3 &a, vecs::Vec3 &b);
	bool compareZ(vecs::Vec3 &a, vecs::Vec3 &b);
}
