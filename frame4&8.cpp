#include <iostream>
#include <algorithm>
#include "Image_Class.h"
using namespace std;

// ============================================================
// FILTER 4 - ADDING A FRAME (simple or decorative)
// ============================================================
void frameFilter(Image& img)
{
    int border = 20;

    unsigned char outerColor[3] = {30, 110, 235};
    unsigned char innerColor[3] = {255, 255, 255};
    int innerGap = 5;

    int choice;
    cout << "\nFrame type -> 1: Simple | 2: Decorative\nChoice: ";
    cin >> choice;

    while (choice != 1 && choice != 2)
    {
        cout << "Wrong choice, enter 1 or 2: ";
        cin >> choice;
    }

    // ---------------- Outer layer ----------------
    int topLimit = min(border, img.height);

    for (int y = 0; y < topLimit; y++)
        for (int x = 0; x < img.width; x++)
            for (int k = 0; k < 3; k++)
                img.setPixel(x, y, k, outerColor[k]);

    int bottomLimit = min(border, img.height);

    for (int y = img.height - bottomLimit; y < img.height; y++)
        for (int x = 0; x < img.width; x++)
            for (int k = 0; k < 3; k++)
                img.setPixel(x, y, k, outerColor[k]);

    int leftLimit = min(border, img.width);

    for (int x = 0; x < leftLimit; x++)
        for (int y = 0; y < img.height; y++)
            for (int k = 0; k < 3; k++)
                img.setPixel(x, y, k, outerColor[k]);

    int rightLimit = min(border, img.width);

    for (int x = img.width - rightLimit; x < img.width; x++)
        for (int y = 0; y < img.height; y++)
            for (int k = 0; k < 3; k++)
                img.setPixel(x, y, k, outerColor[k]);

    // ---------------- Inner layer ----------------
    if (choice == 2)
    {
        // top
        for (int y = border; y < border + innerGap; y++)
            for (int x = border; x < img.width - border; x++)
                for (int k = 0; k < 3; k++)
                    img.setPixel(x, y, k, innerColor[k]);

        // bottom
        for (int y = img.height - border - innerGap; y < img.height - border; y++)
            for (int x = border; x < img.width - border; x++)
                for (int k = 0; k < 3; k++)
                    img.setPixel(x, y, k, innerColor[k]);

        // left
        for (int x = border; x < border + innerGap; x++)
            for (int y = border; y < img.height - border; y++)
                for (int k = 0; k < 3; k++)
                    img.setPixel(x, y, k, innerColor[k]);

        // right
        for (int x = img.width - border - innerGap; x < img.width - border; x++)
            for (int y = border; y < img.height - border; y++)
                for (int k = 0; k < 3; k++)
                    img.setPixel(x, y, k, innerColor[k]);
    }
}

// ============================================================
// FILTER 8 - RESIZING IMAGES
// ============================================================
Image resize(Image& img)
{
    int choice;
    cout << "\nResize mode -> 1: New dimensions | 2: Scale ratio\nChoice: ";
    cin >> choice;

    int newWidth, newHeight;

    if (choice == 1)
    {
        cout << "Enter width and height separated by space (example: 500 300): ";
        cin >> newWidth >> newHeight;
    }
    else
    {
        double ratio;
        cout << "Enter a single number for the ratio (example: 0.5 or 2): ";
        cin >> ratio;

        newWidth = (int)(img.width * ratio);
        newHeight = (int)(img.height * ratio);
    }

    double scaleX = (double)img.width / newWidth;
    double scaleY = (double)img.height / newHeight;

    Image resizedImg(newWidth, newHeight);

    for (int newY = 0; newY < newHeight; newY++)
    {
        for (int newX = 0; newX < newWidth; newX++)
        {
            int oldX = (int)(newX * scaleX);
            int oldY = (int)(newY * scaleY);

            for (int k = 0; k < 3; k++)
            {
                unsigned char color = img.getPixel(oldX, oldY, k);
                resizedImg.setPixel(newX, newY, k, color);
            }
        }
    }

    return resizedImg;
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
        cout << "1. Frame\n";
        cout << "2. Resize\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            frameFilter(image);
        }
        else if (choice == 2)
        {
            image = resize(image);
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