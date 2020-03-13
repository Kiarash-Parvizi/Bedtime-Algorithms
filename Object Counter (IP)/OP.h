// OP

uc getPixelAVG(int loc) {
	uc* buff = &mainBuffer[loc];
	return (buff[0] + buff[1] + buff[2]) / 3;
}


void removePixel(int loc) {
	uc* buff = &mainBuffer[loc];
	buff[0] = 0;  buff[1] = 0; buff[2] = 0;
}


//--------------------------------------------


