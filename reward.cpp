#include "reward.h"
#include <string>

Reward::Reward(int rubies) {
	if (rubies > 0 && rubies < 5) {
		d_rubies = rubies;
	} else {
		throw runtime_error("failed to construct");
	}
}
int Reward::getRubies() const {
	return d_rubies;
}

ostream& operator<<(ostream& o, const Reward& reward) {
	o << "Number of rubies: " << reward.d_rubies;
	return o;
}

#if REWARD_TEST_

int main() {

	cout << "--------------REWARD_TEST_--------------" << endl;

	Reward newReward(2);
	cout << "A Reward with " << newReward.getRubies() << " rubies was created"
	<< endl;
	cout << "The overloaded insertion operator prints as follows: \n"
	<< newReward << endl;
	cout << "--------------END REWARD_TEST_--------------" << endl;
}

#endif
