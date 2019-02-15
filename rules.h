#ifndef RULES_H_
#define RULES_H_

#define RULES_TEST_ 0

#include "game.h"
#include "player.h"

class Rules {
	int d_gameMode;
	int currentSide = 0;
	int block = 0;
private:
	void modifyGameCrab(Game&, string&, Player&);
	void modifyGamePengiun(Game&, Letter&, Number&) const;
	void modifyGameOctupus(Game&, Letter&, Number&, Letter&, Number&);

public:
	Rules(int);
	bool isValid(Game&);
	bool gameOver(const Game&) const;
	bool roundOver(const Game&) const;
	const Player& getNextPlayer(const Game&);
};

#endif /* RULES_H_ */
