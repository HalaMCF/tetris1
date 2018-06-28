#pragma once
#include "cocos2d.h"
#include "Shape.h"
#include <vector>
using namespace std;
class Net : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Net);
private:
	int score;
	int line;
	float speed;
	Shape* NextShape;
	Shape* CurShape;
	vector<int> clearlines;
	int map[BOARD_WIDTH][BOARD_HEIGHT];
	Vector<Block*> blocks;
	vector<int>scores;
	EventListenerKeyboard* listener;

	void SetNext();
	void PushNext(float t);

	void Down(float t);
	void Left();
	void Right();
	void TowardsDown();

	void TurnShape();

	bool checkBorder(int type);

	void SetMap();

	int CalClearNum();
	void BlockClear();

	void AddScore(int num);

	bool isGameOver();
	void gameOver();
};
