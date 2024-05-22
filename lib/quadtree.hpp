#include <iostream>
#include "vectors.hpp"

struct Quadtree
{
	// étiquette
	vecs::Vec2 root;
	// savoir si c'est une feuille
	bool isLeaf;
	// 4 noeuds fils
	Quadtree *topright;
	Quadtree *topleft;
	Quadtree *bottomleft;
	Quadtree *bottomright;
};