/*
	Xoshiro PRNG - modern, fast, not cryptographically sound
	
	Based on a C implmentation written in 2019 by David Blackman and Sebastiano Vigna (vigna@acm.org)

	Adapted for inclusion in CPP programs by Alex <flu0r1ne at flu0r1ne dot net>. Modified to use splitmix to seed 
	with a single uint64_t.
*/

#include <cstdint>

class xoshiro256 {
	uint64_t s[4];

	protected:
		uint64_t next();

	public:

		xoshiro256(uint64_t seed);
		xoshiro256(uint64_t seed[4]);

		void seed(uint64_t seed);
		void seed(uint64_t seed[4]);

		uint64_t operator()();

		/* This is the jump function for the generator. It is equivalent
		to 2^128 calls to next(); it can be used to generate 2^128
		non-overlapping subsequences for parallel computations. */
		void jump();

		/* This is the long-jump function for the generator. It is equivalent to
		2^192 calls to next(); it can be used to generate 2^64 starting points,
		from each of which jump() will generate 2^64 non-overlapping
		subsequences for parallel distributed computations. */
		void long_jump();
};