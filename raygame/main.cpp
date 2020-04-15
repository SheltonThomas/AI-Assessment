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

	Maze<tileType> maze({ mapSize, mapSize }, {25, 25}, grass, GREEN);

	for (float i = 0; i < mapSize; i++)
	{
		maze.createTile({ i, 0 }, wall, GRAY);
		maze.createTile({ 0, i }, wall, GRAY);
		maze.createTile({ i, mapSize - 1 }, wall, GRAY);
		maze.createTile({ mapSize - 1, i }, wall, GRAY);
		if(i != mapSize - 1) maze.createTile({ 1, i }, water, BLUE);
		if (i != 10 && i != 11 && i != 12 && i != 13 && i != mapSize - 1) maze.createTile({ i, 10 }, water, BLUE);
	}

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

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}