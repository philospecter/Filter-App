
//====================================================================================
//======================================Part 1========================================
//             Ahmed Khaled      : 20250021 |||| filter: 1, 5
//             Ammar Gabr        : 20250410 |||| filter: 2, 6
//             Philopateer Farag : 20250475 |||| filter: 3, 7
//             Mohamed Khaled    : 20250557 |||| filter: 4, 8
//                                  Section: S13,14
//===================================================================================
//===================================================================================

#include <iostream>
#include <string>
#include <algorithm>
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
    string input;
    int percentage = 0;
    bool valid = false;

    cout << "Enter percentage to darken or lighten (negative for darken, positive for lighten): ";

    while (!valid)
    {
        cin >> input;
        valid = true;
        
        for (int i = 0; i < input.length(); i++)
        {
            if (i == 0 && input[i] == '-' && input.length() > 1)
                continue;
            if (input[i] < '0' || input[i] > '9')
                valid = false;
        }

        if (valid && input.length() > 4)
            valid = false;

        if (valid)
        {
            percentage = stoi(input);
            if (percentage < -100 || percentage > 100)
                valid = false;
        }

        if (!valid)
            cout << "Invalid input. Please enter a whole number between -100 and 100: ";
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
        cout << "1. grayscale\n";
        cout << "2. Black & White\n";
        cout << "3. Invert\n";
        cout << "4. Adding Frame\n";
        cout << "5. flip\n";
        cout << "6. Rotate\n";
        cout << "7. Darken and Lighten\n";
        cout << "8.Resize\n";
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
        else if (choice == 4)
        {
            frameFilter(image);
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
        else if (choice == 8)
        {
            image=resize(image);
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