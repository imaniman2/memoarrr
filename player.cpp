#include "player.h"

Player::Player() {
	d_name = "";
	d_rubyPoints = 0;
	d_isActive = false;
	d_side = Side::top; //Top by default
	d_displayMode = 0;
}

Player::Player(Side side, string name, bool isActive) {
	d_side = side;
	d_name = name;
	d_rubyPoints = 0;
	d_isActive = isActive;
	d_displayMode = 0;
}

string Player::getName() const {
	return d_name;
}
Side Player::getSide() const {
	return d_side;
}
void Player::setSide(Side side) {
	d_side = side;
}
void Player::setActive(bool isActive) {
	d_isActive = isActive;
}
const bool Player::isActive() const {
	return d_isActive;
}
int Player::getNRubies() const {
	return d_rubyPoints;
}
void Player::setNRubies(int reward) {
	d_rubyPoints = reward;
}
void Player::addReward(const Reward& reward) {
	d_rubyPoints += reward.getRubies();
}
void Player::setDisplayMode(bool endOfGame) {
	if (endOfGame) {
		d_displayMode = 1;
	}

}

ostream& operator<<(ostream& o, const Player& player) {
	string side;
	switch (player.d_side) {
	case Side::left:
		side = "left";
		break;
	case Side::right:
		side = "right";
		break;
	case Side::top:
		;
		side = "top";
		break;
	case Side::bottom:
		side = "bottom";
		break;
	}

	o << player.d_name << ": ";

	if (player.d_displayMode == 0) {
		o << side;
		player.d_isActive ? o << " (active)" : o << " (inactive)";
	}
	//Joe Remember Doe: left (active)

	if (player.d_displayMode == 1) {
		o << player.getNRubies() << " rubies";
	}
	//Joe Remember Doe: 3 rubies

	return o;
}

#if PLAYER_TEST_

int main() {

	cout << "--------------PLAYER_TEST_--------------" << endl;
	Side side = Side::top;
	string name = "Bob";
	Player newPlayer(side, name, false);
	cout << "The name of the player is: " << newPlayer.getName()<< endl;
	cout << "The side (number repersentation) of the player is: " << static_cast<int>(newPlayer.getSide())<< endl;
	cout << "The player is: ";
	newPlayer.isActive()? cout<<"active" <<endl:cout<<"inactive"<< endl;
	newPlayer.setActive(true); //set the status of the player as active or inactive.
	cout << "The player is now: ";
	newPlayer.isActive()? cout<<"active" <<endl:cout<<"inactive"<< endl;
	cout << "The player has: " << newPlayer.getNRubies() <<" rubies"<< endl;
	newPlayer.addReward(Reward(1));//add a reward with a given number of rubies.
	cout << "The player now has: " << newPlayer.getNRubies() <<" rubies"<< endl;
	cout << "The overloaded insertion operator prints as follows: \n" << newPlayer << endl;
	newPlayer.setDisplayMode(true);
	cout << "The overloaded insertion operator prints as follows (at the end of a game): \n" << newPlayer << endl;

	cout << "--------------END PLAYER_TEST_--------------" << endl;

	//void setDisplayMode(bool);

}

#endif

