/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
static cFontMgr* theFontMgr = cFontMgr::getInstance();
static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();
static cButtonMgr* theButtonMgr = cButtonMgr::getInstance();
//sets reference for cTile Map to carMap
cTileMap carMap;
/*
=================================================================================
Constructor
=================================================================================
*/
cGame::cGame()
{

}
/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cGame* cGame::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cGame();
	}
	return cGame::pInstance;
}


void cGame::initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	scoreS = to_string(score);//sets string score to score integer

	// Get width and height of render context
	SDL_GetRendererOutputSize(theRenderer, &renderWidth, &renderHeight);
	this->m_lastTime = high_resolution_clock::now();
	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);
	
	theTextureMgr->setRenderer(theRenderer);
	theFontMgr->initFontLib();
	theSoundMgr->initMixer();

	theAreaClicked = { 0, 0 };
	// Store the textures
	//new texture names
	textureName = { "Red Car", "Blue Car", "Light Green Car", "Blue Lorry", "Yellow Lorry", "Purple Lorry", "Yellow Car", "Border", "theGrid", "BackgroundMenu", "BackgroundEnd" };
	//sets the image locations
	texturesToUse = {"Images/Cars/Red Car.png", "Images/Cars/Blue Car.png", "Images/Cars/Light Green Car.png", "Images/Cars/Blue Lorry.png", "Images/Cars/Yellow Lorry.png", "Images/Cars/Purple Lorry.png", "Images/Cars/Yellow Car.png", "Images/Cars/Border.png", "Images/Bkg/Grid.png", "Images/Bkg/Background.png", "Images/Bkg/Background2.png" };
	for (int tCount = 0; tCount < textureName.size(); tCount++)
	{	
		theTextureMgr->addTexture(textureName[tCount], texturesToUse[tCount]);
	}
	tempTextTexture = theTextureMgr->getTexture("Red Car");
	aRect = { 0, 0, tempTextTexture->getTextureRect().w/2, tempTextTexture->getTextureRect().h };
	aColour = { 228, 213, 238, 255 };
	// Store the textures
	//new replay button
	btnNameList = { "exit_btn", "menu_btn", "play_btn", "replay_btn" };
	btnTexturesToUse = { "Images/Buttons/ExitButton.png", "Images/Buttons/MenuButton.png", "Images/Buttons/PlayButton.png", "Images/Buttons/ReplayButton.png" };
	btnPos = { { 400, 375 }, { 500, 500 }, { 400, 300 }, { 500, 500} };
	for (int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		theTextureMgr->addTexture(btnNameList[bCount], btnTexturesToUse[bCount]);
	}
	for (int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		cButton * newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture(btnNameList[bCount]));
		newBtn->setSpritePos(btnPos[bCount]);
		newBtn->setSpriteDimensions(theTextureMgr->getTexture(btnNameList[bCount])->getTWidth(), theTextureMgr->getTexture(btnNameList[bCount])->getTHeight());
		theButtonMgr->add(btnNameList[bCount], newBtn);
	}
	theGameState = MENU;//sets the renderer to menu scene on startup
	theBtnType = EXIT;
	// Create textures for Game Dialogue (text)
	fontList = { "Traffic"};
	fontsToUse = { "Fonts/TrafficFont.ttf" };
	for (int fonts = 0; fonts < fontList.size(); fonts++)
	{
		theFontMgr->addFont(fontList[fonts], fontsToUse[fonts], 48);
	}
	// Create text Textures
	gameTextNames = { "Title", "Objective", "Congrats", "Congrats2", "TryAgain", "Score"};
	gameTextList = { "RUSH Traffic Jam", "Move the cars to get red car out", "Congrats you solved the ", "Jam with a score of ", "Game Over!! TRY AGAIN", "Score: " };
	for (int text = 0; text < gameTextNames.size(); text++)
	{
		theTextureMgr->addTexture(gameTextNames[text], theFontMgr->getFont("Traffic")->createTextTexture(theRenderer, gameTextList[text], SOLID, { 255, 0, 0, 255 }, { 0, 0, 0, 0 }));
	}
	// Load game sounds
	soundList = { "theme", "screech" };
	soundTypes = { MUSIC, SFX };
	soundsToUse = { "Audio/Theme/Frightened Rabbit.mp3", "Audio/SFX/CarScreech.wav"};
	for (int sounds = 0; sounds < soundList.size(); sounds++)
	{
		theSoundMgr->add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]);
	}

	theSoundMgr->getSnd("theme")->play(-1);//plays song infinetly

	spriteBkgd.setSpritePos({ 0, 0 });//sets background position to top left od SDL window
	spriteBkgd.setTexture(theTextureMgr->getTexture("BackgroundMenu"));//sets background image
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("BackgroundMenu")->getTWidth(), theTextureMgr->getTexture("BackgroundMenu")->getTHeight());//sets the dimensions of background sprite equal to dimension of background image

	carMap.setMapStartXY({ 100, 100 });//sets the x and y of top left of grid to 100X100
}

