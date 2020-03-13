
void LoadImage(string path) {
	img->buffer = stbi_load(path.c_str(), &img->w, &img->h, &img->bpp, 4);
}
