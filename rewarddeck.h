#ifndef REWARDDECK_H_
#define REWARDDECK_H_

#define REWARDDECK_TEST_ 0

#include "deck.h"

class RewardDeck: public Deck<Reward> {
private:
	RewardDeck() {
		myDeck.push_back(Reward(1));
		myDeck.push_back(Reward(1));
		myDeck.push_back(Reward(1));
		myDeck.push_back(Reward(2));
		myDeck.push_back(Reward(2));
		myDeck.push_back(Reward(3));
		myDeck.push_back(Reward(4));

		ptr = &(myDeck.back());
	}
	~RewardDeck() {
		myDeck.clear();
		delete ptr;
	}
public:
	void shuffle() {
		Deck::shuffle();
	}
	static RewardDeck& make_RewardDeck() {

		RewardDeck *rewardDeckPtr = nullptr;

		if (ptr == nullptr) {
			rewardDeckPtr = new RewardDeck();
		}

		return *rewardDeckPtr;

	}

};

#endif /* REWARDDECK_H_ */