void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)//This is constantly runs 
{
	loop = true;

	while (loop)//run while loop is true
	{
		//We get the time that passed since the last frame
		double elapsedTime = this->getElapsedSeconds();

		loop = this->getInput(loop);
		this->update(elapsedTime);
		this->render(theSDLWND, theRenderer);
	}
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	SDL_RenderClear(theRenderer);
	switch (theGameState)
	{
	case MENU:
	{
		{
			//set background for this scene
			spriteBkgd.setSpritePos({ 0, 0 });
			spriteBkgd.setTexture(theTextureMgr->getTexture("BackgroundMenu"));
			spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("BackgroundMenu")->getTWidth(), theTextureMgr->getTexture("BackgroundMenu")->getTHeight());
			spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		}
		// Render the Title
		tempTextTexture = theTextureMgr->getTexture("Title");
		pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		scale = { 1, 1 };
		//render game objective
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		tempTextTexture = theTextureMgr->getTexture("Objective");
		pos = { 10, 75, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		// Render Buttons
		theButtonMgr->getBtn("play_btn")->render(theRenderer, &theButtonMgr->getBtn("play_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("play_btn")->getSpritePos(), theButtonMgr->getBtn("play_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 50, 325 });
		theButtonMgr->getBtn("play_btn")->setSpritePos({ 50, 250 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
	}
	break;
	case PLAYING:
	{
		{
			//set background for this scene
			spriteBkgd.setSpritePos({ 0, 0 });
			spriteBkgd.setTexture(theTextureMgr->getTexture("theGrid"));
			spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theGrid")->getTWidth(), theTextureMgr->getTexture("theGrid")->getTHeight());
			spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		}
		tempTextTexture = theTextureMgr->getTexture("Title");
		pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//render "Score :" at top right
		tempTextTexture = theTextureMgr->getTexture("Score");
		pos = { 700, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//add a text of score string and then render
		theTextureMgr->addTexture("ScoreNum", theFontMgr->getFont("Traffic")->createTextTexture(theRenderer, scoreS.c_str(), SOLID, { 255, 0, 0, 255 }, { 0, 0, 0, 0 }));
		tempTextTexture = theTextureMgr->getTexture("ScoreNum");
		pos = { 900, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		//set top left of grid
		carMap.setMapStartXY({ 100, 100 });
		carMap.render(theSDLWND, theRenderer, theTextureMgr, textureName);
		// Buttons Rendered
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 740, 525 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
	}
	break;
	case END:
	{
		{
			//set background for this scene
			spriteBkgd.setSpritePos({ 0, 0 });
			spriteBkgd.setTexture(theTextureMgr->getTexture("BackgroundEnd"));
			spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("BackgroundEnd")->getTWidth(), theTextureMgr->getTexture("BackgroundEnd")->getTHeight());
			spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		}
		tempTextTexture = theTextureMgr->getTexture("Title");
		pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//render retry text
		tempTextTexture = theTextureMgr->getTexture("TryAgain");
		pos = { 10, 100, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//render buttons
		theButtonMgr->getBtn("menu_btn")->setSpritePos({ 500, 325 });
		theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteScale());
		theButtonMgr->getBtn("replay_btn")->setSpritePos({ 500, 400 });
		theButtonMgr->getBtn("replay_btn")->render(theRenderer, &theButtonMgr->getBtn("replay_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("replay_btn")->getSpritePos(), theButtonMgr->getBtn("replay_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 500, 475 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());	
	}
	break;
	case WON:
	{
		{
			//set background for this scene
			spriteBkgd.setSpritePos({ 0, 0 });
			spriteBkgd.setTexture(theTextureMgr->getTexture("BackgroundEnd"));
			spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("BackgroundEnd")->getTWidth(), theTextureMgr->getTexture("BackgroundEnd")->getTHeight());
			spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		}
		tempTextTexture = theTextureMgr->getTexture("Title");
		pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//render the congratulation message
		tempTextTexture = theTextureMgr->getTexture("Congrats");
		pos = { 10, 100, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		tempTextTexture = theTextureMgr->getTexture("Congrats2");
		pos = { 10, 175, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//render score amount
		theTextureMgr->addTexture("ScoreNum", theFontMgr->getFont("Traffic")->createTextTexture(theRenderer, scoreS.c_str(), SOLID, { 255, 0, 0, 255 }, { 0, 0, 0, 0 }));
		tempTextTexture = theTextureMgr->getTexture("ScoreNum");
		pos = { 600, 175, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		theButtonMgr->getBtn("menu_btn")->setSpritePos({ 500, 325 });
		theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteScale());
		theButtonMgr->getBtn("replay_btn")->setSpritePos({ 500, 400 });
		theButtonMgr->getBtn("replay_btn")->render(theRenderer, &theButtonMgr->getBtn("replay_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("replay_btn")->getSpritePos(), theButtonMgr->getBtn("replay_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 500, 475 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
	}
	break;
	case QUIT:
	{
		//stop the game
		loop = false;
	}
	break;
	default:
		break;
	}
	SDL_RenderPresent(theRenderer);
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre)
{
	SDL_RenderPresent(theRenderer);
}

void cGame::update()
{

}


void cGame::update(double deltaTime)
{
	// CHeck Button clicked and change state
	switch (theGameState)
	{
		case MENU:
		{
			//change scene if button clicked
			theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, QUIT, theAreaClicked);
			theGameState = theButtonMgr->getBtn("play_btn")->update(theGameState, PLAYING, theAreaClicked);
		}
		break;
		case PLAYING:
		{
			if (play){//if play is true then reset game and make play false 
				gameReset(true);
				play = false;
			}
			//change scene if button clicked
			theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, END, theAreaClicked);
		}
		break;
		case END:
		{
			play = true;//play is true
			//change scene if button clicked
			theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, QUIT, theAreaClicked);
			theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, MENU, theAreaClicked);
			theGameState = theButtonMgr->getBtn("replay_btn")->update(theGameState, PLAYING, theAreaClicked);
		}
		break;
		case WON:
		{
			play = true;//play is true
			//change scene if button clicked
			theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, QUIT, theAreaClicked);
			theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, MENU, theAreaClicked);
			theGameState = theButtonMgr->getBtn("replay_btn")->update(theGameState, PLAYING, theAreaClicked);
		}
		break;
		case QUIT:
		{
		}
		break;
		default:
			break;
	}
}

bool cGame::gameReset(bool reset){
	//if reset true then 
	if (reset){
		carMap.reset();//call for positions to be reset 
		score = 0;//score to 0
		scoreS = to_string(score);//convert integer score to a string
		theTextureMgr->deleteTexture("ScoreNum");//delete old text for displaying score 
	}
	return true;
}


bool cGame::getInput(bool theLoop)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			theLoop = false;//the window to close
		}

		switch (event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
				{
					theAreaClicked = { event.motion.x, event.motion.y };//position of area when clicked
				}
				break;
				case SDL_BUTTON_RIGHT:
					break;
				default:
					break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
				{
			
				}
				break;
				case SDL_BUTTON_RIGHT:
					break;
				default:
					break;
				}
				break;
			case SDL_MOUSEMOTION:
			{
			}
			break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					theLoop = false;//closes the window
					break;
				case SDLK_DOWN:
				{
					if (theGameState == PLAYING){//if in play scene
						carMap.subtractOneToMove();//move selected car left or down if possible
						if (carMap.updateScore()){//check if moved
							theSoundMgr->getSnd("screech")->play(0);//play sound once
							score++;//add 1 to score
							scoreS = to_string(score);//convert integer score to a string
							theTextureMgr->deleteTexture("ScoreNum");//delete old text for displaying score 
						}
					}
				}
				break;

				case SDLK_UP:
				{
					if (theGameState == PLAYING){//if in play scene
						carMap.addOneToMove();//move selected car right or up if possible
						if (carMap.endLevel(true)){//check if reached end
							theGameState = WON;//go to won scene
							theAreaClicked = { 0, 0 };//make top left 
						}
						if (carMap.updateScore()){//check if moved
							theSoundMgr->getSnd("screech")->play(0);//play sound once
							score++;//add 1 to score
							scoreS = to_string(score);//convert integer score to a string
							theTextureMgr->deleteTexture("ScoreNum");//delete old text for displaying score 
						}
					}
				}
				break;
				case SDLK_RIGHT:
				{
					if (theGameState == PLAYING){//if in play scene
						carMap.addToCarSelect();//move car selection
					}
				}
				break;
				case SDLK_LEFT:
				{
					if (theGameState == PLAYING){//if in play scene
						carMap.subtractToCarSelect();//move car selection
					}
				}
				break;
				case SDLK_SPACE:
				{
				}
				break;
				default:
					break;
				}

			default:
				break;
		}

	}
	return theLoop;
}


double cGame::getElapsedSeconds()
{
	this->m_CurrentTime = high_resolution_clock::now();
	this->deltaTime = (this->m_CurrentTime - this->m_lastTime);
	this->m_lastTime = this->m_CurrentTime;
	return deltaTime.count();
}

void cGame::cleanUp(SDL_Window* theSDLWND)
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(theSDLWND);

	// Destroy the window
	SDL_DestroyWindow(theSDLWND);

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}

