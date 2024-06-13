/***
* File : level.cpp
* Title : level class cpp file
* 
* Purpose:
* diaxeirizetai kai prosarmozei ta levels tou paixnidiou
* kathos kai buttons

	Fuctions:
* 
*	drawBlock
*		Dimiourgei Box typou block 
		oste na ftiaxtei to efe tis platformas
*
*	drawEnemy
*		Dimiourgei Box typou enemy
*		oste na iparxoyn enemies gia ton player
*
*	drawNotes
*		Dimiourgei Box typou notes
*		oste na mporei o player na mazepsei pontous 
*
*	drawWater
*		Dimiourgei Box typou water
*		oste na iparxoyn block enemies gia ton player
*
*	drawLeng
*		Dimiourgei Box typou leng
*		oste na iparxoyn oria gia tous enemies
*		kai na elegxetai i kinisi tous 
*
*	drawGate
*		Dimiourgei Box typou gate
*		oste na o player na allazei levels
*
*	checkCollisionsBlock
*		Elegxei sigkrouseis tou player me ta blocks
*		oste na mporei na kounithei pano stin platforma
* 
*	checkCollisionsEnemy
*		Elegxei sigkrouseis tou player me tous enemies
*		oste ean pesei pano tous na xasei h na kerdisei pontous
*		intersectDown -> +30 (delete enemy)
*		allios -> -10
*		
*	checkCollisionsNotes
*		Elegxei sigkrouseis tou player me ta notes
*		oste na mporoun na prostethoun pontoi
*		intersect -> +20 (delete note)
* 
* 
*	checkCollisionsWater
*		Elegxei sigkrouseis tou player me ta water
*		oste an pesei se water na xasei pontous
*
*	moveEnemy
*		Elegxei an o enemy sinanta box typoy m_leng 
		kai tote allazei tin fora tis kinisis
* 
*	update
*		kalei update sound kai alles sinartisis
*		oste na kanei update to level
* 
*	draw
*		analoga me to m_status 
*		thetei to sygkekrimeno background
*		kai prosthetei to sound button
* 
*	init
*		Ean to m_status >= 3 tote kalei tin readFile
*		opou pernei san orisma ena txt file (gia kathe level)
* 
* 
*	readFile
*		Dexetai san orisma ena txt file
*		Analoga me ta simvola pou diavazei dimiourgei boxes
*		P -> box typou block (road.png)
*		W -> box typou water (water.png)
*		e -> box typou enemy (enemy.png)
*		l -> box typou leng 
*		n -> box typou notes (notes.png)
*		G -> box typou gate (gate.png)
*	
*
*	updateSound
*		An patithei to S allazei to sound_on se on/off analoga
*		an sound_on -> soundsCheck
* 

*	soundsCheck
*		Elegxei sigkrouseis tou player me diafora boxes
*		oste na prosthesei ta katallila sounds
* 
* 
*	drawSound
*		Dimiourgei to button tou Sound
* 
*	nextLevel
*		An o player erthei se epafi me box typou gate
*		allazei to level se next level 
*		{
*			level 1 -> level 2
*			level 2 -> level 3
*			level 3 -> level 4
*			level 4 -> game over
*		}
*		An o player vgei ektos orion kanei restart to level
*		An oi pontoi tou player midesoun -> restart
* 
* 
*	 Included Files:
* 
* level.h
* sgg/graphics.h
* player.h
* util.h
* iostream
* fstream>
* iomanip
* 
* @file level.cpp
***/




#include "level.h"
#include <sgg/graphics.h>
#include "player.h"
#include "util.h"
#include <iostream>
#include <fstream>
#include <iomanip>

/***
* Drawing Block
* 
* NAME : drawBlock
* 
* @param i
* @param_type int
* @return none
* 
***/
void Level::drawBlock(int i)
{
	Box& box = m_blocks[i];
	std::string& name = m_block_names[i];

	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;


	m_block_brush.texture = m_state->getFullAssetPath("road.png");

	graphics::drawRect(x, y, 3.0f * m_block_size, 2.0f * m_block_size, m_block_brush);

	if (m_state->m_debugging) {
		graphics::drawRect(x, y, m_block_size, 0.4f + m_block_size, m_block_brush_debug);
	}

}

