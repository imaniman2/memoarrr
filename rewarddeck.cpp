#include "rewarddeck.h"

#if REWARDDECK_TEST_

int main() {

	cout << "--------------REWARDDECK_TEST_--------------" << endl;

	RewardDeck &reward = RewardDeck::make_RewardDeck();

	cout << "The unshuffled deck of rewards is as follows: \n";
	for (unsigned i = 0; i < RewardDeck::myDeck.size(); i++) {
		cout << reward.myDeck.at(i) << endl;
	}
	cout << endl;
	reward.shuffle();

	cout << "The shuffled deck of cards is as follows: \n";
	for (unsigned i = 0; i < RewardDeck::myDeck.size(); i++) {
		cout << reward.myDeck.at(i) << endl;
	}
	cout << endl;
	cout << "The deck is ";
	reward.isEmpty() ? cout << "empty" << endl : cout << "not empty" << endl;
	cout << endl;

	cout << "The game needs 7 rewards..." << endl;
	for (unsigned i = 0; i < 7; i++) {
		cout << *reward.getNext() << " pulled from deck at round " << i+1 << endl;
	}
	cout << endl;

	cout << "The deck is ";
	reward.isEmpty() ? cout << "empty" << endl : cout << "not empty" << endl;

	cout << "--------------END REWARDDECK_TEST_--------------" << endl;

}
#endif

