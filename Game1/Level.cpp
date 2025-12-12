#include "level.h"
#include <sgg/graphics.h>
#include "player.h"
#include <iostream>
#include <string>
using namespace std;



void Level::checkCollisions()
{


	m_blocks = map_blocks.at(raceNumber);

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



	std::vector<Box>& m_coins = map_coins.at(raceNumber); // Assuming you want a reference to the vector

	auto coinIt = m_coins.begin(); // Iterator for the vector
	//cout << m_coins.size() << endl;
	while (coinIt != m_coins.end()) {
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersect(*coinIt)) {
			// If there's an intersection, "pop" the coin
			coinIt = m_coins.erase(coinIt);
			graphics::playSound("assets\\collect_coin.wav", 1.0f, false);
			numberOfCollectedCoin++;
			// Here you might want to do something with the coin (e.g., add to player's score)
		}
		else {
			// Move to the next coin
			++coinIt;
		}
	}

	if (raceNumber == 1) {

		for (int i = 0; i < 8; i++) {
			float offset = 0.0f;
			if (offset = m_state->getPlayer()->intersect(*m_enemies[i])) {
				m_state->getPlayer()->setActive(false);
			}
		}
	}

	if (raceNumber == 2) {

		for (int i = 0; i < 8; i++) {
			float offset = 0.0f;
			if (offset = m_state->getPlayer()->intersect(*m_enemies2[i])) {
				m_state->getPlayer()->setActive(false);
			}
		}
	}

	if (raceNumber == 3) {

		for (int i = 0; i < 8; i++) {
			float offset = 0.0f;
			if (offset = m_state->getPlayer()->intersect(*m_enemies3[i])) {
				m_state->getPlayer()->setActive(false);
			}
		}
	}

}


void Level::update(float dt)
{

	//std::vector<Box> m_enemies = map_enemies.at(raceNumber);

	if (raceNumber == 1) {

		for (auto& enemy : m_enemies)
		{
			moveEnemy(enemy);
		}
	}

	if (raceNumber == 2) {

		for (auto& enemy : m_enemies2)
		{
			moveEnemy(enemy);
		}
	}

	if (raceNumber == 3) {

		for (auto& enemy : m_enemies3)
		{
			moveEnemy(enemy);
		}
	}

	
	if (m_state->getPlayer()->m_pos_y > 320) {
		m_state->getPlayer()->setActive(false);
		
	}
	
	

	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->update(dt);


	checkCollisions();

	//Method Change Race
	if (m_state->getPlayer()->m_pos_x > 940 && raceNumber==1) {
		raceNumber=2;
		m_state->getPlayer()->setPlayerInitPosition();
	}
	if (m_state->getPlayer()->m_pos_x > 940 && raceNumber == 2) {
		raceNumber = 3;
		m_state->getPlayer()->setPlayerInitPosition();
	}


	GameObject::update(dt);
}

