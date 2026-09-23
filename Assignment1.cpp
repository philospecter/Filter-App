#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;
#include "Image_Class.h"

int main()
{
	string file_name;
	string output_filename;
	cout << "please enter image name to show it for you: ";
	cin >> file_name;
	Image image(file_name);
	cout << "please enter name of new pic. : ";
	cin >> output_filename;
	image.saveImage(output_filename);
	return 0;
}