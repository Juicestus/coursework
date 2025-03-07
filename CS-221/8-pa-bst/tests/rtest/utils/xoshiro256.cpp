/*
	Xoshiro PRNG - not cryptographically sound
	
	Based on a C implmentation of xoshiro256++ written in 2019 by David Blackman and Sebastiano Vigna (vigna@acm.org)

	Adapted for inclusion in CPP programs by Alex <flu0r1ne at flu0r1ne dot net>. Modified to use splitmix to seed 
	with a single uint64_t.
*/

#include "xoshiro256.h"

static inline uint64_t splitmix64(uint64_t & x) {
	uint64_t z = (x += UINT64_C(0x9E3779B97F4A7C15));
	z = (z ^ (z >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
	z = (z ^ (z >> 27)) * UINT64_C(0x94D049BB133111EB);
	return z ^ (z >> 31);
}

static inline uint64_t rotl(const uint64_t x, int k) {
	return (x << k) | (x >> (64 - k));
}

xoshiro256::xoshiro256(uint64_t seed) {
	this->seed(seed);
}

xoshiro256::xoshiro256(uint64_t seed[4]) {
	this->seed(seed);
}

void xoshiro256::seed(uint64_t seed) {
	s[0] = splitmix64(seed);
	s[1] = splitmix64(seed);
	s[2] = splitmix64(seed);
	s[3] = splitmix64(seed);
}

void xoshiro256::seed(uint64_t seed[4]) {
	s[0] = seed[0];
	s[1] = seed[1];
	s[2] = seed[2];
	s[3] = seed[3];
}

uint64_t xoshiro256::next() {
	const uint64_t result = rotl(s[0] + s[3], 23) + s[0];

	const uint64_t t = s[1] << 17;

	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];

	s[2] ^= t;

	s[3] = rotl(s[3], 45);

	return result;
}

uint64_t xoshiro256::operator()() {
	return next();
}

void xoshiro256::jump() {
	static const uint64_t JUMP[] = { 0x180ec6d33cfd0aba, 0xd5a61266f0c9392c, 0xa9582618e03fc9aa, 0x39abdc4529b1661c };

	uint64_t s0 = 0;
	uint64_t s1 = 0;
	uint64_t s2 = 0;
	uint64_t s3 = 0;
	for(int i = 0; i < (int)(sizeof JUMP / sizeof *JUMP); i++)
		for(int b = 0; b < 64; b++) {
			if (JUMP[i] & UINT64_C(1) << b) {
				s0 ^= s[0];
				s1 ^= s[1];
				s2 ^= s[2];
				s3 ^= s[3];
			}
			next();	
		}
		
	s[0] = s0;
	s[1] = s1;
	s[2] = s2;
	s[3] = s3;
}

void xoshiro256::long_jump() {
	static const uint64_t LONG_JUMP[] = { 0x76e15d3efefdcbbf, 0xc5004e441c522fb3, 0x77710069854ee241, 0x39109bb02acbe635 };

	uint64_t s0 = 0;
	uint64_t s1 = 0;
	uint64_t s2 = 0;
	uint64_t s3 = 0;
	for(int i = 0; i < (int)(sizeof LONG_JUMP / sizeof *LONG_JUMP); i++)
		for(int b = 0; b < 64; b++) {
			if (LONG_JUMP[i] & UINT64_C(1) << b) {
				s0 ^= s[0];
				s1 ^= s[1];
				s2 ^= s[2];
				s3 ^= s[3];
			}
			next();	
		}
		
	s[0] = s0;
	s[1] = s1;
	s[2] = s2;
	s[3] = s3;
}