#include <string>
#include "card.h"

Card::Card() {
	d_animal = FaceAnimal::Crab;
	d_background = FaceBackground::Blue;

	d_rows = nullptr;
}

Card::Card(FaceAnimal animal, FaceBackground background) {

	d_rows = new string[nRows];

	d_animal = animal;
	d_background = background;

	for (int i = 0; i < nRows; i++) {
		d_rows[i] = "";
		for (int j = 0; j < nCols; j++) {
			if (i == 1 && j == 1) {
				d_rows[i] = d_rows[i] + (getAnimalChar(animal));
			} else if (i < 3 && j < 3) {
				d_rows[i] = d_rows[i] + (getBackChar(background));
			} else {
				d_rows[i] = d_rows[i] + " ";
			}
		}
	}
}

int Card::getNRows() const {
	return nRows;
}

string Card::getRow(int i) const {
	return d_rows[i];
}

string Card::operator()(int i) {
	return d_rows[i];
}

FaceAnimal Card::getAnimal() const {
	return d_animal;
}
FaceBackground Card::getBack() const {
	return d_background;
}

char Card::getAnimalChar(FaceAnimal &animal) const {
	switch (animal) {
	case FaceAnimal::Crab:
		return 'C';
	case FaceAnimal::Penguin:
		return 'P';
	case FaceAnimal::Octopus:
		return 'O';
	case FaceAnimal::Turtle:
		return 'T';
	case FaceAnimal::Walrus:
		return 'W';
	default:
		return '0';
	}
}
char Card::getBackChar(FaceBackground &background) const {
	switch (background) {
	case FaceBackground::Red:
		return 'r';
	case FaceBackground::Green:
		return 'g';
	case FaceBackground::Purple:
		return 'p';
	case FaceBackground::Blue:
		return 'b';
	case FaceBackground::Yellow:
		return 'y';
	default:
		return '0';
	}
}

const void Card::printCard() {
	for (int i = 0; i < this->getNRows(); i++) {
		string rowString = this->getRow(i);
		cout << rowString << endl;
	}
}

ostream& operator<<(ostream& o, const Card& card) {
	//Only overloads with name for now
	o << "[Card animal: ";
	switch (card.d_animal) {
	case FaceAnimal::Crab:
		o << "Crab";
		break;
	case FaceAnimal::Penguin:
		o << "Penguin";
		break;
	case FaceAnimal::Octopus:
		o << "Octopus";
		break;
	case FaceAnimal::Turtle:
		o << "Turtle";
		break;
	case FaceAnimal::Walrus:
		o << "Walrus";
		break;
	default:
		o << "unset";
		break;
	}
	o << ", Card Background: ";
	switch (card.d_background) {
	case FaceBackground::Red:
		o << "Red]";
		break;
	case FaceBackground::Green:
		o << "Green]";
		break;
	case FaceBackground::Purple:
		o << "Purple]";
		break;
	case FaceBackground::Blue:
		o << "Blue]";
		break;
	case FaceBackground::Yellow:
		o << "Yellow]";
		break;
	default:
		o << "unset";
		break;
	}
	return o;
}

#if CARD_TEST_

int main() {

	cout << "--------------CARD_TEST_--------------" << endl;

	Card newCard(FaceAnimal::Crab, FaceBackground::Blue);
	cout << "The new card has " << newCard.getNRows() << " rows" << endl;
	cout << "The first row of the card is: " << newCard(0) << endl; //operator() test
	FaceAnimal ana = newCard.getAnimal();
	FaceBackground back = newCard.getBack();

	cout << "The conversion operators reperersent the Animal as ["
	<< newCard.getAnimalChar(ana) << "] and the background as ["
	<< newCard.getBackChar(back) << "]" <<endl;

	cout << "The card prints as shown: \n" << endl;
	newCard.printCard();
	cout << "The overloaded insertion operator prints as follows: \n" << newCard << endl;

	cout << "--------------END CARD_TEST_--------------" << endl;
}

#endif
