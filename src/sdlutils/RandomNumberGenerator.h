#ifndef RANDOM_NUMBER_GENERATOR_H_
#define RANDOM_NUMBER_GENERATOR_H_

#include <cassert>
#include <ctime>
#include <random>

class RandomNumberGenerator {
public:
	RandomNumberGenerator() :
		RandomNumberGenerator(static_cast<unsigned int>(std::time(0))) {
	}

	RandomNumberGenerator(unsigned seed) :
			gen_(seed), dist_() {
	}

	virtual ~RandomNumberGenerator() {
	}

	inline int nextInt() {
		return dist_(gen_);
	}

	// return an integer between low (inclusive) and high (exclusive)
	inline int nextInt(int low, int high) {
		assert(low < high);
		return low + (nextInt() % (high - low));
	}

private:

	std::mt19937 gen_;
	std::uniform_int_distribution<int> dist_;
};
#endif