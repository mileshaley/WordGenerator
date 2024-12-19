#include "weighted_array.h"
#include <iostream>
#include <string>
#include <fstream>
#include <random>

// Need start, middle, and end consonants

int main() {
	std::random_device rd{};
	std::mt19937 gen{ rd() };
	std::ifstream v_in("data/vowel.json");
	std::ifstream c_in("data/consonant.json");
	weighted_array<std::string, double> vowels = json::parse(v_in);
	weighted_array<std::string, double> consonants = json::parse(c_in);
	v_in.close();
	c_in.close();

	std::uniform_real_distribution<> vowel_distr(0, vowels.total_weight());
	std::uniform_real_distribution<> consonant_distr(0, consonants.total_weight());
	std::uniform_int_distribution<> coin_flip_distr(0, 2);
	std::normal_distribution<> word_length_distr(6.5, 1.0);

	const int num_words = 30;

	for (int i = 0; i < num_words; ++i) {
		const int parity_offset = coin_flip_distr(gen);
		const int upper_bound = std::round(word_length_distr(gen)) + parity_offset;
		for (int j = parity_offset; j < upper_bound; ++j) {
			if (j % 2 == 0) {
				std::cout << vowels[vowel_distr(gen)];
			} else {
				std::cout << consonants[consonant_distr(gen)];
			}
		}
		std::cout << std::endl;
	}


	//float total = vowels.total_weight();
	//for (float i = 0; i < total; i += 0.1f)
	//std::cout << i << "/" << total << ": " << vowels[i] << std::endl;

	return 0;
}