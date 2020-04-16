#pragma once
#include "raylib.h"

template <typename T>
struct Tile
{
	T data;
	Color color = DARKGRAY;
};

template <typename T>
class Maze
{
public:
	Maze(Vector2 mapSize, Vector2 tileSize, T initialData, Color initialColor);
	~Maze();

	void createTile(Vector2 coordinates, T data, Color color);

	Tile<T> getTile(Vector2 coordinates);
	Tile<T> checkTile(Vector2 coordinates);

	Vector2 getMapSize() { return m_mapSize; }
	Vector2 getTileSize() { return m_tileSize; }

	T getTileType(Vector2 coordiantes);

	void draw();
	void drawTile(Tile<T> tile, Vector2 coordinates);

private:
	Vector2 m_mapSize;
	Vector2 m_tileSize;
	Tile<T>* m_tileMap;
};

template <typename T>
inline Maze<T>::Maze(Vector2 mapSize, Vector2 tileSize, T initialData, Color initialColor)
{
	m_mapSize = mapSize;
	m_tileSize = tileSize;
	//Initialize the tile map
	int mapLength = (int)(m_mapSize.x) * (int)(m_mapSize.y);
	m_tileMap = new Tile<T>[mapLength];
	for (int i = 0; i < mapLength; i++) {
		m_tileMap[i] = { initialData, initialColor };
	}
}

template <typename T>
inline Maze<T>::~Maze()
{
	delete m_tileMap;
}

template<typename T>
inline void Maze<T>::createTile(Vector2 coordinates, T data, Color color)
{
	//Create the tile
	Tile<T> tile{ data, color };

	//Place the tile
	int index = coordinates.y * m_mapSize.x + coordinates.x;
	m_tileMap[index] = tile;
}

template<typename T>
inline Tile<T> Maze<T>::getTile(Vector2 coordinates)
{
	//Calculate the index of the tile from 2D maze coordinates
	int index = coordinates.y * m_mapSize.x + coordinates.x;
	return m_tileMap[index];
}

template<typename T>
inline Tile<T> Maze<T>::checkTile(Vector2 coordinates)
{
	//Calculate the index of the tile from 2D world coordinates
	coordinates = { coordinates.x / m_tileSize.x , coordinates.y / m_tileSize.y };
	int index = coordinates.y * m_mapSize.x + coordinates.x;
	return m_tileMap[index];
}

template<typename T>
inline T Maze<T>::getTileType(Vector2 coordinates)
{
	int index = coordinates.y * m_mapSize.x + coordinates.x;
	return m_tileMap[index].data;
}

template<typename T>
inline void Maze<T>::draw()
{
	//Draw each tile
	int mapLength = (int)(m_mapSize.x) * (int)(m_mapSize.y);
	for (int i = 0; i < mapLength; i++) {
		//Calculate the position of the tile
		int posX = i % (int)(m_mapSize.x);
		int posY = i / (int)(m_mapSize.x);
		drawTile(m_tileMap[i], { (float)(posX), (float)(posY) });
	}
}

template<typename T>
inline void Maze<T>::drawTile(Tile<T> tile, Vector2 coordinates)
{
	int posX = (int)(coordinates.x) * (int)(m_tileSize.x);
	int posY = (int)(coordinates.y) * (int)(m_tileSize.y);
	int width = (int)(m_tileSize.x);
	int height = (int)(m_tileSize.y);
	Color color = tile.color;
	DrawRectangle(posX, posY, width, height, color);
}
