#ifndef CARDDECK_H_
#define CARDDECK_H_

#define CARDDECK_TEST_ 0

#include "deck.h"

class CardDeck: public Deck<Card> {
private:
	CardDeck() {
		myDeck.push_back(Card(FaceAnimal::Crab, FaceBackground::Red));
		myDeck.push_back(Card(FaceAnimal::Crab, FaceBackground::Green));
		myDeck.push_back(Card(FaceAnimal::Crab, FaceBackground::Purple));
		myDeck.push_back(Card(FaceAnimal::Crab, FaceBackground::Blue));
		myDeck.push_back(Card(FaceAnimal::Crab, FaceBackground::Yellow));
		myDeck.push_back(Card(FaceAnimal::Penguin, FaceBackground::Red));
		myDeck.push_back(Card(FaceAnimal::Penguin, FaceBackground::Green));
		myDeck.push_back(Card(FaceAnimal::Penguin, FaceBackground::Purple));
		myDeck.push_back(Card(FaceAnimal::Penguin, FaceBackground::Blue));
		myDeck.push_back(Card(FaceAnimal::Penguin, FaceBackground::Yellow));
		myDeck.push_back(Card(FaceAnimal::Octopus, FaceBackground::Red));
		myDeck.push_back(Card(FaceAnimal::Octopus, FaceBackground::Green));
		myDeck.push_back(Card(FaceAnimal::Octopus, FaceBackground::Purple));
		myDeck.push_back(Card(FaceAnimal::Octopus, FaceBackground::Blue));
		myDeck.push_back(Card(FaceAnimal::Octopus, FaceBackground::Yellow));
		myDeck.push_back(Card(FaceAnimal::Turtle, FaceBackground::Red));
		myDeck.push_back(Card(FaceAnimal::Turtle, FaceBackground::Green));
		myDeck.push_back(Card(FaceAnimal::Turtle, FaceBackground::Purple));
		myDeck.push_back(Card(FaceAnimal::Turtle, FaceBackground::Blue));
		myDeck.push_back(Card(FaceAnimal::Turtle, FaceBackground::Yellow));
		myDeck.push_back(Card(FaceAnimal::Walrus, FaceBackground::Red));
		myDeck.push_back(Card(FaceAnimal::Walrus, FaceBackground::Green));
		myDeck.push_back(Card(FaceAnimal::Walrus, FaceBackground::Purple));
		myDeck.push_back(Card(FaceAnimal::Walrus, FaceBackground::Blue));
		myDeck.push_back(Card(FaceAnimal::Walrus, FaceBackground::Yellow));

		ptr = &(myDeck.back());
	}
	~CardDeck() {
		myDeck.clear();
		delete ptr;
	}
public:
	void shuffle() {
		Deck::shuffle();
	}
	static CardDeck& make_CardDeck() {

		CardDeck *cardDeckPtr = nullptr;

		if (ptr == nullptr) {
			cardDeckPtr = new CardDeck();
		}

		return *cardDeckPtr;
	}

};

#endif /* CARDDECK_H_ */
