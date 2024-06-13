#pragma once

#include "gameobject.h"
#include <vector>
#include <list>
#include <string>
#include <sgg/graphics.h>
#include <fstream>
#include <iostream>
#include "box.h"
#include "player.h"

class Level : public GameObject
{
	graphics::Brush m_brush_background;

	std::vector<GameObject* > m_static_objects;
	std::list<GameObject* > m_dynamic_objects;

	std::vector<Box> m_blocks;
	std::vector<std::string> m_block_names;

	std::vector<Box> m_enemy;
	std::vector<std::string> m_enemy_names;

	std::vector<Box> m_notes;
	std::vector<std::string> m_notes_names;

	std::vector<Box> m_water;
	std::vector<std::string> m_water_names;

	std::vector<Box> m_leng;
	
	std::vector<Box> m_gate;
	std::vector<std::string> m_gate_names;

	const float m_block_size = 1.0f;
	graphics::Brush m_block_brush;
	graphics::Brush m_block_brush_debug;

	const float m_enemy_size = 1.0f;
	graphics::Brush m_enemy_brush;
	graphics::Brush m_enemy_brush_debug;

	const float m_notes_size = 1.0f;
	graphics::Brush m_notes_brush;
	graphics::Brush m_notes_brush_debug;

	const float m_water_size = 1.0f;
	graphics::Brush m_water_brush;
	graphics::Brush m_water_brush_debug;

	const float m_leng_size = 1.0f;
	graphics::Brush m_leng_brush;
	graphics::Brush m_leng_brush_debug;

	const float m_gate_size = 1.0f;
	graphics::Brush m_gate_brush;
	graphics::Brush m_gate_brush_debug;

	float m_center_x = 5.0f;
	float m_center_y = 5.0f;
	

	void drawBlock(int i);

	void drawEnemy(int j);

	void drawNotes(int n);

	void drawWater(int w);

	void drawLeng(int l);

	void drawGate(int g);

	void checkCollisionsBlock();
	void checkCollisionsEnemy();
	void checkCollisionsNotes();
	void checkCollisionsWater();

	void moveEnemy(float dt);

private:
	int m_status;

public:
	float e_vx = 0.0f;
	bool sound_on = true;

public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	void readFile(const std::string& filename);

	void updateSound();
	void soundsCheck();
	void drawSound();
	void nextLevel();

	Level(const int status);
	~Level() override;

};