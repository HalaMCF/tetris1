#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "cocos2d.h"

USING_NS_CC;

const int BLOCK_SIZE = 14;

class Block : public Sprite
{
public:
	CREATE_FUNC(Block);
	virtual bool init();

	void SetRow(int row)
	{
		this->row = row;
	}
	int GetRow() const 
	{
		return row;
	}
	void SetCol(int col) 
	{ 
		this->col = col;
	}
	int GetCol() const 
	{
		return col; 
	}

	void SetBlockType(int type);
	int GetBlockType()
	{ 
		return type;
	}

private:
	int row;							
	int col;
	int type;
};

#endif