/***
* Drawing Enemy
*
* NAME : drawEnemy
*
* @param j
* @param_type int
* @return none
*
***/
void Level::drawEnemy(int j)
{
	Box& box = m_enemy[j];
	std::string& name = m_enemy_names[j];

	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;


	m_enemy_brush.texture = m_state->getFullAssetPath("enemy.png");

	graphics::drawRect(x, y + 0.5f, 3.0f * m_enemy_size, 2.5f * m_enemy_size, m_enemy_brush);

	if (m_state->m_debugging) {
		graphics::drawRect(x, y + 0.8f, 1.7f * m_enemy_size, 1.5f * m_enemy_size, m_enemy_brush_debug);
	}
}


/***
* Drawing Note
*
* NAME : drawNotes
*
* @param n
* @param_type int
* @return none
*
***/
void Level::drawNotes(int n)
{
	Box& box = m_notes[n];
	std::string& name = m_notes_names[n];

	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;


	m_notes_brush.texture = m_state->getFullAssetPath("notes.png");

	graphics::drawRect(x, y + 0.3f, 3.0f * m_notes_size, 1.8f * m_notes_size, m_notes_brush);

	if (m_state->m_debugging) {
		graphics::drawRect(x, y + 0.3f, 1.8f * m_notes_size, 1.5f * m_notes_size, m_notes_brush_debug);
	}
}


/***
* Drawing Water
*
* NAME : drawWater
*
* @param w
* @param_type int
* @return none
*
***/
void Level::drawWater(int w)
{
	Box& box = m_water[w];
	std::string& name = m_water_names[w];

	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;


	m_water_brush.texture = m_state->getFullAssetPath("water.png");

	graphics::drawRect(x, y, 1.5f * m_water_size, 2.8f * m_water_size, m_water_brush);

	if (m_state->m_debugging) {
		graphics::drawRect(x, y, m_water_size, 0.4f + m_water_size, m_water_brush_debug);
	}
}


/***
* Drawing Oria
*
* NAME : drawLeng
*
* @param l
* @param_type int
* @return none
*
***/
void Level::drawLeng(int l)
{
	Box& box = m_leng[l];

	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;

	graphics::drawRect(x, y, 1.5f * m_leng_size, 2.8f * m_leng_size, m_leng_brush);

	if (m_state->m_debugging)
	{
		graphics::drawRect(x, y, 1.5f * m_block_size, 2.8f * m_leng_size, m_leng_brush_debug);
	}
}


/***
* Drawing Gate
*
* NAME : drawGate
*
* @param g
* @param_type int
* @return none
*
***/
void Level::drawGate(int g)
{
	Box& box = m_gate[g];
	std::string& name = m_gate_names[g];

	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;


	m_gate_brush.texture = m_state->getFullAssetPath("gate.png");

	graphics::drawRect(x, y + 0.2f, 3.0f * m_gate_size, 1.8f * m_gate_size, m_gate_brush);

	if (m_state->m_debugging) {
		graphics::drawRect(x, y + 0.2f, 1.8f * m_gate_size, 1.5f + m_gate_size, m_gate_brush_debug);
	}
}


/***
* Drawing Sound widget
*
* NAME : drawSound
*
* @param none
* @return none
*
***/
void Level::drawSound()
{
	graphics::Brush m_sound;
	m_sound.outline_opacity = 0.0f;
	m_sound.fill_opacity = 1.0f;

	m_sound.texture = m_state->getFullAssetPath("sound.png");

	if (!sound_on)
	{
		m_sound.texture = m_state->getFullAssetPath("sound_off.png");
	}
	else
	{
		m_sound.texture = m_state->getFullAssetPath("sound.png");
	}

	graphics::drawRect(m_state->getCanvasWidth() - 15.0, 2.0f, 3.0f, 3.0f, m_sound);

	graphics::resetPose();
}


/***
* Elegxos gia sigkrouseis me Block
*
* NAME : checkCollisionsBlock
*
* @param none
* @return none
*
***/
void Level::checkCollisionsBlock()
{
	for (auto& block : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectDown(block))
		{
			m_state->getPlayer()->m_pos_y += offset;

			m_state->getPlayer()->m_vy = 0.0f;

			break;
		}
	}

	for (auto& block : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(block))
		{
			m_state->getPlayer()->m_pos_x += offset;

			m_state->getPlayer()->m_vx = 0.0f;
			break;
		}
		if (offset = m_state->getPlayer()->instersectUp(block))
		{
			m_state->getPlayer()->m_pos_y -= offset;

			m_state->getPlayer()->m_vy = 0.0f;
			break;
		}

	}

}


