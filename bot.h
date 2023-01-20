#pragma once
#include "Area.h"
#include <queue>

enum directions {
	UP,
	LEFT,
	DOWN,
	RIGHT,
};
class bot {
private:
	int Botx; // координати для вистрілу
	int Boty; 
	int FindedX;
	int FindedY;// координати новознайденої палуби
	Area bot_mask; //поле-маска для бота
	int bot_score; // рахунок бота
	bool bot_find_ship; // прапор чи знаходится бот в режимі пошуку корабля
	std::queue<directions> q_dir; // черга в якій зберігаються напрямки 

	bool find_new_coordinates(); // знайти нові координати для вистрілу

	bool bot_attack(Area& Board, int ShootX, int ShootY); //функція атаки бота


	void find_directions(int XtoDir, int YtoDir); //знайти можливі напрямки для новознайденої палуби
public:
	void bot_move(Area& Board);//функція ходу бота

	bot(int N); //конструктор бота

	int getBotScore();//повернути рахунок бота

	Area get_bot_mask();

};
