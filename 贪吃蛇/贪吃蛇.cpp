#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <graphics.h>
#include <conio.h>

#include "LinkList.h"

using namespace std;

#define MAP_SIZE 15
#define CELL_SIZE 20
#define DELTA 2
#define TIME 500


LinkList* snake=NULL;
int apple[2];
int next_point[2] = { (MAP_SIZE + 1) / 2 ,(MAP_SIZE + 1) / 2 };

void printMap()
{
	setcolor(RED);
	line(0, 0, 0, MAP_SIZE * CELL_SIZE);
	line(0, 3, MAP_SIZE * CELL_SIZE,3);
	line(MAP_SIZE * CELL_SIZE, 0, MAP_SIZE * CELL_SIZE, MAP_SIZE * CELL_SIZE);
	line(0, MAP_SIZE * CELL_SIZE, MAP_SIZE * CELL_SIZE, MAP_SIZE * CELL_SIZE);

	//setcolor(DARKGRAY);
	//for (int i = 0; i < MAP_SIZE + 1; i++)
	//{
	//	line(i * CELL_SIZE, 0, i * CELL_SIZE, MAP_SIZE * CELL_SIZE);
	//	line( 0, i * CELL_SIZE, MAP_SIZE * CELL_SIZE, i * CELL_SIZE);
	//}
}

void printCell(int point[2],State state)
{
		setfillcolor(BLACK);
		solidrectangle(point[0] * CELL_SIZE, point[1] * CELL_SIZE , (point[0] + 1) * CELL_SIZE,(point[1] + 1) * CELL_SIZE);

		setfillcolor(GREEN);
		switch (state)
		{
		case LeftUp:
			solidrectangle(point[0] * CELL_SIZE + DELTA, point[1] * CELL_SIZE + DELTA, (point[0] + 1) * CELL_SIZE, (point[1] + 1) * CELL_SIZE - DELTA);
			solidrectangle(point[0] * CELL_SIZE + DELTA, point[1] * CELL_SIZE + DELTA, (point[0] + 1) * CELL_SIZE - DELTA, (point[1] + 1) * CELL_SIZE);
			break;
		case LeftDown:
			solidrectangle(point[0] * CELL_SIZE + DELTA, point[1] * CELL_SIZE, (point[0] + 1) * CELL_SIZE - DELTA, (point[1] + 1) * CELL_SIZE - DELTA);
			solidrectangle(point[0] * CELL_SIZE + DELTA, point[1] * CELL_SIZE + DELTA, (point[0] + 1) * CELL_SIZE, (point[1] + 1) * CELL_SIZE - DELTA);
			break;
		case RightUp:
			solidrectangle(point[0] * CELL_SIZE, point[1] * CELL_SIZE + DELTA, (point[0] + 1) * CELL_SIZE - DELTA, (point[1] + 1) * CELL_SIZE - DELTA);
			solidrectangle(point[0] * CELL_SIZE + DELTA, point[1] * CELL_SIZE + DELTA, (point[0] + 1) * CELL_SIZE - DELTA, (point[1] + 1) * CELL_SIZE);
			break;
		case RightDown:
			solidrectangle(point[0] * CELL_SIZE, point[1] * CELL_SIZE + DELTA, (point[0] + 1) * CELL_SIZE - DELTA, (point[1] + 1) * CELL_SIZE - DELTA);
			solidrectangle(point[0] * CELL_SIZE + DELTA, point[1] * CELL_SIZE, (point[0] + 1) * CELL_SIZE - DELTA, (point[1] + 1) * CELL_SIZE - DELTA);
			break;
		case xAxis:
			solidrectangle(point[0] * CELL_SIZE, point[1] * CELL_SIZE + DELTA, (point[0] + 1) * CELL_SIZE, (point[1] + 1) * CELL_SIZE - DELTA);
			break;
		case yAxis:
			solidrectangle(point[0] * CELL_SIZE + DELTA, point[1] * CELL_SIZE, (point[0] + 1) * CELL_SIZE - DELTA, (point[1] + 1) * CELL_SIZE);
			break;
		}
}

