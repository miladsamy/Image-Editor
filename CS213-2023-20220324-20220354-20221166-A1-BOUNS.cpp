// FCAI – OOP – 2023 - Assignment 1 - BOUNS
// Program Name: Image Editor
// Marwan Osama Abd El-Azem Ibrahim >> 20220324
// Milad Samy Milad >> 20220354
// Menna Khaled Gamal >> 20221166

#include <iostream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
using namespace std;
unsigned char image[SIZE][SIZE][RGB]; // Declear the image as a 3d char array
char op; // Declear a char variable to decide which operation to apply

// Load the image to apply changes on it
void LOAD() {
    char imageFileName[100];
    string path = "\\images\\";
    cout << "\nWelcome to our Image Editor programme <3 \n";
    cout << "Please, Enter the name of the image to process (must be in [images] folder): \n"
            ">> ";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    path += imageFileName;
    char cwd[PATH_MAX];
    readRGBBMP(strcat (getcwd(cwd, sizeof(cwd)), path.c_str()), image);
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
// Convert the image to black and white (grayscale) by averaging the color channels
void BW() {
    // Iterate over each pixel in the image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Initialize a variable to store the average color value
            int average = (image[i][j][0] + image[i][j][1] + image[i][j][2]) / 3;

            // Set all three color channels (R, G, B) to the calculated average
            image[i][j][0] = average;
            image[i][j][1] = average;
            image[i][j][2] = average;
        }
    }
}
// Invert the colors of the image
void INVERT() {
    // Iterate over each pixel in the image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Iterate over each color channel (R, G, B)
            for (int k = 0; k < 3; k++) {
                // Invert the color channel by subtracting its value from 255
                image[i][j][k] = 255 - image[i][j][k];
            }
        }
    }
}
// Merge the current image with another image
void MERGE() {
    // Load the second image to merge
    char image2FileName[100];
    unsigned char image2[SIZE][SIZE][RGB];
    cout << "\nEnter the name of the image file to merge with (must be in [images] folder): \n"
            ">> ";
    cin >> image2FileName;

    // Append the file extension to the provided filename
    strcat(image2FileName, ".bmp");

    // Read the second image into the 'image2' array
    readRGBBMP(image2FileName, image2);

    // Merge the two images by taking the average of pixel values for each color channel
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; k++) {
                // Calculate the average by summing the corresponding pixel values from both images
                image[i][j][k] = (image[i][j][k] + image2[i][j][k]) / 2;
            }
        }
    }
}
// Flip the image either horizontally or vertically
void FLIB() {
    cout << "\nFlip (h)orizontally or (v)ertically ? \n"
            ">> ";
    char flib; cin >> flib;
    if (flib == 'v') {
        // Flip vertically: Reverse each column in the image for each color channel (R, G, B)
        for (int i = 0; i < SIZE/2; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++){
                    // Swap pixel values between the top and bottom halves of the image
                    swap(image[i][j][k], image[SIZE - i - 1][j][k]);
                }
            }
        }
    } else if (flib == 'h') {
        // Flip horizontally: Reverse each row in the image for each color channel (R, G, B)
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE/2; j++){
                for (int k = 0; k < 3; k++){
                    // Swap pixel values between the left and right halves of the image
                    swap(image[i][j][k], image[i][SIZE - j - 1][k]);
                }
            }
        }
    } else {
        cout << "\nInvalid Value! \n";
    }
}
// Darken or lighten the image based on user choice
void DL() {
    cout << "\nDo you want to (d)arken or (l)ighten ? \n"
            ">> ";
    char dl; cin >> dl;
    if (dl == 'd'){
        // Darken the image: Reduce the intensity of each color channel (R, G, B)
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] /= 2;
                }
            }
        }
    } else if (dl == 'l'){
        // Lighten the image: Increase the intensity of each color channel (R, G, B)
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    // Ensure the value stays within the valid range (0-255)
                    if (image[i][j][k] < 200) {
                        image[i][j][k] += 50;
                    }
                }
            }
        }
    } else {
        cout << "\nInvalid Value! \n";
    }
}
// Rotate the image by a specified angle (90, 180, 270 degrees) or do a full 360-degree rotation
void ROTATE() {
    cout << "\nRotate (90), (180), (270) or (360) degrees ? \n"
            ">> ";
    int r; cin >> r;
    if (r == 90) {
        // Rotate 90 degrees clockwise: Swap rows and columns, then reverse the rows
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    swap(image[i][j][k], image[j][i][k]);
                }
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                for (int k = 0; k < 3; k++) {
                    swap(image[j][i][k], image[SIZE - j - 1][i][k]);
                }
            }
        }
    } else if (r == 180) {
        // Rotate 180 degrees: Reverse rows and columns
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                for (int k = 0; k < 3; k++) {
                    swap(image[i][j][k], image[i][SIZE - j - 1][k]);
                }
            }
        }
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    swap(image[i][j][k], image[SIZE - i - 1][j][k]);
                }
            }
        }
    } else if (r == 270) {
        // Rotate 270 degrees clockwise: Swap rows and columns, then reverse the columns
        for (int i = 0; i < SIZE; i++) {
            for (int j = i; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    swap(image[i][j][k], image[j][i][k]);
                }
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                for (int k = 0; k < 3; k++) {
                    swap(image[i][j][k], image[i][SIZE - j - 1][k]);
                }
            }
        }
    } else if (r == 360) {
        // A full 360-degree rotation does not require any changes
    } else {
        cout << "\nInvalid Value! \n";
    }
}
// Detect edges in the image using the Sobel operator and create an edge map
void EDGES() {
    // Create a copy of the original image
    unsigned char image2[SIZE][SIZE][RGB];

    // Copy the original image's pixel values into the new image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; k++) {
                image2[i][j][k] = image[i][j][k];
            }
        }
    }

    // Apply the Sobel operator to detect edges and create an edge map
    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 1; j < SIZE - 1; j++) {
            for (int k = 0; k < 3; k++) {
                // Calculate gradient in the x and y directions
                int x = image2[i][j + 1][k] - image2[i][j - 1][k];
                int y = image2[i + 1][j][k] - image2[i - 1][j][k];

                // Compute the magnitude of the gradient
                int magnitude = abs(x) + abs(y);
                image[i][j][k] = magnitude;
            }
        }
    }

    // Invert the colors to enhance the edges
    INVERT();
}
// Enlarge one of the quarters of the image (1, 2, 3, or 4) and replace the original image
void ENLARGE() {
    cout << "\nWhich quarter to enlarge (1), (2), (3) or (4) ? \n"
            ">> ";
    int quarter;
    cin >> quarter;

    // Create a copy of the original image
    unsigned char image2[SIZE][SIZE][RGB];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; k++) {
                image2[i][j][k] = image[i][j][k];
            }
        }
    }

    // Enlarge the selected quarter based on the user's choice
    if (quarter == 1) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = image2[i / 2][j / 2][k];
                }
            }
        }
    } else if (quarter == 2) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = image2[i / 2][j / 2 + 128][k];
                }
            }
        }
    } else if (quarter == 3) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = image2[i / 2 + 128][j / 2][k];
                }
            }
        }
    } else if (quarter == 4) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = image2[i / 2 + 128][j / 2 + 128][k];
                }
            }
        }
    } else {
        cout << "\nInvalid Value! \n";
    }
}
// Shrink the image to 1/2, 1/3, or 1/4 of its original size based on user input
void SHRINK() {
    // Create a copy of the original image
    unsigned char image2[SIZE][SIZE][RGB];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; k++) {
                image2[i][j][k] = image[i][j][k];
            }
        }
    }

    // Set the entire original image to white (255)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; k++){
                image[i][j][k] = 255;
            }
        }
    }

    // Prompt the user to choose a shrink ratio: 1/2, 1/3, or 1/4
    string ratio;
    cout << "Shrink to (1/2), (1/3) or (1/4) ? \n";
    cin >>  ratio ;

    // Shrink the image based on the selected ratio
    if (ratio == "1/2") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++){
                    image[i/2][j/2][k] = image2[i][j][k];
                }
            }
        }
    } else if (ratio == "1/3") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++){
                    image[i/3][j/3][k] = image2[i][j][k];
                }
            }
        }
    } else if (ratio == "1/4") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++){
                    image[i/4][j/4][k] = image2[i][j][k];
                }
            }
        }
    }
}
// Mirror the image either left, right, upper, or down based on user input
void MIRROR() {
    // Prompt the user to choose the mirroring direction (left, right, upper, or down)
    cout << "\nMirror (l)eft, (r)ight, (u)pper, (d)own side ?\n";
    char mirror; cin >> mirror;

    // Apply the selected mirroring operation to the image
    if (mirror == 'l') {
        // Mirror the image to the left
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][SIZE - j - 1][k] = image[i][j][k];
                }
            }
        }
    } else if (mirror == 'r') {
        // Mirror the image to the right
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = image[i][SIZE - j - 1][k];
                }
            }
        }
    } else if (mirror == 'u') {
        // Mirror the image to the upper side
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[SIZE - i - 1][j][k] = image[i][j][k];
                }
            }
        }
    } else if (mirror == 'd') {
        // Mirror the image to the down side
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = image[SIZE - i - 1][j][k];
                }
            }
        }
    } else {
        cout << "\nInvalid Value! \n";
    }
}
// Dividing the image into 4 quarters and rearrange them with the order that user want
void SHUFFLE() {
    // Initialize a new 2D array to store the shuffled image.
    unsigned char image2[SIZE][SIZE][RGB];

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
                for(int k=0;k<3;k++) {
                    image2[i][j][k] = image[i][j][k];
                }
            }
        }
    } else if (a == 2) {
        // Copy the top-right quarter to the corresponding position in image2.
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 128; j++) {
                for(int k=0;k<3;k++) {
                    image2[i][j][k] = image[i][j + 128][k];
                }
            }
        }
    } else if (a == 3) {
        // Copy the bottom-left quarter to the corresponding position in image2.
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for(int k=0;k<3;k++) {
                    image2[i][j][k] = image[i + 128][j][k];
                }
            }
        }
    } else if (a == 4) {
        // Copy the bottom-right quarter to the corresponding position in image2.
        for (int i = 128; i < 256; i++) {
            for (int j = 128; j < 256; j++) {
                for(int k=0;k<3;k++) {
                    image2[i - 128][j - 128][k] = image[i][j][k];
                }
            }
        }
    }

    if (b == 1) {
        // Copy top-left quarter to a different position in image2.
        for (int i = 0; i < 128; i++) {
            for (int j = 128; j < 256; j++) {
                for(int k=0;k<3;k++) {
                    image2[i][j][k] = image[i][j - 128][k];
                }
            }
        }
    } else if (b == 2) {
        // Copy the top-right quarter to the corresponding position in image2.
        for (int i = 0; i < 128; i++) {
            for (int j = 128; j < 256; j++) {
                for(int k=0;k<3;k++) {
                    image2[i][j][k] = image[i][j][k];
                }
            }
        }
    } else if (b == 3) {
        // Copy the bottom-left quarter to the corresponding position in image2.
        for (int i = 0; i < 128; i++) {
            for (int j = 128; j < 256; j++) {
                for(int k=0;k<3;k++) {
                    image2[i][j][k] = image[i + 128][j - 128][k];
                }
            }
        }
    } else if (b == 4) {
        // Copy the bottom-right quarter to the corresponding position in image2.
        for (int i = 0; i < 128; i++) {
            for (int j = 128; j < 256; j++) {
                for(int k=0;k<3;k++) {
                    image2[i][j][k] = image[i + 128][j][k];
                }
            }
        }
    }

    if (c == 1) {
        // Copy the top-left quarter to the corresponding position in image2.
        for (int i = 128; i < 256; i++) {
            for (int j = 0; j < 128; j++) {
                for(int k=0;k<3;k++) {
                    image2[i][j][k] = image[i - 128][j][k];
                }
            }
        }
    } else if (c == 2) {
        // Copy the top-right quarter to the corresponding position in image2.
        for (int i = 128; i < 256; i++) {
            for (int j = 0; j < 128; j++) {
                for(int k=0;k<3;k++) {
                    image2[i][j][k] = image[i - 128][j + 128][k];
                }
            }
        }
    } else if (c == 3) {
        // Copy the bottom-left quarter to the corresponding position in image2.
        for (int i = 128; i < 256; i++) {
            for (int j = 0; j < 128; j++) {
                for(int k=0;k<3;k++) {
                    image2[i][j][k] = image[i][j][k];
                }
            }
        }
    } else if (c == 4) {
        // Copy the bottom-right quarter to the corresponding position in image2.
        for (int i = 128; i < 256; i++) {
            for (int j = 0; j < 128; j++) {
                for(int k=0;k<3;k++) {
                    image2[i][j][k] = image[i][j + 128][k];
                }
            }
        }
    }

    if (d == 1) {
        // Copy the top-left quarter to the corresponding position in image2.
        for (int i = 128; i < 256; i++) {
            for (int j = 128; j < 256; j++) {
                for(int k=0;k<3;k++) {
                    image2[i][j][k] = image[i - 128][j - 128][k];
                }
            }
        }
    } else if (d == 2) {
        // Copy the top-right quarter to the corresponding position in image2.
        for (int i = 128; i < 256; i++) {
            for (int j = 128; j < 256; j++) {
                for(int k=0;k<3;k++) {
                    image2[i][j][k] = image[i - 128][j][k];
                }
            }
        }
    } else if (d == 3) {
        // Copy the bottom-left quarter to the corresponding position in image2.
        for (int i = 128; i < 256; i++) {
            for (int j = 128; j < 256; j++) {
                for(int k=0;k<3;k++) {
                    image2[i][j][k] = image[i][j - 128][k];
                }
            }
        }
    } else if (d == 4) {
        // Copy the bottom-right quarter to the corresponding position in image2.
        for (int i = 128; i < 256; i++) {
            for (int j = 128; j < 256; j++) {
                for(int k=0;k<3;k++) {
                    image2[i][j][k] = image[i][j][k];
                }
            }
        }
    }

    // Copy the shuffled image back to the original image array.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for(int k=0;k<3;k++) {
                image[i][j][k] = image2[i][j][k];
            }
        }
    }
}
// Apply a blurring effect to the image by averaging pixel values
void BLUR() {
    // Initialize the blurring level to 4
    int blurring_level = 4;

    // Repeatedly apply blurring to the image (blurring_level times)
    while (blurring_level--) {
        // Iterate over the pixels in the image, excluding the border
        for (int i = 1; i < SIZE - 1; i++) {
            for (int j = 1; j < SIZE - 1; j++) {
                // Iterate over the color channels (R, G, B)
                for (int k = 0; k < 3; k++) {
                    int sum = 0;

                    // Compute the sum of pixel values in a 3x3 neighborhood
                    for (int x = -1; x <= 1; x++) {
                        for (int y = -1; y <= 1; y++) {
                            sum += image[i + x][j + y][k];
                        }
                    }

                    // Update the pixel value by taking the average of the neighborhood
                    image[i][j][k] = sum / 9;
                }
            }
        }
    }
}
// Crop a rectangular region of the image
void CROP() {
    // Create a temporary image (image2) to store a copy of the original image
    unsigned char image2[SIZE][SIZE][RGB];

    // Copy the original image's pixel values to image2
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; k++) {
                image2[i][j][k] = image[i][j][k];
            }
        }
    }

    // Set all pixel values in the original image to white (255) to clear it
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; k++) {
                image[i][j][k] = 255;
            }
        }
    }

    // Prompt the user to enter coordinates for cropping (x, y, l, w)
    cout << "\nEnter x, y, l and w (separated by spaces):\n>> ";
    int x, y, l, w;
    cin >> x >> y >> l >> w;

    // Copy the cropped region from image2 back to the original image
    for (int i = x; i < l; i++) {
        for (int j = y; j < w; j++) {
            for (int k = 0; k < 3; k++) {
                image[i][j][k] = image2[i][j][k];
            }
        }
    }
}
// Skew the image either to the right or up based on the value of 'op'
void SKEW() {
    // Prompt the user to enter the degree of skew
    if (op == 'e') {
        cout << "\nEnter degree to skew Right:\n>> ";
    } else if (op == 'f') {
        cout << "\nEnter degree to skew Up:\n>> ";
    } else {
        cout << "\nInvalid Value!\n";
    }

    double deg, rad, angle, start, step;
    cin >> deg;

    // Calculate the skew angle in radians
    rad = deg * (M_PI / 180.0);
    angle = tan(rad);

    // Calculate the length of the skew (l)
    int l = 256 / (1 + (1 / angle));

    if (op == 'e') {
        // Create a temporary image (image2) filled with white (255) pixels
        unsigned char image2[SIZE][SIZE][RGB];

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][j][k] = 255;
                }
            }
        }

        // Apply the skew effect to the image by repositioning pixels
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][(j * l) / SIZE][k] = image[i][j][k];
                }
            }
        }

        start = 256.0 - l;
        step = start / 256.0;

        // Shift the skewed image back into the original image
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j + int(start)][k] = image2[i][j][k];
                }
            }
            start -= step;
        }
    } else if (op == 'f') {
        // Create a temporary image (image2) filled with white (255) pixels
        unsigned char image2[SIZE][SIZE][RGB];

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][j][k] = 255;
                }
            }
        }

        // Apply the skew effect to the image by repositioning pixels
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[(i * l) / SIZE][j][k] = image[i][j][k];
                    image[i][j][k] = 255;
                }
            }
        }

        start = 256.0 - l;
        step = start / 256.0;

        // Shift the skewed image back into the original image
        for (int i = 0; i < SIZE; i++) {
            for (int j = start; j < start + l; j++) {
                for (int k = 0; k < 3; k++) {
                    image[j][i][k] = image2[j - int(start)][i][k];
                }
            }
            start -= step;
        }
    } else {
        cout << "\nInvalid Value!\n";
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
    writeRGBBMP(strcat (getcwd(cwd, sizeof(cwd)), path.c_str()), image);
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