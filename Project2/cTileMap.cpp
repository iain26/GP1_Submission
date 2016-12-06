/*
=================
- cTileMap.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cTileMap.h"
SDL_Point theMovement;
int iMove[] = { 2, 3, 5, 3, 4, 2 };
SDL_Rect carPosXY;
cGame game;
/*
=================================================================
 Defualt Constructor
=================================================================
*/
cTileMap::cTileMap() : cSprite()
{
	//this->initialiseMap();
}

cTileMap::cTileMap(cFileHandler* aFile) : cSprite()
{
	/*this->initialiseMapFromFile(aFile);*/
}


void cTileMap::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, cTextureMgr* theTxtMgr, vector<LPCSTR> theTxt)
{

	int iGridSpace = 80;
	// determine number of rows and columns for array
	int numRows = sizeof(tileMap) / sizeof(tileMap[0]);
	int numCols = sizeof(tileMap[0]) / sizeof(tileMap[0][0]);
	for (int row = 0; row < numRows; row++){
		for (int column = 0; column < numCols; column++){
			border.setTexture(theTxtMgr->getTexture(theTxt[7]));
			border.setSpriteDimensions(theTxtMgr->getTexture(theTxt[0])->getTWidth(), theTxtMgr->getTexture(theTxt[0])->getTHeight());
			{
				blue.setTexture(theTxtMgr->getTexture(theTxt[1]));
				blue.setSpriteDimensions(theTxtMgr->getTexture(theTxt[1])->getTWidth(), theTxtMgr->getTexture(theTxt[1])->getTHeight());
				bluePos.w = blue.getSpritePos().w;
				bluePos.x = mapStartXY.x - 80 + iMove[1] *iGridSpace;
				bluePos.y = mapStartXY.y - 80 + 6 * iGridSpace;
				bluePos.h = blue.getSpritePos().h;
				blueFrontCol = { bluePos.x + 80, bluePos.y, bluePos.w, bluePos.h };
				blueBackCol = { bluePos.x - 80, bluePos.y, bluePos.w, bluePos.h };
				blue.render(theRenderer, &blue.getSpriteDimensions(), &bluePos, blue.getSpriteRotAngle(), &blue.getSpriteCentre(), blue.getSpriteScale());
				if (carSelect == 1){
					border.render(theRenderer, &border.getSpriteDimensions(), &bluePos, border.getSpriteRotAngle(), &border.getSpriteCentre(), border.getSpriteScale());
				}
			}
			{
				purpleLorry.setTexture(theTxtMgr->getTexture(theTxt[5]));
				purpleLorry.setSpriteDimensions(theTxtMgr->getTexture(theTxt[5])->getTWidth(), theTxtMgr->getTexture(theTxt[5])->getTHeight());
				purpleLorryPos.w = purpleLorry.getSpritePos().w;
				purpleLorryPos.x = mapStartXY.x - 80 + 6 * iGridSpace;
				purpleLorryPos.y = mapStartXY.y - 80 + iMove[4] * iGridSpace;
				purpleLorryPos.h = purpleLorry.getSpritePos().h;
				purpleLorryFrontCol = { purpleLorryPos.x, purpleLorryPos.y - 80, purpleLorryPos.w, purpleLorryPos.h };
				purpleLorryBackCol = { purpleLorryPos.x, purpleLorryPos.y + 80, purpleLorryPos.w, purpleLorryPos.h };
				purpleLorry.render(theRenderer, &purpleLorry.getSpriteDimensions(), &purpleLorryPos, purpleLorry.getSpriteRotAngle(), &purpleLorry.getSpriteCentre(), purpleLorry.getSpriteScale());
				if (carSelect == 4){
					border.render(theRenderer, &border.getSpriteDimensions(), &purpleLorryPos, border.getSpriteRotAngle(), &border.getSpriteCentre(), border.getSpriteScale());
				}
			}
			{
				yellow.setTexture(theTxtMgr->getTexture(theTxt[6]));
				yellow.setSpriteDimensions(theTxtMgr->getTexture(theTxt[6])->getTWidth(), theTxtMgr->getTexture(theTxt[6])->getTHeight());
				yellowPos.w = yellow.getSpritePos().w;
				yellowPos.x = mapStartXY.x - 80 + iMove[5] *iGridSpace;
				yellowPos.y = mapStartXY.y - 80 + 4 * iGridSpace;
				yellowPos.h = yellow.getSpritePos().h;
				yellowFrontCol = { yellowPos.x + 80, yellowPos.y, yellowPos.w, yellowPos.h };
				yellowBackCol = { yellowPos.x - 80, yellowPos.y, yellowPos.w, yellowPos.h };
				yellow.render(theRenderer, &yellow.getSpriteDimensions(), &yellowPos, yellow.getSpriteRotAngle(), &yellow.getSpriteCentre(), yellow.getSpriteScale());
				if (carSelect == 5){
					border.render(theRenderer, &border.getSpriteDimensions(), &yellowPos, border.getSpriteRotAngle(), &border.getSpriteCentre(), border.getSpriteScale());
				}
			}	
			{
				yellowLorry.setTexture(theTxtMgr->getTexture(theTxt[4]));
				yellowLorry.setSpriteDimensions(theTxtMgr->getTexture(theTxt[4])->getTWidth(), theTxtMgr->getTexture(theTxt[4])->getTHeight());
				yellowLorryPos.w = yellowLorry.getSpritePos().w;
				yellowLorryPos.x = mapStartXY.x - 80 + 4 * iGridSpace;
				yellowLorryPos.y = mapStartXY.y - 80 + iMove[3] * iGridSpace;
				yellowLorryPos.h = yellowLorry.getSpritePos().h;
				yellowLorryFrontCol = { yellowLorryPos.x, yellowLorryPos.y - 80, yellowLorryPos.w, yellowLorryPos.h };
				yellowLorryBackCol = { yellowLorryPos.x, yellowLorryPos.y + 80, yellowLorryPos.w, yellowLorryPos.h };
				yellowLorry.render(theRenderer, &yellowLorry.getSpriteDimensions(), &yellowLorryPos, yellowLorry.getSpriteRotAngle(), &yellowLorry.getSpriteCentre(), yellowLorry.getSpriteScale());
				if (carSelect == 3){
					border.render(theRenderer, &border.getSpriteDimensions(), &yellowLorryPos, border.getSpriteRotAngle(), &border.getSpriteCentre(), border.getSpriteScale());
				}
			}
			{
				lightGreen.setTexture(theTxtMgr->getTexture(theTxt[2]));
				lightGreen.setSpriteDimensions(theTxtMgr->getTexture(theTxt[2])->getTWidth(), theTxtMgr->getTexture(theTxt[2])->getTHeight());
				lightGreenPos.w = lightGreen.getSpritePos().w;
				lightGreenPos.x = mapStartXY.x - 80 + 2 * iGridSpace;
				lightGreenPos.y = mapStartXY.y - 80 + iMove[2] * iGridSpace;
				lightGreenPos.h = lightGreen.getSpritePos().h;
				lightGreenFrontCol = { lightGreenPos.x, lightGreenPos.y - 80, lightGreenPos.w, lightGreenPos.h};
				lightGreenBackCol = { lightGreenPos.x, lightGreenPos.y + 80, lightGreenPos.w, lightGreenPos.h };
				lightGreen.render(theRenderer, &lightGreen.getSpriteDimensions(), &lightGreenPos, lightGreen.getSpriteRotAngle(), &lightGreen.getSpriteCentre(), lightGreen.getSpriteScale());
				if (carSelect == 2){
					border.render(theRenderer, &border.getSpriteDimensions(), &lightGreenPos, border.getSpriteRotAngle(), &border.getSpriteCentre(), border.getSpriteScale());
				}			
			}
			{
				red.setTexture(theTxtMgr->getTexture(theTxt[0]));
				red.setSpriteDimensions(theTxtMgr->getTexture(theTxt[0])->getTWidth(), theTxtMgr->getTexture(theTxt[0])->getTHeight());
				redPos.w = red.getSpritePos().w;
				redPos.x = mapStartXY.x - 80 + iMove[0] *iGridSpace;
				redPos.y = mapStartXY.y - 80 + 3 * iGridSpace;
				redPos.h = red.getSpritePos().h;
				redFrontCol = { redPos.x + 80, redPos.y, redPos.w, redPos.h };
				redBackCol = { redPos.x - 80, redPos.y, redPos.w, redPos.h };
				red.render(theRenderer, &red.getSpriteDimensions(), &redPos, red.getSpriteRotAngle(), &red.getSpriteCentre(), red.getSpriteScale());
				if (carSelect == 0){
					border.render(theRenderer, &border.getSpriteDimensions(), &redPos, border.getSpriteRotAngle(), &border.getSpriteCentre(), border.getSpriteScale());
				}
			}
		}
		//carPosXY.x += red.getSpritePos().w / 2;
	}
	//carPosXY.x = mapStartXY.x;
	//carPosXY.y += red.getSpritePos().h;
}
	



