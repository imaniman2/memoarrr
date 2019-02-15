#ifndef CARD_H_
#define CARD_H_

#define CARD_TEST_ 0

#include <string>
#include <iostream>

using namespace std;

enum class FaceAnimal {
	Crab, Penguin, Octopus, Turtle, Walrus
};
enum class FaceBackground {
	Red, Green, Purple, Blue, Yellow
};

class Card {

	friend class CardDeck;
	static const int nRows = 4;
	static const int nCols = 4;
private:
	string * d_rows;
	FaceAnimal d_animal;
	FaceBackground d_background;
	Card();
	Card(FaceAnimal, FaceBackground);
public:
	int getNRows() const;
	string getRow(int) const;
	string operator()(int);
	FaceAnimal getAnimal() const;
	FaceBackground getBack() const;
	char getAnimalChar(FaceAnimal&) const;
	char getBackChar(FaceBackground&) const;
	const void printCard();
	friend ostream& operator<<(ostream&, const Card&);

	//For access to private functions in CARD_TEST_
#if CARD_TEST_
	friend int main();
#endif
};

#endif /* CARD_H_ */