void CreatApple()
{
	while (1)
	{
		apple[0] = rand() % MAP_SIZE;
		apple[1] = rand() % MAP_SIZE;
		if (findNode(snake, apple,0) == -1)break;
	}
	setfillcolor(RED);
	solidrectangle(apple[0] * CELL_SIZE + 2*DELTA, apple[1] * CELL_SIZE + 2*DELTA, (apple[0] + 1) * CELL_SIZE - 2*DELTA, (apple[1] + 1) * CELL_SIZE - 2*DELTA);
}

void InitGame()
{
	State state = xAxis;
	int initsnake[2] = { (MAP_SIZE + 1) / 2 ,(MAP_SIZE + 1) / 2 };
	srand(time(NULL));
	snake = InitList();
	addHeadList(snake, initsnake,state);
	initgraph(MAP_SIZE * CELL_SIZE+1, MAP_SIZE * CELL_SIZE+1);
	printMap();
	printCell(snake->pHead->Data, snake->pHead->state);
	CreatApple();
	return;
}

Direction GetDirection()
{
	// 检查是否有键盘输入
	if (_kbhit()) {
		int ch = _getch();
		// 方向键通常返回两个字节：第一个是 224（0xE0），第二个是具体方向
		if (ch == 0xE0) {
			ch = _getch(); // 读取第二个字节
			switch (ch) {
			case 72: return Up;    // 上箭头
			case 80: return Down;  // 下箭头
			case 75: return Left;  // 左箭头
			case 77: return Right; // 右箭头
			}
		}
	}
	return Null; // 无输入或非方向键
}

void chengeDirection(Direction* direction)
{
	if (*direction == Null)
		*direction = snake->direction;

	if (*direction <= 2)
		*direction = (snake->direction > 2) ? *direction : snake->direction;
	else
		*direction = (snake->direction <= 2) ? *direction : snake->direction;

	switch (*direction)
	{
	case Up:
		if (snake->direction == Left)snake->pHead->state = LeftDown;
		if (snake->direction == Right)snake->pHead->state = RightDown;
		next_point[1]--;
		break;
	case Down:
		if (snake->direction == Left)snake->pHead->state = LeftUp;
		if (snake->direction == Right)snake->pHead->state = RightUp;
		next_point[1]++;
		break;
	case Left:
		if (snake->direction == Up)snake->pHead->state = RightUp;
		if (snake->direction == Down)snake->pHead->state = RightDown;
		next_point[0]--;
		break;
	case Right:
		if (snake->direction == Up)snake->pHead->state = LeftUp;
		if (snake->direction == Down)snake->pHead->state = LeftDown;
		next_point[0]++;
		break;
	}
}

bool checkWall()
{
	int p[2] = { snake->pHead->Data[0],snake->pHead->Data[1] };
	if ((p[0] == -1 || p[0] == MAP_SIZE) || (p[1] == -1 || p[1] == MAP_SIZE))
		return 1;
	else
		return 0;
}

bool checkSnakeBody()
{
	if (findNode(snake, next_point,1) >= 0)
		return 1;
}


void PlayGame()
{
	cout << "准备好了吗？ ";
	system("pause");
	//printMap();
	Direction direction;
	State state;
	while (1)
	{
		direction = GetDirection();
		chengeDirection(&direction);
		state = (direction <= 2) ? yAxis : xAxis;
		snake->direction = direction;
		printCell(snake->pHead->Data, snake->pHead->state);
		if (checkSnakeBody() == 1)
		{
			cout << "蛇碰到身体，游戏结束" << endl;
			return;
		}
		addHeadList(snake, next_point, state);
		if (checkWall() == 1)
		{
			cout << "蛇碰墙，游戏结束" << endl;
			return;
		}

		if (snake->pHead->Data[0] == apple[0] && snake->pHead->Data[1] == apple[1])
		{
			if (snake->len >= MAP_SIZE * MAP_SIZE)
			{
				cout << "恭喜你，成功通关！" << endl;
			}
			else
				CreatApple();
		}
		else
		{
			printCell(snake->pEnd->Data,air);
			DeleteList(snake, snake->len-1);
		}
		printCell(snake->pHead->Data, snake->pHead->state);
		Sleep(TIME);
	}
}

int main()
{
	InitGame();
	PlayGame();
	system("pause");
}