/***
* Elegxos gia sigkrouseis me Enemy
*
* NAME : checkCollisionsEnemy
*
* @param none
* @return none
*
***/
void Level::checkCollisionsEnemy()
{
	for (auto& box : m_enemy)
	{
		if (m_state->getPlayer()->intersectSideways(box))
		{
			m_state->getPlayer()->drainPoints(10.0f);
		}
	}

	for (auto ot = m_enemy.begin(); ot != m_enemy.end(); )
	{
		//ean o player pesei pano se enemy 
		if (m_state->getPlayer()->intersectDown(*ot))
		{
			if (sound_on)
			{
				graphics::playSound(m_state->getFullAssetPath("extra-bonus.wav"), 1.0f, false);
			}
			//+30 pontoi
			m_state->getPlayer()->drainPoints(-30.0f);

			//o enemy pethainei
			ot = m_enemy.erase(ot);
		}
		else
		{
			++ot;
		}
	}
}



/***
* Elegxos gia sigkrouseis me Note
*
* NAME : checkCollisionsNotes
*
* @param none
* @return none
*
***/
void Level::checkCollisionsNotes()
{
	for (auto it = m_notes.begin(); it != m_notes.end();) {
		if (m_state->getPlayer()->intersect(*it))
		{
			if (sound_on)
			{
				graphics::playSound(m_state->getFullAssetPath("notes.wav"), 1.0f, false);
			}
			m_state->getPlayer()->drainPoints(-20.0f);

			// afairesi tou it stoixeiou apo ton vector ton notes
			it = m_notes.erase(it);
		}
		else {
			++it; // auksisi tou deikti gia to epomeno stoixeio
		}
	}
}



/***
* Elegxos gia sigkrouseis me Water
*
* NAME : checkCollisionsWater
*
* @param none
* @return none
*
***/
void Level::checkCollisionsWater()
{

	for (auto& box : m_water)
	{
		if (m_state->getPlayer()->intersect(box))
		{
			m_state->getPlayer()->drainPoints(20.0f);

		}
	}

	for (auto& block : m_water)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectDown(block))
		{
			m_state->getPlayer()->m_pos_y += offset;

			m_state->getPlayer()->m_vy = 0.0f;

			break;
		}
	}

	for (auto& block : m_water)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(block))
		{
			m_state->getPlayer()->m_pos_x += offset;

			m_state->getPlayer()->m_vx = 0.0f;
			break;
		}
		if (offset = m_state->getPlayer()->instersectUp(block))
		{
			m_state->getPlayer()->m_pos_y -= offset;

			m_state->getPlayer()->m_vy = 0.0f;
			break;
		}

	}

}



/***
* Change Level
*
* NAME : nextLevel
*
* @param none
* @return none
*
***/
void Level::nextLevel() 
{
	
	if (!(m_state->getPlayer()->oria()))
	{
		m_state->updateLevel(m_status - 1);
	}
	for (auto& box : m_gate)
	{
		if (m_state->getPlayer()->intersect(box))
		{
			if(sound_on)
			{
				if (m_status < 6) 
				{
					graphics::playSound(m_state->getFullAssetPath("level.wav"), 1.0f, false);
				}
				else
				{
					graphics::playSound(m_state->getFullAssetPath("completed.wav"), 1.0f, false);
				}
			}
			m_state->updateLevel(m_status);
		}

	}

	if (m_state->getPlayer()->getRemainingPoints() == 0.0f)
	{
		m_state->updateLevel(m_status - 1);
	}
}


/***
* Kinisi enemy
*
* NAME : moveEnemy
*
* @param dt
* @param_type float
* @return none
*
***/
void Level::moveEnemy(float dt)
{
	float move = 0.2f;
	float delta_time = dt / 1000.0f;

	for (auto& enemy : m_enemy)
	{
		static bool change = true;

		//elegxos gia katse enemy  ksexorista
		for (auto& block : m_leng)
		{
			if (change)
			{
				enemy.m_pos_x -= move * delta_time;
				if (block.intersect(enemy))
				{
					change = false;
				}
			}
			else
			{
				enemy.m_pos_x += move * delta_time;

				if (block.intersect(enemy))
				{
					change = true;
				}
			}
		}
	}
}


