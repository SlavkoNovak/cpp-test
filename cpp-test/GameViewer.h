#ifndef _GAME_VIEWER_H
#define _GAME_VIEWER_H

#include "VisualObject.h"
#include <string>
#include <array>

using namespace std;

class GameViewer
{
	array<string, 25> _template = {
		"#################################################\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#                                               #\n",
		"#################################################\n"
	};
	
	string _rendered;
	inline int ToRealXCoor(const int x) const;
	inline int ToRealYCoor(const int y) const;


public:
	GameViewer() = delete;
	explicit GameViewer(const VisualObject & player1, const VisualObject & player2, const std::array<VisualObject*, 10> &_gremlins);
	//	explicit GameViewer(const VisualObject &player1, const VisualObject &player2);
	const string &Render() const;
};

#endif
