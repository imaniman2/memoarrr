#ifndef BOARD_H_
#define BOARD_H_

#define BOARD_TEST_ 0

#include <iostream>
#include <string>

using namespace std;
#include "card.h"
#include "carddeck.h"

enum class Letter {
	A, B, C, D, E
};
enum class Number {
	One, Two, Three, Four, Five
};

struct FaceUpCardsPosition {
	Letter letter;
	Number number;
};

class Board {

private:
	string * row;
	Card *** board;
	bool ** isFaceDown;
	int displayMode;
	int numFaceUp;
	FaceUpCardsPosition * faceUpCards;

	void createBasicBoard();
	void createExpertBoard();

public:
	const int d_width = 23;
	const int d_height = 23;

	Board(int mode);
	~Board();

	bool isFaceUp(const Letter&, const Number&) const; /*returns true if the card at a given position is
	 face up. Letter and Number are enumerations. Throws an exception of type OutOfRange if an invalid
	 Letter and Number combination was given.*/
	bool turnFaceUp(const Letter&, const Number&); /*changes the state of the specified card return false
	 if card was up already. Throws an exception of type OutOfRange if an invalid Letter and Number
	 combination was given.*/
	bool turnFaceDown(const Letter&, const Number&); /*changes the state of the specified card return
	 false if card was down already. Throws an exception of type OutOfRange if an invalid Letter and
	 Number combination was given.*/
	Card* getCard(const Letter&, const Number&); /*returns a pointer to the card at a given location.
	 Throws an exception of type OutOfRange if an invalid Letter and Number combination was given.*/
	void setCard(const Letter&, const Number&, Card*); /*updates the pointer to card at a given location.
	 Throws an exception of type OutOfRange if an invalid Letter and Number combination was given.*/
	void reset(); /*changes the state to all cards to be face down.*/

	friend ostream& operator<<(ostream&, const Board&);
	/*A board must be printable with the insertion operator cout << board. The constructor for board should
	 throw and Exception of type NoMoreCards if there are no more cards available to construct a board.
	 */
    FaceUpCardsPosition* findPosition(const Card*) const;

	//For access to private functions in BOARD_TEST_
	#if BOARD_TEST_
		friend int main();
	#endif

};



#endif /* BOARD_H_ */
