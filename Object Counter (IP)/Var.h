
typedef struct Image {
	int w, h, bpp;
	stbi_uc* buffer; int len;
} Pixel;

Image* img; uc* mainBuffer; int objCount = 0;

//-----------------------------------------------------

stbi_uc* finalBuffer;

void Start_Var() {
	img->len = img->w * img->h * 4;
	finalBuffer = copyBuffer(img->buffer, img->len);
	mainBuffer = img->buffer;
}

//-----------------------------------------------------

string imageLocation;

//-----------------------------------------------------