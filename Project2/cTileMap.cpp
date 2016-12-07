/*
=================
- cTileMap.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cTileMap.h"
int iMove[] = { 2, 3, 5, 3, 4, 2 };//sets original position of cars
//SDL_Rect carPosXY;
cGame game;//variable to reference cGame
/*
=================================================================
 Defualt Constructor
=================================================================
*/
cTileMap::cTileMap() : cSprite()
{
}

cTileMap::cTileMap(cFileHandler* aFile) : cSprite()
{
}


void cTileMap::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, cTextureMgr* theTxtMgr, vector<LPCSTR> theTxt)
{
	int iGridSpace = 80;//sets all grid spaces to 80(half the amount of car width)
	// determine number of rows and columns for array
	int numRows = sizeof(tileMap) / sizeof(tileMap[0]);
	int numCols = sizeof(tileMap[0]) / sizeof(tileMap[0][0]);
	for (int row = 0; row < numRows; row++){
		for (int column = 0; column < numCols; column++){//not sure if I need these last four lines but too afraid to change it
			//sets the border texture then sets dimensions to the dimensions of red car
			border.setTexture(theTxtMgr->getTexture(theTxt[7]));
			border.setSpriteDimensions(theTxtMgr->getTexture(theTxt[0])->getTWidth(), theTxtMgr->getTexture(theTxt[0])->getTHeight());
			//renders cars in exactly the same process 
			//for each car sets texture
			//sets the dimensions
			//makes the SDL_Rect for position equal to dimensions of sprites
			//also makes postion x and y equal to their position they should be at
			//sets collider SDL_Rect for front and back changing x or y depending on orientation
			//render sprite with position and dimensions
			//if the car is selected then true
			//and border is set on top of car sprite with same dimensions 
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
	}
}
	



void cTileMap::renderGridLines(SDL_Renderer* theRenderer, SDL_Rect theRect, SDL_Color theColour)
{

}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cTileMap::update(SDL_Point theMapAreaClicked, int theTileToPlace)
{
	
}
/*
=================================================================
- Set the initial values for the map
=================================================================
*/
void cTileMap::initialiseMap()
{
	

}
/*
=================================================================
- Set the initial values for the map from file input
=================================================================
*/
void cTileMap::initialiseMapFromFile(cFileHandler* aFile)
{


}
/*
=================================================================
- set start position for tile map
=================================================================
*/
void cTileMap::setMapStartXY(SDL_Point startPosXY)//takes in a x and y to set top left of grid 
{
	mapStartXY = startPosXY;
}


void cTileMap::reset(){//resets the original positions and sets car selection back to red car
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
	//booleans set that car can move forward or up depending on orientation of sprite
	bool redMove = true;
	bool yellowMove = true;
	bool blueMove = true;
	bool lightGreenMove = true;
	bool purpleLorryMove = true;
	bool yellowLorryMove = true;
	//detects whether if each car can move forward or up depending on orientation
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
	//checks if every car is selected
	//if selected then checks if it can move
	//and is within confines of grid
	//forward or up
	//boolean for movement is set to true so that score can be updated
		if (carSelect == 0){
			if (redMove){
				if (iMove[0] < 7){
					iMove[0]++;
					moved = true;
					if (iMove[0] == 7){//if position of red car is at 7 (outside of grid)
						finish = true;//then boolean finish set to true so that game can end
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
	//booleans set that car can move backward or down depending on orientation of sprite
	bool redMove = true;
	bool yellowMove = true;
	bool blueMove = true;
	bool lightGreenMove = true;
	bool purpleLorryMove = true;
	bool yellowLorryMove = true;
	//detects whether if each car can move forward or up depending on orientation
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
	//checks if every car is selected
	//if selected then checks if it can move
	//and is within confines of grid
	//backward or down
	//boolean for movement is set to true so that score can be updated
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


bool cTileMap::endLevel(bool levelEnd){//if finish boolean true (solved the game) then return true for function otherwise return false
	if (finish){
		finish = false;
		return true;
	}
	else{
		return false;
	}
}

bool cTileMap::updateScore(){//if moved boolean true (sprite moved) then return true for function otherwise return false
	if (moved){
		moved = false;
		return true;
	}
	else{
		return false;
	}
}

void cTileMap::addToCarSelect()//cycles through car selection
{
	carSelect++;//add 1 to car selection
	if (carSelect > 5){//if go beyond the amount of 6 car types
		carSelect = 0;//then set back to first car selection
	}
}

void cTileMap::subtractToCarSelect()//subtracts 1 to car selection
{
	carSelect -= 1;//subtracts 1 to car selection
	if (carSelect < 0){//if go under the amount of 6 car types
		carSelect = 5;//then set back to last car selection
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


/*
=================================================================
- Write the values from the map to the file
=================================================================
*/
void cTileMap::writeMapDataToFile(cFileHandler* aFile)
{

}
