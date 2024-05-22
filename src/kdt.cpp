#include "kdt.hpp"

namespace kdt
{
	KDTree::KDTree() : position(vecs::Vec3()), axis(0), left(nullptr), right(nullptr) {}
	bool compareX(vecs::Vec3 &a, vecs::Vec3 &b)
	{
		return a.X < b.X;
	}
	bool compareY(vecs::Vec3 &a, vecs::Vec3 &b)
	{
		return a.Y < b.Y;
	}
	bool compareZ(vecs::Vec3 &a, vecs::Vec3 &b)
	{
		return a.Z < b.Z;
	}
	KDTree *buildKDTree(const std::vector<vecs::Vec3> &points)
	{
		if (points.empty())
		{
			std::cerr << "Erreur: il n'y a aucun points à traier" << std::endl;
			return nullptr;
		}
		else if (points.size() == 1)
		{
			// Seulement un point donc un fait une feuille
			KDTree *kdtree = new KDTree();
			kdtree->position = points[0];
			kdtree->left = nullptr;
			kdtree->right = nullptr;
			return kdtree;
		}

		int axis = 0;
		for (int i = 0; i < 3; i += 1)
		{
			float varianceX = 0.0f;
			float varianceY = 0.0f;
			float varianceZ = 0.0f;
			for (const vecs::Vec3 &point : points)
			{
				varianceX += (point.X) * (point.X);
				varianceY += (point.Y) * (point.Y);
				varianceZ += (point.Z) * (point.Z);
			}
			varianceX /= points.size();
			varianceY /= points.size();
			varianceZ /= points.size();

			float maxVar = std::max(std::max(varianceX, varianceY), varianceZ);

			if (maxVar == varianceX)
			{
				axis = 0;
			}
			else if (maxVar == varianceY)
			{
				axis = 1;
			}
			else
			{
				axis = 2;
			}
		}

		std::vector<vecs::Vec3> sortedPoints = points;
		if (axis == 0)
		{
			std::sort(sortedPoints.begin(), sortedPoints.end(), compareX);
		}
		else if (axis == 1)
		{
			std::sort(sortedPoints.begin(), sortedPoints.end(), compareY);
		}
		else
		{
			std::sort(sortedPoints.begin(), sortedPoints.end(), compareZ);
		}

		KDTree *kdtree = new KDTree();
		kdtree->position = sortedPoints[sortedPoints.size() / 2];
		kdtree->axis = axis;
		kdtree->left = buildKDTree(std::vector<vecs::Vec3>(sortedPoints.begin(), sortedPoints.begin() + sortedPoints.size() / 2));
		kdtree->right = buildKDTree(std::vector<vecs::Vec3>(sortedPoints.begin() + sortedPoints.size() / 2 + 1, sortedPoints.end()));
		return kdtree;
	}

	bool isPointInsideTriangle(const vecs::Vec3 &point, const vecs::Vec3 &v0, const vecs::Vec3 &v1, const vecs::Vec3 &v2)
	{
		vecs::Vec3 edge0 = v1 - v0;
		vecs::Vec3 edge1 = v2 - v1;
		vecs::Vec3 edge2 = v0 - v2;

		vecs::Vec3 c0 = vecs::crossV3(edge0, point - v0);
		vecs::Vec3 c1 = vecs::crossV3(edge1, point - v1);
		vecs::Vec3 c2 = vecs::crossV3(edge2, point - v2);

		return vecs::dotV3(c0, c1) >= 0 && vecs::dotV3(c1, c2) >= 0 && vecs::dotV3(c2, c0) >= 0;
	}

	bool sphereTriangleCollision(const vecs::Vec3 &sphereCenter, const float sphereRadius, const vecs::Vec3 &v0, const vecs::Vec3 &v1, const vecs::Vec3 &v2)
	{
		vecs::Vec3 normal = vecs::crossV3(v1 - v0, v2 - v0);
		float distance = normal.norm();
		if (distance > sphereRadius || distance < -sphereRadius)
		{
			return false;
		}
		vecs::Vec3 projectedPoint = sphereCenter - (normal * distance);

		if (!isPointInsideTriangle(projectedPoint, v0, v1, v2))
		{
			return false;
		}

		float distanceSquared = (sphereCenter - projectedPoint).norm() * (sphereCenter - projectedPoint).norm();
		return distanceSquared <= (sphereRadius * sphereRadius);
	}
}