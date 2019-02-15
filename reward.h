#ifndef REWARD_H_
#define REWARD_H_

#define REWARD_TEST_ 0

#include <iostream>
#include <string>
#include <exception>

using namespace std;

class Reward {
	friend class RewardDeck;
private:
	int d_rubies;
	Reward();
	Reward(int);
public:
	int getRubies() const;
	friend ostream& operator<<(ostream&, const Reward&);

	//For access to the reward constructor in PLAYER_TEST_
#if (REWARD_TEST_ || PLAYER_TEST_)
	friend int main();
#endif
};

#endif /* REWARD_H_ */
