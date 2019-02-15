#define MAIN_IMPLEM_ 1

#if MAIN_IMPLEM_

#include <iostream>
#include <vector>
using namespace std;

#include "rules.h"
#include "rewarddeck.h"

int main() {

	int gameMode = 0;
	int displayMode = 0;
	int playerNum = 0;
	vector<string> names;

	while ((cout << "Choose Game Mode (1 for Regular, 2 for Expert) : "
			&& !(cin >> gameMode)) || (gameMode != 1 && gameMode != 2)) {
		cin.clear(); //clear bad input flag
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
		cout << "Invalid input; please re-enter.\n";
	}
	while ((cout << "Choose Display Mode (1 for Regular, 2 for Expert) : "
			&& !(cin >> displayMode)) || (displayMode != 1 && displayMode != 2)) {
		cin.clear(); //clear bad input flag
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
		cout << "Invalid input; please re-enter.\n";
	}

	while ((cout << "Choose the number of players (2-4 Players) : "
			&& !(cin >> playerNum))
			|| (playerNum != 2 && playerNum != 3 && playerNum != 4)) {
		cin.clear(); //clear bad input flag
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
		cout << "Invalid input; please re-enter.\n";
	}
	for (int i = 0; i < playerNum; i++) {
		string temp;
		cout << "Enter name of Player " << (i + 1) << ": ";
		cin >> temp;
		names.push_back(temp);
	}

	Game game(displayMode);
	Rules rules(gameMode);
	RewardDeck &reward = RewardDeck::make_RewardDeck();
	reward.shuffle();

	for (int i = 0; i < playerNum; i++) {
		game.addPlayer(Player(static_cast<Side>(i), names.at(i), false));
	}

	cout << game;

	//Temporarily reveal 3 cards directly in front of the player

	for (int i = 0; i < playerNum; i++) { //update status of all players in game as active

		//Temporarily reveal 3 cards directly in front of the player
		Side thisSide = static_cast<Side>(i);
		Card** tempCardReveal = new Card*[3];
		if (thisSide == Side::left) {
			tempCardReveal[0] = game.getCard(Letter::B, Number::One);
			tempCardReveal[1] = game.getCard(Letter::C, Number::One);
			tempCardReveal[2] = game.getCard(Letter::D, Number::One);
		}
		if (thisSide == Side::right) {
			tempCardReveal[0] = game.getCard(Letter::B, Number::Five);
			tempCardReveal[1] = game.getCard(Letter::C, Number::Five);
			tempCardReveal[2] = game.getCard(Letter::D, Number::Five);
		}
		if (thisSide == Side::top) {
			tempCardReveal[0] = game.getCard(Letter::A, Number::Two);
			tempCardReveal[1] = game.getCard(Letter::A, Number::Three);
			tempCardReveal[2] = game.getCard(Letter::A, Number::Four);
		}
		if (thisSide == Side::bottom) {
			tempCardReveal[0] = game.getCard(Letter::E, Number::Two);
			tempCardReveal[1] = game.getCard(Letter::E, Number::Three);
			tempCardReveal[2] = game.getCard(Letter::E, Number::Four);
		}
		cout << "The temporary card reveal for "
				<< game.getPlayer(thisSide).getName() << " is:" << endl;
		for (int i = 0; i < 4; i++) {
			cout
					<< tempCardReveal[0]->getRow(i)
							+ tempCardReveal[1]->getRow(i)
							+ tempCardReveal[2]->getRow(i) << endl;
		}
	}
	cout << "-------------------------" << endl;
	while (!rules.gameOver(game)) {
		//resets board, increments round
		game.nextRound();

		//sets all players as active
		for (int i = 0; i < game.getPlayerNum(); i++) {
			Player updatePlayer = game.getPlayer(static_cast<Side>(i));
			updatePlayer.setActive(true);
			game.addPlayer(updatePlayer);
		}

		while (!rules.roundOver(game)) {		//while Rules.roundOver is false
			Player playersTurn = rules.getNextPlayer(game); //next active player takes turn
			//get selection of card to turn face up from active player

			string card;

			while ((cout << playersTurn.getName() << ", please pick a card: "
					&& !(cin >> card)) || !(game.isValidInput(card))) {
				cout << "Invalid input; please re-enter.\n";
			}

			//update board in game

			game.setCurrentCard(
					game.getCard(game.toLetter(card[0]),
							game.toNumber(card[1])));

			if (!rules.isValid(game)) {			//if Rules.isValid is false
				//player is no longer part of current round
				//current player becomes inactive
				cout << playersTurn.getName() << " is out." << endl;
				playersTurn.setActive(false);
				game.addPlayer(playersTurn);

			}
			//display game
			game.printBoard();

		}
		//Remaining active player receives reward (rubies)
		Player whoWonLastRound = rules.getNextPlayer(game);
		Reward wonreward = *(reward.getNext());
		whoWonLastRound.addReward(wonreward);
		game.addPlayer(whoWonLastRound);
		cout << "Player " << whoWonLastRound.getName() << " won last round."
				<< endl;
		cout << "Player " << whoWonLastRound.getName() << " gets "
				<< wonreward.getRubies() << " rubies." << endl;
	}
	cout << "-------------------------" << endl;

	cout << "End of game." << endl;
	//print players with their number of rubies sorted from least to most rubies
	cout << "-------------------------" << endl;

	//first remove players from game to an array
	Player* playersAfterGame = new Player[playerNum];
	for (int i = 0; i < playerNum; i++) {
		playersAfterGame[i] = game.getPlayer(static_cast<Side>(i));
		playersAfterGame[i].setDisplayMode(true);

	}

	//secondly sort players least to most rubies (bubblesort)
	for (int i = 0; i < playerNum; i++) {
		for (int j = i + 1; j < playerNum; j++) {
			if (playersAfterGame[i].getNRubies()
					> playersAfterGame[j].getNRubies()) {
				Player tmp = playersAfterGame[i];
				playersAfterGame[i] = playersAfterGame[j];
				playersAfterGame[j] = tmp;
			}
		}
	}

	//lastly, print
	for (int i = 0; i < playerNum; i++) {
		cout << "Player " << playersAfterGame[i].getName() << " has "
				<< playersAfterGame[i].getNRubies() << " rubies." << endl;
	}

	//print overall winner
	if (playersAfterGame[playerNum - 2].getNRubies()
			== playersAfterGame[playerNum - 1].getNRubies()) {
		cout << "-------------------------" << endl;
		cout << "There is a tie between "
				<< playersAfterGame[playerNum - 2].getName() << " and "
				<< playersAfterGame[playerNum - 1].getName() << endl;
		cout << "-------------------------" << endl;
	} else {
		cout << "-------------------------" << endl;
		cout << "The winner is " << playersAfterGame[playerNum - 1].getName()
				<< endl;
		cout << "-------------------------" << endl;
	}

	delete[] playersAfterGame;

	return 0;

}

#endif
