#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "filters.h"
#include <thread>  
#include <atomic>  
#include <cmath>

#define BLACK 0

using namespace std;

// Filtro plano como ejemplo
void plain(ppm& img, unsigned char c){
	for(int i = 0; i < img.height; i++)
		for(int j = 0; j < img.width; j++)			
			img.setPixel(i, j, pixel(c,c,c));

}

void blackWhite(ppm& img) {
    for(int i = 0; i < img.height; i++) {
        for(int j = 0; j < img.width; j++) {
            pixel p = img.getPixel(i, j);
            int g = (p.r + p.g + p.b)/3;
            pixel np(g, g, g);		
            img.setPixel(i, j, np);
        }
    }
}

int filtro(int c) {
    int x = (259*(c+255)) / (255*(259-c));
    return x;
}

void contrast(ppm& img, float contrast) {
    for(int i = 0; i < img.height; i++) {
        for(int j = 0; j < img.width; j++) {
            int r = filtro(img.getPixel(i, j).r - 128) + 128;
            int g = filtro(img.getPixel(i, j).g - 128) + 128;
            int b = filtro(img.getPixel(i, j).b - 128) + 128;
        }
    }
}

void brightness(ppm& img, float b, int start, int end) {
    for(int i = 0; i < img.height; i++) {
        for(int j = 0; j < img.width; j++) {
            pixel p = img.getPixel(i, j);
            int nr = p.r + 255*b;
            int ng = p.g + 255*b;
            int nb = p.b + 255*b;
            pixel np(nr, ng, nb);		
            img.setPixel(i, j, np.truncate());
        }
    }
}

void shades(ppm& img, unsigned char shades) {
    for(int i = 0; i < img.height; i++) {
        for(int j = 0; j < img.width; j++) {
            pixel p = img.getPixel(i, j);
            int range = 255/(shades-1);
            int gp = (p.r + p.g + p.b)/3;
            int g = (gp/range)*range;
            pixel np(g, g, g);		
            img.setPixel(i, j, np);
        }
    }
}

void merge(ppm& img1, ppm& img2, float alpha) {

    for(int i = 0; i < img1.height; i++) {
        for(int j = 0; j < img1.width; j++) {
            pixel p1 = img1.getPixel(i, j);
            pixel p2 = img2.getPixel(i, j);
            int nr = (p1.r*alpha+p2.r*(1-alpha));
            int ng = (p1.g*alpha+p2.g*(1-alpha));
            int nb = (p1.b*alpha+p2.b*(1-alpha));
            pixel np(nr,ng, nb);
            img1.setPixel(i, j, np);
        }
    }
}

void boxBlur(ppm &img) {
    float kernel[] = {1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9};
    for(int i = 1; i < img.height-1; i++) {
        for(int j = 1; j < img.width-1; j++) {
            pixel np;
            pixel pixels[] = {
                img.getPixel(i - 1, j - 1), img.getPixel(i - 1, j), img.getPixel(i - 1, j + 1),
                img.getPixel(i, j - 1), img.getPixel(i, j), img.getPixel(i, j + 1),
                img.getPixel(i + 1, j - 1), img.getPixel(i + 1, j), img.getPixel(i + 1, j + 1)
            };
            for(int k = 0; k < 9; k++) {
                pixels[k].mult(kernel[k]);
                np.addp(pixels[k]);
            }   
            //pixels[0].addp(pixels[1].addp(pixels[2].addp(pixels[3].addp(pixels[4].addp(pixels[5].addp(pixels[6].addp(pixels[7].addp(pixels[8]))))))));
            img.setPixel(i, j, np);
        }
    }
}

void edgeDetection(ppm &img) {
    blackWhite(img);
    boxBlur(img);
    ppm image = img;
    ppm image_s = img;
    int kernel[] = {1, 0, -1, 2, 0, -2, 1, 0, -1};
    int kernel_t[] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    for(int i = 1; i < img.height-1; i++) {
        for(int j = 1; j < img.width-1; j++) {
            pixel np;
            pixel temp;
            pixel temp_d;
            pixel pixels[] = {
                image.getPixel(i - 1, j - 1), image.getPixel(i - 1, j), image.getPixel(i - 1, j + 1),
                image.getPixel(i, j - 1), image.getPixel(i, j), image.getPixel(i, j + 1),
                image.getPixel(i + 1, j - 1), image.getPixel(i + 1, j), image.getPixel(i + 1, j + 1)
            };
            pixel pixels_s[] = {
                image_s.getPixel(i - 1, j - 1), image_s.getPixel(i - 1, j), image_s.getPixel(i - 1, j + 1),
                image_s.getPixel(i, j - 1), image_s.getPixel(i, j), image_s.getPixel(i, j + 1),
                image_s.getPixel(i + 1, j - 1), image_s.getPixel(i + 1, j), image_s.getPixel(i + 1, j + 1)
            };
            for(int k = 0; k < 9; k++) {
                pixels[k].mult(kernel[k]);
                temp.addp(pixels[k]);
                pixels_s[k].mult(kernel_t[k]);
                temp_d.addp(pixels_s[k]);
            }
            // /*   
            temp.r = temp.r * temp.r;
            temp.g = temp.g * temp.g;
            temp.b = temp.b * temp.b;
            temp_d.r = temp_d.r * temp_d.r;
            temp_d.g = temp_d.g * temp_d.g;
            temp_d.b = temp_d.b * temp_d.b;
            np = temp.addp(temp_d);
            np.r = sqrt(np.r);
            np.g = sqrt(np.g);
            np.b = sqrt(np.b);
            // /*
            img.setPixel(i, j, np);
        }
    }
}

void sharpen(ppm &img) {
    int kernel[] = {0, -1, 0, -1, 5, -1, 0, -1, 0};
    for(int i = 1; i < img.height-1; i++) {
        for(int j = 1; j < img.width-1; j++) {
            pixel np;
            pixel pixels[] = {
                img.getPixel(i - 1, j - 1), img.getPixel(i - 1, j), img.getPixel(i - 1, j + 1),
                img.getPixel(i, j - 1), img.getPixel(i, j), img.getPixel(i, j + 1),
                img.getPixel(i + 1, j - 1), img.getPixel(i + 1, j), img.getPixel(i + 1, j + 1)
            };
            for(int k = 0; k < 9; k++) {
                pixels[k].mult(kernel[k]);
                np.addp(pixels[k]);
            }
            np.truncate();
            img.setPixel(i, j, np);
        }
    }
}


// COMPLETAR :)


