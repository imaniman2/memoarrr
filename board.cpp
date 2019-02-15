#include "board.h"
#include <string>

class OutOfRangeException: public exception {
	virtual const char* what() const throw () {
		return "The letter and number values are out of range of the board.";
	}
} OutOfRange;

class NoMoreCardsException: public exception {
	virtual const char* what() const throw () {
		return "There are not enough cards in the card deck to make board.";
	}
} NoMoreCards;

Board::Board(int mode) :
		displayMode(mode), numFaceUp(0) {

	CardDeck &carddeck = CardDeck::make_CardDeck();
	carddeck.shuffle();

	board = new Card **[5];
	for (int i = 0; i < 5; i++) {
		board[i] = new Card *[5];
	}
	isFaceDown = new bool *[5];
	for (int i = 0; i < 5; i++) {
		isFaceDown[i] = new bool[5];
		for (int j = 0; j < 5; j++) {
			isFaceDown[i][j] = false;
		}
	}
	row = new string[d_width];

	for (int i = 0; i < d_width; i++) {
		row[i].reserve(d_height);
		row[i].assign(d_height, ' ');
	}
	try {
		//adding 24 cards to board
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (carddeck.isEmpty()) {
					throw NoMoreCards;
				}
				if (!(i == 2 && j == 2)) {
					board[i][j] = carddeck.getNext();
				} else {
					board[2][2] = nullptr;
				}

			}
		}
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (i != 2 || j != 2) {
				isFaceDown[i][j] = true;
			}
		}
	}

	if (displayMode == 1) {
		createBasicBoard();
	}
	if (displayMode == 2) {
		createExpertBoard();
		faceUpCards = new FaceUpCardsPosition[24];
	}
}

Board::~Board() {
	delete row;
	delete board;
	delete isFaceDown;
	delete faceUpCards;
}

bool Board::isFaceUp(const Letter& letter, const Number& number) const {
	try {
		if (static_cast<int>(letter) > 4 || static_cast<int>(number) > 4) {
			throw OutOfRange;
		}
		return !isFaceDown[static_cast<int>(letter)][static_cast<int>(number)];
	} catch (exception& e) {
		cout << e.what() << endl;
		throw e;

	}
}
/*returns true if the card at a given position is
 face up. Letter and Number are enumerations. Throws an exception of type OutOfRange if an invalid
 Letter and Number combination was given.*/
bool Board::turnFaceUp(const Letter& letter, const Number& number) {
	try {
		if (static_cast<int>(letter) > 4 || static_cast<int>(number) > 4) {
			throw OutOfRange;
		}
		if (isFaceUp(letter, number)) {
			return false;
		} else {
			isFaceDown[static_cast<int>(letter)][static_cast<int>(number)] =
					false;
			if (displayMode == 1) {
				createBasicBoard();
			}
			if (displayMode == 2) {
				faceUpCards[numFaceUp] = FaceUpCardsPosition { letter, number };
				numFaceUp++;
				createExpertBoard();
			}
			return true;
		}
	} catch (exception& e) {
		cout << e.what() << endl;
		throw e;

	}
}
/*changes the state of the specified card return false
 if card was up already. Throws an exception of type OutOfRange if an invalid Letter and Number
 combination was given.*/
bool Board::turnFaceDown(const Letter& letter, const Number& number) {
	try {
		if (static_cast<int>(letter) > 4 || static_cast<int>(number) > 4) {
			throw OutOfRange;
		}
		if (!isFaceUp(letter, number)) {
			return false;
		} else {
			isFaceDown[static_cast<int>(letter)][static_cast<int>(number)] =
					true;
			numFaceUp--;
			if (displayMode == 1) {
				createBasicBoard();
			}
			if (displayMode == 2) {
				createExpertBoard();
			}
			return true;
		}
	} catch (exception& e) {
		cout << e.what() << endl;
		throw e;

	}
}
/*changes the state of the specified card return
 false if card was down already. Throws an exception of type OutOfRange if an invalid Letter and
 Number combination was given.*/
Card* Board::getCard(const Letter& letter, const Number& number) {
	try {
		if (static_cast<int>(letter) > 4 || static_cast<int>(number) > 4) {
			throw OutOfRange;
		}
		return board[static_cast<int>(letter)][static_cast<int>(number)];
	} catch (exception& e) {
		cout << e.what() << endl;
		throw e;
	}
}
/*returns a pointer to the card at a given location.
 Throws an exception of type OutOfRange if an invalid Letter and Number combination was given.*/
void Board::setCard(const Letter& letter, const Number& number, Card* card) {
	try {
		if (static_cast<int>(letter) > 4 || static_cast<int>(number) > 4) {
			throw OutOfRange;
		}
		board[static_cast<int>(letter)][static_cast<int>(number)] = card;
		if (displayMode == 1) {
			createBasicBoard();
		}
		if (displayMode == 2) {
			createExpertBoard();
		}
	} catch (exception& e) {
		cout << e.what() << endl;
		throw e;
	}
}
/*updates the pointer to card at a given location.
 Throws an exception of type OutOfRange if an invalid Letter and Number combination was given.*/
void Board::reset() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (i != 2 || j != 2) {
				isFaceDown[i][j] = true;
			}
		}
	}
	if (displayMode == 1) {
		createBasicBoard();
	}
	if (displayMode == 2) {
		numFaceUp = 0;
		createExpertBoard();
	}
}
/*changes the state to all cards to be face down.*/

