/*
=================
cTileMap.h
- Header file for class definition - SPECIFICATION
- Header file for the tileMap class which is a child of cSprite class
=================
*/
#ifndef _CTILEMAP_H
#define _CTILEMAP_H
#include "MazeMakerEditor.h"
#include <sstream>


class cTileMap: public cSprite
{
protected:
	//Initialised the Tilemap
	int tileMap[6][6];

private:
	//Sets where the top left of grid should be
	SDL_Point mapStartXY;
	//A sprite is set for each car 
	cSprite red;
	cSprite blue;
	cSprite lightGreen;
	cSprite black;
	cSprite yellow;
	cSprite blueLorry;
	cSprite yellowLorry;
	cSprite purpleLorry;
	//border sprite for car selection
	cSprite border;

	void initialiseMap();

	// Set the initial values for the map

public:
	cTileMap();
	cTileMap(cFileHandler* aFile);
	//These will be positions and dimensions for each sprite
	SDL_Rect redPos;
	SDL_Rect bluePos;
	SDL_Rect lightGreenPos;
	SDL_Rect blackPos;
	SDL_Rect yellowPos;
	SDL_Rect blueLorryPos;
	SDL_Rect yellowLorryPos;
	SDL_Rect purpleLorryPos;
	//The box at front of each sprite to detect collision
	SDL_Rect redFrontCol;
	SDL_Rect blueFrontCol;
	SDL_Rect lightGreenFrontCol;
	SDL_Rect blackFrontCol;
	SDL_Rect yellowFrontCol;
	SDL_Rect blueLorryFrontCol;
	SDL_Rect yellowLorryFrontCol;
	SDL_Rect purpleLorryFrontCol;
	//The box at back of each sprite to detect collision
	SDL_Rect redBackCol;
	SDL_Rect blueBackCol;
	SDL_Rect lightGreenBackCol;
	SDL_Rect blackBackCol;
	SDL_Rect yellowBackCol;
	SDL_Rect blueLorryBackCol;
	SDL_Rect yellowLorryBackCol;
	SDL_Rect purpleLorryBackCol;
	//booleans used for updating score and whether won game
	bool finish = false;
	bool moved = false;
	//integer for setting what car to move
	int carSelect = 0;
	//functions instantiated so they can be called 
	void reset();//set game to original positions
	bool endLevel(bool levelEnd);//if reached the end return true
	bool updateScore();//if moved return true
	void initialiseMapFromFile(cFileHandler* aFile);		// Set the initial values for the map from file input
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, cTextureMgr* theTxtMgr, vector<LPCSTR> theTxt);		// Default render function
	void renderGridLines(SDL_Renderer* theRenderer, SDL_Rect theRect, SDL_Color theColour); // Draw grid lines
	void update(SDL_Point theMapAreaClicked, int theTileToPlace);
	void setMapStartXY(SDL_Point startPosXY);
	void addOneToMove();//change position 
	void subtractOneToMove();//change position 
	void addToCarSelect();//car selection function
	void subtractToCarSelect();//car selection function
	SDL_Point getMapStartXY();//get the top left of grid
	string getMapData();
	void writeMapDataToFile(cFileHandler* aFile);
};
#endif