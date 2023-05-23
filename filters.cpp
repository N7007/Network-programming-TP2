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
            pixel p;
            p = img.getPixel(i, j);
            int g = (p.r + p.g + p.b)/3;		
            img.setPixel(i, j, pixel(g, g, g));
        }
    }
}



// COMPLETAR :)


