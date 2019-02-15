#ifndef GAME_H_
#define GAME_H_

#define GAME_TEST_ 0

#include "player.h"
#include "card.h"
#include "board.h"

#include <string>
#include <iostream>

using namespace std;

class Game {

	int d_round;
	int d_playerNum;
	Board d_board;

	Card const * prevCard;
	Card const * currentCard;

	vector<Player> players;

public:
	Game(int mode);
	~Game();

	int getRound() const; // returns a number between 0 and 6 corresponding to the current round of the game
	void nextRound();
	int getPlayerNum() const;

	void addPlayer(const Player&); //which adds a Player to this game.
	const Player& getPlayer(Side) const;
	const Card* getPreviousCard() const;
	const Card* getCurrentCard() const;
	void setCurrentCard(const Card*);

	Card* getCard(const Letter&, const Number&);
	void setCard(const Letter&, const Number&, Card*);

	//Functions that call the corresponding method in Board
	void turnFaceDown(const Letter&, const Number&);
	void turnFaceUp(const Letter&, const Number&);
	FaceUpCardsPosition* findPosition(const Card*) const;
	const bool isFaceUp(const Letter&, const Number&) const;

	void printBoard();
	bool isValidInput(const string&) const;
	//Conversion operators
	const Letter toLetter(const char&) const;
	const Number toNumber(const char&) const;
	friend ostream& operator<<(ostream&, const Game&);

	void modifyGameOctupus(const Letter&, const Number&, const Letter&,
			const Number&);

};

#endif /* GAME_H_ */
