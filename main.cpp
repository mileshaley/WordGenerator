#include "weighted_array.h"
#include <iostream>
#include <string>
#include <fstream>

int main() {

	std::ifstream in("data/vowel.json");
	json vjs = json::parse(in);
	weighted_array<std::string> vowels = vjs;

	
	//goant.push_back("helno", 3);
	//goant.push_back("tingo", 1.5f);
	//goant.push_back("pung", 0.783f);
	//goant.push_back("pinds", 8);


	float total = vowels.total_weight();
	for (float i = 0; i < total; i += 0.1f)
	std::cout << i << "/" << total << ": " << vowels[i] << std::endl;

	return 0;
}