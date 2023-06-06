#ifndef FILTERS_H
#define FILTERS_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <atomic>
#include "ppm.h"

// FILTROS SINGLE-THREAD

void blackWhite(ppm &img);                              // implementado
void contrast(ppm &img, float contrast);                // implementado
void brightness(ppm &img, float b, int start, int end); // implementado
void shades(ppm &img, unsigned char shades);            // implementado
void merge(ppm &img1, ppm &img2, float alpha);          // implementado
void boxBlur(ppm &img);                                 // implementado
void edgeDetection(ppm &img);                           // implementado
void sharpen(ppm &img);                                 // implementado
void plain(ppm &img, unsigned char c);                  // implementado

// FILTROS MULTI-THREAD

void applyFilter();
void applyFilterMultiThread();
vector<ppm> threadsImageDivision(ppm &img, int threads);
void multiThreadBlackWhite(ppm &img, int threads);
void multiThreadContrast(ppm &img, float contrast, int threads);
void multiThreadBrightness(ppm &img, float b, int start, int end, int threads);
void multiThreadShades(ppm &img, unsigned char shades, int threads);
void multiThreadMerge(ppm &img1, ppm &img2, float alpha, int threads);
void multiThreadBoxBlur(ppm &img, int threads);
void multiThreadEdgeDetection(ppm &img, int threads);
void multiThreadSharpen(ppm &img, int threads);
void multiThreadPlain(ppm &img, unsigned char c, int threads);

#endif