#include "pch.h"
#include "GameController.h"
#include "GameViewer.h"
#include <conio.h>
#include <Windows.h>
#include <iostream>

GameController::GameController(): _ch(0), _key(0), _doGame(true)
{
	_consoleOutHandler = (int)::GetStdHandle(STD_OUTPUT_HANDLE);

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

	for (std::size_t i = 0; i < _gremlins.size(); i++)
	{
		//_gremlins[i] = new VisualObject(0, 0, '*');
	}

	for (auto &gremlin : _gremlins)
	{
		gremlin = new VisualObject(0, 0, '*');
	}
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

	//Check overlap
	if (refPlayer1 == static_cast<Point>(refPlayer2)) _doGame = false;

	//Do player1 -->
	if(refPlayer1.X() <= _topLeftPoint.X()) refPlayer1.SetX(_topLeftPoint.X() + 1);
	if(refPlayer1.X() >= _bottomRightPoint.X()) refPlayer1.SetX(_bottomRightPoint.X() - 1);

	if (refPlayer1.X() <= _topLeftPoint.X()) refPlayer1.SetX(_topLeftPoint.X() + 1);
	if (refPlayer1.X() >= _bottomRightPoint.X()) refPlayer1.SetX(_bottomRightPoint.X() - 1);

	if (refPlayer1.Y() >= _topLeftPoint.Y()) refPlayer1.SetY(_topLeftPoint.Y() - 1);
	if (refPlayer1.Y() <= _bottomRightPoint.Y()) refPlayer1.SetY(_bottomRightPoint.Y() + 1);

	if (refPlayer1.Y() >= _topLeftPoint.Y()) refPlayer1.SetY(_topLeftPoint.Y() - 1);
	if (refPlayer1.Y() <= _bottomRightPoint.Y()) refPlayer1.SetY(_bottomRightPoint.Y() + 1);
	//<-- Do player1

	//Do player2 -->
	if (refPlayer2.X() <= _topLeftPoint.X()) refPlayer2.SetX(_topLeftPoint.X() + 1);
	if (refPlayer2.X() >= _bottomRightPoint.X()) refPlayer2.SetX(_bottomRightPoint.X() - 1);

	if (refPlayer2.X() <= _topLeftPoint.X()) refPlayer2.SetX(_topLeftPoint.X() + 1);
	if (refPlayer2.X() >= _bottomRightPoint.X()) refPlayer1.SetX(_bottomRightPoint.X() - 1);

	if (refPlayer2.Y() >= _topLeftPoint.Y()) refPlayer2.SetY(_topLeftPoint.Y() - 1);
	if (refPlayer2.Y() <= _bottomRightPoint.Y()) refPlayer2.SetY(_bottomRightPoint.Y() + 1);

	if (refPlayer2.Y() >= _topLeftPoint.Y()) refPlayer2.SetY(_topLeftPoint.Y() - 1);
	if (refPlayer2.Y() <= _bottomRightPoint.Y()) refPlayer2.SetY(_bottomRightPoint.Y() + 1);
	//<-- Do player2

	for (auto &gremlin : _gremlins)
	{
		int randomX = (rand() % (MAX_X_COOR - 1) + _topLeftPoint.X() + 1);
		int randomY = (rand() % (MAX_Y_COOR - 1) - _topLeftPoint.Y() + 1);
		gremlin->SetX(randomX).SetY(randomY);
	}
}

void GameController::DoRender()
{
	//::system("cls");
	COORD coordScreen = { 0, 0 };
	DWORD dwConSize = 0;

	::SetConsoleCursorPosition((HANDLE)_consoleOutHandler, coordScreen);
	std::cout << GameViewer(*_player1, *_player2, _gremlins).Render();
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
	delete[] _gremlins.data();
}

void GameController::DoGame()
{
	CONSOLE_CURSOR_INFO     cursorInfo;

	::GetConsoleCursorInfo((HANDLE)_consoleOutHandler, &cursorInfo);
	cursorInfo.bVisible = false;
	::SetConsoleCursorInfo((HANDLE)_consoleOutHandler, &cursorInfo);

	while (_doGame)
	{
		DoInput();
		DoRules();
		DoRender();

		::Sleep(33);
	}

	cursorInfo.bVisible = true;
	::SetConsoleCursorInfo((HANDLE)_consoleOutHandler, &cursorInfo);
}
