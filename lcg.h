#ifndef AHI_LCG_H
#define AHI_LCG_H

struct LCG {
	constexpr LCG(size_t s) : seed{s} {}
	constexpr size_t operator()() {
		seed = seed * 7 + 3;
		return seed;
	}
private:
	size_t seed;
};

#endif