void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();


	string nameOfBackground = "bg" + std::to_string(raceNumber) + ".png";

	m_brush_background.texture = m_state->getFullAssetPath(nameOfBackground);

	

	graphics::drawRect(w/2, h/2, w, h, m_brush_background);

	

	
	
	if (m_state->getPlayer()->isActive()) {
		m_state->getPlayer()->draw();


		//draw enemies
		//std::vector<Box> m_enemies = map_enemies.at(raceNumber);
		if (raceNumber == 1) {
			graphics::Brush brush_en;
			for (auto& enemy : m_enemies)
			{

				brush_en.outline_opacity = 0.0f;
				brush_en.texture = m_state->getFullAssetPath("ghost.png");
				graphics::drawRect(enemy->m_pos_x, enemy->m_pos_y, enemy->m_width, enemy->m_height, brush_en);
			}
		}

		if (raceNumber == 2) {
			graphics::Brush brush_en;
			for (auto& enemy : m_enemies2)
			{

				brush_en.outline_opacity = 0.0f;
				brush_en.texture = m_state->getFullAssetPath("ghost.png");
				graphics::drawRect(enemy->m_pos_x, enemy->m_pos_y, enemy->m_width, enemy->m_height, brush_en);
			}
		}

		if (raceNumber == 3) {
			graphics::Brush brush_en;
			for (auto& enemy : m_enemies3)
			{

				brush_en.outline_opacity = 0.0f;
				brush_en.texture = m_state->getFullAssetPath("ghost.png");
				graphics::drawRect(enemy->m_pos_x, enemy->m_pos_y, enemy->m_width, enemy->m_height, brush_en);
			}
		}




		std::vector<Box> m_coins = map_coins.at(raceNumber);


		//draw coins
		graphics::Brush brush_coin;
		for (auto& coin : m_coins)
		{

			brush_coin.outline_opacity = 0.0f;
			brush_coin.texture = m_state->getFullAssetPath("c1.png");
			graphics::drawRect(coin.m_pos_x, coin.m_pos_y, coin.m_width, coin.m_height, brush_coin);
		}

		if (m_state->getPlayer()->isActive()) {

			graphics::Brush br10;

			drawText(GameState::getInstance()->getCanvasWidth() / 2 - 480, GameState::getInstance()->getCanvasHeight() / 2-120 , 20 , "Collected Coins : " + to_string(numberOfCollectedCoin) , br10);



		}


	}else {//Game Over

		if (!game_end_sound) {
			graphics::playSound("assets\\game_over.wav", 1.0f, false);
			game_end_sound = true;
		}
		graphics::Brush br;
		br.outline_opacity = 0.0f;
		br.fill_color[0] = 0.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.0f;
		
		
		graphics::drawRect(w / 2, h / 2, w, h,br);
		graphics::setFont("assets\\font.ttf");
		graphics::Brush br2;
		br2.fill_color[0] = 1.0f;
		br2.fill_color[1] = 1.0f;
		br2.fill_color[2] = 1.0f;

		float offsetWidth = GameState::getInstance()->getCanvasHeight() * sinf(graphics::getGlobalTime() / 1000.0f) / 12;
		float offsetSize = GameState::getInstance()->getCanvasHeight() * sinf(graphics::getGlobalTime() / 1000.0f) / 20;

		drawText(GameState::getInstance()->getCanvasWidth()/2-110, GameState::getInstance()->getCanvasHeight()/2 + offsetWidth,  40+offsetSize, "Game Over", br2);
	}

	if (raceNumber == 3 && m_state->getPlayer()->m_pos_x > 940) {

		graphics::Brush br;
		br.outline_opacity = 0.0f;
		br.fill_color[0] = 0.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.0f;


		graphics::drawRect(w / 2, h / 2, w, h, br);
		graphics::setFont("assets\\font.ttf");
		graphics::Brush br2;
		br2.fill_color[0] = 1.0f;
		br2.fill_color[1] = 1.0f;
		br2.fill_color[2] = 1.0f;

		float offsetWidth = GameState::getInstance()->getCanvasHeight() * sinf(graphics::getGlobalTime() / 1000.0f) / 12;
		float offsetSize = GameState::getInstance()->getCanvasHeight() * sinf(graphics::getGlobalTime() / 1000.0f) / 20;

		drawText(GameState::getInstance()->getCanvasWidth() / 2 - 250, GameState::getInstance()->getCanvasHeight() / 2 + offsetWidth, 40 + offsetSize, "Congratulations You Win", br2);
	
		if (!game_end_sound) {
			graphics::playSound("assets\\win_game.wav", 1.0f, false);
			game_end_sound = true;
		}
	
	}
	
	
}

