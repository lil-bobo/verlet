#include "loader.hpp"

namespace objl
{
	Loader::Loader() {}
	void Loader::load(const std::string &fileame)
	{
		std::ifstream objfile(fileame);
		if (!objfile)
		{
			std::cerr << "Impossible de trouver le fichier obj" << std::endl;
		}
		else
		{
			std::string line;
			while (std::getline(objfile, line))
			{
				std::istringstream iss(line);
				std::string prefix;
				iss >> prefix;
				if (prefix == "v")
				{
					vecs::Vec3 vertex;
					iss >> vertex.X >> vertex.Z >> vertex.Y;
					this->vertices.push_back(vertex);
				}
				else if (prefix == "vn")
				{
					vecs::Vec3 normal;
					iss >> normal.X >> normal.Z >> normal.Y;
					this->normals.push_back(normal);
				}
				else if (prefix == "f")
				{
					Face face;
					std::string vertexStr;
					while (iss >> vertexStr)
					{
						std::istringstream viss(vertexStr);
						int vIndex, tIndex, nIndex;
						char slash;
						viss >> vIndex >> slash >> tIndex >> slash >> nIndex;
						// On se fiche des textures pour l'instant
						face.vertexIndices.push_back(vIndex);
						face.vertexNormals.push_back(nIndex);
					}
					if (face.vertexIndices.size() != 3 || face.vertexNormals.size() != 3)
					{
						std::cerr << "Erreur: le format du fichier .obj ne convient pas car les faces ne sont pas triangulées." << std::endl;
						return;
					}
					this->faces.push_back(face);
				}
				else
				{
					// std::cerr << "Avertissement: préfixe non traité. Suivant.." << std::endl;
					continue;
				}
			}
		}
	}

}