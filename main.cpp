#include "weighted_array.h"
#include <iostream>
#include <string>

int main() {
	weighted_array<std::string> goant;

	goant.push_back("helno", 3);
	goant.push_back("tingo", 1.5f);
	goant.push_back("pung", 0.783f);
	goant.push_back("pinds", 8);
	float total = goant.total_weight();
	for (float i = 0; i < total; i += 0.1f)
	std::cout << i << "/" << total << ": " << goant[i] << std::endl;

	return 0;
}