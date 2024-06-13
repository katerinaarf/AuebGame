#pragma once

#include <string>
#include <sgg/graphics.h>

class GameState
{
	//status gia diaforetikes energeies tou paixnidiou
	typedef enum { STATUS_START, STATUS_HELP, STATUS_GAME_OVER, STATUS_LEVEL_1, STATUS_LEVEL_2, STATUS_LEVEL_3, STATUS_LEVEL_4 } status;

private:
	static GameState* m_unique_instance;

	status current_status = STATUS_START;  // arxiko status paixnidiou (Start Screen)

	graphics::Brush m_brush_background;  //brush gia background

	const std::string m_asset_path = "assets\\";     

	const float m_canvas_width = 24.0f;
	const float m_canvas_height = 26.0f;

	class Level* m_current_level = 0 ;
	class Player* m_player = 0;

	bool music_on = true;      //metavliti gia on/off music

	GameState();

public:
	float m_global_offset_x = 5.0f;
	float m_global_offset_y = 5.0f;

	bool m_debugging = false;
	float w = getCanvasWidth();
	float h = getCanvasHeight();


public:
	~GameState();
	static GameState* getInstance();

	void init();
	void draw();

	void drawBack();   
	void drawMusic();
	void drawBattery();

	void update(float dt);

	void updateStartScreen();

	void updateLevel(const int m_status);

	void updateMusic(); 
	void updateMusicOnOff();
	void updateBack();

	std::string getFullAssetPath(const std::string& asset);
	std::string getAssetDir();

	float getCanvasWidth() { return m_canvas_width; }
	float getCanvasHeight() { return m_canvas_height; }

	class Player* getPlayer() { return m_player; }
	bool playMusic() const { return music_on; };

};