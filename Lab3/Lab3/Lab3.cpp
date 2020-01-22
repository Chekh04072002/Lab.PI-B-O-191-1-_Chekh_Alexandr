#include <iostream>
#include "libbmp.h"

int main() {
	char text[10000];
	int position = 0;
	char pol = 0;
	int counter = 0;
	bool end = false;
	BmpImg img;
	int bit;
	img.read("pic10.bmp");
	const int width = img.get_width();
	const int height = img.get_height();
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			bit = img.blue_at(j, i);
			pol <<= 1;
			if (bit % 2 == 1) {
				pol++;
			}
			counter++;
			if (counter == 8) {
				text[position] = pol;
					position++;
				counter = 0;
				if (pol == '\0') {
					end = true;
					break;
				}
			}

			bit = img.green_at(j, i);
			pol <<= 1;
			if (bit % 2 == 1) {
				pol++;
			}
			counter++;
			if (counter == 8) {
				text[position] = pol;
				position++;
				counter = 0;
				if (pol == '\0') {
					end = true;
					break;
				}
			}

			bit = img.red_at(j, i);
			pol <<= 1;
			if (bit % 2 == 1) {
				pol++;
			}
			counter++;
			if (counter == 8) {
				text[position] = pol;
				position++;
				counter = 0;
				if (pol == '\0') {
					end = true;
					break;
				}
			}
		}
		if (end)break;
	}
	std::cout << text;
}