#ifndef FILTERS_H
#define FILTERS_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "ppm.h"
#include <atomic>


// FILTROS SINGLE-THREAD

void blackWhite(ppm& img); //implementado
void contrast(ppm& img, float contrast); //implementado
void brightness(ppm& img, float b, int start, int end); //implementado
void shades(ppm& img, unsigned char shades); //implementado
void merge(ppm& img1, ppm& img2, float alpha); //implementado
void boxBlur(ppm &img); //implementado
void edgeDetection(ppm &img); //implementado
void sharpen(ppm &img); //implementado
void plain(ppm &img, unsigned char c); //implementado
//void frame(ppm& img, pixel color, int x);
//void zoom(ppm &img, ppm &img_zoomed, int n);

// FILTROS MULTI-THREAD

// Completar :)

#endif