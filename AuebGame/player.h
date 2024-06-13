#pragma once

#include "gameobject.h"
#include <sgg/graphics.h>
#include "box.h"

class Player : public Box, public GameObject
{

	graphics::Brush m_brush_player;

	const float m_accel_horizontal = 20.0f;
	const float m_accel_vertical = 300.1f;
	const float m_max_velocity = 5.0f;
	const float m_gravity = 10.0f;
	float points = 20.0f;
public:
	float m_vx = 0.0f;
	float m_vy = 0.0f;


public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	void drainPoints(float amount) { points = std::max<float>(0.0f, points - amount); } //Auksomiosi  points
	float getRemainingPoints() const { return points; }    // return ta points tou player
	bool oria();
	Player(std::string name) : GameObject(name) {}


protected:
	void debugDraw();

	void movePlayer(float dt);
};