/***
* Elegxos sound
*
* NAME : soundsCheck
*
* @param none
* @return none
*
***/
void Level::soundsCheck()
{
	if (graphics::getKeyState(graphics::SCANCODE_W) || (graphics::getKeyState(graphics::SCANCODE_UP)))
	{
		graphics::playSound(m_state->getFullAssetPath("jumping.wav"), 1.0f, false);
	}

	for (auto& box : m_water)
	{
		if (m_state->getPlayer()->intersect(box))
		{
			graphics::playSound(m_state->getFullAssetPath("water.wav"), 1.0f, false);
		}
	}
	for (auto& box : m_enemy)
	{
		if (m_state->getPlayer()->intersect(box))
		{
			graphics::playSound(m_state->getFullAssetPath("enemy.wav"), 1.0f, false);
		}
	}
	if ((graphics::getKeyState(graphics::SCANCODE_RETURN)) || (graphics::getKeyState(graphics::SCANCODE_KP_ENTER))
		|| (graphics::getKeyState(graphics::SCANCODE_M)) || (graphics::getKeyState(graphics::SCANCODE_S)) || (graphics::getKeyState(graphics::SCANCODE_H))
		|| (graphics::getKeyState(graphics::SCANCODE_BACKSPACE)))
	{
		graphics::playSound(m_state->getFullAssetPath("button.wav"), 1.0f, false);
	}
}


/***
* Update sound
*
* NAME : updateSound
*
* @param none
* @return none
*
***/
void Level::updateSound()
{
	
	if (graphics::getKeyState(graphics::SCANCODE_S))
	{
		sound_on = !sound_on;
	}
	if (sound_on)
	{
		soundsCheck();
	}
}

/***
* Update
*
* NAME : update
*
* @param dt
* @param_type float
* @return none
*
***/
void Level::update(float dt)
{
	updateSound();
	
	if(m_status >= 3) 
	{
		if (m_state->getPlayer()->isActive())
			m_state->getPlayer()->update(dt);
	}
		checkCollisionsBlock();
		checkCollisionsEnemy();
		checkCollisionsNotes();
		checkCollisionsWater();

		moveEnemy(dt);

		GameObject::update(dt);
	

	nextLevel();
}


