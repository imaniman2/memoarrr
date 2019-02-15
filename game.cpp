#include "game.h"

class NoPlayerHereException: public exception {
	virtual const char* what() const throw () {
		return "There is no player at this side.";
	}
} NoPlayerHere;

Game::Game(int displayMode) :
		d_round(0), d_playerNum(0), d_board(displayMode) {
	prevCard = nullptr;
	currentCard = nullptr;
}
Game::~Game() {
	players.clear();
	prevCard = nullptr;
	currentCard = nullptr;
}
int Game::getRound() const {
	return d_round;
}
void Game::nextRound() {
	prevCard = nullptr;
	currentCard = nullptr;
	d_board.reset();

	d_round++;
}
int Game::getPlayerNum() const {
	return d_playerNum;
}

//adds or updates a player. If Player is already in Game, the player is
//updated, and if not it is added.
void Game::addPlayer(const Player& newplayer) {
	bool foundPlayer = false;
	for (int i = 0; i < d_playerNum; i++) {
		if (newplayer.getName() == players.at(i).getName()) {
			foundPlayer = true;
			players.at(i).setActive(newplayer.isActive());
			players.at(i).setNRubies(newplayer.getNRubies());
		}
	}
	if (!foundPlayer) {
		players.push_back(newplayer);
		d_playerNum++;
	}
}

const Player& Game::getPlayer(Side side) const {

	Player const * ptr = &(players.front());
	try {

		for (int i = 0; i < d_playerNum; i++) {
			if ((ptr->getSide()) == (side)) {
				return *ptr;
			}
			ptr++;
		}
		throw NoPlayerHere;
	} catch (exception& e) {
		cout << e.what() << endl;
		throw e;
	}

}
const Card* Game::getPreviousCard() const {
	return prevCard;
}
const Card* Game::getCurrentCard() const {
	return currentCard;
}
void Game::setCurrentCard(const Card* newCurrent) {

	//(const Letter& letter, const Number& number)

	//Find Card to flip
	Number found_number = Number::One;
	Letter found_letter = Letter::A;

	for (Number number = Number::One; (static_cast<int>(number)) < 5; number =
			static_cast<Number>((static_cast<int>(number)) + 1)) {
		for (Letter letter = Letter::A; (static_cast<int>(letter)) < 5; letter =
				static_cast<Letter>((static_cast<int>(letter)) + 1)) {
			if (newCurrent == d_board.getCard(letter, number)) {
				found_number = number;
				found_letter = letter;
				goto FOUND;
			}
		}
	}
	FOUND: if (!d_board.isFaceUp(found_letter, found_number)) {
		d_board.turnFaceUp(found_letter, found_number);
	} else {
		d_board.turnFaceDown(found_letter, found_number);
	}

	prevCard = currentCard;
	currentCard = newCurrent;
}

Card* Game::getCard(const Letter& letter, const Number& number) {
	return d_board.getCard(letter, number);
}

//In expert mode, you will have to exchange two cards.
//With this function, you can update the pointer to card for a certain position on the board.
void Game::setCard(const Letter& letter, const Number& number, Card* card) {
	d_board.setCard(letter, number, card);
}

void Game::turnFaceDown(const Letter& letter, const Number& number) {
	d_board.turnFaceDown(letter, number);
}

void Game::turnFaceUp(const Letter& letter, const Number& number) {
	d_board.turnFaceUp(letter, number);
}

FaceUpCardsPosition* Game::findPosition(const Card* card) const {
	return d_board.findPosition(card);
}

const bool Game::isFaceUp(const Letter& letter, const Number& number) const {
	return d_board.isFaceUp(letter, number);
}

void Game::printBoard() {
	cout << "-------------------------" << endl;
	cout << d_board;
	cout << "-------------------------" << endl;

}

bool Game::isValidInput(const string &input) const {
	bool valid = true;
	if (input.length() != 2) {
		valid = false;
	}
	if (!isalpha(input[0]) || !isdigit(input[1])) {
		valid = false;
	}
	if (!((input[0] >= 'A') && (input[0] <= 'E'))
			&& !((input[0] >= 'a') && (input[0] <= 'e'))) {
		valid = false;
	}
	if (!((input[1] >= '1') && (input[1] <= '5'))) {
		valid = false;
	}
	if (d_board.isFaceUp(toLetter(input[0]), toNumber(input[1]))) {
		valid = false;
	}
	return valid;
}

const Letter Game::toLetter(const char &letter) const {
	switch (letter) {
	case 'A':
	case 'a':
		return Letter::A;
	case 'B':
	case 'b':
		return Letter::B;
	case 'C':
	case 'c':
		return Letter::C;
	case 'D':
	case 'd':
		return Letter::D;
	case 'E':
	case 'e':
		return Letter::E;
	default:
		return Letter::A;
	}
}
const Number Game::toNumber(const char &number) const {
	switch (number) {
	case '1':
		return Number::One;
	case '2':
		return Number::Two;
	case '3':
		return Number::Three;
	case '4':
		return Number::Four;
	case '5':
		return Number::Five;
	default:
		return Number::One;
	}
}

ostream& operator<<(ostream& o, const Game& game) {

	o << "The game has " << game.d_playerNum
			<< " players and is currently on round " << game.d_round << "."
			<< endl;
	o << "-------------------------" << endl;
	o << game.d_board;
	for (int i = 0; i < game.d_playerNum; i++) {
		o << game.players.at(i) << endl;
	}
	o << "-------------------------" << endl;
	return o;
}

#if GAME_TEST_

int main() {

	cout << "--------------GAME_TEST_--------------" << endl;

	int mode;
	while ((cout
					<< "Enter the display mode of the board (1 for Regular, 2 for Expert): "
					&& !(cin >> mode)) || (mode != 1 && mode != 2)) {
		cin.clear(); //clear bad input flag
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//discard input
		cout << "Invalid input; please re-enter.\n";
	}
	Game newGame(mode);

	for (int i = 0; i < 4; i++) {
		newGame.addPlayer(Player(static_cast<Side>(i), "Bob " + to_string(i) , false));
		cout << newGame.getPlayer(static_cast<Side>(i)) << " created\n";
	}

	cout << "The current round is " << newGame.getRound() << endl;
	cout << "incrementing round... " << endl;
	newGame.nextRound();
	cout << "The current round is now " << newGame.getRound() << endl;

	string card;
	while ((cout << "Please pick a card on board: " && !(cin >> card))
			|| !(newGame.isValidInput(card))) {
		cout << "Invalid input; please re-enter.\n";
	}
	newGame.setCurrentCard(
			newGame.getCard(newGame.toLetter(card[0]), newGame.toNumber(card[1])));
	newGame.printBoard();

	while ((cout << "Please pick a second card on board: " && !(cin >> card))
			|| !(newGame.isValidInput(card))) {
		cout << "Invalid input; please re-enter.\n";
	}
	newGame.setCurrentCard(
			newGame.getCard(newGame.toLetter(card[0]), newGame.toNumber(card[1])));
	newGame.printBoard();

	cout << "The current card is " << *newGame.getCurrentCard() << endl;
	cout << "The previous card is " << *newGame.getPreviousCard() << endl;

	cout << "\nThe overloaded insertion operator prints as follows: \n\n" << newGame << endl;

	//	Card* getCard(const Letter&, const Number&);
	//Already tested in Board
	//	void setCard(const Letter&, const Number&, Card*);
	//Already tested in Board

	cout << "--------------END GAME_TEST_--------------" << endl;
}

#endif
