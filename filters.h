#ifndef FILTERS_H
#define FILTERS_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <atomic>
#include "ppm.h"

// FILTROS SINGLE-THREAD

// void applyFilter(char *argv[], int nthreads);
// void blackWhite(ppm &img);                              // implementado
// void contrast(ppm &img, float contrast);                // implementado
// void brightness(ppm &img, float b, int start, int end); // implementado
// void shades(ppm &img, unsigned char shades);            // implementado
// void merge(ppm &img1, ppm &img2, float alpha);          // implementado
// void boxBlur(ppm &img);                                 // implementado
// void edgeDetection(ppm &img);                           // implementado
// void sharpen(ppm &img);                                 // implementado
// void plain(ppm &img, unsigned char c);                  // implementado


void applyFilter(char *argv[], int nthreads);
void blackWhite(char *argv[]);                           
void contrast(char *argv[]);               
void brightness(char *argv[]);
void shades(char *argv[]);            
void merge(char *argv[]);         
void boxBlur(char *argv[]);                               
void edgeDetection(char *argv[]);                        
void sharpen(char *argv[]);                              
void plain(char *argv[]);

// DIVIDE LA IMAGEN EN BASE A LA CANTIDAD DE THREADS

vector<ppm> threadsImageDivision(ppm &img, int threads);


#endif