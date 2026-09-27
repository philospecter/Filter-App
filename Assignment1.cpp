#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include "Image_Class.h"

using namespace std;

// =============================================================
// FILTER 1 - GRAYSCALE
// =============================================================

void grayscale(Image& image)
{
    for (int y = 0; y < image.height; y++)
    {
        for (int x = 0; x < image.width; x++)
        {
            int r = image.getPixel(x, y, 0);
            int g = image.getPixel(x, y, 1);
            int b = image.getPixel(x, y, 2);
            int gray = (r + g + b) / 3;
            image.setPixel(x, y, 0, gray);
            image.setPixel(x, y, 1, gray);
            image.setPixel(x, y, 2, gray);
        }
    }
}



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
// FILTER 3 - INVERT
// ============================================================
 void invert(Image& image){
    
    for (int y = 0; y < image.height; y++)
    {
        for (int x = 0; x < image.width; x++)
        {
            int r = image.getPixel(x, y, 0);
            int g = image.getPixel(x, y, 1);
            int b = image.getPixel(x, y, 2);

            image.setPixel(x, y, 0, 255 - r);
            image.setPixel(x, y, 1, 255 - g);
            image.setPixel(x, y, 2, 255 - b);
        }
    }
 }

// ============================================================
// FILTER 5 - FLIP
// ============================================================

void flip(Image& image)
{
    int choice;
    cout << "===================\n";
    cout << "1.flip horizontal\n";
    cout << "2.flip vertical  \n";
    cout << "enter your choice: ";
    cin >> choice;

    if (choice == 1)
    {
        Image new_image(image.width, image.height);

        for (int y = 0; y < image.height; y++)
        {
            for (int x = 0; x < image.width; x++)
            {
               
                int r = image.getPixel(x, y, 0);
                int g = image.getPixel(x, y, 1);
                int b = image.getPixel(x, y, 2);
                int new_x = image.width - 1 - x;
                new_image.setPixel(new_x, y, 0, r);
                new_image.setPixel(new_x, y, 1, g);
                new_image.setPixel(new_x, y, 2, b);
                
            }
        }
        image = new_image;


    }
    else if (choice == 2)
    {
        Image new_image(image.width, image.height);
        for (int y = 0;y < image.height;y++)
        {
            for (int x = 0;x < image.width;x++)
            {
                int r = image.getPixel(x, y, 0);
                int g = image.getPixel(x, y, 1);
                int b = image.getPixel(x, y, 2);
                int new_y = image.height - 1 - y;
                new_image.setPixel(x, new_y, 0, r);
                new_image.setPixel(x, new_y, 1, g);
                new_image.setPixel(x, new_y, 2, b);
            }
        }
       
        image = new_image;


    }
    else
    {
        cout << "invalide flip choice\n";
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
// FILTER 7 - Darken and Lighten
// ============================================================
    void darkenAndLighten(Image& image)
    {
        int percentage;
    cout << "Enter percentage to darken or lighten (negative for darken, positive for lighten): ";
    cin >> percentage;
    while (percentage < -100 || percentage > 100)
    {
        cout << "Invalid percentage. Please enter a value between -100 and 100." << endl;
        cout << "Enter percentage: ";
        cin >> percentage;
    }
    if (percentage < 0)
    {
        double factorValue = 1 - (abs(percentage) / 100.0);
        for (int y = 0; y < image.height; y++)
        {
            for (int x = 0; x < image.width; x++)
            {
              int r = image.getPixel(x, y, 0);
                int g = image.getPixel(x, y, 1);
                int b = image.getPixel(x, y, 2);

                image.setPixel(x,y, 0 , r*factorValue);
                image.setPixel(x,y, 1 , g*factorValue);
                image.setPixel(x,y, 2 , b*factorValue);
            }
        }
    }
    else
    {

        double factorValue = 1 + (percentage / 100.0);
    
        for (int y = 0; y < image.height; y++)
        {
            for (int x = 0; x < image.width; x++)
            {
                int r = image.getPixel(x, y, 0);
                int g = image.getPixel(x, y, 1);
                int b = image.getPixel(x, y, 2);

                double newR = r * factorValue;
                if (newR > 255) newR = 255;
                double newG = g * factorValue;
                if (newG > 255) newG = 255;
                double newB = b * factorValue;
                if (newB > 255) newB = 255;


                image.setPixel(x,y, 0 , newR);
                image.setPixel(x,y, 1 , newG);
                image.setPixel(x,y, 2 , newB);
            }
        }
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
        cout << "1. grayscale\n";
        cout << "2. Black & White\n";
        cout << "3. Invert\n";
        cout << "5. flip\n";
        cout << "6. Rotate\n";
        cout << "7. Darken and Lighten\n";
        cout << "17. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            grayscale(image);
        }
        else if (choice == 2)
        {
            blackAndWhite(image);
        }
        else if (choice == 3)
        {
            invert(image);
        }
        else if (choice == 5)
        {
            flip(image);
        }
        else if (choice == 6)
        {
            rotate(image);
        }
        else if (choice == 7)
        {
            darkenAndLighten(image);
        }
        else if (choice == 17)
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