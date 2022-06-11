#include "Game.h"
Game::Game() : m_window("Chapter 2", sf::Vector2u(800, 600))
{
	
	Texture_add();
	Sprite_set();
	set_position();
	set_scale();
	//set_map();
	m_window.GetEventManager()->AddCallBack("Search", &Game::search_sprite, this);

}
Game::~Game() {}
void Game::Update() { m_window.Update(); }
void Game::Render() 
{ 
	m_window.BeginDraw();
	m_window.Draw(Background_Sprite);
	for (auto& h : Sprite_Storage_B)
		m_window.Draw(h);
	for (auto& h : Sprite_Storage_W)
		m_window.Draw(h);
	for (size_t check{ 0 }; check != Sprite_Storage_B.size(); check++)
		m_window.Draw(Sprite_Storage_B[check]);
	for (auto& h : point_to_go)
		m_window.Draw(h);
	for (auto& h : kill_chess)
		m_window.Draw(h);
	m_window.EndDraw();

}
void Game::Texture_add() { 
	sf::Texture texture;
	Background_Texture.loadFromFile("chess.jpg");
	for (size_t check{ 0 }; check != 6; check++)
	{
		std::ostringstream name;
		name << "W_" << check + 1 << ".png";
		texture.loadFromFile(name.str());
		Texture_Storage_W.push_back(texture);
	}
	for (size_t check{ 0 }; check != 6; check++)
	{
		std::ostringstream name;
		name << "B_" << check + 1 << ".png";
		texture.loadFromFile(name.str());
		Texture_Storage_B.push_back(texture);
	}

}
void Game::Sprite_set()
{
	sf::Sprite temp;
	Background_Sprite.setTexture(Background_Texture);
	for (size_t check{ 0 }; check != 5; check++)
	{
		temp.setTexture(Texture_Storage_W[check]);
		Sprite_Storage_W.push_back(temp);
	}
	for (size_t check{ 0 }; check != 3; check++)
	{
		temp.setTexture(Texture_Storage_W[2 - check]);
		Sprite_Storage_W.push_back(temp);
	}
	for (size_t check{ 0 }; check != 8; check++)
	{
		temp.setTexture(Texture_Storage_W[5]);
		Sprite_Storage_W.push_back(temp);
	}

	////////////////////
	for (size_t check{ 0 }; check != 5; check++)
	{
		temp.setTexture(Texture_Storage_B[check]);
		Sprite_Storage_B.push_back(temp);
	}
	for (size_t check{ 0 }; check != 3; check++)
	{
		temp.setTexture(Texture_Storage_B[2 - check]);
		Sprite_Storage_B.push_back(temp);
	}
	for (size_t check{ 0 }; check != 8; check++)
	{
		temp.setTexture(Texture_Storage_B[5]);
		Sprite_Storage_B.push_back(temp);
	}

}
void Game::set_position()
{
	float x{ 25.0 }, y{ 0.0 };
	for (size_t check{ 0 }; check != Sprite_Storage_W.size(); check++)
	{
		if (check == 8)
		{
			x = 25.0;
			y += 75.0;
		}
		Sprite_Storage_W[check].setPosition(x, y);
		x += 100.0;
	}
	x = 25.0,y=525.0;
	for (size_t check{ 0 }; check != Sprite_Storage_B.size(); check++)
	{
		if (check == 8)
		{
			x = 25.0;
			y -= 75;
		}
		Sprite_Storage_B[check].setPosition(x, y);
		x += 100.0;
	}

}
void Game::set_scale()
{
	for (auto& h : Sprite_Storage_B)
		h.setScale(0.8f, 0.8f);
	for (auto& h : Sprite_Storage_W)
		h.setScale(0.8f, 0.8f);
}
void Game::search_sprite(EventDetails* l_details)
{
	if((Sprite_Storage_B[4].getPosition().x==-100&& Sprite_Storage_B[4].getPosition().y == -100) 
		|| Sprite_Storage_W[4].getPosition().x == -100 && Sprite_Storage_W[4].getPosition().y == -100) return;
	sf::Vector2i mousepos = m_window.GetEventManager()->GetMousePos(m_window.GetRenderWindow());
	std::cout << mousepos.x <<" "<<mousepos.y<< std::endl;
	if (moved_sprite == nullptr)
	{
		int check{ 0 };
		for (auto& h : Sprite_Storage_W)
		{
			if (turn == false) break;
			if (h.getGlobalBounds().contains(mousepos.x, mousepos.y))
			{
				std::cout << "Find" << "\n" << check << std::endl;
				moved_sprite = &h;
				find_point_w(h, check);
				return;
			}
			check++;
		}
		check = 0;
		for (auto& h : Sprite_Storage_B)
		{
			if (turn == true) break;
			if (h.getGlobalBounds().contains(mousepos.x, mousepos.y))

			{
				std::cout << "Find" << "\n" << check << std::endl;
				moved_sprite = &h;
				find_point_b(h, check);
				return;
			}
			check++;
		}
	}
	else
	{
		for (auto& h : point_to_go)
			//if (h.getGlobalBounds().contains(mousepos.x, mousepos.y)) moved_sprite->setPosition(mousepos.x, mousepos.y);
			if (h.getGlobalBounds().contains(mousepos.x, mousepos.y))
			{
				std::cout << "Point_to_go" << std::endl;
				moved_sprite->setPosition(/*moved_sprite->getPosition().x*//*mousepos.x-(mousepos.x%10)*/h.getPosition().x, mousepos.y - (mousepos.y % 75));
				std::cout << moved_sprite->getPosition().x << " " << moved_sprite->getPosition().y << std::endl;
				point_to_go.clear();
				kill_chess.clear();
				moved_sprite = nullptr;
				turn = !turn;
				return;

			}
		for (auto& h : kill_chess)
		{
			if(turn==true){
				for (auto& hh : Sprite_Storage_B)
				{
					if (hh.getGlobalBounds().contains(mousepos.x, mousepos.y))
					{
						moved_sprite->setPosition(hh.getPosition().x, hh.getPosition().y);
						hh.setPosition(-100, -100);
						point_to_go.clear();
						kill_chess.clear();
						moved_sprite = nullptr;
						turn = !turn;
						return;
						
					}

				}
			}
			else{
				for (auto& hh : Sprite_Storage_W)
				{
					if (hh.getGlobalBounds().contains(mousepos.x, mousepos.y))
					{
						moved_sprite->setPosition(hh.getPosition().x, hh.getPosition().y);
						hh.setPosition(-100, -100);
						point_to_go.clear();
						kill_chess.clear();
						moved_sprite = nullptr;
						turn = !turn;
						return;

					}

				}

			}

			}
		}
	point_to_go.clear();
	kill_chess.clear();
	moved_sprite = nullptr;
	
		
	
}
void Game::find_point_w(sf::Sprite& _sprite,const int& check)
{
	point_to_go.clear();
	kill_chess.clear();
	std::cout << "Move sprite" << std::endl;
	if (check >= 8)
	{
		/*int row{ 0 }, column{ 0 }, t_row{ 0 }, t_column{ 0 };
		for (const auto& h : map)
		{
			for (const auto& hh : h)
			{
				if (hh->getPosition().x == _sprite.getPosition().x && hh->getPosition().y == _sprite.getPosition().y)
				{
					std::cout << "Hello!" << std::endl;
				}
				++column;
			}
			++row;
			
		}*/
		std::cout <<"Left: " << _sprite.getGlobalBounds().left <<"\n"<<"width: " << _sprite.getGlobalBounds().width << std::endl;
		sf::CircleShape first(25.f);
		sf::CircleShape second(25.f);
		sf::CircleShape three(25.f);
		sf::CircleShape four(25.f);
		bool col_first{ false };
		bool col_second{ false };
		bool col_three{ false };
		bool col_four{ false };
		first.setPosition(_sprite.getPosition().x, _sprite.getPosition().y + 75);
		second.setPosition(_sprite.getPosition().x, _sprite.getPosition().y + 150);
		three.setPosition(_sprite.getPosition().x-100, _sprite.getPosition().y + 75);
		four.setPosition(_sprite.getPosition().x + 100, _sprite.getPosition().y + 75);
		for (auto& h : Sprite_Storage_B)
		{
			if (h.getGlobalBounds().contains(three.getPosition().x, three.getPosition().y))
			{
				col_three = true;
				break;
			}
		}
		for (auto& h : Sprite_Storage_B)
		{
			if (h.getGlobalBounds().contains(four.getPosition().x, four.getPosition().y))
			{
				col_four = true;
				break;
			}
		}
		for (auto& h : Sprite_Storage_B)
		{
			if (h.getGlobalBounds().contains(first.getPosition().x, first.getPosition().y)) { /*point_to_go.push_back(first); break;*/ col_first = true; /*break;*/ }
		}
		for (auto& h : Sprite_Storage_W)
		{
			if (h.getGlobalBounds().contains(first.getPosition().x, first.getPosition().y)) { /*point_to_go.push_back(first); break;*/ col_first = true; /*break;*/ }
		}
		for (auto& h : Sprite_Storage_W)
		{
			if (h.getGlobalBounds().contains(second.getPosition().x, second.getPosition().y)) { /*point_to_go.push_back(second); break;*/ col_second = true; /*break;*/ }
		}
		if (col_first == false) point_to_go.push_back(first);
		for (auto& h : Sprite_Storage_B)
		{
			if (h.getGlobalBounds().contains(second.getPosition().x, second.getPosition().y)) { /*point_to_go.push_back(second); break;*/ col_second = true; /*break;*/}
		}
		if (col_second == false && col_first==false && _sprite.getPosition().y==75) point_to_go.push_back(second);
		std::cout << col_first << " " << col_second << std::endl;
		//if (col_first == false) point_to_go.push_back(first);
		//if (col_second == false) point_to_go.push_back(second);
		if (col_three == true) kill_chess.push_back(three);
		if (col_four == true) kill_chess.push_back(four);
		/*point_to_go.push_back(first);
		point_to_go.push_back(second);*/
		//point_to_go.push_back(three);
		//point_to_go.push_back(four);
	}
	if (check == 0 || check == 7)
	{
		float x{ 0.0 }, y{ 80.0 };
		////std::vector<sf::CircleShape> down;
		//std::vector<sf::CircleShape> up;
		//std::vector<sf::CircleShape> left;
		//std::vector<sf::CircleShape> right;
		while (true)
		{
			bool colission{ false };
			bool kill_find{ false };
			sf::CircleShape _down(25.f);
			_down.setPosition(_sprite.getPosition().x, _sprite.getPosition().y + y);
			y += 80;
			if (_down.getPosition().y > 600) break;
			for (auto& h : Sprite_Storage_W)
				if (h.getGlobalBounds().contains(_down.getPosition().x, _down.getPosition().y)) { colission = true; break; };
			if (colission == true) break;
			for (auto& h : Sprite_Storage_B)
			{
				if (h.getGlobalBounds().contains(_down.getPosition().x, _down.getPosition().y)) { kill_find = true; break; }
			}
			if (kill_find == true && colission == false) { kill_chess.push_back(_down); break; }
			if (kill_find == false && colission==false) point_to_go.push_back(_down);
		}
		x = 100.0, y = 0.0;
		while (true)
		{
			bool colission{ false };
			bool kill_find{ false };
			sf::CircleShape left(25.f);
			left.setPosition(_sprite.getPosition().x - x, _sprite.getPosition().y);
			x += 100;
			if (left.getPosition().x < 0) break;
			for (auto& h : Sprite_Storage_W)
				if (h.getGlobalBounds().contains(left.getPosition().x, left.getPosition().y)) { colission = true; break; };
			if (colission == true) break;
			for (auto& h : Sprite_Storage_B)
			{
				if (h.getGlobalBounds().contains(left.getPosition().x, left.getPosition().y)) { kill_find = true; break; }
			}
			if (kill_find == true && colission == false) { kill_chess.push_back(left); break;}
			if (kill_find == false && colission == false) point_to_go.push_back(left);
		}
		/////////////////////////////////
		x = 100.0, y = 0.0;
		while (true)
		{
			bool colission{ false };
			bool kill_find{ false };
			sf::CircleShape right(25.f);
			right.setPosition(_sprite.getPosition().x + x, _sprite.getPosition().y);
			x += 100;
			if (right.getPosition().x > 800) break;
			for (auto& h : Sprite_Storage_W)
				if (h.getGlobalBounds().contains(right.getPosition().x, right.getPosition().y)) { colission = true; break; };
			if (colission == true) break;
			for (auto& h : Sprite_Storage_B)
			{
				if (h.getGlobalBounds().contains(right.getPosition().x, right.getPosition().y)) { kill_find = true; break; }
			}
			if (kill_find == true && colission == false) { kill_chess.push_back(right);break; }
			if (kill_find == false && colission == false) point_to_go.push_back(right);

		}
		//////////////////////////
		x = 0.0, y = 70.0;
		while (true)
		{
			bool colission{ false };
			bool kill_find{ false };
			sf::CircleShape up(25.f);
			up.setPosition(_sprite.getPosition().x, _sprite.getPosition().y - y);
			y += 70;
			if (up.getPosition().y < 0) break;
			for (auto& h : Sprite_Storage_W)
				if (h.getGlobalBounds().contains(up.getPosition().x, up.getPosition().y)) { colission = true; break; };
			if (colission == true) break;
			for (auto& h : Sprite_Storage_B)
			{
				if (h.getGlobalBounds().contains(up.getPosition().x, up.getPosition().y)) { kill_find = true; break; }
			}
			if (kill_find == true && colission == false) { kill_chess.push_back(up);break; }
			if (kill_find == false && colission == false) point_to_go.push_back(up);
		}
	}
		if (check == 1 || check == 6)
		{
			float x{ 200.0 }, y{ 70.0 };
			std::cout << "Check";
			int temp{ 0 };
			while (temp <2)
			{
				bool colission{ false };
				bool kill_find{ false };
				sf::CircleShape left_up(25.f);
				left_up.setPosition(_sprite.getPosition().x - x, _sprite.getPosition().y - y);
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(left_up.getPosition().x, left_up.getPosition().y)) {  colission = true; break; }
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(left_up.getPosition().x, left_up.getPosition().y)) { kill_find = true; break; }
				}
				if (kill_find == true && colission == false) { kill_chess.push_back(left_up);break; }
				if (kill_find == false && colission == false) point_to_go.push_back(left_up);
				x = 100, y = 140;
				temp++;

			}
			/////////////////////
			x = 100.0, y = 140.0,temp=0;
			while (temp < 2)
			{
				bool colission{ false };
				bool kill_find{ false };
				sf::CircleShape right_up(25.f);
				right_up.setPosition(_sprite.getPosition().x + x, _sprite.getPosition().y - y);
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(right_up.getPosition().x, right_up.getPosition().y)) { colission = true; break; };
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(right_up.getPosition().x, right_up.getPosition().y)) { kill_find = true; break; }
				}
				if (kill_find == true && colission == false) { kill_chess.push_back(right_up); }
				if (kill_find == false && colission == false) point_to_go.push_back(right_up);
				x = 200, y = 70;
				temp++;
			}
			////////////////////////
			x = 200.0, y = 80.0, temp = 0;
			while (temp < 2)
			{
				bool colission{ false };
				bool kill_find{ false };
				sf::CircleShape left_down(25.f);
				left_down.setPosition(_sprite.getPosition().x - x, _sprite.getPosition().y + y);
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(left_down.getPosition().x, left_down.getPosition().y)) { colission = true; break; };
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(left_down.getPosition().x, left_down.getPosition().y)) { kill_find = true; break; }
				}
				if (kill_find == true && colission == false) { kill_chess.push_back(left_down); }
				if (kill_find == false && colission == false) point_to_go.push_back(left_down);
				x = 100, y = 160;
				temp++;
			}
			//////////////////////////////
			x = 200.0, y = 80.0, temp = 0;
			while (temp < 2)
			{
				bool colission{ false };
				bool kill_find{ false };
				sf::CircleShape right_down(25.f);
				right_down.setPosition(_sprite.getPosition().x + x, _sprite.getPosition().y + y);
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(right_down.getPosition().x, right_down.getPosition().y)) { colission = true; break; };
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(right_down.getPosition().x, right_down.getPosition().y)) { kill_find = true; break; }
				}
				if (kill_find == true && colission == false) { kill_chess.push_back(right_down); }
				if (kill_find == false && colission == false) point_to_go.push_back(right_down);
				x = 100, y = 160;
				temp++;
			}
		}
		if (check == 2 || check == 5)
		{
			float x{100.0 }, y{ 70.0 };
		
			while (true)
			{
				bool colission{ false };
				bool kill_find{ false };
				sf::CircleShape left_up(25.f);
				left_up.setPosition(_sprite.getPosition().x - x, _sprite.getPosition().y - y);
				if (left_up.getPosition().x < 0 || left_up.getPosition().y < 0) break;
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(left_up.getPosition().x, left_up.getPosition().y)) { colission = true; break; }
				if (colission == true) break;
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(left_up.getPosition().x, left_up.getPosition().y)) { kill_find = true; break; }
				}
				if (kill_find == true && colission == false) { kill_chess.push_back(left_up);break; }
				if (kill_find == false && colission == false) point_to_go.push_back(left_up);
				x += 100.0;
				y += 70.0;
			}
			////////////////////
			x = 100.0, y = 75.0;
			
			while (true)
			{
				bool colission{ false };
				bool kill_find{ false };
				sf::CircleShape right_up(25.f);
				right_up.setPosition(_sprite.getPosition().x + x, _sprite.getPosition().y - y);
				if (right_up.getPosition().x > 800 || right_up.getPosition().y < 0) break;
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(right_up.getPosition().x, right_up.getPosition().y)) { colission = true; break; }
				if (colission == true) break;
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(right_up.getPosition().x, right_up.getPosition().y)) { kill_find = true; break; }
				}
				if (kill_find == true && colission == false) { kill_chess.push_back(right_up);break; }
				if (kill_find == false && colission == false) point_to_go.push_back(right_up);
				x += 100.0;
				y += 75.0;
			}
			////////////////////////
			x = 100.0, y = 75.0;
			while (true)
			{
				bool colission{ false };
				bool kill_find{ false };
				sf::CircleShape left_down(25.f);
				left_down.setPosition(_sprite.getPosition().x - x, _sprite.getPosition().y + y);
				if (left_down.getPosition().x < 0 || left_down.getPosition().y > 600) break;
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(left_down.getPosition().x, left_down.getPosition().y)) { colission = true; break; }
				if (colission == true) break;
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(left_down.getPosition().x, left_down.getPosition().y)) { kill_find = true; break; }
				}
				if (kill_find == true && colission == false) { kill_chess.push_back(left_down);break; }
				if (kill_find == false && colission == false) point_to_go.push_back(left_down);
				x += 100.0;
				y += 75.0;
			}
			/////////////////////////////
			x = 100.0, y = 75.0;
			while (true)
			{
				bool colission{ false };
				bool kill_find{ false };
				sf::CircleShape right_down(25.f);
				right_down.setPosition(_sprite.getPosition().x + x, _sprite.getPosition().y + y);
				if (right_down.getPosition().x > 800 || right_down.getPosition().y > 600) break;
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(right_down.getPosition().x, right_down.getPosition().y)) { colission = true; break; }
				if (colission == true) break;
			
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(right_down.getPosition().x, right_down.getPosition().y)) { kill_find = true; break; }
				}
				if (kill_find == true && colission == false) { kill_chess.push_back(right_down);break; }
				if (kill_find == false && colission == false) point_to_go.push_back(right_down);
				x += 100.0;
				y += 75.0;
			}

		}
		if (check == 3)
		{
			float x{ 0.0 }, y{ 80.0 };
			////std::vector<sf::CircleShape> down;
			//std::vector<sf::CircleShape> up;
			//std::vector<sf::CircleShape> left;
			//std::vector<sf::CircleShape> right;
			while (true)
			{
				bool colission{ false };
				bool kill_find{ false };
				sf::CircleShape _down(25.f);
				_down.setPosition(_sprite.getPosition().x, _sprite.getPosition().y + y);
				y += 80;
				if (_down.getPosition().y > 600) break;
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(_down.getPosition().x, _down.getPosition().y)) { colission = true; break; };
				if (colission == true) break;
				
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(_down.getPosition().x, _down.getPosition().y)) { kill_find = true; break; }
				}
				if (kill_find == true && colission == false) { kill_chess.push_back(_down);break; }
				if (kill_find == false && colission == false) point_to_go.push_back(_down);
			}
			x = 100.0, y = 0.0;
			while (true)
			{
				bool colission{ false };
				bool kill_find{ false };
				sf::CircleShape left(25.f);
				left.setPosition(_sprite.getPosition().x - x, _sprite.getPosition().y);
				x += 100;
				if (left.getPosition().x < 0) break;
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(left.getPosition().x, left.getPosition().y)) { colission = true; break; };
				if (colission == true) break;
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(left.getPosition().x, left.getPosition().y)) { kill_find = true; break; }
				}
				if (kill_find == true && colission == false) { kill_chess.push_back(left);break; }
				if (kill_find == false && colission == false) point_to_go.push_back(left);

			}
			/////////////////////////////////
			x = 100.0, y = 0.0;
			while (true)
			{
				bool colission{ false };
				bool kill_find{ false };
				sf::CircleShape right(25.f);
				right.setPosition(_sprite.getPosition().x + x, _sprite.getPosition().y);
				x += 100;
				if (right.getPosition().x > 800) break;
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(right.getPosition().x, right.getPosition().y)) { colission = true; break; };
				if (colission == true) break;
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(right.getPosition().x, right.getPosition().y)) { kill_find = true; break; }
				}
				if (kill_find == true && colission == false) { kill_chess.push_back(right);break; }
				if (kill_find == false && colission == false) point_to_go.push_back(right);
			}
			//////////////////////////
			x = 0.0, y = 70.0;
			while (true)
			{
				bool colission{ false };
				bool kill_find{ false };
				sf::CircleShape up(25.f);
				up.setPosition(_sprite.getPosition().x, _sprite.getPosition().y - y);
				y += 70;
				if (up.getPosition().y < 0) break;
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(up.getPosition().x, up.getPosition().y)) { colission = true; break; };
				if (colission == true) break;
			
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(up.getPosition().x, up.getPosition().y)) { kill_find = true; break; }
				}
				if (kill_find == true && colission == false) { kill_chess.push_back(up);break; }
				if (kill_find == false && colission == false) point_to_go.push_back(up);
			}
			x = 100.0, y = 70.0;

			while (true)
			{
				bool colission{ false };
				bool kill_find{ false };
				sf::CircleShape left_up(25.f);
				left_up.setPosition(_sprite.getPosition().x - x, _sprite.getPosition().y - y);
				if (left_up.getPosition().x < 0 || left_up.getPosition().y < 0) break;
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(left_up.getPosition().x, left_up.getPosition().y)) { colission = true; break; }
				if (colission == true) break;
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(left_up.getPosition().x, left_up.getPosition().y)) { kill_find = true; break; }
				}
				if (kill_find == true && colission == false) { kill_chess.push_back(left_up);break; }
				if (kill_find == false && colission == false) point_to_go.push_back(left_up);
				x += 100.0;
				y += 70.0;
			}
			////////////////////
			x = 100.0, y = 70.0;

			while (true)
			{
				bool colission{ false };
				bool kill_find{ false };
				sf::CircleShape right_up(25.f);
				right_up.setPosition(_sprite.getPosition().x + x, _sprite.getPosition().y - y);
				if (right_up.getPosition().x > 800 || right_up.getPosition().y < 0) break;
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(right_up.getPosition().x, right_up.getPosition().y)) { colission = true; break; }
				if (colission == true) break;
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(right_up.getPosition().x, right_up.getPosition().y)) { kill_find = true; break; }
				}
				if (kill_find == true && colission == false) { kill_chess.push_back(right_up);break; }
				if (kill_find == false && colission == false) point_to_go.push_back(right_up);
				x += 100.0;
				y += 70.0;
			}
			////////////////////////
			x = 100.0, y = 80.0;
			while (true)
			{
				bool colission{ false };
				bool kill_find{ false };
				sf::CircleShape left_down(25.f);
				left_down.setPosition(_sprite.getPosition().x - x, _sprite.getPosition().y + y);
				if (left_down.getPosition().x < 0 || left_down.getPosition().y > 600) break;
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(left_down.getPosition().x, left_down.getPosition().y)) { colission = true; break; }
				if (colission == true) break;
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(left_down.getPosition().x, left_down.getPosition().y)) { kill_find = true; break; }
				}
				if (kill_find == true && colission == false) { kill_chess.push_back(left_down);break; }
				if (kill_find == false && colission == false) point_to_go.push_back(left_down);
				x += 100.0;
				y += 80.0;
			}
			/////////////////////////////
			x = 100.0, y = 80.0;
			while (true)
			{
				bool colission{ false };
				bool kill_find{ false };
				sf::CircleShape right_down(25.f);
				right_down.setPosition(_sprite.getPosition().x + x, _sprite.getPosition().y + y);
				if (right_down.getPosition().x > 800 || right_down.getPosition().y > 600) break;
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(right_down.getPosition().x, right_down.getPosition().y)) { colission = true; break; }
				if (colission == true) break;
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(right_down.getPosition().x, right_down.getPosition().y)) { kill_find = true; break; }
				}
				if (kill_find == true && colission == false) { kill_chess.push_back(right_down);break; }
				if (kill_find == false && colission == false) point_to_go.push_back(right_down);
				x += 100.0;
				y += 80.0;
			}
			}
			if (check == 4)
			{
				std::vector<bool> collision(8, false);
				std::vector<bool> kill_find(8, false);
				sf::CircleShape left(25.f);
				sf::CircleShape left_up(25.f);
				sf::CircleShape up(25.f);
				sf::CircleShape up_right(25.f);
				sf::CircleShape right(25.f);
				sf::CircleShape right_down(25.f);
				sf::CircleShape down(25.f);
				sf::CircleShape left_down(25.f);

				left.setPosition(_sprite.getPosition().x-100, _sprite.getPosition().y);
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(left.getPosition().x, left.getPosition().y)) { collision[0] = true; break; };
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(left.getPosition().x, left.getPosition().y)) { kill_find[0] = true; break; }
				}
				if (kill_find[0] == true && collision[0] == false) { kill_chess.push_back(left); }
				if (kill_find[0] == false && collision[0] == false) point_to_go.push_back(left);
				////////////////////////
				left_up.setPosition(_sprite.getPosition().x - 100, _sprite.getPosition().y-75);
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(left_up.getPosition().x, left_up.getPosition().y)) { collision[1] = true; break; };
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(left_up.getPosition().x, left_up.getPosition().y)) { kill_find[1] = true; break; }
				}
				if (kill_find[1] == true && collision[0] == false) { kill_chess.push_back(left_up); }
				if (kill_find[1] == false && collision[0] == false) point_to_go.push_back(left_up);
				////////////////////////////////
				up.setPosition(_sprite.getPosition().x , _sprite.getPosition().y - 75);
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(up.getPosition().x, up.getPosition().y)) { collision[2] = true; break; };
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(up.getPosition().x, up.getPosition().y)) { kill_find[2] = true; break; }
				}
				if (kill_find[2] == true && collision[2] == false) { kill_chess.push_back(up); }
				if (kill_find[2] == false && collision[2] == false) point_to_go.push_back(up);
				////////////////////////////////
				up_right.setPosition(_sprite.getPosition().x+100, _sprite.getPosition().y - 75);
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(up_right.getPosition().x, up_right.getPosition().y)) { collision[3] = true; break; };
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(up_right.getPosition().x, up_right.getPosition().y)) { kill_find[3] = true; break; }
				}
				if (kill_find[3] == true && collision[3] == false) { kill_chess.push_back(up_right); }
				if (kill_find[3] == false && collision[3] == false) point_to_go.push_back(up_right);
				////////////////////////////////
				right.setPosition(_sprite.getPosition().x+100, _sprite.getPosition().y);
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(right.getPosition().x, right.getPosition().y)) { collision[4] = true; break; };
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(right.getPosition().x, right.getPosition().y)) { kill_find[4] = true; break; }
				}
				if (kill_find[4] == true && collision[4] == false) { kill_chess.push_back(right); }
				if (kill_find[4] == false && collision[4] == false) point_to_go.push_back(right);
				////////////////////////////////
				right_down.setPosition(_sprite.getPosition().x + 100, _sprite.getPosition().y+75);
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(right_down.getPosition().x, right_down.getPosition().y)) { collision[5] = true; break; };
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(right_down.getPosition().x, right_down.getPosition().y)) { kill_find[5] = true; break; }
				}
				if (kill_find[5] == true && collision[5] == false) { kill_chess.push_back(right_down); }
				if (kill_find[5] == false && collision[5] == false) point_to_go.push_back(right_down);
				////////////////////////////////
				down.setPosition(_sprite.getPosition().x, _sprite.getPosition().y + 75);
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(down.getPosition().x, down.getPosition().y)) { collision[6] = true; break; };
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(down.getPosition().x, down.getPosition().y)) { kill_find[6] = true; break; }
				}
				if (kill_find[6] == true && collision[6] == false) { kill_chess.push_back(down); }
				if (kill_find[6] == false && collision[6] == false) point_to_go.push_back(down);
				////////////////////////////////
				left_down.setPosition(_sprite.getPosition().x-100, _sprite.getPosition().y + 75);
				for (auto& h : Sprite_Storage_W)
					if (h.getGlobalBounds().contains(left_down.getPosition().x, left_down.getPosition().y)) { collision[7] = true; break; };
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(left_down.getPosition().x, left_down.getPosition().y)) { kill_find[7] = true; break; }
				}
				if (kill_find[7] == true && collision[7] == false) { kill_chess.push_back(left_down); }
				if (kill_find[7] == false && collision[7] == false) point_to_go.push_back(left_down);
				////////////////////////////////



			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		void Game::find_point_b(sf::Sprite& _sprite, const int& check)
		{
			
			point_to_go.clear();
			kill_chess.clear();
			std::cout << "Move sprite" << std::endl;
			if (check >= 8)
			{
				/*int row{ 0 }, column{ 0 }, t_row{ 0 }, t_column{ 0 };
				for (const auto& h : map)
				{
					for (const auto& hh : h)
					{
						if (hh->getPosition().x == _sprite.getPosition().x && hh->getPosition().y == _sprite.getPosition().y)
						{
							std::cout << "Hello!" << std::endl;
						}
						++column;
					}
					++row;

				}*/
				std::cout << "Left: " << _sprite.getGlobalBounds().left << "\n" << "width: " << _sprite.getGlobalBounds().width << std::endl;
				sf::CircleShape first(25.f);
				sf::CircleShape second(25.f);
				sf::CircleShape three(25.f);
				sf::CircleShape four(25.f);
				bool col_first{ false };
				bool col_second{ false };
				bool col_three{ false };
				bool col_four{ false };
				first.setPosition(_sprite.getPosition().x, _sprite.getPosition().y - 75);
				second.setPosition(_sprite.getPosition().x, _sprite.getPosition().y - 150);
				three.setPosition(_sprite.getPosition().x - 100, _sprite.getPosition().y - 75);
				four.setPosition(_sprite.getPosition().x + 100, _sprite.getPosition().y - 75);
				for (auto& h : Sprite_Storage_W)
				{
					if (h.getGlobalBounds().contains(three.getPosition().x, three.getPosition().y))
					{
						col_three = true;
						break;
					}
				}
				for (auto& h : Sprite_Storage_W)
				{
					if (h.getGlobalBounds().contains(four.getPosition().x, four.getPosition().y))
					{
						col_four = true;
						break;
					}
				}
				for (auto& h : Sprite_Storage_W)
				{
					if (h.getGlobalBounds().contains(first.getPosition().x, first.getPosition().y)) { /*point_to_go.push_back(first); break;*/ col_first = true; /*break;*/ }
				}
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(first.getPosition().x, first.getPosition().y)) { /*point_to_go.push_back(first); break;*/ col_first = true; /*break;*/ }
				}
				for (auto& h : Sprite_Storage_B)
				{
					if (h.getGlobalBounds().contains(second.getPosition().x, second.getPosition().y)) { /*point_to_go.push_back(second); break;*/ col_second = true; /*break;*/ }
				}
				if (col_first == false) point_to_go.push_back(first);
				for (auto& h : Sprite_Storage_W)
				{
					if (h.getGlobalBounds().contains(second.getPosition().x, second.getPosition().y)) { /*point_to_go.push_back(second); break;*/ col_second = true; /*break;*/ }
				}
				if (col_second == false && col_first == false && _sprite.getPosition().y == 450) point_to_go.push_back(second);
				std::cout << col_first << " " << col_second << std::endl;
				//if (col_first == false) point_to_go.push_back(first);
				//if (col_second == false) point_to_go.push_back(second);
				if (col_three == true) kill_chess.push_back(three);
				if (col_four == true) kill_chess.push_back(four);
				/*point_to_go.push_back(first);
				point_to_go.push_back(second);*/
				//point_to_go.push_back(three);
				//point_to_go.push_back(four);
			}
			if (check == 0 || check == 7)
			{
				float x{ 0.0 }, y{ 80.0 };
				////std::vector<sf::CircleShape> down;
				//std::vector<sf::CircleShape> up;
				//std::vector<sf::CircleShape> left;
				//std::vector<sf::CircleShape> right;
				while (true)
				{
					bool colission{ false };
					bool kill_find{ false };
					sf::CircleShape _down(25.f);
					_down.setPosition(_sprite.getPosition().x, _sprite.getPosition().y + y);
					y += 80;
					if (_down.getPosition().y > 600) break;
					for (auto& h : Sprite_Storage_B)
						if (h.getGlobalBounds().contains(_down.getPosition().x, _down.getPosition().y)) { colission = true; break; };
					if (colission == true) break;
					for (auto& h : Sprite_Storage_W)
					{
						if (h.getGlobalBounds().contains(_down.getPosition().x, _down.getPosition().y)) { kill_find = true; break; }
					}
					if (kill_find == true && colission == false) { kill_chess.push_back(_down);break; }
					if (kill_find == false && colission == false) point_to_go.push_back(_down);
				}
				x = 100.0, y = 0.0;
				while (true)
				{
					bool colission{ false };
					bool kill_find{ false };
					sf::CircleShape left(25.f);
					left.setPosition(_sprite.getPosition().x - x, _sprite.getPosition().y);
					x += 100;
					if (left.getPosition().x < 0) break;
					for (auto& h : Sprite_Storage_B)
						if (h.getGlobalBounds().contains(left.getPosition().x, left.getPosition().y)) { colission = true; break; };
					if (colission == true) break;
					for (auto& h : Sprite_Storage_W)
					{
						if (h.getGlobalBounds().contains(left.getPosition().x, left.getPosition().y)) { kill_find = true; break; }
					}
					if (kill_find == true && colission == false) { kill_chess.push_back(left);break; }
					if (kill_find == false && colission == false) point_to_go.push_back(left);
				}
				/////////////////////////////////
				x = 100.0, y = 0.0;
				while (true)
				{
					bool colission{ false };
					bool kill_find{ false };
					sf::CircleShape right(25.f);
					right.setPosition(_sprite.getPosition().x + x, _sprite.getPosition().y);
					x += 100;
					if (right.getPosition().x > 800) break;
					for (auto& h : Sprite_Storage_B)
						if (h.getGlobalBounds().contains(right.getPosition().x, right.getPosition().y)) { colission = true; break; };
					if (colission == true) break;
					for (auto& h : Sprite_Storage_W)
					{
						if (h.getGlobalBounds().contains(right.getPosition().x, right.getPosition().y)) { kill_find = true; break; }
					}
					if (kill_find == true && colission == false) { kill_chess.push_back(right);break; }
					if (kill_find == false && colission == false) point_to_go.push_back(right);

				}
				//////////////////////////
				x = 0.0, y = 70.0;
				while (true)
				{
					bool colission{ false };
					bool kill_find{ false };
					sf::CircleShape up(25.f);
					up.setPosition(_sprite.getPosition().x, _sprite.getPosition().y - y);
					y += 70;
					if (up.getPosition().y < 0) break;
					for (auto& h : Sprite_Storage_B)
						if (h.getGlobalBounds().contains(up.getPosition().x, up.getPosition().y)) { colission = true; break; };
					if (colission == true) break;
					for (auto& h : Sprite_Storage_W)
					{
						if (h.getGlobalBounds().contains(up.getPosition().x, up.getPosition().y)) { kill_find = true; break; }
					}
					if (kill_find == true && colission == false) { kill_chess.push_back(up);break; }
					if (kill_find == false && colission == false) point_to_go.push_back(up);
				}
			}
			if (check == 1 || check == 6)
			{
				float x{ 200.0 }, y{ 70.0 };
				std::cout << "Check";
				int temp{ 0 };
				while (temp < 2)
				{
					bool colission{ false };
					bool kill_find{ false };
					sf::CircleShape left_up(25.f);
					left_up.setPosition(_sprite.getPosition().x - x, _sprite.getPosition().y - y);
					for (auto& h : Sprite_Storage_B)
						if (h.getGlobalBounds().contains(left_up.getPosition().x, left_up.getPosition().y)) { colission = true; break; }
					for (auto& h : Sprite_Storage_W)
					{
						if (h.getGlobalBounds().contains(left_up.getPosition().x, left_up.getPosition().y)) { kill_find = true; break; }
					}
					if (kill_find == true && colission == false) { kill_chess.push_back(left_up); }
					if (kill_find == false && colission == false) point_to_go.push_back(left_up);
					x = 100, y = 140;
					temp++;

				}
				/////////////////////
				x = 100.0, y = 140.0, temp = 0;
				while (temp < 2)
				{
					bool colission{ false };
					bool kill_find{ false };
					sf::CircleShape right_up(25.f);
					right_up.setPosition(_sprite.getPosition().x + x, _sprite.getPosition().y - y);
					for (auto& h : Sprite_Storage_B)
						if (h.getGlobalBounds().contains(right_up.getPosition().x, right_up.getPosition().y)) { colission = true; break; };
					for (auto& h : Sprite_Storage_W)
					{
						if (h.getGlobalBounds().contains(right_up.getPosition().x, right_up.getPosition().y)) { kill_find = true; break; }
					}
					if (kill_find == true && colission == false) { kill_chess.push_back(right_up); }
					if (kill_find == false && colission == false) point_to_go.push_back(right_up);
					x = 200, y = 70;
					temp++;
				}
				////////////////////////
				x = 200.0, y = 80.0, temp = 0;
				while (temp < 2)
				{
					bool colission{ false };
					bool kill_find{ false };
					sf::CircleShape left_down(25.f);
					left_down.setPosition(_sprite.getPosition().x - x, _sprite.getPosition().y + y);
					for (auto& h : Sprite_Storage_B)
						if (h.getGlobalBounds().contains(left_down.getPosition().x, left_down.getPosition().y)) { colission = true; break; };
					for (auto& h : Sprite_Storage_W)
					{
						if (h.getGlobalBounds().contains(left_down.getPosition().x, left_down.getPosition().y)) { kill_find = true; break; }
					}
					if (kill_find == true && colission == false) { kill_chess.push_back(left_down); }
					if (kill_find == false && colission == false) point_to_go.push_back(left_down);
					x = 100, y = 160;
					temp++;
				}
				//////////////////////////////
				x = 200.0, y = 80.0, temp = 0;
				while (temp < 2)
				{
					bool colission{ false };
					bool kill_find{ false };
					sf::CircleShape right_down(25.f);
					right_down.setPosition(_sprite.getPosition().x + x, _sprite.getPosition().y + y);
					for (auto& h : Sprite_Storage_B)
						if (h.getGlobalBounds().contains(right_down.getPosition().x, right_down.getPosition().y)) { colission = true; break; };
					for (auto& h : Sprite_Storage_W)
					{
						if (h.getGlobalBounds().contains(right_down.getPosition().x, right_down.getPosition().y)) { kill_find = true; break; }
					}
					if (kill_find == true && colission == false) { kill_chess.push_back(right_down); }
					if (kill_find == false && colission == false) point_to_go.push_back(right_down);
					x = 100, y = 160;
					temp++;
				}
			}
			if (check == 2 || check == 5)
			{
				float x{ 100.0 }, y{ 70.0 };

				while (true)
				{
					bool colission{ false };
					bool kill_find{ false };
					sf::CircleShape left_up(25.f);
					left_up.setPosition(_sprite.getPosition().x - x, _sprite.getPosition().y - y);
					if (left_up.getPosition().x < 0 || left_up.getPosition().y < 0) break;
					for (auto& h : Sprite_Storage_B)
						if (h.getGlobalBounds().contains(left_up.getPosition().x, left_up.getPosition().y)) { colission = true; break; }
					if (colission == true) break;
					for (auto& h : Sprite_Storage_W)
					{
						if (h.getGlobalBounds().contains(left_up.getPosition().x, left_up.getPosition().y)) { kill_find = true; break; }
					}
					if (kill_find == true && colission == false) { kill_chess.push_back(left_up);break; }
					if (kill_find == false && colission == false) point_to_go.push_back(left_up);
					x += 100.0;
					y += 70.0;
				}
				////////////////////
				x = 100.0, y = 75.0;

				while (true)
				{
					bool colission{ false };
					bool kill_find{ false };
					sf::CircleShape right_up(25.f);
					right_up.setPosition(_sprite.getPosition().x + x, _sprite.getPosition().y - y);
					if (right_up.getPosition().x > 800 || right_up.getPosition().y < 0) break;
					for (auto& h : Sprite_Storage_B)
						if (h.getGlobalBounds().contains(right_up.getPosition().x, right_up.getPosition().y)) { colission = true; break; }
					if (colission == true) break;
					for (auto& h : Sprite_Storage_W)
					{
						if (h.getGlobalBounds().contains(right_up.getPosition().x, right_up.getPosition().y)) { kill_find = true; break; }
					}
					if (kill_find == true && colission == false) { kill_chess.push_back(right_up);break; }
					if (kill_find == false && colission == false) point_to_go.push_back(right_up);
					x += 100.0;
					y += 75.0;
				}
				////////////////////////
				x = 100.0, y = 75.0;
				while (true)
				{
					bool colission{ false };
					bool kill_find{ false };
					sf::CircleShape left_down(25.f);
					left_down.setPosition(_sprite.getPosition().x - x, _sprite.getPosition().y + y);
					if (left_down.getPosition().x < 0 || left_down.getPosition().y > 600) break;
					for (auto& h : Sprite_Storage_B)
						if (h.getGlobalBounds().contains(left_down.getPosition().x, left_down.getPosition().y)) { colission = true; break; }
					if (colission == true) break;
					for (auto& h : Sprite_Storage_W)
					{
						if (h.getGlobalBounds().contains(left_down.getPosition().x, left_down.getPosition().y)) { kill_find = true; break; }
					}
					if (kill_find == true && colission == false) { kill_chess.push_back(left_down);break; }
					if (kill_find == false && colission == false) point_to_go.push_back(left_down);
					x += 100.0;
					y += 75.0;
				}
				/////////////////////////////
				x = 100.0, y = 75.0;
				while (true)
				{
					bool colission{ false };
					bool kill_find{ false };
					sf::CircleShape right_down(25.f);
					right_down.setPosition(_sprite.getPosition().x + x, _sprite.getPosition().y + y);
					if (right_down.getPosition().x > 800 || right_down.getPosition().y > 600) break;
					for (auto& h : Sprite_Storage_B)
						if (h.getGlobalBounds().contains(right_down.getPosition().x, right_down.getPosition().y)) { colission = true; break; }
					if (colission == true) break;

					for (auto& h : Sprite_Storage_W)
					{
						if (h.getGlobalBounds().contains(right_down.getPosition().x, right_down.getPosition().y)) { kill_find = true; break; }
					}
					if (kill_find == true && colission == false) { kill_chess.push_back(right_down);break; }
					if (kill_find == false && colission == false) point_to_go.push_back(right_down);
					x += 100.0;
					y += 75.0;
				}

			}
			if (check == 3)
			{
				float x{ 0.0 }, y{ 80.0 };
				////std::vector<sf::CircleShape> down;
				//std::vector<sf::CircleShape> up;
				//std::vector<sf::CircleShape> left;
				//std::vector<sf::CircleShape> right;
				while (true)
				{
					bool colission{ false };
					bool kill_find{ false };
					sf::CircleShape _down(25.f);
					_down.setPosition(_sprite.getPosition().x, _sprite.getPosition().y + y);
					y += 80;
					if (_down.getPosition().y > 600) break;
					for (auto& h : Sprite_Storage_B)
						if (h.getGlobalBounds().contains(_down.getPosition().x, _down.getPosition().y)) { colission = true; break; };
					if (colission == true) break;

					for (auto& h : Sprite_Storage_W)
					{
						if (h.getGlobalBounds().contains(_down.getPosition().x, _down.getPosition().y)) { kill_find = true; break; }
					}
					if (kill_find == true && colission == false) { kill_chess.push_back(_down);break; }
					if (kill_find == false && colission == false) point_to_go.push_back(_down);
				}
				x = 100.0, y = 0.0;
				while (true)
				{
					bool colission{ false };
					bool kill_find{ false };
					sf::CircleShape left(25.f);
					left.setPosition(_sprite.getPosition().x - x, _sprite.getPosition().y);
					x += 100;
					if (left.getPosition().x < 0) break;
					for (auto& h : Sprite_Storage_B)
						if (h.getGlobalBounds().contains(left.getPosition().x, left.getPosition().y)) { colission = true; break; };
					if (colission == true) break;
					for (auto& h : Sprite_Storage_W)
					{
						if (h.getGlobalBounds().contains(left.getPosition().x, left.getPosition().y)) { kill_find = true; break; }
					}
					if (kill_find == true && colission == false) { kill_chess.push_back(left);break; }
					if (kill_find == false && colission == false) point_to_go.push_back(left);

				}
				/////////////////////////////////
				x = 100.0, y = 0.0;
				while (true)
				{
					bool colission{ false };
					bool kill_find{ false };
					sf::CircleShape right(25.f);
					right.setPosition(_sprite.getPosition().x + x, _sprite.getPosition().y);
					x += 100;
					if (right.getPosition().x > 800) break;
					for (auto& h : Sprite_Storage_B)
						if (h.getGlobalBounds().contains(right.getPosition().x, right.getPosition().y)) { colission = true; break; };
					if (colission == true) break;
					for (auto& h : Sprite_Storage_W)
					{
						if (h.getGlobalBounds().contains(right.getPosition().x, right.getPosition().y)) { kill_find = true; break; }
					}
					if (kill_find == true && colission == false) { kill_chess.push_back(right);break; }
					if (kill_find == false && colission == false) point_to_go.push_back(right);
				}
				//////////////////////////
				x = 0.0, y = 70.0;
				while (true)
				{
					bool colission{ false };
					bool kill_find{ false };
					sf::CircleShape up(25.f);
					up.setPosition(_sprite.getPosition().x, _sprite.getPosition().y - y);
					y += 70;
					if (up.getPosition().y < 0) break;
					for (auto& h : Sprite_Storage_B)
						if (h.getGlobalBounds().contains(up.getPosition().x, up.getPosition().y)) { colission = true; break; };
					if (colission == true) break;

					for (auto& h : Sprite_Storage_W)
					{
						if (h.getGlobalBounds().contains(up.getPosition().x, up.getPosition().y)) { kill_find = true; break; }
					}
					if (kill_find == true && colission == false) { kill_chess.push_back(up);break; }
					if (kill_find == false && colission == false) point_to_go.push_back(up);
				}
				x = 100.0, y = 70.0;

				while (true)
				{
					bool colission{ false };
					bool kill_find{ false };
					sf::CircleShape left_up(25.f);
					left_up.setPosition(_sprite.getPosition().x - x, _sprite.getPosition().y - y);
					if (left_up.getPosition().x < 0 || left_up.getPosition().y < 0) break;
					for (auto& h : Sprite_Storage_B)
						if (h.getGlobalBounds().contains(left_up.getPosition().x, left_up.getPosition().y)) { colission = true; break; }
					if (colission == true) break;
					for (auto& h : Sprite_Storage_W)
					{
						if (h.getGlobalBounds().contains(left_up.getPosition().x, left_up.getPosition().y)) { kill_find = true; break; }
					}
					if (kill_find == true && colission == false) { kill_chess.push_back(left_up);break; }
					if (kill_find == false && colission == false) point_to_go.push_back(left_up);
					x += 100.0;
					y += 70.0;
				}
				////////////////////
				x = 100.0, y = 70.0;

				while (true)
				{
					bool colission{ false };
					bool kill_find{ false };
					sf::CircleShape right_up(25.f);
					right_up.setPosition(_sprite.getPosition().x + x, _sprite.getPosition().y - y);
					if (right_up.getPosition().x > 800 || right_up.getPosition().y < 0) break;
					for (auto& h : Sprite_Storage_B)
						if (h.getGlobalBounds().contains(right_up.getPosition().x, right_up.getPosition().y)) { colission = true; break; }
					if (colission == true) break;
					for (auto& h : Sprite_Storage_W)
					{
						if (h.getGlobalBounds().contains(right_up.getPosition().x, right_up.getPosition().y)) { kill_find = true; break; }
					}
					if (kill_find == true && colission == false) { kill_chess.push_back(right_up);break; }
					if (kill_find == false && colission == false) point_to_go.push_back(right_up);
					x += 100.0;
					y += 70.0;
				}
				////////////////////////
				x = 100.0, y = 80.0;
				while (true)
				{
					bool colission{ false };
					bool kill_find{ false };
					sf::CircleShape left_down(25.f);
					left_down.setPosition(_sprite.getPosition().x - x, _sprite.getPosition().y + y);
					if (left_down.getPosition().x < 0 || left_down.getPosition().y > 600) break;
					for (auto& h : Sprite_Storage_B)
						if (h.getGlobalBounds().contains(left_down.getPosition().x, left_down.getPosition().y)) { colission = true; break; }
					if (colission == true) break;
					for (auto& h : Sprite_Storage_W)
					{
						if (h.getGlobalBounds().contains(left_down.getPosition().x, left_down.getPosition().y)) { kill_find = true; break; }
					}
					if (kill_find == true && colission == false) { kill_chess.push_back(left_down);break; }
					if (kill_find == false && colission == false) point_to_go.push_back(left_down);
					x += 100.0;
					y += 80.0;
				}
				/////////////////////////////
				x = 100.0, y = 80.0;
				while (true)
				{
					bool colission{ false };
					bool kill_find{ false };
					sf::CircleShape right_down(25.f);
					right_down.setPosition(_sprite.getPosition().x + x, _sprite.getPosition().y + y);
					if (right_down.getPosition().x > 800 || right_down.getPosition().y > 600) break;
					for (auto& h : Sprite_Storage_B)
						if (h.getGlobalBounds().contains(right_down.getPosition().x, right_down.getPosition().y)) { colission = true; break; }
					if (colission == true) break;
					for (auto& h : Sprite_Storage_W)
					{
						if (h.getGlobalBounds().contains(right_down.getPosition().x, right_down.getPosition().y)) { kill_find = true; break; }
					}
					if (kill_find == true && colission == false) { kill_chess.push_back(right_down);break; }
					if (kill_find == false && colission == false) point_to_go.push_back(right_down);
					x += 100.0;
					y += 80.0;
				}
			}
			if (check == 4)
			{
				std::vector<bool> collision(8, false);
				std::vector<bool> kill_find(8, false);
				sf::CircleShape left(25.f);
				sf::CircleShape left_up(25.f);
				sf::CircleShape up(25.f);
				sf::CircleShape up_right(25.f);
				sf::CircleShape right(25.f);
				sf::CircleShape right_down(25.f);
				sf::CircleShape down(25.f);
				sf::CircleShape left_down(25.f);

				left.setPosition(_sprite.getPosition().x - 100, _sprite.getPosition().y);
				for (auto& h : Sprite_Storage_B)
					if (h.getGlobalBounds().contains(left.getPosition().x, left.getPosition().y)) { collision[0] = true; break; };
				for (auto& h : Sprite_Storage_W)
				{
					if (h.getGlobalBounds().contains(left.getPosition().x, left.getPosition().y)) { kill_find[0] = true; break; }
				}
				if (kill_find[0] == true && collision[0] == false) { kill_chess.push_back(left); }
				if (kill_find[0] == false && collision[0] == false) point_to_go.push_back(left);
				////////////////////////
				left_up.setPosition(_sprite.getPosition().x - 100, _sprite.getPosition().y - 75);
				for (auto& h : Sprite_Storage_B)
					if (h.getGlobalBounds().contains(left_up.getPosition().x, left_up.getPosition().y)) { collision[1] = true; break; };
				for (auto& h : Sprite_Storage_W)
				{
					if (h.getGlobalBounds().contains(left_up.getPosition().x, left_up.getPosition().y)) { kill_find[1] = true; break; }
				}
				if (kill_find[1] == true && collision[0] == false) { kill_chess.push_back(left_up); }
				if (kill_find[1] == false && collision[0] == false) point_to_go.push_back(left_up);
				////////////////////////////////
				up.setPosition(_sprite.getPosition().x, _sprite.getPosition().y - 75);
				for (auto& h : Sprite_Storage_B)
					if (h.getGlobalBounds().contains(up.getPosition().x, up.getPosition().y)) { collision[2] = true; break; };
				for (auto& h : Sprite_Storage_W)
				{
					if (h.getGlobalBounds().contains(up.getPosition().x, up.getPosition().y)) { kill_find[2] = true; break; }
				}
				if (kill_find[2] == true && collision[2] == false) { kill_chess.push_back(up); }
				if (kill_find[2] == false && collision[2] == false) point_to_go.push_back(up);
				////////////////////////////////
				up_right.setPosition(_sprite.getPosition().x + 100, _sprite.getPosition().y - 75);
				for (auto& h : Sprite_Storage_B)
					if (h.getGlobalBounds().contains(up_right.getPosition().x, up_right.getPosition().y)) { collision[3] = true; break; };
				for (auto& h : Sprite_Storage_W)
				{
					if (h.getGlobalBounds().contains(up_right.getPosition().x, up_right.getPosition().y)) { kill_find[3] = true; break; }
				}
				if (kill_find[3] == true && collision[3] == false) { kill_chess.push_back(up_right); }
				if (kill_find[3] == false && collision[3] == false) point_to_go.push_back(up_right);
				////////////////////////////////
				right.setPosition(_sprite.getPosition().x + 100, _sprite.getPosition().y);
				for (auto& h : Sprite_Storage_B)
					if (h.getGlobalBounds().contains(right.getPosition().x, right.getPosition().y)) { collision[4] = true; break; };
				for (auto& h : Sprite_Storage_W)
				{
					if (h.getGlobalBounds().contains(right.getPosition().x, right.getPosition().y)) { kill_find[4] = true; break; }
				}
				if (kill_find[4] == true && collision[4] == false) { kill_chess.push_back(right); }
				if (kill_find[4] == false && collision[4] == false) point_to_go.push_back(right);
				////////////////////////////////
				right_down.setPosition(_sprite.getPosition().x + 100, _sprite.getPosition().y + 75);
				for (auto& h : Sprite_Storage_B)
					if (h.getGlobalBounds().contains(right_down.getPosition().x, right_down.getPosition().y)) { collision[5] = true; break; };
				for (auto& h : Sprite_Storage_W)
				{
					if (h.getGlobalBounds().contains(right_down.getPosition().x, right_down.getPosition().y)) { kill_find[5] = true; break; }
				}
				if (kill_find[5] == true && collision[5] == false) { kill_chess.push_back(right_down); }
				if (kill_find[5] == false && collision[5] == false) point_to_go.push_back(right_down);
				////////////////////////////////
				down.setPosition(_sprite.getPosition().x, _sprite.getPosition().y + 75);
				for (auto& h : Sprite_Storage_B)
					if (h.getGlobalBounds().contains(down.getPosition().x, down.getPosition().y)) { collision[6] = true; break; };
				for (auto& h : Sprite_Storage_W)
				{
					if (h.getGlobalBounds().contains(down.getPosition().x, down.getPosition().y)) { kill_find[6] = true; break; }
				}
				if (kill_find[6] == true && collision[6] == false) { kill_chess.push_back(down); }
				if (kill_find[6] == false && collision[6] == false) point_to_go.push_back(down);
				////////////////////////////////
				left_down.setPosition(_sprite.getPosition().x - 100, _sprite.getPosition().y + 75);
				for (auto& h : Sprite_Storage_B)
					if (h.getGlobalBounds().contains(left_down.getPosition().x, left_down.getPosition().y)) { collision[7] = true; break; };
				for (auto& h : Sprite_Storage_W)
				{
					if (h.getGlobalBounds().contains(left_down.getPosition().x, left_down.getPosition().y)) { kill_find[7] = true; break; }
				}
				if (kill_find[7] == true && collision[7] == false) { kill_chess.push_back(left_down); }
				if (kill_find[7] == false && collision[7] == false) point_to_go.push_back(left_down);
				////////////////////////////////



			}
		}


