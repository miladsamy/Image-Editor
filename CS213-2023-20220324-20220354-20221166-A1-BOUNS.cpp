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
unsigned char image[SIZE][SIZE][RGB];
char op;

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
void BW() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; k++){
                char average = (image[i][j][0] + image[i][j][1] + image[i][j][2]) / 3;
                image[i][j][0] = average;
                image[i][j][1] = average;
                image[i][j][2] = average;
            }
        }
    }
}
void INVERT() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; k++) {
                image[i][j][k] = 255 - image[i][j][k];
            }
        }
    }
}
void MERGE() {
        // load the second image
        char image2FileName[100];
        unsigned char image2[SIZE][SIZE][RGB];
        cout << "\nEnter name of image file to merge with (must be in [images] folder): \n"
                  ">> ";
        cin >> image2FileName;
        strcat(image2FileName, ".bmp");
        readRGBBMP(image2FileName, image2);

        // merge filter function
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = (image[i][j][k] + image2[i][j][k]) / 2;
                }
            }
        }
}
void FLIB() {
    cout << "\nFlip (h)orizontally or (v)ertically ? \n"
            ">> ";
    char flib; cin >> flib;
    if (flib == 'v') {
        // reverse each column in the 2D array (image)
        for (int i = 0; i < SIZE/2; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++){

                    swap(image[i][j][k], image[SIZE - i - 1][j][k]);
                }
            }
        }
    } else if (flib == 'h') {
        // reverse each row in the 2D array (image)
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE/2; j++){
                for (int k = 0; k < 3; k++){
                    swap(image[i][j][k], image[i][SIZE - j - 1][k]);
                }
            }
        }
    } else {
        cout << "\nInvalid Value! \n";
    }
}
void DL() {
    cout << "\nDo you want to (d)arken or (l)ighten ? \n"
            ">> ";
    char dl; cin >> dl;
    if (dl == 'd'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] /= 2;
                }
            }
        }
    } else if (dl == 'l'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
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
void ROTATE() {
    cout << "\nRotate (90), (180), (270) or (360) degrees ? \n"
            ">> ";
    int r; cin >> r;
    if (r == 90) {
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

    } else {
        cout << "\nInvalid Value! \n";
    }
}
void EDGES() {
    unsigned char image2[SIZE][SIZE][RGB];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; k++) {
                image2[i][j][k] = image[i][j][k];
            }
        }
    }

    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 1; j < SIZE - 1; j++) {
            for (int k = 0; k < 3; k++) {
                int x = image2[i][j + 1][k] - image2[i][j - 1][k];
                int y = image2[i + 1][j][k] - image2[i - 1][j][k];
                int magnitude = abs(x) + abs(y);
                image[i][j][k] = magnitude;
            }
        }
    }

    INVERT();
}
void ENLARGE() {
    cout << "\nWhich quarter to enlarge (1), (2), (3) or (4) ? \n"
            ">> ";
    int quarter; cin >> quarter;
    unsigned char image2[SIZE][SIZE][RGB];
    for (int i = 0;i < SIZE; i++) {
        for (int j = 0;j < SIZE; j++) {
            for (int k = 0; k < 3; k++) {
                image2[i][j][k] = image[i][j][k];
            }
        }
    }
    if (quarter == 1) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = image2[i / 2][j / 2][k];
                }
            }
        }
    } else if (quarter == 2) {
        for (int i = 0;i < SIZE;i++) {
            for (int j = 0;j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = image2[i / 2][j / 2 + 128][k];
                }
            }
        }
    } else if (quarter == 2) {
        for (int i = 0;i < SIZE;i++) {
            for (int j = 0;j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = image2[i / 2 + 128][j / 2][k];
                }
            }
        }
    } else if (quarter == 3) {
        for (int i = 0;i < SIZE;i++) {
            for (int j = 0;j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = image2[i / 2 + 128][j / 2][k];
                }
            }
        }
    } else if (quarter == 4) {
        for (int i = 0;i < SIZE;i++) {
            for (int j = 0;j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = image2[i / 2 + 128][j / 2 + 128][k];
                }
            }
        }
    } else {
        cout << "\nInvalid Value! \n";
    }
}
void SHRINK() {
    unsigned char image2[SIZE][SIZE][RGB];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; k++){
                image2[i][j][k] = image[i][j][k];
            }
        }
    }

    for (int i = 0;i < SIZE; i++) {
        for (int j = 0;j < SIZE; j++) {
            for (int k = 0; k < 3; k++){
                image[i][j][k] = 255;
            }
        }
    }

    string ratio;
    cout << "Shrink to (1/2), (1/3) or (1/4) ? \n"; cin >>  ratio ;

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
                    image[i/3][j/3][k]= image2[i][j][k];
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
void MIRROR() {
    cout << "\nMirror (l)eft, (r)ight, (u)pper, (d)own side ?\n"
            ">> ";
    char mirror; cin >> mirror;
    if (mirror == 'l') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][SIZE - j - 1][k] = image[i][j][k];
                }
            }
        }
    } else if (mirror == 'r') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = image[i][SIZE - j - 1][k];
                }
            }
        }
    } else if (mirror == 'u') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[SIZE - i - 1][j][k] = image[i][j][k];
                }
            }
        }
    } else if (mirror == 'd') {
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
void SHUFFLE() {
    unsigned char image2[SIZE][SIZE][RGB];
    cout << "\nEnter the new order of quarters (separated by spaces):\n"
            ">> ";
    int a, b, c, d; cin >> a >> b >> c >> d;

    if (a == 1) {
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 128; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][j][k] = image[i][j][k];
                }
            }
        }
    } else if (a == 2) {
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 128; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][j][k] = image[i][j + 128][k];
                }
            }
        }
    } else if (a == 3) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][j][k] = image[i + 128][j][k];
                }
            }
        }
    } else if (a == 4) {
        for (int i = 128; i < 256; i++) {
            for (int j = 128; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i - 128][j - 128][k] = image[i][j][k];
                }
            }
        }
    }

    if (b == 1) {
        for (int i = 0; i < 128; i++) {
            for (int j = 128; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][j][k] = image[i][j - 128][k];
                }
            }
        }
    } else if (b == 2) {
        for (int i = 0; i < 128; i++) {
            for (int j = 128; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][j][k] = image[i][j][k];
                }
            }
        }
    } else if (b == 3) {
        for (int i = 0; i < 128; i++) {
            for (int j = 128; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][j][k] = image[i + 128][j - 128][k];
                }
            }
        }
    } else if (b == 4) {
        for (int i = 0; i < 128; i++) {
            for (int j = 128; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][j][k] = image[i + 128][j][k];
                }
            }
        }
    }

    if (c == 1) {
        for (int i = 128; i < 256; i++) {
            for (int j = 0; j < 128; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][j][k] = image[i - 128][j][k];
                }
            }
        }
    } else if (c == 2) {
        for (int i = 128; i < 256; i++) {
            for (int j = 0; j < 128; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][j][k] = image[i - 128][j + 128][k];
                }
            }
        }
    } else if (c == 3) {
        for (int i = 128; i < 256; i++) {
            for (int j = 0; j < 128; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][j][k] = image[i][j][k];
                }
            }
        }
    } else if (c == 4) {
        for (int i = 128; i < 256; i++) {
            for (int j = 0; j < 128; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][j][k] = image[i][j + 128][k];
                }
            }
        }
    }

    if (d == 1) {
        for (int i = 128; i < 256; i++) {
            for (int j = 128; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][j][k] = image[i - 128][j - 128][k];
                }
            }
        }
    } else if (d == 2) {
        for (int i = 128; i < 256; i++) {
            for (int j = 128; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][j][k] = image[i - 128][j][k];
                }
            }
        }
    } else if (d == 3) {
        for (int i = 128; i < 256; i++) {
            for (int j = 128; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][j][k] = image[i][j - 128][k];
                }
            }
        }
    } else if (d == 4) {
        for (int i = 128; i < 256; i++) {
            for (int j = 128; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][j][k] = image[i][j][k];
                }
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; k++) {
                image[i][j][k] = image2[i][j][k];
            }
        }
    }
}
void BLUR() {
    int blurring_level = 4;
    while (blurring_level--){
        for (int i = 1; i < SIZE - 1; i++) {
            for (int j = 1; j < SIZE - 1; j++) {
                for (int k = 0; k < 3; k++) {
                    int sum = 0;
                    for (int x = -1; x <= 1; x++) {
                        for (int y = -1; y <= 1; y++) {
                                sum += image[i + x][j + y][k];
                        }
                    }
                    image[i][j][k] = sum / 9;
                }
            }
        }
    }
}
void CROP() {
    unsigned char image2[SIZE][SIZE][RGB];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for(int k=0;k<3;k++) {
                image2[i][j][k] = image[i][j][k];
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for(int k=0;k<3;k++) {
                image[i][j][k] = 255;
            }
        }
    }

    cout << "\nEnter x, y, l and w (separated by spaces): \n"
            ">> ";
    int x, y, l, w; cin >> x >> y >> l >> w;

    for (int i = x; i < l; i++) {
        for (int j = y; j < w; j++) {
            for(int k=0;k<3;k++) {
                image[i][j][k] = image2[i][j][k];
            }
        }
    }

}
void SKEW() {
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

    if (op == 'e') {
        unsigned char image2[SIZE][SIZE][RGB];

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][j][k] = 255;
                }
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][(j * l) / SIZE][k] = image[i][j][k];
                }
            }
        }

        start = 256.0 - l;
        step = start / 256.0;

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j + int(start)][k] = image2[i][j][k];
                }
            }
            start -= step;
        }
    } else if (op == 'f') {
        unsigned char image2[SIZE][SIZE][RGB];

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    image2[i][j][k] = 255;
                }
            }
        }

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

        for (int i = 0; i < SIZE; i++) {
            for (int j = start; j < start + l; j++) {
                for (int k = 0; k < 3; k++) {
                    image[j][i][k] = image2[j - int(start)][i][k];
                }
            }
            start -= step;
        }
    } else {
        cout << "\nInvalid Value! \n";
    }
}
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
    while (true) {
        APPLY();
    }
    return 0;
}