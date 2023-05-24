#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "filters.h"
#include <thread>  
#include <atomic>  

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

void contrast(ppm& img, float contrast) {

}

void brightness(ppm& img, float b, int start, int end) {

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



// COMPLETAR :)


