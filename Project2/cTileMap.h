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
	int tileMap[6][6];

private:
	SDL_Point mapStartXY;
	SDL_Point theMovement;
	SDL_Point tileClickedRC;
	cSprite red;
	cSprite blue;
	cSprite lightGreen;
	cSprite black;
	cSprite yellow;
	cSprite blueLorry;
	cSprite yellowLorry;
	cSprite purpleLorry;
	cSprite border;
	void initialiseMap();

	// Set the initial values for the map

public:
	cTileMap();
	cTileMap(cFileHandler* aFile);
	
	SDL_Rect redPos;
	SDL_Rect bluePos;
	SDL_Rect lightGreenPos;
	SDL_Rect blackPos;
	SDL_Rect yellowPos;
	SDL_Rect blueLorryPos;
	SDL_Rect yellowLorryPos;
	SDL_Rect purpleLorryPos;

	SDL_Rect redFrontCol;
	SDL_Rect blueFrontCol;
	SDL_Rect lightGreenFrontCol;
	SDL_Rect blackFrontCol;
	SDL_Rect yellowFrontCol;
	SDL_Rect blueLorryFrontCol;
	SDL_Rect yellowLorryFrontCol;
	SDL_Rect purpleLorryFrontCol;

	SDL_Rect redBackCol;
	SDL_Rect blueBackCol;
	SDL_Rect lightGreenBackCol;
	SDL_Rect blackBackCol;
	SDL_Rect yellowBackCol;
	SDL_Rect blueLorryBackCol;
	SDL_Rect yellowLorryBackCol;
	SDL_Rect purpleLorryBackCol;

	bool finish = false;
	bool moved = false;
	int carSelect = 0;

	void reset();
	bool endLevel(bool levelEnd);
	bool updateScore();
	void initialiseMapFromFile(cFileHandler* aFile);		// Set the initial values for the map from file input
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, cTextureMgr* theTxtMgr, vector<LPCSTR> theTxt);		// Default render function
	void renderGridLines(SDL_Renderer* theRenderer, SDL_Rect theRect, SDL_Color theColour); // Draw grid lines
	void update(SDL_Point theMapAreaClicked, int theTileToPlace);
	void setMapStartXY(SDL_Point startPosXY);
	void carReset();
	void addOneToMove();
	void subtractOneToMove();
	void addToCarSelect();
	void subtractToCarSelect();
	SDL_Point getMapStartXY();
	string getMapData();
	void writeMapDataToFile(cFileHandler* aFile);
};
#endif