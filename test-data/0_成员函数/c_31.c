/*
0_成员函数.md
为struct Image添加rotate和flip成员函数
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WIDTH 100
#define MAX_HEIGHT 100

typedef struct {
    char pixels[MAX_HEIGHT][MAX_WIDTH];
    int width;
    int height;
} Image;

// Initialize an image with default values
void init_image(Image* img, int width, int height) {
    img->width = width;
    img->height = height;
    
    // Initialize with spaces
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            img->pixels[i][j] = ' ';
        }
    }
}

// Fill the image with a pattern
void fill_image(Image* img, char pattern) {
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            img->pixels[i][j] = pattern;
        }
    }
}

// Draw a simple pattern in the image
void draw_pattern(Image* img) {
    // Draw a diagonal line
    int min_dim = img->width < img->height ? img->width : img->height;
    for (int i = 0; i < min_dim; i++) {
        img->pixels[i][i] = '*';
    }
    
    // Draw a border
    for (int i = 0; i < img->width; i++) {
        img->pixels[0][i] = '#';
        img->pixels[img->height-1][i] = '#';
    }
    
    for (int i = 0; i < img->height; i++) {
        img->pixels[i][0] = '#';
        img->pixels[i][img->width-1] = '#';
    }
}

// Display the image
void display_image(Image* img) {
    printf("Image %dx%d:\n", img->width, img->height);
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            printf("%c", img->pixels[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Rotate the image 90 degrees clockwise
void rotate_image(Image* img) {
    char temp[MAX_HEIGHT][MAX_WIDTH];
    int new_width = img->height;
    int new_height = img->width;
    
    // Copy to temp with rotation
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            temp[j][new_width-1-i] = img->pixels[i][j];
        }
    }
    
    // Copy back to original
    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            img->pixels[i][j] = temp[i][j];
        }
    }
    
    // Update dimensions
    img->width = new_width;
    img->height = new_height;
}

// Flip the image horizontally
void flip_image(Image* img) {
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width / 2; j++) {
            char temp = img->pixels[i][j];
            img->pixels[i][j] = img->pixels[i][img->width - 1 - j];
            img->pixels[i][img->width - 1 - j] = temp;
        }
    }
}

int main() {
    Image img;
    
    // Initialize a 10x5 image
    init_image(&img, 10, 5);
    draw_pattern(&img);
    
    printf("Original Image:\n");
    display_image(&img);
    
    // Rotate the image
    rotate_image(&img);
    printf("After Rotation:\n");
    display_image(&img);
    
    // Flip the image horizontally
    flip_image(&img);
    printf("After Horizontal Flip:\n");
    display_image(&img);
    
    return 0;
}
