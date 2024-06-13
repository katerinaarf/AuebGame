/***
* File : gamestate.cpp
* Title : game state class cpp file
* 
* Purpose :
* Diaxeirizetai ta status tou paixnidiou 
* kai kapoia widgets/buttons
* 
*	Fuctions:
*	
*	init
*		Analoga me to status kalei tin Level oste na dimiourgisei 
*		ta diaforetika states tou paixnidiou
* 
*	draw
*		Analoga me ta diaforetika states prosthetei
*		ta aparaithta buttons kai widgets
* 
*	drawBack
*		Dimiourgei to back button
*		//an patithei to Backspace key epistrefei ton xristi sto Start Screen
* 
*	drawMusic
*		Dimiourgei to music button 
* 
*	drawBattery
*		Dimiourgei to battery widget
*		analoga me ta points tou player dialegei mia eikona battery, oste na dinei tin aisthsh animated battery
* 
*	update
*		Kalei oles tis update gia na ananeosei to state
*		ean patithei to 0 key emfanizei to debugging mode
* 
*	updateStartScreen
*		Update gia Start Screen
*		an patithei to ENTER allazei to state se LEVEL 1
*		an patithei to  H allazei to state se HELP
* 
*	updateMusic 
*		Update gia tin mousiki tou paixnidiou
*		an patithei to M antistrefei to music_on
* 
*	update MusicOnOff
*		an music_on = true -> play Music allios stop Music
*		
*	updateBack
*		Update gia to back button
*		an patithei to BACKSPASE allazei to state se START SCREEN
* 
*	updateLevel
*		(kirios gia ta 4 levels tou paixnidiou)
*		pairnei os orisma to current level/status (se int) tou paixnidiou 
*		kai to allazei me to amesos epomeno tou 
*		(an level = 4) tote status = GAME OVER
*		
*	getFullAssetPath
*		epistrefei to  full asset path
* 
*	getAssetDir
*		epistrefei to asset dir
* 
*	 Included Files:
* 
* gamestate.h
* level.h
* player.h
* thread
* chrono
* 
* 
*@file gamestate.cpp 
***/


#include "gamestate.h"
#include "level.h"
#include "player.h"
#include <thread>
#include <chrono>
using namespace std::chrono_literals;


GameState::GameState()
{
}

GameState::~GameState()
{
	if (m_current_level)
		delete m_current_level;
}

GameState* GameState::getInstance()
{
	if (!m_unique_instance)
	{
		m_unique_instance = new GameState();
	}
	return m_unique_instance;
}



/***
* Init GameState
* 
* 
* NAME : init
* 
* @param  none
* @return  none
* 
***/
void GameState::init()
{
	if (music_on)
	{
		graphics::playMusic(getFullAssetPath("music.mp3"), 1.0f, true, 400);   
	}

	switch (current_status)
	{
		case STATUS_START:
		{
			m_current_level = new Level(current_status);
			break;
		}
		case STATUS_GAME_OVER:
		{
			m_current_level = new Level(current_status);
			break;
		}
		case STATUS_HELP:
		{
			m_current_level = new Level(current_status);
			break;
		}
		case STATUS_LEVEL_1:
		{
			m_current_level = new Level(current_status);
			break;
		}
		case STATUS_LEVEL_2:
		{
			m_current_level = new Level(current_status);
			break;
		}
		case STATUS_LEVEL_3:
		{
			m_current_level = new Level(current_status);
			break;
		}
		case STATUS_LEVEL_4:
		{
			m_current_level = new Level(current_status);
			break;
		}
	}

	m_current_level->init();
	
	m_player = new Player("Player");
	m_player->init();

}


/***
* Drawing buttons
* 
* NAME : draw
* 
* @param none
* @return none
* 
***/
void GameState::draw()
{
	m_current_level->draw();
	
	if (current_status != STATUS_START)
	{
		drawBack();

		if ((current_status != STATUS_GAME_OVER) && (current_status != STATUS_HELP))
		{
			drawBattery();
		}
	}
	
	drawMusic();
}


/***
* Drawing Back button
*
* NAME : drawBack
* 
* @param none
* @return none
* 
***/
void GameState::drawBack()
{
	graphics::Brush m_back;
	m_back.outline_opacity = 0.0f;
	m_back.fill_opacity = 1.0f;

	m_back.texture = getFullAssetPath("back.png");

	graphics::drawRect(getCanvasWidth() - 21.0, 2.0f, 3.0f, 1.5f, m_back);

	graphics::resetPose();
}


/***
* Drawing Music button
* 
* NAME : drawMusic
* 
* @param none
* @return none
* 
***/
void GameState::drawMusic()
{
	graphics::Brush m_music;
	m_music.outline_opacity = 0.0f;
	m_music.fill_opacity = 1.0f;

	m_music.texture = getFullAssetPath("music.png");

	if (!music_on)
	{
		m_music.texture = getFullAssetPath("music_off.png");
	}
	else
	{
		m_music.texture = getFullAssetPath("music.png");
	}

	graphics::drawRect(getCanvasWidth() - 10.0, 2.0f, 2.7f, 2.7f, m_music);

	graphics::resetPose();
}