void Level::init()
{
	/*
	// Stage 1
	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->init();

	for (auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->init();
	*/

	/*
	m_blocks.push_back(Box(75, 215, 103, 20));
	m_blocks.push_back(Box(180, 150, 140, 20));
	m_blocks.push_back(Box(330, 280, 75, 20));
	m_blocks.push_back(Box(510, 260, 150, 20));
	m_blocks.push_back(Box(640, 195, 90, 20));
	m_blocks.push_back(Box(755, 150, 140, 20));
	m_blocks.push_back(Box(755, 240, 180, 20));
	m_blocks.push_back(Box(910, 50, 90, 20));
	*/

	


	m_sprites_coins.push_back(m_state->getFullAssetPath("c1.png"));
	m_sprites_coins.push_back(m_state->getFullAssetPath("c2.png"));
	m_sprites_coins.push_back(m_state->getFullAssetPath("c3.png"));
	m_sprites_coins.push_back(m_state->getFullAssetPath("c4.png"));
	m_sprites_coins.push_back(m_state->getFullAssetPath("c5.png"));
	m_sprites_coins.push_back(m_state->getFullAssetPath("c6.png"));
	m_sprites_coins.push_back(m_state->getFullAssetPath("c7.png"));
	m_sprites_coins.push_back(m_state->getFullAssetPath("c8.png"));
	
	/*
	map_enemies[1].push_back(Box(80, 180, 25, 25));
	map_enemies[1].push_back(Box(185, 115, 25, 25));
	map_enemies[1].push_back(Box(335, 245, 25, 25));
	*/

	map_coins[1].push_back(Box(75, 180, 25, 25));
	map_coins[1].push_back(Box(180, 115, 25, 25));
	map_coins[1].push_back(Box(330, 245, 25, 25));
	map_coins[1].push_back(Box(510, 225, 25, 25));
	map_coins[1].push_back(Box(640, 160, 25, 25));
	map_coins[1].push_back(Box(755, 115, 25, 25));
	map_coins[1].push_back(Box(755, 205, 25, 25));
	//map_coins[1].push_back(Box(910, 30, 25, 25));
	
	map_coins[2].push_back(Box(55, 180, 25, 25));
	map_coins[2].push_back(Box(180, 110, 25, 25));
	map_coins[2].push_back(Box(280, 110, 25, 25));
	map_coins[2].push_back(Box(375, 110, 25, 25));
	map_coins[2].push_back(Box(475, 50, 25, 25));
	map_coins[2].push_back(Box(325, 250, 25, 25));
	map_coins[2].push_back(Box(650, 210, 25, 25));
	map_coins[2].push_back(Box(790, 160, 25, 25));
	map_coins[2].push_back(Box(960, 160, 25, 25));
	
	map_coins[3].push_back(Box(40, 72, 25, 25));
	map_coins[3].push_back(Box(147, 115, 25, 25));
	map_coins[3].push_back(Box(147, 205, 25, 25));
	map_coins[3].push_back(Box(275, 240, 25, 25));
	map_coins[3].push_back(Box(395, 175, 25, 25));
	map_coins[3].push_back(Box(593, 200, 25, 25));



	map_blocks[1].push_back(Box(80, 215, 103, 20));
	map_blocks[1].push_back(Box(180, 150, 140, 20));
	map_blocks[1].push_back(Box(330, 280, 75, 20));
	map_blocks[1].push_back(Box(515, 260, 150, 20));
	map_blocks[1].push_back(Box(640, 195, 90, 20));
	map_blocks[1].push_back(Box(755, 150, 140, 20));
	map_blocks[1].push_back(Box(780, 240, 220, 20));
	map_blocks[1].push_back(Box(910, 75, 110, 20));

	map_blocks[2].push_back(Box(55, 215, 110, 20));
	map_blocks[2].push_back(Box(180, 145, 70, 20));
	map_blocks[2].push_back(Box(280, 145, 70, 20));
	map_blocks[2].push_back(Box(375, 145 , 70, 20));
	map_blocks[2].push_back(Box(475, 80, 70, 20));
	map_blocks[2].push_back(Box(330, 280, 420, 20));
	map_blocks[2].push_back(Box(650, 240, 110, 20));
	map_blocks[2].push_back(Box(790, 195, 70, 20));
	map_blocks[2].push_back(Box(960, 195, 70, 20));

	map_blocks[3].push_back(Box(40, 87, 70, 5)); 
	map_blocks[3].push_back(Box(147, 130, 26*2, 5));
	map_blocks[3].push_back(Box(147, 220, 45*2, 20));
	map_blocks[3].push_back(Box(275, 255, 26*2, 5));
	map_blocks[3].push_back(Box(390, 190, 95*2, 5));
	map_blocks[3].push_back(Box(593, 215, 26*2, 5));
	map_blocks[3].push_back(Box(850, 260, 320, 20));



}

Level::Level(const std::string& name)
	: GameObject(name)
{
	

	m_brush_background.outline_opacity = 0.0f;

	
}

Level::~Level()
{
	for (auto p_go : m_enemies)
		delete p_go;
	for (auto p_go : m_enemies2)
		delete p_go;
	for (auto p_go : m_enemies3)
		delete p_go;

}


void Level::moveEnemy(Box* enemy) {


	if (enemy->lookingAt == 0) {
		enemy->m_pos_x= enemy->m_pos_x-0.6;
	}
}