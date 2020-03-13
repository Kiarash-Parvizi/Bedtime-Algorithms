#include<iostream>
#include<stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include"stb_image.h"
#include"stb_image_write.h"
using namespace std;
#include"Side.h"
#include"Var.h"
#include"OP.h"
#include"Loader.h"
#include"Writer.h"
#include"Process.h"


int main() {
	img = (Image*)malloc(sizeof(Image));
	cout << "Image relative path: "; cin >> imageLocation;
	LoadImage(imageLocation);
	Start_Var();

	Process_Core();

	system("mkdir res");
	WriteImage("res/Pixel.png");
	cout << "Process Finished Successfully\n";
	cout << "------------------------\nobj Count: " << objCount << endl;
}
