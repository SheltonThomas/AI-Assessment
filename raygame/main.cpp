/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "Maze.h"
#include "Pathfinding.h"
#include <vector>
#include <iostream>

using namespace pathfinding;

enum tileType {
	grass,
	bush,
	water,
	wall
};

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 1280;
	int screenHeight = 720;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(0);
	//--------------------------------------------------------------------------------------
	float mapSize = 25;
	float tileSize = 25;

	std::vector<Node*> nodeMap;
	Maze<tileType> maze({ mapSize, mapSize }, { tileSize, tileSize }, grass, GREEN);

	for (float i = 0; i < mapSize; i++)
	{
		maze.createTile({ i, 0 }, wall, GRAY);
		maze.createTile({ 0, i }, wall, GRAY);
		maze.createTile({ i, mapSize - 1 }, wall, GRAY);
		maze.createTile({ mapSize - 1, i }, wall, GRAY);
		if (i != mapSize - 1) maze.createTile({ 1, i }, water, BLUE);
		if (i != 10 && i != 11 && i != 12 && i != 13 && i != mapSize - 1) maze.createTile({ i, 10 }, water, BLUE);
	}

	for (float i = 0; i < mapSize; i++)
	{
		for (float j = 0; j < mapSize; j++)
		{
			Node* tempNode = new Node({ i, j });

			nodeMap.push_back(tempNode);
		}
	}

	for (float i = 0; i < mapSize; i++)
	{
		for (float j = 0; j < mapSize; j++)
		{
			if (maze.getTileType({ j, i }) == wall) continue;
			if (maze.getTileType({ j, i }) == water) continue;
			if (maze.getTileType({ j, i }) == bush) continue;

			float currentCoordinate = j * mapSize + i;
			Node* currentNode = nodeMap.at(currentCoordinate);
			tileType currentTile = maze.getTileType({ j, i });

			if (i != mapSize - 1 && currentTile == grass)
			{
				tileType nextTile = maze.getTileType({ j, i + 1 });
				if (nextTile == grass)
				{
					float nextCoordinate = j * mapSize + (i + 1);
					Edge tempEdge = { nodeMap.at(nextCoordinate), 0 };
					currentNode->connections.push_back(tempEdge);
				}
				
				nextTile = maze.getTileType({ j + 1, i + 1 });
				if (nextTile == grass)
				{
					float nextCoordinate = (j + 1) * mapSize + (i + 1);
					Edge tempEdge = { nodeMap.at(nextCoordinate), 0 };
					currentNode->connections.push_back(tempEdge);
				}

				nextTile = maze.getTileType({ j - 1, i + 1 });
				if (nextTile == grass)
				{
					float nextCoordinate = (j - 1) * mapSize + (i + 1);
					Edge tempEdge = { nodeMap.at(nextCoordinate), 0 };
					currentNode->connections.push_back(tempEdge);
				}
			}

			if (i != 0 && currentTile == grass)
			{
				tileType nextTile = maze.getTileType({ j, i - 1 });
				if (nextTile == grass)
				{
					float nextCoordinate = j * mapSize + (i - 1);
					Edge tempEdge = { nodeMap.at(nextCoordinate), 0 };
					currentNode->connections.push_back(tempEdge);
				}

				nextTile = maze.getTileType({ j + 1, i - 1 });
				if (nextTile == grass)
				{
					float nextCoordinate = (j + 1) * mapSize + (i - 1);
					Edge tempEdge = { nodeMap.at(nextCoordinate), 0 };
					currentNode->connections.push_back(tempEdge);
				}

				nextTile = maze.getTileType({ j - 1, i - 1 });
				if (nextTile == grass)
				{
					float nextCoordinate = (j - 1) * mapSize + (i - 1);
					Edge tempEdge = { nodeMap.at(nextCoordinate), 0 };
					currentNode->connections.push_back(tempEdge);
				}
			}

			if (j != mapSize - 1 && currentTile == grass)
			{
				tileType nextTile = maze.getTileType({ j + 1, i });
				if (nextTile == grass)
				{
					float nextCoordinate = (j + 1) * mapSize + i;
					Edge tempEdge = { nodeMap.at(nextCoordinate), 0 };
					currentNode->connections.push_back(tempEdge);
				}

				nextTile = maze.getTileType({ j + 1, i + 1 });
				if (nextTile == grass)
				{
					float nextCoordinate = (j + 1) * mapSize + (i + 1);
					Edge tempEdge = { nodeMap.at(nextCoordinate), 0 };
					currentNode->connections.push_back(tempEdge);
				}

				nextTile = maze.getTileType({ j + 1, i - 1 });
				if (nextTile == grass)
				{
					float nextCoordinate = (j + 1) * mapSize + (i - 1);
					Edge tempEdge = { nodeMap.at(nextCoordinate), 0 };
					currentNode->connections.push_back(tempEdge);
				}
			}

			if (j != 0 && currentTile == grass)
			{
				tileType nextTile = maze.getTileType({ j - 1, i });
				if (nextTile == grass)
				{
					float nextCoordinate = (j - 1) * mapSize + i;
					Edge tempEdge = { nodeMap.at(nextCoordinate), 0 };
					currentNode->connections.push_back(tempEdge);
				}

				nextTile = maze.getTileType({ j - 1, i + 1 });
				if (nextTile == grass)
				{
					float nextCoordinate = (j - 1) * mapSize + (i + 1);
					Edge tempEdge = { nodeMap.at(nextCoordinate), 0 };
					currentNode->connections.push_back(tempEdge);
				}

				nextTile = maze.getTileType({ j - 1, i - 1 });
				if (nextTile == grass)
				{
					float nextCoordinate = (j - 1) * mapSize + (i - 1);
					Edge tempEdge = { nodeMap.at(nextCoordinate), 0 };
					currentNode->connections.push_back(tempEdge);
				}
			}
		}
	}

	std::vector<Node*> path = pathFinding(nodeMap.at(57), nodeMap.at(163));

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);

		maze.draw();

		//drawGraph(nodeMap.at(76), { tileSize, tileSize });

		/*for (Node* node : nodeMap) {
			drawNode(node, { tileSize, tileSize }, true);
		}*/

		for (Node* node : path) {
			drawNode(node, { tileSize, tileSize }, true);
		}

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}