//add private function, turns card array into a board of strings
void Board::createBasicBoard() {
	for (int i = 0; i < 5; i++) { //going throw row of cards
		int count = 0;
		while (count < 3) {
			row[i * 4 + count] = "";
			if (count == 1) {
				if (i == 0) {
					row[i * 4 + count].append(" A ");
				} else if (i == 1) {
					row[i * 4 + count].append(" B ");
				} else if (i == 2) {
					row[i * 4 + count].append(" C ");
				} else if (i == 3) {
					row[i * 4 + count].append(" D ");
				} else if (i == 4) {
					row[i * 4 + count].append(" E ");
				}
			} else {
				row[i * 4 + count].append("   ");
			}
			for (int j = 0; j < 5; j++) {
				if ((i == 2) && (j == 2)) {
					row[i * 4 + count].append("    ");
				} else {
					if (isFaceUp(static_cast<Letter>(i),
							static_cast<Number>(j))) {
						row[i * 4 + count].append(board[i][j]->getRow(count));
					} else {
						row[i * 4 + count].append("zzz ");
					}
				}

			}
			count++;
		}
		row[i * 4 + 3].assign(d_height, ' ');
	}
	row[21].assign("    1   2   3   4   5  ");
	row[22].assign(d_height, ' ');
}

void Board::createExpertBoard() {
	for (int i = 0; i < 3; i++) {
		row[i] = "";
		for (int j = 0; j < numFaceUp; j++) {
			row[i].append(
					board[static_cast<int>(faceUpCards[j].letter)][static_cast<int>(faceUpCards[j].number)]->getRow(
							i));
		}
	}
	row[3].assign(d_height, ' ');
	row[4].assign(d_height, ' ');
	row[5] = "";
	for (int i = 0; i < numFaceUp; i++) {
		row[5].append(" ");
		if (faceUpCards[i].letter == Letter::A) {
			row[5].append("A");
		} else if (faceUpCards[i].letter == Letter::B) {
			row[5].append("B");
		} else if (faceUpCards[i].letter == Letter::C) {
			row[5].append("C");
		} else if (faceUpCards[i].letter == Letter::D) {
			row[5].append("D");
		} else if (faceUpCards[i].letter == Letter::E) {
			row[5].append("E");
		}
		if (faceUpCards[i].number == Number::One) {
			row[5].append("1");
		} else if (faceUpCards[i].number == Number::Two) {
			row[5].append("2");
		} else if (faceUpCards[i].number == Number::Three) {
			row[5].append("3");
		} else if (faceUpCards[i].number == Number::Four) {
			row[5].append("4");
		} else if (faceUpCards[i].number == Number::Five) {
			row[5].append("5");
		}
	}
}

ostream& operator<<(ostream& o, const Board& board) {
	//Create each row and draw to the screen
	if (board.displayMode == 1) {
		for (int i = 0; i < board.d_height; i++) {
			o << board.row[i] << "\n";
		}
	}
	if (board.displayMode == 2) {
		for (int i = 0; i < 6; i++) {
			o << board.row[i] << "\n";
		}
	}

	return o;
}

FaceUpCardsPosition* Board::findPosition(const Card* card) const {
	FaceUpCardsPosition * result = new FaceUpCardsPosition();
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (board[i][j] == card) {
				result->letter = static_cast<Letter>(i);
				result->number = static_cast<Number>(j);
			}
		}
	}
	return result;
}

#if BOARD_TEST_

int main() {
	cout << "--------------BOARD_TEST_--------------" << endl;

	int displayMode;
	while ((cout
					<< "Enter the display mode of the board (1 for Regular, 2 for Expert): "
					&& !(cin >> displayMode)) || (displayMode != 1 && displayMode != 2)) {
		cin.clear(); //clear bad input flag
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//discard input
		cout << "Invalid input; please re-enter.\n";
	}

	//The constructor of Board makes CardDeck and shuffles it.
	//It also uses getNext() to empty CardDeck and fill the Card matrix in Board.
	Board newBoard(displayMode);

	cout << "The card at postion A1 is ";
	newBoard.isFaceUp(Letter::A, Number::One)? cout << "face up.\n" : cout << "face down.\n";

	cout << "Turning card at postion A1 face up... " << endl;
	newBoard.turnFaceUp(Letter::A, Number::One);

	cout << "The card at postion A1 is ";
	newBoard.isFaceUp(Letter::A, Number::One)? cout << "face up.\n" : cout << "face down.\n";

	cout << "\n The overloaded insertion operator prints as follows: \n" << newBoard << endl;

	cout << "Turning card at postion A1 face down... " << endl;
	newBoard.turnFaceDown(Letter::A, Number::One);

	cout << "The card at postion A1 is ";
	newBoard.isFaceUp(Letter::A, Number::One)? cout << "face up.\n" : cout << "face down.\n\n";

	cout << "The card at postion A2, B1 and C4 is " <<endl;

	cout << *newBoard.getCard(Letter::A, Number::Two) <<endl;
	cout << *newBoard.getCard(Letter::B, Number::One) <<endl;
	cout << *newBoard.getCard(Letter::C, Number::Four) <<endl;

	cout << "Turning these cards face up..." <<endl;

	newBoard.turnFaceUp(Letter::A, Number::Two);
	newBoard.turnFaceUp(Letter::B, Number::One);
	newBoard.turnFaceUp(Letter::C, Number::Four);

	cout << "\nThe overloaded insertion operator prints as follows: \n" << newBoard << endl;

	cout << "Setting the card at postion A2 to be the card at postion B1...";
	newBoard.setCard(Letter::A, Number::Two,newBoard.getCard(Letter::B, Number::One));

	cout << "\nThe overloaded insertion operator prints as follows: \n" << newBoard << endl;

	cout << "Resetting board..";
	newBoard.reset();
	cout << "\nThe overloaded insertion operator prints as follows: \n" << newBoard << endl;

	cout << "--------------END BOARD_TEST_--------------" << endl;

}

#endif
