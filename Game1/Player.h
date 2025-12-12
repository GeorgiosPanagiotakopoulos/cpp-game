#pragma once

#include "gameobject.h"
#include <sgg/graphics.h>
#include "box.h"

#if (STAGE > 1)
#include <array>
#endif

#if (STAGE >= 4)
#include "sprite.h"
#endif

class Player : public Box, public GameObject
{
	// animated player
	std::vector<std::string> m_sprites;


	// float Stage 1 variables
	graphics::Brush m_brush_player;

	// dynamic motion control
	const float m_accel_horizontal = 6.0f;
	const float m_accel_vertical = 6.0f;
	const float m_max_velocity = 3.0f;
	const float m_gravity = 0.2f;
public:
	float m_vx = 0.0f;
	float m_vy = 0.0f;


public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	Player(std::string name) : GameObject(name) {};
	void setPlayerInitPosition() {
		m_pos_x = 65.0f;
		m_pos_y = 0.0f;
	}

protected:
	

	// dynamic motion control
	void movePlayer(float dt);
};



