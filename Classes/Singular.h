#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Shape.h"
#include <vector>
using namespace std;
extern int score1, score2, score3;
class Sin : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Sin);
	
	void menuCallBack(Ref* obj);
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

#endif