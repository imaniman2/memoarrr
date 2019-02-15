#ifndef DECK_H_
#define DECK_H_

#include <vector>
#include <algorithm>
#include "card.h"
#include "reward.h"

using namespace std;

template<class C>

//Factory pattern

class Deck {

protected:
	static vector<C> myDeck;
	static C* ptr;
	virtual ~Deck() {
		myDeck.clear();
		delete ptr;
	}
public:
	virtual void shuffle() = 0;
	C* getNext();
	bool isEmpty();

	//For access to the deck constructor in CARDDECK_TEST_ or REWARDDECK_TEST_
#if (CARDDECK_TEST_ || REWARDDECK_TEST_ || BOARD_TEST_)
	friend int main();
#endif
};

template<class C>
std::vector<C> Deck<C>::myDeck;
template<class C>
C* Deck<C>::ptr = nullptr;

template<class C>
void Deck<C>::shuffle() {
	random_shuffle(myDeck.begin(), myDeck.end());
}
template<class C>
C* Deck<C>::getNext() {
	if (myDeck.empty()) {
		return nullptr;
	}
	C* curr_ptr = ptr;
	if (ptr != &(myDeck.front())) {
		ptr--;
	}
	myDeck.pop_back();
	if (myDeck.empty()) {
		ptr = nullptr;
	}
	return curr_ptr;
}
template<class C>
bool Deck<C>::isEmpty() {
	return myDeck.empty();
}

#endif /* DECK_H_ */
