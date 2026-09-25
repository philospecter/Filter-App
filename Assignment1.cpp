#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include "Image_Class.h"

using namespace std;


// ============================================================
// FILTER 2 - BLACK & WHITE
// ============================================================

void blackAndWhite(Image& image)
{
    int threshold = 128;

    for (int y = 0; y < image.height; y++)
    {
        for (int x = 0; x < image.width; x++)
        {
            int r = image.getPixel(x, y, 0);
            int g = image.getPixel(x, y, 1);
            int b = image.getPixel(x, y, 2);

            int gray = (r + g + b) / 3;

            if (gray < threshold)
            {
                image.setPixel(x, y, 0, 0);
                image.setPixel(x, y, 1, 0);
                image.setPixel(x, y, 2, 0);
            }
            else
            {
                image.setPixel(x, y, 0, 255);
                image.setPixel(x, y, 1, 255);
                image.setPixel(x, y, 2, 255);
            }
        }
    }
}


// ============================================================
// FILTER 6 - ROTATE
// ============================================================

void rotate(Image& image)
{
    int choice;

    cout << "\nChoose Rotation Angle:\n";
    cout << "1. Rotate 90 degrees\n";
    cout << "2. Rotate 180 degrees\n";
    cout << "3. Rotate 270 degrees\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1)
    {
        Image newImage(image.height, image.width);

        for (int y = 0; y < image.height; y++)
        {
            for (int x = 0; x < image.width; x++)
            {
                for (int c = 0; c < 3; c++)
                {
                    newImage.setPixel(
                        image.height - 1 - y,
                        x,
                        c,
                        image.getPixel(x, y, c)
                    );
                }
            }
        }

        image = newImage;
    }
    else if (choice == 2)
    {
        Image newImage(image.width, image.height);

        for (int y = 0; y < image.height; y++)
        {
            for (int x = 0; x < image.width; x++)
            {
                for (int c = 0; c < 3; c++)
                {
                    newImage.setPixel(
                        image.width - 1 - x,
                        image.height - 1 - y,
                        c,
                        image.getPixel(x, y, c)
                    );
                }
            }
        }

        image = newImage;
    }
    else if (choice == 3)
    {
        Image newImage(image.height, image.width);

        for (int y = 0; y < image.height; y++)
        {
            for (int x = 0; x < image.width; x++)
            {
                for (int c = 0; c < 3; c++)
                {
                    newImage.setPixel(
                        y,
                        image.width - 1 - x,
                        c,
                        image.getPixel(x, y, c)
                    );
                }
            }
        }

        image = newImage;
    }
    else
    {
        cout << "Invalid rotation choice.\n";
    }
}


// ============================================================
// MAIN - TESTING ONLY
// ============================================================

int main()
{
    string fileName;
    string outputFileName;

    cout << "Enter image file name: ";
    cin >> fileName;

    try
    {
        Image image(fileName);

        int choice;

        cout << "\n==============================\n";
        cout << "       IMAGE FILTERS\n";
        cout << "==============================\n";
        cout << "1. Black & White\n";
        cout << "2. Rotate\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            blackAndWhite(image);
        }
        else if (choice == 2)
        {
            rotate(image);
        }
        else if (choice == 3)
        {
            return 0;
        }
        else
        {
            cout << "Invalid choice.\n";
            return 0;
        }

        cout << "\nEnter output image file name: ";
        cin >> outputFileName;

        image.saveImage(outputFileName);

        cout << "\nImage saved successfully.\n";
    }
    catch (const exception& e)
    {
        cout << "\nError: " << e.what() << endl;
    }

    return 0;
}