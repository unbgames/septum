#include "TileMap.h"
#include "Camera.h"
#include "Game.h"
#include <fstream>
#include <stdexcept>
#include <string>

#define PARALLAX_FACTOR 0.7

using std::ifstream;
using std::string;

TileMap::TileMap (GameObject& associated, string file, TileSet* tileSet, Vec2 offset) :
		Component(associated), tileSet(tileSet), offset(offset) {
	Load(file);
}

void TileMap::Load (string file) {
	ifstream tileFile(file.c_str());
	if (tileFile.is_open()) {
		string aux;
		std::getline(tileFile, aux, ',');
		mapWidth = std::stoi(aux);

		std::getline(tileFile, aux, ',');
		mapHeight = std::stoi(aux);

		std::getline(tileFile, aux, ',');
		mapDepth = std::stoi(aux);

		string tile;
		int count = 0;
		while (std::getline(tileFile, tile, ',')
				&& count < (mapWidth * mapHeight * mapDepth)) {
			// Subtracts one for convenience
			tileMatrix.push_back(std::stoi(tile) - 1);
			count++;
		}
	}
	else {
		throw std::runtime_error("Couldn't open TileMap file");
	}
}

void TileMap::SetTileSet (TileSet *tileSet) {
	this->tileSet = tileSet;
}

int& TileMap::At (int x, int y, int z) {
	int zOffset = z * mapWidth * mapHeight;
	int yOffset = y * mapWidth;
	return tileMatrix[zOffset + yOffset + x];
}

void TileMap::RenderLayer (int layer, int cameraX, int cameraY) {
	int posx = offset.x + cameraX % Game::GetInstance().GetWidth();
	int posy = cameraY + offset.y;
	for (int y = 0; y < mapHeight; ++y) {
		for (int x = 0; x < mapWidth; ++x) {
			int index = At(x, y, layer);
			if (index >= 0) {
				tileSet->RenderTile(index,
						(tileSet->GetTileWidth() * x) - posx - posx * layer * PARALLAX_FACTOR,
						(tileSet->GetTileHeight() * y) - posy - posy * layer * PARALLAX_FACTOR);
			}
		}
	}
	int diff = Game::GetInstance().GetWidth() - ((tileSet->GetTileWidth() * mapWidth) - posx);
	if (diff > 0) {
		int layerAmount = 1 + tileSet->GetTileWidth() / diff;
		posx = -(Game::GetInstance().GetWidth() - diff);
		for (int y = 0; y < mapHeight; ++y) {
			for (int x = 0; x < layerAmount; ++x) {
				int index = At(x, y, layer);
				if (index >= 0) {
					tileSet->RenderTile(index,
							(tileSet->GetTileWidth() * x) - posx - posx * layer * PARALLAX_FACTOR,
							(tileSet->GetTileHeight() * y) - posy - posy * layer * PARALLAX_FACTOR);
				}
			}
		}
	}
}

void TileMap::Render () {
	for (int z = 0; z < mapDepth; ++z) {
		RenderLayer(z, Camera::pos.x, Camera::pos.y);
	}
}

int TileMap::GetWidth () const {
	return mapWidth;
}
int TileMap::GetHeight () const {
	return mapHeight;
}
int TileMap::GetDepth () const {
	return mapDepth;
}

void TileMap::Update (float dt) {

}

bool TileMap::Is (string type) const {
	return (type == "TileMap");
}
