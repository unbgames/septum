#pragma once
#include "GameObject.h"
#include <string>
#include <vector>
#include "TileSet.h"
#include "Component.h"
#include "Vec2.h"

using std::string;
using std::vector;

class TileMap: public Component {
	public:
		TileMap (GameObject& associated, string file, TileSet* tileSet, Vec2 offset = {0,0});
		void Load (string file);
		void SetTileSet (TileSet* tileSet);
		int& At (int x, int y, int z = 0);
		void RenderLayer (int layer, int cameraX = 0, int cameraY = 0);

		int GetWidth () const;
		int GetHeight () const;
		int GetDepth () const;

		/**
		 * Updates component state
		 * @param dt
		 */
		void Update (float dt);

		/**
		 * Renders the component
		 */
		void Render ();

		void Render (int cameraX, int cameraY);

		/**
		 * Checks if the Component is from the type TileMap
		 * @param type type to be checked
		 * @return whether the type matches or not
		 */
		bool Is (string type) const;

	private:
		vector<int> tileMatrix;
		TileSet* tileSet;
		int mapWidth;
		int mapHeight;
		int mapDepth;
		Vec2 offset;
};
