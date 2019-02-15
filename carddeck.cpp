#include "carddeck.h"

#if CARDDECK_TEST_

int main() {

	cout << "--------------CARDDECK_TEST_--------------" << endl;

	CardDeck &carddeck = CardDeck::make_CardDeck();
	cout << "The unshuffled deck of cards is as follows: \n";
	for (unsigned i = 0; i < CardDeck::myDeck.size(); i++) {
		cout << carddeck.myDeck.at(i) << endl;
	}
	cout << endl;
	carddeck.shuffle();

	cout << "The shuffled deck of cards is as follows: \n";
	for (unsigned i = 0; i < CardDeck::myDeck.size(); i++) {
		cout << carddeck.myDeck.at(i) << endl;
	}
	cout << endl;
	cout << "The board takes 24 cards to fill the table..." << endl;
	for (unsigned i = 0; i < 24; i++) {
		cout << *(carddeck.getNext()) << " pulled from deck" << endl;
	}
	cout << endl;
	cout << "The remaining card is: " << endl;
	for (unsigned i = 0; i < CardDeck::myDeck.size(); i++) {
		cout << carddeck.myDeck.at(i) << endl;
	}

	cout << "The deck is ";
	carddeck.isEmpty() ? cout << "empty" << endl : cout << "not empty" << endl;

	cout << "Removing last card... " << endl;
	cout << *(carddeck.getNext()) << " pulled from deck" << endl;

	cout << "The deck is ";
	carddeck.isEmpty() ? cout << "empty" << endl : cout << "not empty" << endl;

	cout << "--------------END CARDDECK_TEST_--------------" << endl;

}

#endif

