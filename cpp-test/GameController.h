#ifndef _GAME_CONTROLLER_H
#define _GAME_CONTROLLER_H

#include <map>
#include "VisualObject.h"

class GameController
{
	const int CHAR_ESC = 27;
	const int KEY_LEFT = 75;
	const int KEY_RIGHT = 77;
	const int KEY_UP = 72;
	const int KEY_DOWN = 80;
	const int CHAR_A = 'A';
	const int CHAR_D = 'D';
	const int CHAR_W = 'W';
	const int CHAR_S = 'S';

	int _key;
	int _ch;
	bool _doGame;

	GameController();
	void KeyLeft();
	void KeyRight();
	void KeyUp();
	void KeyDown();
	void KeyA();
	void KeyD();
	void KeyW();
	void KeyS();
	void KeyESC();

	std::map<int, void (GameController::*)()> _keyEventHandlerMap;

	VisualObject *_player1;
	VisualObject *_player2;
	Point _topLeftPoint;
	Point _bottomRightPoint;

	void DoInput();
	void DoRules();
	void DoRender();

public:
	const int MAX_X_COOR = 48;
	const int MAX_Y_COOR = 24;
	static GameController &Instance();
	~GameController();
	void DoGame();
};

#endif
