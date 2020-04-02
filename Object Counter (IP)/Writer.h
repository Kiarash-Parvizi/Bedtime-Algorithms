#pragma once

void WriteImage(const char* path) {
	stbi_write_png(path, img->w, img->h, 4, finalBuffer, 0);
}
