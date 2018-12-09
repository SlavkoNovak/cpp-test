#include "pch.h"
#include "GameController.h"
#include "GameViewer.h"
#include <conio.h>
#include <Windows.h>
#include <iostream>

GameController::GameController(): _ch(0), _key(0), _doGame(true)
{
	_topLeftPoint = Point(-(MAX_X_COOR / 2), MAX_Y_COOR / 2);
	_bottomRightPoint = Point(MAX_X_COOR / 2, -(MAX_Y_COOR / 2));

	_keyEventHandlerMap[KEY_LEFT] = &GameController::KeyLeft;
	_keyEventHandlerMap[KEY_RIGHT] = &GameController::KeyRight;
	_keyEventHandlerMap[KEY_UP] = &GameController::KeyUp;
	_keyEventHandlerMap[KEY_DOWN] = &GameController::KeyDown;

	_keyEventHandlerMap[CHAR_A] = &GameController::KeyA;
	_keyEventHandlerMap[CHAR_D] = &GameController::KeyD;
	_keyEventHandlerMap[CHAR_W] = &GameController::KeyW;
	_keyEventHandlerMap[CHAR_S] = &GameController::KeyS;
	_keyEventHandlerMap[CHAR_ESC] = &GameController::KeyESC;

	_player1 = new VisualObject(-12, 0, '@');
	_player2 = new VisualObject(12, 0, '$');
}

void GameController::KeyLeft()
{
	*_player2 -= Point(1, 0);
}

void GameController::KeyRight()
{
	*_player2 += Point(1, 0);
}

void GameController::KeyUp()
{
	*_player2 += Point(0, 1);
}

void GameController::KeyDown()
{
	*_player2 -= Point(0, 1);
}

void GameController::KeyA()
{
	*_player1 -= Point(1, 0);
}

void GameController::KeyD()
{
	*_player1 += Point(1, 0);
}

void GameController::KeyW()
{
	*_player1 += Point(0, 1);
}

void GameController::KeyS()
{
	*_player1 -= Point(0, 1);
}

void GameController::KeyESC()
{
	_doGame = false;
}

void GameController::DoInput()
{
	if (::_kbhit())
	{
		_ch = ::toupper(::_getch());
		_key = ::_getch();
		int index = _key ? _key : _ch;

		void (GameController::*fp)() = nullptr;

		if (fp = _keyEventHandlerMap[index])
		{
			(*this.*fp)();
		}
	}
}

void GameController::DoRules()
{
	VisualObject &refPlayer1 = *_player1;
	VisualObject &refPlayer2 = *_player2;

	if (refPlayer1 == static_cast<Point>(refPlayer2)
		|| refPlayer1.X() <= _topLeftPoint.X()
		|| refPlayer1.X() >= _bottomRightPoint.X()
		|| refPlayer1.Y() >= _topLeftPoint.Y()
		|| refPlayer1.Y() <= _bottomRightPoint.Y()
		|| refPlayer2.X() <= _topLeftPoint.X()
		|| refPlayer2.X() >= _bottomRightPoint.X()
		|| refPlayer2.Y() >= _topLeftPoint.Y()
		|| refPlayer2.Y() <= _bottomRightPoint.Y())
	{
		_doGame = false;
	}
}

void GameController::DoRender()
{
	::system("cls");
	std::cout << GameViewer(*_player1, *_player2).Render();
}

GameController &GameController::Instance()
{
	static GameController *instance = nullptr;

	if (nullptr == instance)
	{
		instance = new GameController();
	}

	return *instance;
}

GameController::~GameController()
{
	delete _player1;
	delete _player2;
}

void GameController::DoGame()
{
	while (_doGame)
	{
		DoInput();
		DoRules();
		DoRender();

		::Sleep(100);
	}
}
