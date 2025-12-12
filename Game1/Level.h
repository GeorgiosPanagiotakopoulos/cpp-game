#pragma once

#include "gameobject.h"
#include <vector>
#include <list>
#include <string>
#include <sgg/graphics.h>
#include "player.h"
#include <unordered_map>

class Level : public GameObject
{

	

	int numberOfCollectedCoin = 0;

	bool game_end_sound = false; // for win or lose

	graphics::Brush m_brush_background;
	

	std::vector<std::string> m_sprites_coins;



	// add some collidable blocks
	std::vector<Box> m_blocks;


	std::unordered_map<int, std::vector<Box>> map_coins;

	std::unordered_map<int, std::vector<Box>> map_blocks;

	//std::unordered_map<int, std::vector<Box>> map_enemies;
	Box* m_enemies[8] = { new Box(80, 180, 40, 60) , 
		new Box(185, 115, 40, 60) , 
		new Box(335, 245, 40, 60) , 

		new Box(420, 100, 40, 60) ,
		new Box(950, 145, 40, 60) ,
		new Box(635, 195, 40, 60) ,

		new Box(700, 115, 40, 60) ,
		new Box(900, 100, 40, 60)
	};




	Box* m_enemies2[8] = { new Box(80, 180,40, 60) ,
		new Box(185, 115, 40, 60) ,
		new Box(335, 245, 40, 60) ,

		new Box(420, 145, 40, 60) ,
		new Box(550, 145, 40, 60) ,
		new Box(635, 195, 40, 60) ,

		new Box(700, 115, 40, 60) ,
		new Box(900, 115, 40, 60)
	};


	Box* m_enemies3[8] = { new Box(80, 180, 60, 60) ,
		new Box(185, 115, 60, 60) ,
		new Box(335, 245, 60, 60) ,

		new Box(420, 145, 60, 60) ,
		new Box(550, 145, 60, 60) ,
		new Box(635, 195, 60, 60) ,

		new Box(700, 115, 60, 60) ,
		new Box(750, 115, 60, 60)
	};


	std::vector<std::string> m_block_names;
	
	const float m_block_size = 1.0f; 
	
	graphics::Brush m_block_brush;
	graphics::Brush m_block_brush_debug;
	
	


	
	float m_center_x = 500.0f;
	float m_center_y = 150.0f;

	int raceNumber = 1;

	// detect collisions
	void checkCollisions();




public:
	void update(float dt) override;
	void draw() override;
	void init() override;

	Level(const std::string& name = "Level0");
	void moveEnemy(Box* enemy);

	~Level() override;
};