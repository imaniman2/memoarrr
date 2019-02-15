#include "rules.h"

Rules::Rules(int gameMode) :
		d_gameMode(gameMode) {
}

//Returns true if previous and current card math; false otherwise

bool Rules::isValid(Game& game) {
	if (d_gameMode == 2) {
		const Card* previous = game.getPreviousCard();
		const Card* current = game.getCurrentCard();
		bool result;
		if (previous == nullptr) {
			result = true;
		} else {
			result = (previous->getAnimal() == current->getAnimal())
					|| (previous->getBack() == current->getBack());
		}
		if (block == 1) {
			FaceUpCardsPosition* selectionPosition = game.findPosition(
					current);
			game.setCurrentCard(
					game.getCard(selectionPosition->letter,
							selectionPosition->number));
			cout
					<< "Previous card was a walrus. Therefore, this card is blocked."
					<< endl;
			block = 0;
			string card;
			Player playerPickCard = game.getPlayer(
					static_cast<Side>(currentSide - 1));
			while ((cout << playerPickCard.getName() << ", please pick a card: "
					&& !(cin >> card)) || !(game.isValidInput(card))) {
				cout << "Invalid input; please re-enter.\n";
			}
			game.setCurrentCard(
					game.getCard(game.toLetter(card[0]),
							game.toNumber(card[1])));
			current = game.getCurrentCard();
			result = (previous->getAnimal() == current->getAnimal())
					|| (previous->getBack() == current->getBack());
		}

		if (result) {
			if (current->getAnimal() == FaceAnimal::Octopus) {
				//When an octopus card is turned over, the card is exchanging position with an adjacent card in the same row or the same column (4-neighbourhood).
				//The adjacent card may be face up or down and will remain unchanged
				cout
						<< "The card is a octopus! Pick an adjacent card to switch cards with."
						<< endl;
				string card;
				Player playerPickCard = game.getPlayer(
						static_cast<Side>(currentSide - 1));
				while ((cout << playerPickCard.getName()
						<< ", please pick a card: " && !(cin >> card))
						|| !(game.isValidInput(card))) {
					cout << "Invalid input; please re-enter.\n";
				}
				Letter letterAdjacent = game.toLetter(card[0]);
				Number numberAdjacent = game.toNumber(card[1]);
				FaceUpCardsPosition* currentPosition = game.findPosition(
						current);
				while (!(((static_cast<int>(letterAdjacent)
						- static_cast<int>(currentPosition->letter) > -2)
						&& (static_cast<int>(letterAdjacent)
								- static_cast<int>(currentPosition->letter) < 2))
						&& (static_cast<int>(numberAdjacent)
								- static_cast<int>(currentPosition->number) == 0))
						&& !(((static_cast<int>(numberAdjacent)
								- static_cast<int>(currentPosition->number) > -2)
								&& (static_cast<int>(numberAdjacent)
										- static_cast<int>(currentPosition->number)
										< 2))
								&& (static_cast<int>(letterAdjacent)
										- static_cast<int>(currentPosition->letter)
										== 0))) {
					cout
							<< "This card is not a neighbour, please pick another card."
							<< endl;
					while ((cout << playerPickCard.getName()
							<< ", please pick a card: " && !(cin >> card))
							|| !(game.isValidInput(card))) {
						cout << "Invalid input; please re-enter.\n";
					}
					letterAdjacent = game.toLetter(card[0]);
					numberAdjacent = game.toNumber(card[1]);
				}
				this->modifyGameOctupus(game, letterAdjacent, numberAdjacent,
						currentPosition->letter, currentPosition->number);
			}
			if (current->getAnimal() == FaceAnimal::Penguin) {
				//If a player turns over a penguin, then this player is allowed to turn a face-up card face-down.
				//If the penguin is the first card turned up, no special action will take place
				if (previous == nullptr) {
					cout
							<< "The card is a penguin! However, this is the first card, so no special actions take place."
							<< endl;
				} else {
					cout
							<< "The card is a penguin! Pick a face-up card to turn to face-down."
							<< endl;
					string card;
					Player playerPickCard = game.getPlayer(
							static_cast<Side>(currentSide - 1));
					while ((cout << playerPickCard.getName()
							<< ", please pick a card: " && !(cin >> card))
							|| !(game.isFaceUp(game.toLetter(card[0]),
									game.toNumber(card[1])))) {
						cout
								<< "That card is face down. Please pick another card."
								<< endl;
					}
					Letter letter = game.toLetter(card[0]);
					Number number = game.toNumber(card[1]);
					this->modifyGamePengiun(game, letter, number);
				}
			}
			if (current->getAnimal() == FaceAnimal::Walrus) {
				//The walrus enables a player to block a face down card for the next player and hence the next player must choose another location
				cout << "The card is a walrus!" << endl;
				block = 1;
			}
			if (current->getAnimal() == FaceAnimal::Crab) {
				//The player who turns over a crab card must immediately turn over another card.
				//If that card does not fit, the player loses the current round
				cout << "The card is a crab! Please pick another card." << endl;
				string card;
				Player playerPickCard = game.getPlayer(
						static_cast<Side>(currentSide - 1));
				while ((cout << playerPickCard.getName()
						<< ", please pick a card: " && !(cin >> card))
						|| !(game.isValidInput(card))) {
					cout << "Invalid input; please re-enter.\n";
				}
				this->modifyGameCrab(game, card, playerPickCard);
			}
			if (current->getAnimal() == FaceAnimal::Turtle) {
				//Finally, with the turtle the next player in the current round is skipped, i.e., the next player will not turn over a card and will not lose in the next step.
				Player skipPlayer = this->getNextPlayer(game);
				cout << "The card is a turtle! Player " << skipPlayer.getName()
						<< " loses next turn." << endl;
			}
		}
		return result;
	} else {
		const Card* previous = game.getPreviousCard();
		const Card* current = game.getCurrentCard();
		bool result;
		if (previous == nullptr) {
			result = true;
		} else {
			result = (previous->getAnimal() == current->getAnimal())
					|| (previous->getBack() == current->getBack());
		}
		return result;
	}
}

