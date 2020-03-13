void Remove_ThePixel(int loc);


void Process_Core() {
	int rgb_sum, avg; int len = img->w * img->h * 4;
	stbi_uc* buffer = mainBuffer;
	cout << "Buffer-> len: " << img->len << endl;
	for (int x = 0; x < len; x+=4)
	{
		//if (x % 4 == 0) printf("\n");
		//printf("P[%d] : %d\t", x, buffer[x]);
	
		//Algo
		avg = getPixelAVG(x);
		if (avg > 30)
		{
			Remove_ThePixel(x); objCount++;
			if (x + 14 < img->len) {
				finalBuffer[x + 1] = 0;
				finalBuffer[x + 2] = 0;
				finalBuffer[x] = 255;
				finalBuffer[x + 4] = 255;
				finalBuffer[x + 5] = 0;
				finalBuffer[x + 6] = 0;
				finalBuffer[x + 8] = 255;
				finalBuffer[x + 9] = 0;
				finalBuffer[x + 10] = 0;
				finalBuffer[x + 12] = 255;
				finalBuffer[x + 13] = 0;
				finalBuffer[x + 14] = 0;
			}
		}
	
		//----------------------------
	}
}




int tempLoc;
void Remove_ThePixel(int loc) {
	removePixel(loc);
	tempLoc = loc + 4; if (tempLoc < img->len && getPixelAVG(tempLoc) > 30) Remove_ThePixel(tempLoc);
	tempLoc = loc - 4; if (tempLoc > 0 && getPixelAVG(tempLoc) > 30) Remove_ThePixel(tempLoc);
	tempLoc = loc + 4 * img->w; if (tempLoc < img->len && getPixelAVG(tempLoc) > 30) Remove_ThePixel(tempLoc);
	tempLoc = loc - 4 * img->w; if (tempLoc >= 0 && getPixelAVG(tempLoc) > 30) Remove_ThePixel(tempLoc);
}


//Depricated:
// This algorithm might be faster but doesn't work for all cases (and a little buggy...  more than a little :/ )
//void Remove_TheStar(int loc) {
//	int w = img->w; int avg; char firstTime = 1; int temp;
//	char backWasChecked = 0; int downPos; int dir = 4;
//	for (int i = 0; true ; i+=w*4) { // Vertical
//		if (i + loc >= img->len || (getPixelAVG(loc+i) < 30 && getPixelAVG(loc + i + 4) < 30))
//		{
//			break;
//		}
//		for (int j = 0; true; j+=dir) // Horizontal
//		{
//			if (i + j + loc >= img->len) {
//				break;
//			}
//			if (getPixelAVG(loc + i + j) < 30) {
//				if (!backWasChecked) {
//					/*FirstTime*/
//					//if (firstTime) { firstTime = 0;
//					//	temp = (j/4)/2; loc += temp * 4;
//					//	j = -temp * 4;
//					//}
//					//else {
//						j = 0;
//					//}
//					backWasChecked = true; dir = -4;
//				}
//				else { dir = 4; backWasChecked = false; break; }
//			} else {
//				removePixel(loc + i + j);
//			}
//		}
//	}
//}
