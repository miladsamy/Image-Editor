// FCAI – OOP – 2023 - Assignment 1 - FULL
// Program Name: Image Editor
// Marwan Osama Abd El-Azem Ibrahim >> 20220324
// Milad Samy Milad >> 20220354
// Menna Khaled Gamal >> 20221166

#include <iostream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
using namespace std;

unsigned char image[SIZE][SIZE]; // Declear the image as a 2d char array
char op; // Declear a char variable to decide which operation to apply

// Load the image to apply changes on it
void LOAD() {
    char imageFileName[100];
    string path = "\\images\\";
    cout << "\nWelcome to our Image Editor program <3 \n";
    cout << "Please, Enter name of the image file to process (must be in [images] folder): \n"
            ">> ";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    path += imageFileName;
    char cwd[PATH_MAX];
    readGSBMP(strcat (getcwd(cwd, sizeof(cwd)), path.c_str()), image);
}
// The program interface
void CHOOSE() {
    cout << "\nPlease, Select a filter to Apply or 0 to Exit: \n"
            "(1) Black & White Filter \n"
            "(2) Invert Filter \n"
            "(3) Merge Filter \n"
            "(4) Flip Image \n"
            "(5) Darken and Lighten Image \n"
            "(6) Rotate Image \n"
            "(7) Detect Image Edges \n"
            "(8) Enlarge Image \n"
            "(9) Shrink Image \n"
            "(a) Mirror 1/2 Image \n"
            "(b) Shuffle Image \n"
            "(c) Blur Image \n"
            "(d) Crop Image \n"
            "(e) Skew Image Right \n"
            "(f) Skew Image Up \n"
            "(s) Save the image \n"
            "(0) Exit \n";
}
// Make the image black and white
void BW() {
    // Loop through each pixel in the image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Check if the pixel intensity is greater than 127
            if (image[i][j] > 127) {
                // Set the pixel to white (255) if it's brighter than a threshold
                image[i][j] = 255;
            } else {
                // Set the pixel to black (0) if it's not brighter than the threshold
                image[i][j] = 0;
            }
        }
    }
}
// Invert the colors of the entire image
void INVERT() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Calculate the negative of the pixel value by subtracting it from the highest value (255)
            image[i][j] = 255 - image[i][j];
        }
    }
}
// Merge the current image with another image loaded from a file
void MERGE() {
    char image2FileName[100];
    unsigned char image2[SIZE][SIZE];

    // Prompt the user for the name of the image file to merge with
    cout << "\nEnter name of image file to merge with (must be in [images] folder): \n"
            ">> ";
    cin >> image2FileName;

    // Append ".bmp" to the filename to ensure it's a BMP file
    strcat(image2FileName, ".bmp");

    // Read the second image from the specified file
    readGSBMP(image2FileName, image2);

    // Merge the two images by taking the average of corresponding pixel values
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Merge by taking the average of the sum of pixel values from both images
            image[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
}
// Flip the image either horizontally or vertically based on user input
void FLIB() {
    cout << "\nFlip (h)orizontally or (v)ertically ? \n"
            ">> ";
    char flib;
    cin >> flib;

    if (flib == 'v') {
        // Flip the image vertically by reversing each column in the 2D array
        for (int i = 0; i < SIZE/2; i++) {
            for (int j = 0; j < SIZE; j++) {
                swap(image[i][j], image[SIZE - i - 1][j]);
            }
        }
    } else if (flib == 'h') {
        // Flip the image horizontally by reversing each row in the 2D array
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE/2; j++) {
                swap(image[i][j], image[i][SIZE - j - 1]);
            }
        }
    } else {
        // Display an error message for an invalid input
        cout << "\nInvalid Value! \n";
    }
}
// Darken or lighten the image based on user input
void DL() {
    cout << "\nDo you want to (d)arken or (l)ighten ? \n"
            ">> ";
    char dl;
    cin >> dl;

    if (dl == 'd') {
        // Darken the image by reducing each pixel value by 50% and ensuring it stays within the valid range (0-255)
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] *= 0.5; // to darken it by 50%
                // Ensure the value stays within the valid range (0-255)
                if (image[i][j] < 0) {
                    image[i][j] = 0;
                }
            }
        }
    } else if (dl == 'l') {
        // Lighten the image by increasing each pixel value by 50% (with a maximum limit of 255)
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (image[i][j] + 50 < 255) {
                    image[i][j] += 50;  // We adjust it by testing
                }
            }
        }
    } else {
        // Display an error message for an invalid input
        cout << "\nInvalid Value! \n";
    }
}
// Rotate the image by 90, 180, 270, or 360 degrees based on user input
void ROTATE() {
    cout << "\nRotate (90), (180), (270) or (360) degrees ? \n"
            ">> ";
    int r;
    cin >> r;

    if (r == 90) {
        // Rotate the image 90 degrees by transposing the 2D array and reversing each column
        for (int i = 0; i < SIZE; i++) {
            for (int j = i; j < SIZE; j++) {
                swap(image[i][j], image[j][i]);
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE/2; j++) {
                swap(image[j][i], image[SIZE - j - 1][i]);
            }
        }
    } else if (r == 180) {
        // Rotate the image 180 degrees by reversing each row and column in the 2D array
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE/2; j++) {
                swap(image[i][j], image[i][SIZE - j - 1]);
            }
        }
        for (int i = 0; i < SIZE/2; i++) {
            for (int j = 0; j < SIZE; j++) {
                swap(image[i][j], image[SIZE - i - 1][j]);
            }
        }
    } else if (r == 270) {
        // Rotate the image 270 degrees by transposing the 2D array and reversing each row
        for (int i = 0; i < SIZE; i++) {
            for (int j = i; j < SIZE; j++) {
                swap(image[i][j], image[j][i]);
            }
        }
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE/2; j++){
                swap(image[i][j], image[i][SIZE - j - 1]);
            }
        }
    } else if (r == 360) {
        // 360-degree rotation does not affect the image, so the function remains empty
    } else {
        // Display an error message for an invalid input
        cout << "\nInvalid Value! \n";
    }
}
// Detect edges in the image using the Sobel operator
void EDGES() {
    // Create a copy of the image to preserve the original data
    unsigned char image2[SIZE][SIZE];

    // Copy the pixel values from the original image to the copy
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image2[i][j] = image[i][j];
        }
    }

    // Apply the Sobel operator to detect edges in the image
    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 1; j < SIZE - 1; j++) {
            // Calculate gradient values in both the x and y directions
            int x = image2[i][j + 1] - image2[i][j - 1];
            int y = image2[i + 1][j] - image2[i - 1][j];

            // Calculate the magnitude of the gradient
            int magnitude = abs(x) + abs(y);

            // Update the pixel in the original image with the magnitude
            image[i][j] = magnitude;
        }
    }

    // Invert the colors of the edge-detected image
    INVERT();
}
// Enlarge a specific quarter of the image based on user input
void ENLARGE() {
    cout << "\nWhich quarter to enlarge (1), (2), (3) or (4) ? \n"
            ">> ";
    int quarter;
    cin >> quarter;

    // Create a copy of the original image
    unsigned char image2[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image2[i][j] = image[i][j];
        }
    }

    if (quarter == 1) {
        // Enlarge the first quarter of the image
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image2[i / 2][j / 2];
            }
        }
    } else if (quarter == 2) {
        // Enlarge the second quarter of the image
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image2[i / 2][j / 2 + 128];
            }
        }
    } else if (quarter == 3) {
        // Enlarge the third quarter of the image
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image2[i / 2 + 128][j / 2];
            }
        }
    } else if (quarter == 4) {
        // Enlarge the fourth quarter of the image
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image2[i / 2 + 128][j / 2 + 128];
            }
        }
    } else {
        // Display an error message for an invalid input
        cout << "\nInvalid Value! \n";
    }
}
// Shrink the image to a specified ratio based on user input
void SHRINK() {
    char image2FileName[100];
    unsigned char image2[SIZE][SIZE];
    strcat(image2FileName, ".bmp");

    // Create a copy of the original image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image2[i][j] = image[i][j];
        }
    }

    // Set all pixel values in the original image to 255 (white)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = 255;
        }
    }

    string ratio;
    cout << "\nShrink to (1/2), (1/3) or (1/4) ? \n"
            ">> ";
    cin >> ratio;

    if (ratio == "1/2") {
        // Shrink the image to 1/2 of its size by selecting every second pixel
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i / 2][j / 2] = image2[i][j];
            }
        }
    } else if (ratio == "1/3") {
        // Shrink the image to 1/3 of its size by selecting every third pixel
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i / 3][j / 3] = image2[i][j];
            }
        }
    } else if (ratio == "1/4") {
        // Shrink the image to 1/4 of its size by selecting every fourth pixel
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i / 4][j / 4] = image2[i][j];
            }
        }
    } else {
        // Display an error message for an invalid input
        cout << "\nInvalid Value! \n";
    }
}
// Mirror the image either left, right, upper, or lower side based on user input
void MIRROR() {
    cout << "\nMirror (l)eft, (r)ight, (u)pper, (d)own side ?\n"
            ">> ";
    char mirror;
    cin >> mirror;

    if (mirror == 'l') {
        // Mirror the image to the left by reversing the pixel order in each row
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][SIZE - j - 1] = image[i][j];
            }
        }
    } else if (mirror == 'r') {
        // Mirror the image to the right by reversing the pixel order in each row
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image[i][SIZE - j - 1];
            }
        }
    } else if (mirror == 'u') {
        // Mirror the image to the upper side by reversing the pixel order in each column
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[SIZE - i - 1][j] = image[i][j];
            }
        }
    } else if (mirror == 'd') {
        // Mirror the image to the lower side by reversing the pixel order in each column
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image[SIZE - i - 1][j];
            }
        }
    } else {
        // Display an error message for an invalid input
        cout << "\nInvalid Value! \n";
    }
}
// Dividing the image into 4 quarters and rearrange them with the order that user want
void SHUFFLE() {
    // Initialize a new 2D array to store the shuffled image.
    unsigned char image2[SIZE][SIZE];

    // Prompt the user to enter the new order of quarters.
    cout << "\nEnter the new order of quarters (separated by spaces):\n"
            ">> ";
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    // Shuffle the quarters of the image based on user inputs 'a', 'b', 'c', and 'd'.
    if (a == 1) {
        // Copy the top-left quarter to the corresponding position in image2.
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 128; j++) {
                image2[i][j] = image[i][j];
            }
        }
    } else if (a == 2) {
        // Copy the top-right quarter to the corresponding position in image2.
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 128; j++) {
                image2[i][j] = image[i][j + 128];
            }
        }
    } else if (a == 3) {
        // Copy the bottom-left quarter to the corresponding position in image2.
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image2[i][j] = image[i + 128][j];
            }
        }
    } else if (a == 4) {
        // Copy the bottom-right quarter to the corresponding position in image2.
        for (int i = 128; i < 256; i++) {
            for (int j = 128; j < 256; j++) {
                image2[i - 128][j - 128] = image[i][j];
            }
        }
    }

    if (b == 1) {
        // Copy top-left quarter to a different position in image2.
        for (int i = 0; i < 128; i++) {
            for (int j = 128; j < 256; j++) {
                image2[i][j] = image[i][j - 128];
            }
        }
    } else if (b == 2) {
        // Copy the top-right quarter to the corresponding position in image2.
        for (int i = 0; i < 128; i++) {
            for (int j = 128; j < 256; j++) {
                image2[i][j] = image[i][j];
            }
        }
    } else if (b == 3) {
        // Copy the bottom-left quarter to the corresponding position in image2.
        for (int i = 0; i < 128; i++) {
            for (int j = 128; j < 256; j++) {
                image2[i][j] = image[i + 128][j - 128];
            }
        }
    } else if (b == 4) {
        // Copy the bottom-right quarter to the corresponding position in image2.
        for (int i = 0; i < 128; i++) {
            for (int j = 128; j < 256; j++) {
                image2[i][j] = image[i + 128][j];
            }
        }
    }

    if (c == 1) {
        // Copy the top-left quarter to the corresponding position in image2.
        for (int i = 128; i < 256; i++) {
            for (int j = 0; j < 128; j++) {
                image2[i][j] = image[i - 128][j];
            }
        }
    } else if (c == 2) {
        // Copy the top-right quarter to the corresponding position in image2.
        for (int i = 128; i < 256; i++) {
            for (int j = 0; j < 128; j++) {
                image2[i][j] = image[i - 128][j + 128];
            }
        }
    } else if (c == 3) {
        // Copy the bottom-left quarter to the corresponding position in image2.
        for (int i = 128; i < 256; i++) {
            for (int j = 0; j < 128; j++) {
                image2[i][j] = image[i][j];
            }
        }
    } else if (c == 4) {
        // Copy the bottom-right quarter to the corresponding position in image2.
        for (int i = 128; i < 256; i++) {
            for (int j = 0; j < 128; j++) {
                image2[i][j] = image[i][j + 128];
            }
        }
    }

    if (d == 1) {
        // Copy the top-left quarter to the corresponding position in image2.
        for (int i = 128; i < 256; i++) {
            for (int j = 128; j < 256; j++) {
                image2[i][j] = image[i - 128][j - 128];
            }
        }
    } else if (d == 2) {
        // Copy the top-right quarter to the corresponding position in image2.
        for (int i = 128; i < 256; i++) {
            for (int j = 128; j < 256; j++) {
                image2[i][j] = image[i - 128][j];
            }
        }
    } else if (d == 3) {
        // Copy the bottom-left quarter to the corresponding position in image2.
        for (int i = 128; i < 256; i++) {
            for (int j = 128; j < 256; j++) {
                image2[i][j] = image[i][j - 128];
            }
        }
    } else if (d == 4) {
        // Copy the bottom-right quarter to the corresponding position in image2.
        for (int i = 128; i < 256; i++) {
            for (int j = 128; j < 256; j++) {
                image2[i][j] = image[i][j];
            }
        }
    }

    // Copy the shuffled image back to the original image array.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = image2[i][j];
        }
    }
}
// Apply a blurring effect to the image using a simple averaging technique
void BLUR() {
    int blurring_level = 4;

    // Repeat blurring process multiple times (4 in this case)
    while (blurring_level--) {
        for (int i = 1; i < SIZE - 1; i++) {
            for (int j = 1; j < SIZE - 1; j++) {
                int sum = 0;

                // Calculate the average of neighboring pixel values
                for (int x = -1; x <= 1; x++) {
                    for (int y = -1; y <= 1; y++) {
                        sum += image[i + x][j + y];
                    }
                }

                // Update the pixel value with the calculated average
                image[i][j] = sum / 9;  // 9 is used for normalization
            }
        }
    }
}
// Crop a rectangular portion of the image specified by user-defined coordinates and dimensions
void CROP() {
    unsigned char image2[SIZE][SIZE];

    // Copy the original image to a temporary image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image2[i][j] = image[i][j];
        }
    }

    // Initialize the entire image to a white background
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = 255;
        }
    }

    // Prompt the user to enter the coordinates and dimensions for cropping
    cout << "\nEnter x, y, l and w (separated by spaces): \n"
            ">> ";
    int x, y, l, w;
    cin >> x >> y >> l >> w;

    // Copy the selected portion from the temporary image to the current image
    for (int i = x; i < l; i++) {
        for (int j = y; j < w; j++) {
            image[i][j] = image2[i][j];
        }
    }
}
// Skew the image either to the right (horizontal skew) or upwards (vertical skew) based on the user's choice
void SKEW() {
    // Check if the user wants to skew the image horizontally ('e') or vertically ('f')
    if (op == 'e') {
        cout << "\nEnter degree to skew Right: \n"
                ">> ";
    } else if (op == 'f') {
        cout << "\nEnter degree to skew Up: \n"
                ">> ";
    } else {
        cout << "\nInvalid Value! \n";
    }

    double deg, rad, angle, start, step;
    cin >> deg;
    rad = deg * (M_PI / 180.0);
    angle = tan(rad);
    int l = 256 / (1 + (1 / angle));

    // If skewing horizontally ('e'), create a temporary image to store the skewed content
    if (op == 'e') {
        unsigned char image2[SIZE][SIZE];

        // Initialize the temporary image with a white background
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                image2[i][j] = 255;
            }
        }

        // Skew the image to the right by repositioning pixels
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image2[i][(j * l) / SIZE] = image[i][j];
            }
        }

        start = 256.0 - l;
        step = start / 256.0;

        // Reposition the skewed content back to the original image
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j + int(start)] = image2[i][j];
            }
            start -= step;
        }

    }
        // If skewing vertically ('f'), create a temporary image to store the skewed content
    else if (op == 'f') {
        unsigned char image2[SIZE][SIZE];

        // Initialize the temporary image with a white background
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                image2[i][j] = 255;
            }
        }

        // Skew the image upwards by repositioning pixels
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image2[(i * l) / SIZE][j] = image[i][j];
                image[i][j] = 255;
            }
        }

        start = 256.0 - l;
        step = start / 256.0;

        // Reposition the skewed content back to the original image
        for (int i = 0; i < SIZE; i++) {
            for (int j = start; j < start + l; j++) {
                image[j][i] = image2[j - int(start)][i];
            }
            start -= step;
        }
    }
        // Handle invalid user input
    else {
        cout << "\nInvalid Value! \n";
    }
}
// Save the edited image to a file
void SAVE() {
    char imageFileName[100];
    string path = "\\edited images\\";
    cout << "\nPlease, Enter target file name for the edited image: \n"
            ">> ";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    path += imageFileName;
    char cwd[PATH_MAX];
    writeGSBMP(strcat (getcwd(cwd, sizeof(cwd)), path.c_str()), image);
    cout << "\nThe image has been saved in [edited images] folder! \n"
            "Thanks for using our program <3 \n";
}
// Check the user's input to apply the required operation
void APPLY() {
    cout <<"\nChoose which option to apply from the list: \n";
    cout << ">> "; cin >> op;
    if (op == '1') {
        BW();
    } else if (op == '2') {
        INVERT();
    } else if (op == '3') {
        MERGE();
    } else if (op == '4') {
        FLIB();
    } else if (op == '5') {
        DL();
    } else if (op == '6') {
        ROTATE();
    } else if (op == '7') {
        EDGES();
    } else if (op == '8') {
        ENLARGE();
    } else if (op == '9') {
        SHRINK();
    } else if (op == 'a') {
        MIRROR();
    } else if (op == 'b') {
        SHUFFLE();
    } else if (op == 'c') {
        BLUR();
    } else if (op == 'd') {
        CROP();
    } else if (op == 'e') {
        SKEW();
    } else if (op == 'f') {
        SKEW();
    } else if (op == 's') {
        SAVE();
        exit(0);
    } else if (op == '0') {
        cout << "\nBye <3 \n";
        exit(0);
    } else {
        cout << "\nInvalid Value! \n";
    }
}

int main(){
    LOAD();
    CHOOSE();
    // Infinte while loop to allow the user to do more than one change and stops when the user save or exit
    while (true) {
        APPLY();
    }
    // End the program
    return 0;
}