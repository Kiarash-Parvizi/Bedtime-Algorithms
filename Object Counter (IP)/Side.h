#define uc unsigned char

string err_message = "-----------------------------ERR:\nYour system memory is full, please close some applications and try again\n-----------------------------\n";

stbi_uc* copyBuffer(stbi_uc* buffer, int len) {
	stbi_uc* newBuffer = (stbi_uc*)malloc(len);
	if (malloc == NULL) {
		cout << err_message; exit(1);
	}
	for (len--; len-1; len--) {
		newBuffer[len] = buffer[len];
	}
	return newBuffer;
}

