
//====================================================================================
//======================================Part 1========================================
//             Ahmed Khaled      : 20250021 |||| filter: 1, 5, 9, 13, 17
//             Ammar Gabr        : 20250410 |||| filter: 2, 6, 10, 14, 18
//             Philopateer Farag : 20250475 |||| filter: 3, 7, 11, 15,
//             Mohamed Khaled    : 20250557 |||| filter: 4, 8, 12, 16
//                                  Section: S11,12 / Lab(7)
//===================================================================================
//===================================================================================

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
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
// FILTER 9 - MERGE TWO IMAGES
// ============================================================
void mergeImages(Image& image)
{
    string secondFile;
    cout << "Enter the second image file name: ";
    cin >> secondFile;

    try
    {
        Image secondImage(secondFile);
        int newWidth = min(image.width, secondImage.width);
        int newHeight = min(image.height, secondImage.height);

        for (int y = 0; y < newHeight; y++)
        {
            for (int x = 0; x < newWidth; x++)
            {
                for (int c = 0; c < 3; c++)
                {
                    int firstColor = image.getPixel(x, y, c);
                    int secondColor = secondImage.getPixel(x, y, c);
                    image.setPixel(x, y, c, (firstColor + secondColor) / 2);
                }
            }
        }
        cout << "The overlapping parts of the two images were merged.\n";
    }
    catch (const exception& e)
    {
        cout << "Could not load the second image: " << e.what() << endl;
    }
}

// ============================================================
// FILTER 10 - EDGE DETECTION
// ============================================================
void edgeDetection(Image& image)
{
    Image result(image.width, image.height);

    for (int y = 0; y < image.height; y++)
    {
        for (int x = 0; x < image.width; x++)
        {
            int r = image.getPixel(x, y, 0);
            int g = image.getPixel(x, y, 1);
            int b = image.getPixel(x, y, 2);
            int gray = (r + g + b) / 3;

            int rightGray = gray;
            int downGray = gray;

            if (x + 1 < image.width)
            {
                rightGray = (
                    image.getPixel(x + 1, y, 0) +
                    image.getPixel(x + 1, y, 1) +
                    image.getPixel(x + 1, y, 2)) / 3;
            }

            if (y + 1 < image.height)
            {
                downGray = (
                    image.getPixel(x, y + 1, 0) +
                    image.getPixel(x, y + 1, 1) +
                    image.getPixel(x, y + 1, 2)) / 3;
            }

            int difference = abs(gray - rightGray) + abs(gray - downGray);
            int color = (difference > 35) ? 0 : 255;

            for (int c = 0; c < 3; c++)
                result.setPixel(x, y, c, color);
        }
    }

    image = result;
}

// ============================================================
// FILTER 11 - CROP
// ============================================================
void cropImage(Image& image)
{
    int startX, startY, cropWidth, cropHeight;

    cout << "Enter starting X and Y: ";
    cin >> startX >> startY;
    cout << "Enter crop width and height: ";
    cin >> cropWidth >> cropHeight;

    if (startX < 0 || startY < 0 || cropWidth <= 0 || cropHeight <= 0 ||
        startX >= image.width || startY >= image.height ||
        startX + cropWidth > image.width || startY + cropHeight > image.height)
    {
        cout << "Invalid crop dimensions. The image was not changed.\n";
        return;
    }

    Image cropped(cropWidth, cropHeight);

    for (int y = 0; y < cropHeight; y++)
    {
        for (int x = 0; x < cropWidth; x++)
        {
            for (int c = 0; c < 3; c++)
                cropped.setPixel(x, y, c, image.getPixel(startX + x, startY + y, c));
        }
    }

    image = cropped;
}

// ============================================================
// FILTER 12 - BLUR
// ============================================================
void blurImage(Image& image)
{
    int radius;
    cout << "Enter blur strength (1-5): ";
    cin >> radius;

    if (radius < 1 || radius > 5)
    {
        cout << "Invalid strength. Enter a number from 1 to 5.\n";
        return;
    }

    Image result(image.width, image.height);

    for (int y = 0; y < image.height; y++)
    {
        for (int x = 0; x < image.width; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                int total = 0;
                int count = 0;

                for (int dy = -radius; dy <= radius; dy++)
                {
                    for (int dx = -radius; dx <= radius; dx++)
                    {
                        int nx = x + dx;
                        int ny = y + dy;

                        if (nx >= 0 && nx < image.width && ny >= 0 && ny < image.height)
                        {
                            total += image.getPixel(nx, ny, c);
                            count++;
                        }
                    }
                }

                result.setPixel(x, y, c, total / count);
            }
        }
    }

    image = result;
}

// ============================================================
// FILTER 13 - IMPROVE SUNLIGHT
// ============================================================
void improveSunlight(Image& image)
{
    for (int y = 0; y < image.height; y++)
    {
        for (int x = 0; x < image.width; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                int color = image.getPixel(x, y, c);
                int brighter = color + 45;

                if (brighter > 255)
                    brighter = 255;

                image.setPixel(x, y, c, brighter);
            }
        }
    }
}

// ============================================================
// FILTER 14 - OLD TV EFFECT
// ============================================================
void oldTVEffect(Image& image)
{
    for (int y = 0; y < image.height; y++)
    {
        for (int x = 0; x < image.width; x++)
        {
            int r = image.getPixel(x, y, 0);
            int g = image.getPixel(x, y, 1);
            int b = image.getPixel(x, y, 2);
            int gray = (r + g + b) / 3;

            if (y % 4 == 0)
                gray = gray * 3 / 4;

            image.setPixel(x, y, 0, gray);
            image.setPixel(x, y, 1, gray);
            image.setPixel(x, y, 2, gray);
        }
    }
}

