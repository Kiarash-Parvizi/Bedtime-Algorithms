#pragma once
#include<fstream>

void LoadImage(string path) {
	fstream fileStream;
	fileStream.open(path.c_str());
	if (fileStream.fail()) {
		// file could not be opened
		std::cout << "Err:\n\tFile not found\n";
		exit(0);
	}
	img->buffer = stbi_load(path.c_str(), &img->w, &img->h, &img->bpp, 4);
}
