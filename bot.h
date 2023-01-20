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
	int Botx; // ���������� ��� �������
	int Boty; 
	int FindedX;
	int FindedY;// ���������� ������������ ������
	Area bot_mask; //����-����� ��� ����
	int bot_score; // ������� ����
	bool bot_find_ship; // ������ �� ���������� ��� � ����� ������ �������
	std::queue<directions> q_dir; // ����� � ��� ����������� �������� 

	bool find_new_coordinates(); // ������ ��� ���������� ��� �������

	bool bot_attack(Area& Board, int ShootX, int ShootY); //������� ����� ����


	void find_directions(int XtoDir, int YtoDir); //������ ������ �������� ��� ������������ ������
public:
	void bot_move(Area& Board);//������� ���� ����

	bot(int N); //����������� ����

	int getBotScore();//��������� ������� ����

	Area get_bot_mask();

};
