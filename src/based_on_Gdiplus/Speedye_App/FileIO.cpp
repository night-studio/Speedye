#include "FileIO.h"

extern unsigned int ShowWidth;
extern unsigned int ShowHeight;

bool ReadParameters() {
	std::ifstream file;
	file.open("PARAMETERS.prmt");
	if (!file.is_open()) return false;
	else {
		if (file.good()) {

		}
	}
	return true;
}