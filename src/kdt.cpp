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
}