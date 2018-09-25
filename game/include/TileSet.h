#pragma once
#include <string>
#include "Sprite.h"
#include "GameObject.h"

using std::string;

class TileSet {
	public:
		TileSet (int tileWidth, int tileHeight, string file,
				GameObject& associated);
		/**
		 * Renders a tile on the position x y
		 * @param index tile index
		 * @param x x-axis coordinate
		 * @param y y-axis coordinate
		 */
		void RenderTile (unsigned int index, float x, float y);
		/**
		 * Returns the tile width
		 * @return tile width
		 */
		int GetTileWidth () const;
		/**
		 * Returns the tile height
		 * @return tile height
		 */
		int GetTileHeight () const;

	private:
		Sprite tileSet;
		int rows;
		int columns;
		int tileWidth;
		int tileHeight;
};
