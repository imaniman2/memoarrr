#ifndef PLAYER_H_
#define PLAYER_H_

#define PLAYER_TEST_ 0

using namespace std;
#include <string>
#include <iostream>

#include "reward.h"

enum class Side {
	left, right, top, bottom
};

class Player {

private:
	Side d_side;
	string d_name;
	int d_rubyPoints;
	bool d_isActive;
	int d_displayMode;

public:
	Player();
	Player(Side, string, bool);
	string getName() const;  //return the name of the player.
	Side getSide() const;
	void setSide(Side side);
	void setActive(bool); //set the status of the player as active or inactive.
	const bool isActive() const; //returns true if the player is active.
	int getNRubies() const;  //return the number of rubies won by this player.
	void setNRubies(int reward);
	void addReward(const Reward& reward); //add a reward with a given number of rubies.
	void setDisplayMode(bool);

public:
	friend ostream& operator<<(ostream&, const Player&);

};

#endif /* PLAYER_H_ */
