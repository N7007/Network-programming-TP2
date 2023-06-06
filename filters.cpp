#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "filters.h"
#include "ppm.h"
#include <thread>
#include <atomic>
#include <cmath>
#include <map>
#include <functional>
#include <variant>

#include "filters.h"
#include "ppm.h"

#define BLACK 0

using namespace std;

// Filtro plano como ejemplo
void plain(ppm &img, unsigned char c)
{
    for (int i = 0; i < img.height; i++)
        for (int j = 0; j < img.width; j++)
            img.setPixel(i, j, pixel(c, c, c));
}

void plain(char argv[])
{
    string img1(argv[4]);
    ppm img(img1);
    float p1 = atof(argv[3]);
    plain(img, p1);
}

void blackWhite(ppm &img)
{
    for (int i = 0; i < img.height; i++)
    {
        for (int j = 0; j < img.width; j++)
        {
            pixel p = img.getPixel(i, j);
            int g = (p.r + p.g + p.b) / 3;
            pixel np(g, g, g);
            img.setPixel(i, j, np);
        }
    }
}

void blackWhite(char *argv[])
{
    string img1(argv[4]);
    ppm img(img1);
    blackWhite(img);
}

void contrast(ppm &img, float contrast)
{
    float c = (259.f * (contrast + 255.f)) / (255.f * (259.f - contrast));
    for (int i = 0; i < img.height; i++)
    {
        for (int j = 0; j < img.width; j++)
        {
            pixel p = img.getPixel(i, j);
            int r = c * (p.r - 128) + 128;
            int g = c * (p.g - 128) + 128;
            int b = c * (p.b - 128) + 128;
            pixel np(r, g, b);
            img.setPixel(i, j, np.truncate());
        }
    }
}

void contrast(char *argv[])
{
    string img1(argv[4]);
    ppm img(img1);
    float p1 = atof(argv[3]);
    contrast(img, p1);
}

void brightness(ppm &img, float b, int start, int end)
{
    for (int i = 0; i < img.height; i++)
    {
        for (int j = 0; j < img.width; j++)
        {
            pixel p = img.getPixel(i, j);
            int nr = p.r + 255 * b;
            int ng = p.g + 255 * b;
            int nb = p.b + 255 * b;
            pixel np(nr, ng, nb);
            img.setPixel(i, j, np.truncate());
        }
    }
}

void brightness(char *argv[])
{
    string img1(argv[4]);
    ppm img(img1);
    float p1 = atof(argv[3]);
    brightness(img, p1, 0, 0);
}

void shades(ppm &img, unsigned char shades)
{
    for (int i = 0; i < img.height; i++)
    {
        for (int j = 0; j < img.width; j++)
        {
            pixel p = img.getPixel(i, j);
            int range = 255 / (shades - 1);
            int gp = (p.r + p.g + p.b) / 3;
            int g = (gp / range) * range;
            pixel np(g, g, g);
            img.setPixel(i, j, np);
        }
    }
}

void shades(char *argv[])
{
    string img1(argv[4]);
    ppm img(img1);
    float p1 = atof(argv[3]);
    shades(img, p1);
}

void merge(ppm &img1, ppm &img2, float alpha)
{

    for (int i = 0; i < img1.height; i++)
    {
        for (int j = 0; j < img1.width; j++)
        {
            pixel p1 = img1.getPixel(i, j);
            pixel p2 = img2.getPixel(i, j);
            int nr = (p1.r * alpha + p2.r * (1 - alpha));
            int ng = (p1.g * alpha + p2.g * (1 - alpha));
            int nb = (p1.b * alpha + p2.b * (1 - alpha));
            pixel np(nr, ng, nb);
            img1.setPixel(i, j, np);
        }
    }
}

void merge(char *argv[])
{
    string imgStr1(argv[4]);
    string imgStr2(argv[7]);
    ppm img1(imgStr1);
    ppm img2(imgStr2);
    float p1 = atof(argv[3]);
    merge(img1, img2, p1);
}

void boxBlur(ppm &img)
{
    float kernel[] = {1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9};
    for (int i = 1; i < img.height - 1; i++)
    {
        for (int j = 1; j < img.width - 1; j++)
        {
            pixel np;
            pixel pixels[] = {
                img.getPixel(i - 1, j), img.getPixel(i - 1, j + 1),
                img.getPixel(i, j - 1), img.getPixel(i, j), img.getPixel(i, j + 1),
                img.getPixel(i + 1, j - 1), img.getPixel(i + 1, j), img.getPixel(i + 1, j + 1)};
            for (int k = 0; k < 9; k++)
            {
                pixels[k].mult(kernel[k]);
                np.addp(pixels[k]);
            }
            // pixels[0].addp(pixels[1].addp(pixels[2].addp(pixels[3].addp(pixels[4].addp(pixels[5].addp(pixels[6].addp(pixels[7].addp(pixels[8]))))))));
            img.setPixel(i, j, np);
        }
    }
}

void boxBlur(char *argv[])
{
    string img1(argv[4]);
    ppm img(img1);
    boxBlur(img);
}