/***
* Drawing Battery widget
* 
* NAME : drawBattery
* 
* @param none
* @return none
* 
***/
void GameState::drawBattery()
{
	float m_player_points = m_player ? m_player->getRemainingPoints() : 0;    //ean exei pontous allios arxikopoioume me 0

	graphics::Brush m_poi;
	m_poi.outline_opacity = 0.0f;
	m_poi.fill_opacity = 1.0f;

	std::string imagePath = "assets\\battery_0.png";        //arxikopoihsi tou path

	//analoga me to posous pontous exei o paiktis rithmizoume thn eikona tou pawer
	if (m_player_points == 0)
	{
		imagePath = getFullAssetPath("battery_0.png");
	}
	else if (m_player_points < 20)
	{
		imagePath = getFullAssetPath("battery_1.png");
	}
	else if (m_player_points < 30)
	{
		imagePath = getFullAssetPath("battery_2.png");
	}
	else if (m_player_points < 40)
	{
		imagePath = getFullAssetPath("battery_3.png");
	}
	else if (m_player_points < 50)
	{
		imagePath = getFullAssetPath("battery_4.png");
	}
	else
	{
		imagePath = getFullAssetPath("battery_5.png");
	}

	m_poi.texture = imagePath.c_str();  // xrisimopoioume to  c_str() gia to path tis eikonas


	graphics::drawRect(getCanvasWidth() - 4.0, 2.0f, 4.0f, 2.0f, m_poi);
}


/***
* Update GameState
* 
* NAME : update
* 
* @param dt
* @param_type float
* @return none
***/
void GameState::update(float dt)
{

	// Skip an update if a long delay is detected 
	// to avoid messing up the collision simulation
	if (dt > 500) // ms
		return;

	// Avoid too quick updates
	float sleep_time = std::max(17.0f - dt, 0.0f);
	if (sleep_time > 0.0f)
	{
		std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));
	}
	
	m_current_level->update(dt);

	updateBack();
	
	updateMusic();

	updateStartScreen();
	
	m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
}



/***
* Update Start Screen
* 
* NAME : updateStartScreen
* 
* @param none
* @return none
* 
***/
void GameState::updateStartScreen()
{
	if ((graphics::getKeyState(graphics::SCANCODE_KP_ENTER)) || (graphics::getKeyState(graphics::SCANCODE_RETURN)))
	{
		current_status = STATUS_LEVEL_1;
		init();
	}
	if (graphics::getKeyState(graphics::SCANCODE_H))
	{
		current_status = STATUS_HELP;
		init();
	}
}


/***
* Update Music 
* 
* NAME : updateMusic
* 
* @param none
* @return none
* 
***/
void GameState::updateMusic()
{	
	if (graphics::getKeyState(graphics::SCANCODE_M))
	{
		music_on = !music_on;
		updateMusicOnOff();
	}

}


/***
* Update Music On Off
* 
* NAME : updateMusicOnOff
* 
* @param none
* @return none
* 
***/
void GameState::updateMusicOnOff()
{

	if (music_on)
	{
		graphics::playMusic(getFullAssetPath("music.mp3"), 1.0f);
	}
	else
	{
		graphics::stopMusic(400);
	}
}


/***
*Update Back
* 
* NAME updateBack
* 
* @param none
* @return none
* 
***/
void GameState::updateBack()
{
	if(graphics::getKeyState(graphics::SCANCODE_BACKSPACE))
	{
		current_status = STATUS_START;
		init();
	}
}


/***
*Update Level status
* 
* NAME : updateLevel
* 
* @param m_status
* @param_type const int
* @return none
* 
***/
void GameState::updateLevel(const int m_status)
{

	switch (m_status)
	{
	case 3 :
		current_status = STATUS_LEVEL_2;
		break;
	case 4 :
		current_status = STATUS_LEVEL_3;
		break;
	case 5:
		current_status = STATUS_LEVEL_4;
		break;
	case 6:
		current_status = STATUS_GAME_OVER;
		break;
	}

	init();
}


/***
* Get Full Asset Path 
* 
* NAME : getFullAssetPath
* 
* @param asset
* @param_type const std::string&
* @return asset path
* @rtype std::string
* 
***/
std::string GameState::getFullAssetPath(const std::string& asset)
{
	return m_asset_path + asset;
}


/***
* Get Asset Dir
*
* NAME : getAssetDir
*
* @param none
* @return asset path
* @rtype std::string
*
***/
std::string GameState::getAssetDir()
{
	return m_asset_path;
}

GameState* GameState::m_unique_instance = nullptr;