//void Game::set_map()
//{
//	/*map[8][8] = { {&Sprite_Storage_W[0], &Sprite_Storage_W[1],&Sprite_Storage_W[2],&Sprite_Storage_W[3],&Sprite_Storage_W[4],&Sprite_Storage_W[5],&Sprite_Storage_W[6],&Sprite_Storage_W[7]},
//	   {&Sprite_Storage_W[8],&Sprite_Storage_W[9],&Sprite_Storage_W[10],&Sprite_Storage_W[11],&Sprite_Storage_W[12],&Sprite_Storage_W[13],&Sprite_Storage_W[14],&Sprite_Storage_W[15]},
//	   {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
//	   {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
//	   {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
//	   {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
//	   {&Sprite_Storage_B[0],&Sprite_Storage_B[1],&Sprite_Storage_B[2],&Sprite_Storage_B[3],&Sprite_Storage_B[4],&Sprite_Storage_B[5],&Sprite_Storage_B[6],&Sprite_Storage_B[7]},
//	   {&Sprite_Storage_B[8],&Sprite_Storage_B[9],&Sprite_Storage_B[10],&Sprite_Storage_B[11],&Sprite_Storage_B[12],&Sprite_Storage_B[13],&Sprite_Storage_B[14],&Sprite_Storage_B[15]}
//   };*/
//	/*map = { { Sprite_Storage_W[0], Sprite_Storage_W[1], Sprite_Storage_W[2], Sprite_Storage_W[3], Sprite_Storage_W[4], Sprite_Storage_W[5], Sprite_Storage_W[6], Sprite_Storage_W[7] },
//	{ Sprite_Storage_W[8], Sprite_Storage_W[9], Sprite_Storage_W[10], Sprite_Storage_W[11], Sprite_Storage_W[12], Sprite_Storage_W[13], Sprite_Storage_W[14], Sprite_Storage_W[15] },
//	{ NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL },
//	{ NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL },
//	{ NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL },
//	{ NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL },
//	{ Sprite_Storage_B[0], Sprite_Storage_B[1], Sprite_Storage_B[2], Sprite_Storage_B[3], Sprite_Storage_B[4], Sprite_Storage_B[5], Sprite_Storage_B[6], Sprite_Storage_B[7] },
//	{ Sprite_Storage_B[8], Sprite_Storage_B[9], Sprite_Storage_B[10], Sprite_Storage_B[11], Sprite_Storage_B[12], Sprite_Storage_B[13], Sprite_Storage_B[14], Sprite_Storage_B[15] }
//	};*/
//
//	
//
//}