void edgeDetection(ppm &img)
{
    blackWhite(img);
    boxBlur(img);
    ppm image = img;
    ppm image_s = img;
    int kernel[] = {1, 0, -1, 2, 0, -2, 1, 0, -1};
    int kernel_t[] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    for (int i = 1; i < img.height - 1; i++)
    {
        for (int j = 1; j < img.width - 1; j++)
        {
            pixel np;
            pixel temp;
            pixel temp_d;
            pixel pixels[] = {
                image.getPixel(i - 1, j - 1), image.getPixel(i - 1, j), image.getPixel(i - 1, j + 1),
                image.getPixel(i, j - 1), image.getPixel(i, j), image.getPixel(i, j + 1),
                image.getPixel(i + 1, j - 1), image.getPixel(i + 1, j), image.getPixel(i + 1, j + 1)};
            pixel pixels_s[] = {
                image_s.getPixel(i - 1, j - 1), image_s.getPixel(i - 1, j), image_s.getPixel(i - 1, j + 1),
                image_s.getPixel(i, j - 1), image_s.getPixel(i, j), image_s.getPixel(i, j + 1),
                image_s.getPixel(i + 1, j - 1), image_s.getPixel(i + 1, j), image_s.getPixel(i + 1, j + 1)};
            for (int k = 0; k < 9; k++)
            {
                pixels[k].mult(kernel[k]);
                temp.addp(pixels[k]);
                pixels_s[k].mult(kernel_t[k]);
                temp_d.addp(pixels_s[k]);
            }
            // /*
            temp.r = temp.r * temp.r;
            temp_d.r = temp_d.r * temp_d.r;
            np = temp.addp(temp_d);
            int sqrt_r = sqrt(np.r);
            np.r = sqrt_r;
            np.g = sqrt_r;
            np.b = sqrt_r;
            // /*
            img.setPixel(i, j, np);
        }
    }
}

void edgeDetection(char *argv[])
{
    string img1(argv[4]);
    ppm img(img1);
    edgeDetection(img);
}

void sharpen(ppm &img)
{
    int kernel[] = {0, -1, 0, -1, 5, -1, 0, -1, 0};
    for (int i = 1; i < img.height - 1; i++)
    {
        for (int j = 1; j < img.width - 1; j++)
        {
            pixel np;
            pixel pixels[] = {
                img.getPixel(i - 1, j - 1), img.getPixel(i - 1, j), img.getPixel(i - 1, j + 1),
                img.getPixel(i, j - 1), img.getPixel(i, j), img.getPixel(i, j + 1),
                img.getPixel(i + 1, j - 1), img.getPixel(i + 1, j), img.getPixel(i + 1, j + 1)};
            for (int k = 0; k < 9; k++)
            {
                pixels[k].mult(kernel[k]);
                np.addp(pixels[k]);
            }
            np.truncate();
            img.setPixel(i, j, np);
        }
    }
}

void sharpen(char *argv[])
{
    string img1(argv[4]);
    ppm img(img1);
    sharpen(img);
}

// // Mapa de las funciones

// // first create a function template
// map<string, function<void(char[])>> filtersMap;

// filtersMap["plain"] = plain;

// // Definición del mapa con funciones
// std::map<std::string, FuncPtr> functionMap;

map<string, std::function<void(char *argv[])>> functionMap = {
        {"plain", plain}
        /*
        {"blackWhite", blackWhite},
        {"contrast", contrast},
        {"brightness", brightness},
        {"shades", shades},
        {"merge", merge},
        {"boxBlur", boxBlur},
        {"edgeDetection", edgeDetection},
        {"sharpen", sharpen}
        */
};

// void applyFilter(string filterName, ppm &img1, ppm img2, int firstParameter)
void applyFilter(char *argv[], map<string, function<void()>> functionMap)  //map<string, function<void()>> functionMap
{
    function<void(char*[])> choosenFilter = functionMap[argv[1]];
    choosenFilter(argv[]);
}

void applyFilterMultiThread(string filterName, ppm &img, ppm img2, int p1)
{
    applyFilter(filterName, img, img2, p1)
}

// Multi-Threads

vector<ppm> threadsImageDivision(ppm &img, int threads)
{
    int pixelsPerThread = img.size / threads;
    int threadWidth = img.width / threads;
    int restPixel = img.size % threads;
    vector<ppm> vecImages;

    for (int thread; thread < threads; thread++)
    {
        ppm threadImage(threadWidth, img.height);

        int initialPosX = threadWidth * thread;
        for (int y; y < img.height; y++)
        {
            for (int x = initialPosX; x < initialPosX + threadWidth, x < threadWidth; x++)
            {
                threadImage.setPixel(y, x - initialPosX, img.getPixel(y, x));
            }
        }
        vecImages.push_back(threadImage);
    }
    return vecImages;
}

void multiThreadBlackWhite(ppm &img, int thread)
{
}

void multiThreadContrast(ppm &img, float contrast, int threads)
{
    vector<ppm> vecImages = threadsImageDivision(img, threads);
    for (int image; image < vecImages.size(); image++)
    {
        blackWhite(vecImages[image]);
    }
}
void multiThreadBrightness(ppm &img, float b, int start, int end, int threads)
{
}
void multiThreadShades(ppm &img, unsigned char shades, int threads)
{
}
void multiThreadMerge(ppm &imgOne, ppm &imgTwo, float alpha, int threads)
{
}
void multiThreadBoxBlur(ppm &img, int threads) {}
void multiThreadEdgeDetection(ppm &img, int threads) {}
void multiThreadSharpen(ppm &img, int threads) {}
void multiThreadPlain(ppm &img, unsigned char c, int threads) {}