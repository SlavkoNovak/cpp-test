#include "pch.h"
#include "GameViewer.h"
#include "GameController.h"
#include <sstream>
#include <iomanip>

int GameViewer::ToRealXCoor(const int x) const
{
	return x + GameController::Instance().MAX_X_COOR / 2;
}

int GameViewer::ToRealYCoor(const int y) const
{
	return GameController::Instance().MAX_Y_COOR - (y + GameController::Instance().MAX_Y_COOR / 2);
}

GameViewer::GameViewer(const VisualObject &player1, const VisualObject &player2, const std::array<VisualObject *, 10> &_gremlins)
	: _rendered("")
{
	VisualObject &refPlayer1 = const_cast<VisualObject &>(player1);
	VisualObject &refPlayer2 = const_cast<VisualObject &>(player2);

	ostringstream os;
	os << "@ pos: (" << setw(3) << refPlayer1.X() << ", " << setw(3) << refPlayer1.Y() << ");\t";
	os << "$ pos: (" << setw(3) << refPlayer2.X() << ", " << setw(3) << refPlayer2.Y() << ")\n";

	int player1RealX = ToRealXCoor(refPlayer1.X());
	int player1RealY = ToRealYCoor(refPlayer1.Y());
	int player2RealX = ToRealXCoor(refPlayer2.X());
	int player2RealY = ToRealYCoor(refPlayer2.Y());

	for (auto &gremlin : _gremlins)
	{
		int gremlinRealX = ToRealXCoor(gremlin->X());
		int gremlinRealY = ToRealYCoor(gremlin->Y());
		_template.at(gremlinRealY).at(gremlinRealX) = gremlin->Symbol();
	}

	_template.at(player1RealY).at(player1RealX) = refPlayer1.Symbol();
	_template.at(player2RealY).at(player2RealX) = refPlayer2.Symbol();

	for (const auto &line : _template)
	{
		os << line;
	}

	_rendered.append(os.str());
}

string &GameViewer::Render()
{
	return _rendered;
}