/***
* Read File
*
* NAME : readFile
*
* @param filename
* @param_type const std::string&
* @return none
*
***/
void Level::readFile(const std::string& filename) {
	std::ifstream file(filename, std::ios::in | std::ios::binary);

	if (file.is_open()) {
		file >> std::noskipws;   // to xrisimopoioume oste na emfanistoun ta blocks stin thesi pou topothetountai sto txt arxeio
		char cell;
		float x = 0.0f;
		float y = 0.0f;

		while (file >> cell) {
			if (cell == '\n') {
				y += 2.0f;     // +2.0 oste na exoun tin katallili apostasi y ta blocks metaksi tous
				x = 0.0f;
				continue;
			}
			if (cell == 'P') {  // opou iparxei stixeio "P" sto map, topothetoume block typou road
				m_blocks.push_back(Box(x, y, 1.5, 2.0));

				m_block_names.push_back("road.png");

				m_block_brush.outline_opacity = 0.0f;
				m_block_brush_debug.fill_opacity = 0.1f;
				SETCOLOR(m_block_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
				SETCOLOR(m_block_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);
			}

			if (cell == 'W') { //opou iparxei stoixeio "W" sto map, topothetoume block typou water
				m_water.push_back(Box(x, y, 1.5, 2.0));

				m_water_names.push_back("water.png");

				m_water_brush.outline_opacity = 0.0f;
				m_water_brush_debug.fill_opacity = 0.1f;
				SETCOLOR(m_water_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
				SETCOLOR(m_water_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);
			}

			if (cell == 'n') {  //opou iparxei stoixeio "n" sto map, topothetoume block typou note
				m_notes.push_back(Box(x, y, 1.5, 2.0));

				m_notes_names.push_back("notes.png");

				m_notes_brush.outline_opacity = 0.0f;
				m_notes_brush_debug.fill_opacity = 0.1f;
				SETCOLOR(m_notes_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
				SETCOLOR(m_notes_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);
			}

			if (cell == 'e') { //opou iparxei stoixeio "n" sto map, topothetoume block typou enemy
				m_enemy.push_back(Box(x, y, 1.5, 1.0));

				m_enemy_names.push_back("enemy.png");

				m_enemy_brush.outline_opacity = 0.0f;
				m_enemy_brush_debug.fill_opacity = 0.1f;
				SETCOLOR(m_enemy_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
				SETCOLOR(m_enemy_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);

			}

			if (cell == 'l') // prospatheia gia oria oste na kinountai oi enemies mexri ena simeio, opou iparxei "l" ftiaxe ena aorato orthogonio
			{
				m_leng.push_back(Box(x, y, 1.5, 1.0));

				m_leng_brush.outline_opacity = 0.0f;
				m_leng_brush.fill_opacity = 0.0f;
				m_leng_brush_debug.fill_opacity = 0.0f;
				SETCOLOR(m_leng_brush_debug.fill_color, 0.0f, 0.0f, 0.0f);
				SETCOLOR(m_leng_brush_debug.outline_color, 0.0f, 0.0f, 0.0f);
			}

			if (cell == 'G') { //opou iparxei stoixeio "G" sto map, topothetoume block typou gate gia na perasoume sto epomeno level
				m_gate.push_back(Box(x, y, 1.5, 1.0));

				m_gate_names.push_back("gate.png");

				m_gate_brush.outline_opacity = 0.0f;
				m_gate_brush_debug.fill_opacity = 0.1f;
				SETCOLOR(m_gate_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
				SETCOLOR(m_gate_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);

			}
			x += 1.1f;    // +1.1 oste na exoun tin katallili apostasi x ta blocks metaksi tous
		}

		file.close();
	}
	else {
		std::cerr << "Σφάλμα: Δεν ήταν δυνατή η ανάγνωση του αρχείου.\n";
	}
}


/***
* Drawing Level
*
* NAME : draw
*
* @param none
* @return none
*
***/
void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	
	if (m_status >= 3)
	{
		float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
		float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;

		//draw background
		m_brush_background.texture = m_state->getFullAssetPath("background.png");
		graphics::drawRect(offset_x, offset_y, 2.0f * w, 4.0f * w, m_brush_background);

		// draw player
		if (m_state->getPlayer()->isActive())
			m_state->getPlayer()->draw();

		// draw blocks

		for (int i = 0; i < m_blocks.size(); i++)
		{
			drawBlock(i);
		}

		for (int j = 0; j < m_enemy.size(); j++)
		{
			drawEnemy(j);
		}

		for (int n = 0; n < m_notes.size(); n++)
		{
			drawNotes(n);
		}

		for (int w = 0; w < m_water.size(); w++)
		{
			drawWater(w);
		}

		for (int l = 0; l < m_leng.size(); l++)
		{
			drawLeng(l);
		}

		for (int g = 0; g < m_gate.size(); g++)
		{
			drawGate(g);
		}
	}
	else if (m_status == 0)
	{
		m_brush_background.texture = m_state->getFullAssetPath("start.png");
		graphics::drawRect(w / 2.0f, h / 2.0f, w, h, m_brush_background);
	}
	else if (m_status == 1)
	{
		m_brush_background.texture = m_state->getFullAssetPath("help.png");
		graphics::drawRect(w / 2.0f, h / 2.0f, w, h, m_brush_background);
	}
	else if (m_status == 2)
	{
		m_brush_background.texture = m_state->getFullAssetPath("over.png");
		graphics::drawRect(w / 2.0f, h / 2.0f, w, h, m_brush_background);
	}

	drawSound();
}


/***
* Init Level
*
* NAME : init
*
* @param none
* @return none
*
***/
void Level::init()
{
	if(m_status >= 3)
	{
		for (auto p_gob : m_static_objects)
			if (p_gob) p_gob->init();

		for (auto p_gob : m_dynamic_objects)
			if (p_gob) p_gob->init();

		if (m_status == 3)
			readFile(m_state->getFullAssetPath("level1.txt"));
		if(m_status == 4)
			readFile(m_state->getFullAssetPath("level2.txt"));
		if(m_status == 5)
			readFile(m_state->getFullAssetPath("level3.txt"));
		if (m_status == 6)
			readFile(m_state->getFullAssetPath("level4.txt"));
	}

}


/***
* Level
*
* NAME : level
*
* @param status
* @param_type const int
* @return none
*
***/
Level::Level(const int status)
{
	m_brush_background.outline_opacity = 0.0f;
	
	m_status = status;

	switch (m_status)
	{
	case 0:
		m_brush_background.texture = m_state->getFullAssetPath("start.png");
		break;
	case 1:
		m_brush_background.texture = m_state->getFullAssetPath("help.png");
		break;
	case 2 :
		m_brush_background.texture = m_state->getFullAssetPath("over.png");
		break;
	default:

		m_brush_background.texture = m_state->getFullAssetPath("background.png");
		break;
	}
	
}

Level::~Level()
{
	for (auto p_go : m_static_objects)
		delete p_go;
	for (auto p_go : m_dynamic_objects)
		delete p_go;
}