//Returns true if number of rounds has reached 7
bool Rules::gameOver(const Game& game) const {
	return (game.getRound() == 7) && roundOver(game);
}

//Returns true if there is only on active player left
bool Rules::roundOver(const Game& game) const {
	int numOfActivePlayers = 0;
	for (int i = 0; i < game.getPlayerNum(); i++) {
		if (game.getPlayer(static_cast<Side>(i)).isActive()) {
			numOfActivePlayers++;
		}
	}

	return (numOfActivePlayers == 1);

}

//Returns next player in game
//As in next active player
const Player& Rules::getNextPlayer(const Game& game) {
	if (currentSide == game.getPlayerNum()) {
		currentSide = 0;
	}
	while (!game.getPlayer(static_cast<Side>(currentSide)).isActive()) {
		currentSide++;
		if (currentSide == game.getPlayerNum()) {
			currentSide = 0;
		}
	}
	return game.getPlayer(static_cast<Side>(currentSide++));
}

void Rules::modifyGameCrab(Game& game, string& card, Player& playerPickCard) {
	//update board in game
	game.setCurrentCard(
			game.getCard(game.toLetter(card[0]), game.toNumber(card[1])));
	if (!(this->isValid(game))) {			//if Rules.isValid is false
		//player is no longer part of current round
		//current player becomes inactive
		game.turnFaceUp(game.toLetter(card[0]), game.toNumber(card[1]));

		cout << playerPickCard.getName() << " is out." << endl;
		playerPickCard.setActive(false);
		game.addPlayer(playerPickCard);
	}

}
void Rules::modifyGamePengiun(Game& game, Letter& letter,
		Number& number) const {
	game.turnFaceDown(letter, number);
}

void Rules::modifyGameOctupus(Game& game, Letter& letterA, Number& numberA,
		Letter& letterB, Number& numberB) {
	Card* cardA = game.getCard(letterA, numberA);
	Card* cardB = game.getCard(letterB, numberB);
	game.setCard(letterA, numberA, cardB);
	game.setCard(letterB, numberB, cardA);
	if (!game.isFaceUp(letterB, numberB)) {
		game.turnFaceUp(letterA, numberA);
		game.turnFaceUp(letterB, numberB);
	} else if (game.isFaceUp(letterB, numberB)) {
		game.turnFaceDown(letterA, numberA);
		game.turnFaceUp(letterB, numberB);
	}
}

#if RULES_TEST_

int main() {
	cout << "--------------RULES_TEST_--------------" << endl;

	//Default display mode
	Game newGame(1);
	int gameMode = 0;
	vector<string> names;
	int playerNum = 0;

	while ((cout << "Choose Game Mode (1 for Regular, 2 for Expert) : "
					&& !(cin >> gameMode)) || (gameMode != 1 && gameMode != 2)) {
		cin.clear(); //clear bad input flag
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//discard input
		cout << "Invalid input; please re-enter.\n";
	}
	while ((cout << "Choose the number of players (2-4 Players) : "
					&& !(cin >> playerNum))
			|| (playerNum != 2 && playerNum != 3 && playerNum != 4)) {
		cin.clear(); //clear bad input flag
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//discard input
		cout << "Invalid input; please re-enter.\n";
	}
	for (int i = 0; i < playerNum; i++) {
		string temp;
		cout << "Enter name of Player " << (i + 1) << ": ";
		cin >> temp;
		names.push_back(temp);
	}

	Rules newRules(gameMode);

	for (int i = 0; i < playerNum; i++) {
		newGame.addPlayer(Player(static_cast<Side>(i), names.at(i), false));
	}

	cout << newGame;
	while (!newRules.gameOver(newGame)) {
		//resets board, increments round
		newGame.nextRound();

		//sets all players as active
		for (int i = 0; i < newGame.getPlayerNum(); i++) {
			Player updatePlayer = newGame.getPlayer(static_cast<Side>(i));
			updatePlayer.setActive(true);
			newGame.addPlayer(updatePlayer);
		}

		while (!newRules.roundOver(newGame)) {	//while Rules.roundOver is false
			Player playersTurn = newRules.getNextPlayer(newGame);//next active player takes turn
			//get selection of card to turn face up from active player

			string card;

			while ((cout << playersTurn.getName() << ", please pick a card: "
							&& !(cin >> card)) || !(newGame.isValidInput(card))) {
				cout << "Invalid input; please re-enter.\n";
			}

			//update board in game

			newGame.setCurrentCard(
					newGame.getCard(newGame.toLetter(card[0]),
							newGame.toNumber(card[1])));

			if (!newRules.isValid(newGame)) {	//if Rules.isValid is false
				//player is no longer part of current round
				//current player becomes inactive
				cout << playersTurn.getName() << " is out." << endl;
				playersTurn.setActive(false);
				newGame.addPlayer(playersTurn);

			}
			//display game
			newGame.printBoard();

		}
		//Remaining active player receives reward (rubies)
		Player whoWonLastRound = newRules.getNextPlayer(newGame);

	}
	cout << "/n Someone won. /n";

	cout << "-------------------------" << endl;

	cout << "End of game." << endl;
	//print players with their number of rubies sorted from least to most rubies
	cout << "-------------------------" << endl;

	cout << "\n--------------END RULES_TEST_--------------" << endl;

}

#endif
