#pragma once

#include "vectors.hpp"
#include <sstream>
#include <fstream>
#include <iostream>

namespace objl
{
	struct Face
	{
		std::vector<int> vertexIndices;
		std::vector<int> vertexNormals; // somme des normales de chaque sommet qui compose la face triangle
	};
	struct Loader
	{
		// Le chargeur de fichier obj
		Loader();
		std::vector<vecs::Vec3> vertices;
		std::vector<vecs::Vec3> normals;
		std::vector<Face> faces;
		void load(const std::string &fileame);
	};
}