// ============================================================
// FILTER 15 - PURPLE EFFECT
// ============================================================
void purpleEffect(Image& image)
{
    for (int y = 0; y < image.height; y++)
    {
        for (int x = 0; x < image.width; x++)
        {
            int r = image.getPixel(x, y, 0);
            int g = image.getPixel(x, y, 1);
            int b = image.getPixel(x, y, 2);

            int newR = min(255, r + 35);
            int newG = g * 3 / 4;
            int newB = min(255, b + 55);

            image.setPixel(x, y, 0, newR);
            image.setPixel(x, y, 1, newG);
            image.setPixel(x, y, 2, newB);
        }
    }
}

// ============================================================
// FILTER 16 - INFRARED EFFECT
// ============================================================
void infraredEffect(Image& image)
{
    for (int y = 0; y < image.height; y++)
    {
        for (int x = 0; x < image.width; x++)
        {
            int r = image.getPixel(x, y, 0);
            int g = image.getPixel(x, y, 1);
            int b = image.getPixel(x, y, 2);

            int newR = min(255, 255 - g);
            int newG = min(255, 255 - b);
            int newB = min(255, 255 - r);

            image.setPixel(x, y, 0, newR);
            image.setPixel(x, y, 1, newG);
            image.setPixel(x, y, 2, newB);
        }
    }
}

// ============================================================
// FILTER 17 - SKEW
// ============================================================
void skewImage(Image& image)
{
    double angle;
    cout << "Enter skew angle in degrees (5-30): ";
    cin >> angle;

    if (angle < 5 || angle > 30)
    {
        cout << "Invalid angle. Enter a value from 5 to 30.\n";
        return;
    }

    double tangent = tan(angle * 3.14159265358979323846 / 180.0);
    int extraWidth = (int)(image.height * tangent);
    if (extraWidth < 1)
        extraWidth = 1;

    Image skewed(image.width + extraWidth, image.height);

    for (int y = 0; y < image.height; y++)
    {
        int shift = (int)((image.height - 1 - y) * tangent);

        for (int x = 0; x < image.width; x++)
        {
            for (int c = 0; c < 3; c++)
                skewed.setPixel(x + shift, y, c, image.getPixel(x, y, c));
        }
    }

    image = skewed;
}

// ============================================================
// FILTER 18 - OIL PAINTING EFFECT
// ============================================================
void oilPainting(Image& image)
{
    Image result(image.width, image.height);

    for (int y = 0; y < image.height; y++)
    {
        for (int x = 0; x < image.width; x++)
        {
            int totalR = 0;
            int totalG = 0;
            int totalB = 0;
            int count = 0;

            for (int dy = -1; dy <= 1; dy++)
            {
                for (int dx = -1; dx <= 1; dx++)
                {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && nx < image.width && ny >= 0 && ny < image.height)
                    {
                        totalR += image.getPixel(nx, ny, 0);
                        totalG += image.getPixel(nx, ny, 1);
                        totalB += image.getPixel(nx, ny, 2);
                        count++;
                    }
                }
            }

            int r = (totalR / count / 32) * 32;
            int g = (totalG / count / 32) * 32;
            int b = (totalB / count / 32) * 32;

            result.setPixel(x, y, 0, r);
            result.setPixel(x, y, 1, g);
            result.setPixel(x, y, 2, b);
        }
    }

    image = result;
}


// ============================================================
// MAIN
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
        int choice = 0;

        while (choice != 19)
        {
            cout << "\n====================================\n";
            cout << "          IMAGE FILTERS\n";
            cout << "====================================\n";
            cout << " 1. Grayscale\n";
            cout << " 2. Black & White\n";
            cout << " 3. Invert\n";
            cout << " 4. Add Frame\n";
            cout << " 5. Flip\n";
            cout << " 6. Rotate\n";
            cout << " 7. Darken / Lighten\n";
            cout << " 8. Resize\n";
            cout << " 9. Merge Images\n";
            cout << "10. Edge Detection\n";
            cout << "11. Crop\n";
            cout << "12. Blur\n";
            cout << "13. Improve Sunlight\n";
            cout << "14. Old TV Effect\n";
            cout << "15. Purple Effect\n";
            cout << "16. Infrared Effect\n";
            cout << "17. Skew\n";
            cout << "18. Oil Painting\n";
            cout << "19. Save and Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1)
                grayscale(image);
            else if (choice == 2)
                blackAndWhite(image);
            else if (choice == 3)
                invert(image);
            else if (choice == 4)
                frameFilter(image);
            else if (choice == 5)
                flip(image);
            else if (choice == 6)
                rotate(image);
            else if (choice == 7)
                darkenAndLighten(image);
            else if (choice == 8)
                image = resize(image);
            else if (choice == 9)
                mergeImages(image);
            else if (choice == 10)
                edgeDetection(image);
            else if (choice == 11)
                cropImage(image);
            else if (choice == 12)
                blurImage(image);
            else if (choice == 13)
                improveSunlight(image);
            else if (choice == 14)
                oldTVEffect(image);
            else if (choice == 15)
                purpleEffect(image);
            else if (choice == 16)
                infraredEffect(image);
            else if (choice == 17)
                skewImage(image);
            else if (choice == 18)
                oilPainting(image);
            else if (choice == 19)
                break;
            else
            {
                cout << "Invalid choice. Please choose from 1 to 19.\n";
                continue;
            }

            if (choice >= 1 && choice <= 18)
                cout << "Filter operation finished.\n";
        }

        cout << "Enter output image file name (example: result.jpg): ";
        cin >> outputFileName;
        image.saveImage(outputFileName);
        cout << "Image saved successfully.\n";
    }
    catch (const exception& e)
    {
        cout << "\nError: " << e.what() << endl;
    }

    return 0;
}
