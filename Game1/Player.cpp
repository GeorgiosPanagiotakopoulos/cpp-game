#include "player.h"
#include "Config.h"
#include <cmath>
#include <iostream>
using namespace std;

void Player::update(float dt)
{	
	/*
	cout << m_pos_x << endl;
	
	float delta_time = dt / 100.0f;

	const float velocity = 10.f;
	if (graphics::getKeyState(graphics::SCANCODE_A))
		m_pos_x -= delta_time * velocity;
	if (graphics::getKeyState(graphics::SCANCODE_D))
		m_pos_x += delta_time * velocity;
	if (graphics::getKeyState(graphics::SCANCODE_W))
		m_pos_y -= delta_time * velocity;
	if (graphics::getKeyState(graphics::SCANCODE_S))
		m_pos_y += delta_time * velocity;
	*/
	movePlayer(dt);

	// update offset for other game objects
	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	GameObject::update(dt);

}

void Player::draw()
{

	int sprite = (int)fmodf(10000.0f - m_pos_x * 8.0f, m_sprites.size());
	m_brush_player.texture = m_sprites[sprite];

	graphics::drawRect(m_pos_x, m_pos_y, 40.0f, 40.0f, m_brush_player);

}

void Player::init()
{
	// stage 1
	setPlayerInitPosition();

	//m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	//m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	m_brush_player.fill_opacity = 1.0f;
	m_brush_player.outline_opacity = 0.0f;
	m_brush_player.texture = m_state->getFullAssetPath("p1.png");

	m_sprites.push_back(m_state->getFullAssetPath("p1.png"));
	m_sprites.push_back(m_state->getFullAssetPath("p2.png"));
	m_sprites.push_back(m_state->getFullAssetPath("p3.png"));
	m_sprites.push_back(m_state->getFullAssetPath("p4.png"));


	// Adjust width for finer collision detection
	m_width = 0.5f;

}

void Player::movePlayer(float dt)
{
	float delta_time = dt / 40.0f;

	// Stage 2 code: Acceleration-based velocity
	float move = 0.0f;
	if (graphics::getKeyState(graphics::SCANCODE_A)) {
		move -= 1.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_D)) {
		move = 1.0f;
	}


	//X
	m_vx = std::min<float>(m_max_velocity, m_vx + delta_time * move * m_accel_horizontal);//frazw thn taxythta
	m_vx = std::max<float>(-m_max_velocity, m_vx);//frazw thn taxuthta
	m_vx -= 0.2f * m_vx / (0.1f + fabs(m_vx));// einai gia na stamataei...synexws epibradinei
	// den prepei sunexws na epibradinei...an einai kati poly mikro to kanei 0
	if (fabs(m_vx) < 0.01f) {
		m_vx = 0.0f;
	}
	m_pos_x += m_vx * delta_time;



	//Y
	// jump only when not in flight:
	if (m_vy == 0.0f)
		m_vy -= (graphics::getKeyState(graphics::SCANCODE_W) ? m_accel_vertical : 0.0f) ;// not delta_time!! Burst 

	
	// add gravity
	m_vy += delta_time * m_gravity;

	// adjust vertical position
	m_pos_y += m_vy * delta_time;

	

}
