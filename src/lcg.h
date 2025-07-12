#ifndef AHI_LCG_H
#define AHI_LCG_H

struct LCG {
	constexpr LCG() : seed{} {}
	constexpr void Init(std::size_t s) {
		LCG &self = *this;

		self.seed = s;
	}
	constexpr size_t operator()() {
		seed = seed * 7 + 3;
		return seed;
	}
private:
	std::size_t seed;
};

#endif