void cTileMap::renderGridLines(SDL_Renderer* theRenderer, SDL_Rect theRect, SDL_Color theColour)
{
	//SDL_Rect tilePosXY;
	//tilePosXY = { mapStartXY.x, mapStartXY.y, theRect.w, theRect.h };
	//// determine number of rows and columns for array
	//int numRows = sizeof(tileMap) / sizeof(tileMap[0]);
	//int numCols = sizeof(tileMap[0]) / sizeof(tileMap[0][0]);
	//SDL_SetRenderDrawColor(theRenderer, theColour.r, theColour.g, theColour.b, theColour.a);
	//for (int row = 0; row < numRows; row++)
	//{
	//	for (int column = 0; column < numCols; column++)
	//	{
	//		SDL_RenderDrawRect(theRenderer, &tilePosXY);
	//		tilePosXY.x += theRect.w;
	//	}
	//	tilePosXY.x = mapStartXY.x;
	//	tilePosXY.y += theRect.h;
	//}
	//SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cTileMap::update(SDL_Point theMapAreaClicked, int theTileToPlace)
{
	//SDL_Point areaClicked = theMapAreaClicked;
	/*if (theTileToPlace > -1)
		{
			if (areaClicked.x > this->mapStartXY.x && areaClicked.x < 612 && areaClicked.y > this->mapStartXY.y && areaClicked.y < 612)
			{
				this->tileClickedRC.x = (int)(areaClicked.x - this->mapStartXY.x) / this->red.getSpriteDimensions().w;
				this->tileClickedRC.y = (int)(areaClicked.y - this->mapStartXY.y) / this->red.getSpriteDimensions().h;
				this->tileMap[this->tileClickedRC.y][this->tileClickedRC.x] = theTileToPlace;
			}
		}*/
}
/*
=================================================================
- Set the initial values for the map
=================================================================
*/
void cTileMap::initialiseMap()
{
	//srand(time(NULL));
	//for (int row = 0; row < 6; row++)
	//{
	//	for (int column = 0; column < 6; column++)
	//	{
	//		this->tileMap[row][column] = -1;
	//	}
	//}

}
/*
=================================================================
- Set the initial values for the map from file input
=================================================================
*/
void cTileMap::initialiseMapFromFile(cFileHandler* aFile)
{
	//string fileData;
	//fileData = aFile->readDataFromFile();

	//stringstream mapData(fileData);

	//// Fill map with data from file

}
/*
=================================================================
- set start position for tile map
=================================================================
*/
void cTileMap::setMapStartXY(SDL_Point startPosXY)
{
	mapStartXY = startPosXY;
}


void cTileMap::reset(){
	iMove[0] = 2;
	iMove[1] = 3;
	iMove[2] = 5;
	iMove[3] = 3;
	iMove[4] = 4;
	iMove[5] = 2;
	carSelect = 0;
}

void cTileMap::addOneToMove()
{
	bool redMove = true;
	bool yellowMove = true;
	bool blueMove = true;
	bool lightGreenMove = true;
	bool purpleLorryMove = true;
	bool yellowLorryMove = true;

	if (collidedWith(&redFrontCol, &bluePos) || collidedWith(&redFrontCol, &yellowPos) || collidedWith(&redFrontCol, &lightGreenPos) || collidedWith(&redFrontCol, &purpleLorryPos) || collidedWith(&redFrontCol, &yellowLorryPos)){
		redMove = false;
	}
	if (collidedWith(&yellowFrontCol, &redPos) || collidedWith(&yellowFrontCol, &bluePos) || collidedWith(&yellowFrontCol, &lightGreenPos) || collidedWith(&yellowFrontCol, &purpleLorryPos) || collidedWith(&yellowFrontCol, &yellowLorryPos)){
		yellowMove = false;
	}
	if (collidedWith(&blueFrontCol, &redPos) || collidedWith(&blueFrontCol, &yellowPos) || collidedWith(&blueFrontCol, &lightGreenPos) || collidedWith(&blueFrontCol, &purpleLorryPos) || collidedWith(&blueFrontCol, &yellowLorryPos)){
		blueMove = false;
	}
	if (collidedWith(&lightGreenFrontCol, &redPos) || collidedWith(&lightGreenFrontCol, &yellowPos) || collidedWith(&lightGreenFrontCol, &bluePos) || collidedWith(&lightGreenFrontCol, &purpleLorryPos) || collidedWith(&lightGreenFrontCol, &yellowLorryPos)){
		lightGreenMove = false;
	}
	if (collidedWith(&yellowLorryFrontCol, &redPos) || collidedWith(&yellowLorryFrontCol, &yellowPos) || collidedWith(&yellowLorryFrontCol, &lightGreenPos) || collidedWith(&yellowLorryFrontCol, &purpleLorryPos) || collidedWith(&yellowLorryFrontCol, &bluePos)){
		yellowLorryMove = false;
	}
	if (collidedWith(&purpleLorryFrontCol, &redPos) || collidedWith(&purpleLorryFrontCol, &yellowPos) || collidedWith(&purpleLorryFrontCol, &lightGreenPos) || collidedWith(&purpleLorryFrontCol, &bluePos) || collidedWith(&purpleLorryFrontCol, &yellowLorryPos)){
		purpleLorryMove = false;
	}
	
		if (carSelect == 0){
			if (redMove){
				if (iMove[0] < 7){
					iMove[0]++;
					moved = true;
					if (iMove[0] == 7){
						finish = true;
						//reset();
					}
				}
			}
		}
		else if (carSelect == 1){
			if (blueMove){
				if (iMove[1] < 5){
					iMove[1]++;
					moved = true;
				}
			}
		}
		else if (carSelect == 2){
			if (lightGreenMove){
				if (iMove[2] > 1){
					iMove[2] -= 1;
					moved = true;
				}
			}
		}
		else if (carSelect == 3){
			if (yellowLorryMove){
				if (iMove[3] > 1){
					iMove[3] -= 1;
					moved = true;
				}
			}
		}
		else if (carSelect == 4){
			if (purpleLorryMove){
				if (iMove[4] > 1){
					iMove[4] -= 1;
					moved = true;
				}
			}
		}
		else if (carSelect == 5){
			if (yellowMove){
				if (iMove[5] < 5){
					iMove[5]++;
					moved = true;
				}
			}
		}
	}


void cTileMap::subtractOneToMove()
{
	bool redMove = true;
	bool yellowMove = true;
	bool blueMove = true;
	bool lightGreenMove = true;
	bool purpleLorryMove = true;
	bool yellowLorryMove = true;

	if (collidedWith(&redBackCol, &bluePos) || collidedWith(&redBackCol, &yellowPos) || collidedWith(&redBackCol, &lightGreenPos) || collidedWith(&redBackCol, &purpleLorryPos) || collidedWith(&redBackCol, &yellowLorryPos)){
		redMove = false;
	}
	if (collidedWith(&yellowBackCol, &redPos) || collidedWith(&yellowBackCol, &bluePos) || collidedWith(&yellowBackCol, &lightGreenPos) || collidedWith(&yellowBackCol, &purpleLorryPos) || collidedWith(&yellowBackCol, &yellowLorryPos)){
		yellowMove = false;
	}
	if (collidedWith(&blueBackCol, &redPos) || collidedWith(&blueBackCol, &yellowPos) || collidedWith(&blueBackCol, &lightGreenPos) || collidedWith(&blueBackCol, &purpleLorryPos) || collidedWith(&blueBackCol, &yellowLorryPos)){
		blueMove = false;
	}
	if (collidedWith(&lightGreenBackCol, &redPos) || collidedWith(&lightGreenBackCol, &yellowPos) || collidedWith(&lightGreenBackCol, &bluePos) || collidedWith(&lightGreenBackCol, &purpleLorryPos) || collidedWith(&lightGreenBackCol, &yellowLorryPos)){
		lightGreenMove = false;
	}
	if (collidedWith(&yellowLorryBackCol, &redPos) || collidedWith(&yellowLorryBackCol, &yellowPos) || collidedWith(&yellowLorryBackCol, &lightGreenPos) || collidedWith(&yellowLorryBackCol, &purpleLorryPos) || collidedWith(&yellowLorryBackCol, &bluePos)){
		yellowLorryMove = false;
	}
	if (collidedWith(&purpleLorryBackCol, &redPos) || collidedWith(&purpleLorryBackCol, &yellowPos) || collidedWith(&purpleLorryBackCol, &lightGreenPos) || collidedWith(&purpleLorryBackCol, &bluePos) || collidedWith(&purpleLorryBackCol, &yellowLorryPos)){
		purpleLorryMove = false;
	}

	if (carSelect == 0){
		if (redMove){
			if (iMove[0] > 1){
				iMove[0] -= 1;
				moved = true;
			}
		}
	}
	else if (carSelect == 1){
		if (blueMove){
			if (iMove[1] > 1){
				iMove[1] -= 1;
				moved = true;
			}
		}
	}
	else if (carSelect == 2){
		if (lightGreenMove){
			if (iMove[2] < 5){
				iMove[2]++;
				moved = true;
			}
		}
	}
	else if (carSelect == 3){
		if (yellowLorryMove){
			if (iMove[3] < 4){
				iMove[3]++;
				moved = true;
			}
		}
	}
	else if (carSelect == 4){
		if (purpleLorryMove){
			if (iMove[4] < 4){
				iMove[4]++;
				moved = true;
			}
		}
	}
	else if (carSelect == 5){
		if (yellowMove){
			if (iMove[5] > 1){
				iMove[5] -= 1;
				moved = true;
			}
		}
	}
}


bool cTileMap::endLevel(bool levelEnd){
	if (finish){
		finish = false;
		return true;
	}
	else{
		return false;
	}
}

bool cTileMap::updateScore(){
	if (moved){
		moved = false;
		return true;
	}
	else{
		return false;
	}
}

void cTileMap::addToCarSelect()
{
	carSelect++;
	if (carSelect > 5){
		carSelect = 0;
	}
}

void cTileMap::subtractToCarSelect()
{
	carSelect -= 1;
	if (carSelect < 0){
		carSelect = 5;
	}
}


/*
=================================================================
- get start pposition for tile map
=================================================================
*/
SDL_Point cTileMap::getMapStartXY()
{
	return mapStartXY;
}
/*
=================================================================
- get the tile map as a string
=================================================================
*/
//string cTileMap::getMapData()
//{
//	string mapData = "";
//	for (int row = 0; row < 8; row++)
//	{
//		for (int column = 0; column < 8; column++)
//		{
//			mapData += to_string(this->tileMap[row][column]) + ',';
//		}
//		//mapData += '\n';
//	}
//	
//	return mapData;
//}

/*
=================================================================
- Write the values from the map to the file
=================================================================
*/
void cTileMap::writeMapDataToFile(cFileHandler* aFile)
{
	//string mapDataToWrite = "";
	//string theMapData = this->getMapData();
	//stringstream outputStr(theMapData);
	//if (!theMapData.empty())
	//{
	//	while (getline(outputStr, mapDataToWrite, '\n')){
	//		mapDataToWrite += '\n';
	//		aFile->writeDataToFile(mapDataToWrite);
	//	}
	//}
	//aFile->closeFile();
}
