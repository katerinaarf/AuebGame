#include "player.h"
#include "util.h"
#include <cmath>

void Player::update(float dt)
{
	float delta_time = dt / 1000.0f;

	movePlayer(dt);

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;


	GameObject::update(dt);

}

void Player::draw()
{

	m_brush_player.texture = m_state->getFullAssetPath("kat.png");
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 2.0f, 2.0f, m_brush_player);

	if (m_state->m_debugging)
		debugDraw();
}


/***
* Sinartisi oria oste na elegxoume pou vrisketai o player
* an kseperastoun na mporei na ginei restart
* 
* NAME : oria
* 
* @param none
* @return none
* 
***/
bool Player::oria()
{
	float left_x = -30.0f;
	float right_x = 3.0f * m_state->getCanvasWidth();
	float top_y = -20.0f;
	float bottom_y = 4.0f * m_state->getCanvasHeight();

	
	return (m_pos_x >= left_x && m_pos_x <= right_x && m_pos_y >= top_y && m_pos_y <= bottom_y);
}

void Player::init()
{
	m_pos_x = 8.0f;
	m_pos_y = 6.0f;

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	m_brush_player.fill_opacity = 1.0f;
	m_brush_player.outline_opacity = 0.0f;
	m_brush_player.texture = m_state->getFullAssetPath("kat.png");


	m_width = 0.6f;
}

void Player::debugDraw()
{
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, m_width, m_height, debug_brush);

	char s[20];
	sprintf_s(s, "(%5.2f, %5.2f)", m_pos_x, m_pos_y);
	SETCOLOR(debug_brush.fill_color, 1, 0, 0);
	debug_brush.fill_opacity = 1.0f;
	graphics::drawText(m_state->getCanvasWidth() * 0.5f - 0.4f, m_state->getCanvasHeight() * 0.5f - 0.6f, 0.15f, s, debug_brush);
}


/***
* Elegxos key oste na mporei o player na metakinithei 
* 
* NAME : movePlayer
* 
* @param dt
* @param_type float
* @return none
* 
***/
void Player::movePlayer(float dt)
{
	float delta_time = dt / 1000.0f;

	
	float move = 0.0f;
	if ((graphics::getKeyState(graphics::SCANCODE_A)) || (graphics::getKeyState(graphics::SCANCODE_LEFT)))
		move -= 1.8f;
	if ((graphics::getKeyState(graphics::SCANCODE_D)) || (graphics::getKeyState(graphics::SCANCODE_RIGHT)))
		move = 1.8f;

	m_vx = std::min<float>(m_max_velocity, m_vx + delta_time * move * m_accel_horizontal);
	m_vx = std::max<float>(-m_max_velocity, m_vx);

	
	m_vx -= 0.2f * m_vx / (0.4f + fabs(m_vx));


	if (fabs(m_vx) < 0.01f)
		m_vx = 0.0f;

	
	m_pos_x += m_vx * delta_time;

	
	if (m_vy == 0.0f)
		m_vy -= ((graphics::getKeyState(graphics::SCANCODE_W)) || (graphics::getKeyState(graphics::SCANCODE_UP)) ? m_accel_vertical : 0.0f) * 0.02f;
	
	
	m_vy += delta_time * m_gravity;

	
	m_pos_y += m_vy * delta_time;

}
