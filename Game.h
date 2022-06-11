#ifndef GAME_H
#define GAME_H
#include "Window.h"
class Game
{
public:
	Game();
	~Game();
	//void HandleInput();
	void Update();
	void Render();
	Window* GetWindow() { return &m_window; }
	void Texture_add();
	void Sprite_set();
	void set_position();
	void set_scale();
	void search_sprite(EventDetails* l_details);
	void find_point_w(sf::Sprite& _sprite,const int& i);
	void find_point_b(sf::Sprite& _sprite, const int& i);
	/*void set_map();*/

private:
	Window m_window;
	std::vector <sf::Texture> Texture_Storage_W;
	std::vector <sf::Texture> Texture_Storage_B;
	sf::Texture Background_Texture;
	std::vector <sf::Sprite> Sprite_Storage_W;
	std::vector <sf::Sprite> Sprite_Storage_B;
	sf::Sprite Background_Sprite;
	std::vector <sf::CircleShape> point_to_go;
	sf::Sprite* moved_sprite=nullptr;
	bool turn = true;
	/*int map[8][8] = {
	{ 1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0},
	{ -1,-1,-1,-1,-1,-1,-1,-1},
	{ -1,-1,-1,-1,-1,-1,-1,-1 }
	};*/
	//std::vector <sf::Sprite*> map [8][8];
	/*std::vector<std::vector<sf::Sprite>> map;*/
	/*sf::Sprite* map[8][8];*/
	std::vector <sf::CircleShape> kill_chess;


};
#endif

