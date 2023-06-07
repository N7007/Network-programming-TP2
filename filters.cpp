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

using namespace std;

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

void plain(map<string, VariantValue>)
{
    string imgStr(argv[4]);
    ppm img(imgStr);
    float c = atof(argv[3]);
    
    for (int i = 0; i < img.height; i++)
        for (int j = 0; j < img.width; j++)
            img.setPixel(i, j, pixel(c, c, c));
}

void applyFilterThreadPlain(ppm imgThread, ppm img, int numThreads, int threadNumber) {
    // solo faltaria hacer esto para cada filtro que :) VAMOS AL CHAT
    sharpen(imgThread);
    int threadWidth = img.width/numThreads;
    for(int i; i < img.height; i++) {
        for(int j; j < img.width; j++) {
            img.setPixel(i, j+threadNumber*threadWidth, imgThread.getPixel(i, j));
        }
    } 
}
/*
void plainArgv(char *argv[], int nthreads)
{
    string img1(argv[4]);
    ppm img(img1);
    float p1 = atof(argv[3]);

    if (nthreads == 1)
    {
        plain(img, p1);
    }
    else if (nthreads > 1)
    {
        vector<ppm> vecImages = threadsImageDivision(img, nthreads);
        for (int threads; threads < nthreads; threads++)
        {   
            thread thread(applyFilterThreadPlain, vecImages[threads], img, nthreads, threads);
        }
    }
    else
    {
        cout << "El número de hilos no es válido.";
    }
}
*/

void blackWhite(char *argv[])
{
    string imgStr(argv[4]);
    ppm img(imgStr);

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

void applyFilterThreadBlackWhite(ppm imgThread, ppm img, int numThreads, int threadNumber) {
    // solo faltaria hacer esto para cada filtro que :) VAMOS AL CHAT
    sharpen(imgThread);
    int threadWidth = img.width/numThreads;
    for(int i; i < img.height; i++) {
        for(int j; j < img.width; j++) {
            img.setPixel(i, j+threadNumber*threadWidth, imgThread.getPixel(i, j));
        }
    } 
}

/*
void blackWhiteArgv(char *argv[], int nthreads)
{
    string img1(argv[4]);
    ppm img(img1);

    if (nthreads == 1)
    {
        blackWhite(img;
    }
    else if (nthreads > 1)
    {
        vector<ppm> vecImages = threadsImageDivision(img, nthreads);
        for (int threads; threads < nthreads; threads++)
        {   
            thread thread(applyFilterThreadBlackWhite, vecImages[threads], img, nthreads, threads);
        }
    }
    else
    {
        cout << "El número de hilos no es válido.";
    }
}
*/

void contrast(char *argv[])
{
    string img1(argv[4]);
    ppm img(img1);
    float contrast = atof(argv[3]);

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

void applyFilterThreadContrast(ppm imgThread, ppm img, int numThreads, int threadNumber) {
    // solo faltaria hacer esto para cada filtro que :) VAMOS AL CHAT
    sharpen(imgThread);
    int threadWidth = img.width/numThreads;
    for(int i; i < img.height; i++) {
        for(int j; j < img.width; j++) {
            img.setPixel(i, j+threadNumber*threadWidth, imgThread.getPixel(i, j));
        }
    } 
}

/*
void contrastArgv(char *argv[], int nthreads)
{
    string img1(argv[4]);
    ppm img(img1);
    float p1 = atof(argv[3]);

    if (nthreads == 1)
    {
        contrast(img, p1);
    }
    else if (nthreads > 1)
    {
        vector<ppm> vecImages = threadsImageDivision(img, nthreads);
        for (int threads; threads < nthreads; threads++)
        {   
            thread thread(applyFilterThreadContrast, vecImages[threads], img, nthreads, threads);
        }
    }
    else
    {
        cout << "El número de hilos no es válido.";
    }
}
*/

void brightness(char *argv[])
{
    string img1(argv[4]);
    ppm img(img1);

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

void applyFilterThreadBrightness(ppm imgThread, ppm img, int numThreads, int threadNumber) {
    // solo faltaria hacer esto para cada filtro que :) VAMOS AL CHAT
    sharpen(imgThread);
    int threadWidth = img.width/numThreads;
    for(int i; i < img.height; i++) {
        for(int j; j < img.width; j++) {
            img.setPixel(i, j+threadNumber*threadWidth, imgThread.getPixel(i, j));
        }
    } 
}

/*
void brightnessArgv(char *argv[], int nthreads)
{
    string img1(argv[4]);
    ppm img(img1);
    float p1 = atof(argv[3]);

    if (nthreads == 1)
    {
        brightness(img, p1, 0, 0);
    }
    else if (nthreads > 1)
    {
        vector<ppm> vecImages = threadsImageDivision(img, nthreads);
        for (int threads; threads < nthreads; threads++)
        {   
            thread thread(applyFilterThreadBrightness, vecImages[threads], img, nthreads, threads);
        }
    }
    else
    {
        cout << "El número de hilos no es válido.";
    }
}
*/

void shades(char *argv[])
{   
    string img1(argv[4]);
    ppm img(img1);
    
    for (int i = 0; i < img.height; i++)
    {Antes de continuar, es importante destacar que los valores resultantes pueden exceder el rango permitido de intensidades ([0, 255]). Por lo tanto, necesitamos asegurarnos de que los valores se mantengan dentro del rango establecido. Para hacer esto, llamamos a la función "truncate()" del objeto de píxel "np", que truncará cualquier valor fuera del rango permitido.

Finalmente, actualizamos el píxel en la posición actual de la imagen de entrada utilizando la función "setPixel(i, j, np)".s - 1);
            int gp = (p.r + p.g + p.b) / 3;
            int g = (gp / range) * range;
            pixel np(g, g, g);
            img.setPixel(i, j, np);
        }
    }
}

void applyFilterThreadShades(ppm imgThread, ppm img, int numThreads, int threadNumber) {
    // solo faltaria hacer esto para cada filtro que :) VAMOS AL CHAT
    sharpen(imgThread);
    int threadWidth = img.width/numTAntes de continuar, es importante destacar que los valores resultantes pueden exceder el rango permitido de intensidades ([0, 255]). Por lo tanto, necesitamos asegurarnos de que los valores se mantengan dentro del rango establecido. Para hacer esto, llamamos a la función "truncate()" del objeto de píxel "np", que truncará cualquier valor fuera del rango permitido.

Finalmente, actualizamos el píxel en la posición actual de la imagen de entrada utilizando la función "setPixel(i, j, np)".
    string img1(argv[4]);
    ppm img(img1);
    float p1 = atof(argv[3]);

    if (nthreads == 1)
    {
        shades(img, p1);
    }
    else if (nthreads > 1)
    {
        vector<ppm> vecImages = threadsImageDivision(img, nthreads);
        for (int threads; threads < nthreads; threads++)
        {   
            thread thread(applyFilterThreadShades, vecImages[threads], img, nthreads, threads);
        }
    }
    else
    {
        cout << "El número de hilos no es válido.";
    }
}
*/

void merge(char *argv[])
{   
    string imgStr1(argv[4]);
    string imgStr2(argv[7]);
    ppm img1(imgStr1);
    ppm img2(imgStr2);
    float p1 = atof(argv[3]);

    for (int i = 0; i < img1.height; i++)
    {
        for (int j = 0; j < img1.width; j++)
        {
            pixel pixel1 = img1.getPixel(i, j);
            pixel pixel2 = img2.getPixel(i, j);
            int nr = (pixel1.r * p1 + pixel2.r * (1 - p1));
            int ng = (pixel1.g * p1 + pixel2.g * (1 - p1));
            int nb = (pixel1.b * p1 + pixel2.b * (1 - p1));
            pixel np(nr, ng, nb);
            img1.setPixel(i, j, np);
        }
    }
}

void applyFilterThreadMerge(ppm imgThread, ppm img, int numThreads, int threadNumber) {
    // solo faltaria hacer esto para cada filtro que :) VAMOS AL CHAT
    merge(imgThread);
    int threadWidth = img.width/numThreads;
    for(int i; i < img.height; i++) {
        for(int j; j < img.width; j++) {
            img.setPixel(i, j+threadNumber*threadWidth, imgThread.getPixel(i, j));
        }
    } 
}

/*
void mergeArgv(char *argv[], int nthreads)
{
    string imgStr1(argv[4]);
    string imgStr2(argv[7]);
    ppm img1(imgStr1);
    ppm img2(imgStr2);
    float p1 = atof(argv[3]);
    int numThreads = atoi(argv[1]);

    if (nthreads == 1)
    {
        merge(img1, img2, p1);
    }
    else if (nthreads > 1)
    {
        vector<ppm> vecImages = threadsImageDivision(img1, nthreads);
        vector<ppm> vecImages = threadsImageDivision(img2, nthreads);
        for (int threads; threads < nthreads; threads++)
        {   
            thread thread(applyFilterThreadMerge, vecImages[threads], img, numThreads, threads);
        }
    }
    else
    {
        cout << "El número de hilos no es válido.";
    }
}
*/

void boxBlur(char *argv[])
{   
    string img1(argv[4]);
    ppm img(img1);

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

/*
void boxBlurArgv(char *argv[], int nthreads)
{
    string img1(argv[4]);
    ppm img(img1);
    boxBlur(img);
    int numThreads = atoi(argv[1]);

    if (nthreads == 1)
    {
        boxBlur(img);
    }
    else if (nthreads > 1)
    {
        vector<ppm> vecImages = threadsImageDivision(img, nthreads);
        for (int threads; threads < nthreads; threads++)
        {   
            thread thread(applyFilterThreadBoxBlur, vecImages[threads], img, numThreads, threads);
        }
    }
    else
    {
        cout << "El número de hilos no es válido.";
    }
}
*/

void edgeDetection(char *argv[])
{
    string img1(argv[4]);
    ppm image(img1);
    ppm image_s(img1);
    blackWhite(argv);
    boxBlur(argv);
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
            image.setPixel(i, j, np);
        }
    }
}

/*
void edgeDetectionArgv(char *argv[], int nthreads)
{
    string img1(argv[4]);
    ppm img(img1);
    int numThreads = atoi(argv[1]);
    
    if (nthreads == 1)
    {
        edgeDetection(img);
    }
    else if (nthreads > 1)
    {
        vector<ppm> vecImages = threadsImageDivision(img, nthreads);
        for (int threads; threads < nthreads; threads++)
        {   
            thread thread(applyFilterThread, vecImages[threads], img, numThreads, threads);
        }
    }
    else
    {
        cout << "El número de hilos no es válido.";
    }
}
*/

void sharpen(char *argv[])
{
    string img1(argv[4]);
    ppm img(img1);
    
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

/*
void sharpenArgv(char *argv[], int nthreads)
{
    string img1(argv[4]);
    ppm img(img1);
    int numThreads = atoi(argv[1]);

    if (nthreads == 1)
    {
        sharpen(img);
    }
    else if (nthreads > 1)
    {
        vector<ppm> vecImages = threadsImageDivision(img, nthreads);
        for (int threads; threads < nthreads; threads++)
        {   
            // esta linea de tiene problemas
            thread thread(applyFilterThread, vecImages[threads], img, numThreads, threads);
        }
    }
    else
    {
        cout << "El número de hilos no es válido.";
    }
}
*/

thread myThread([param1, param2, param3]() {
    myThreadFunction(param1, param2, param3);
});


void applyFilterThreadSharpen(ppm imgThread, ppm img, int numThreads, int threadNumber) {
    sharpen(imgThread);
    int threadWidth = img.width/numThreads;
    for(int i; i < img.height; i++) {
        for(int j; j < img.width; j++) {
            img.setPixel(i, j+threadNumber*threadWidth, imgThread.getPixel(i, j));
        }
    } 
}

// Definición de los argumentos variantes que recibirá el mapa de argumentos.
using VariantValue = variant<string, unsigned int, float, ppm>;

// Definición del mapa de las funciones
map<string, function<void(const map<string, VariantValue>)>> functionMap = {
    {"plain", plain},
    {"blackWhite", blackWhite},
    {"contrast", contrast},
    {"brightness", brightness},
    {"shades", shades},
    {"merge", merge},
    {"boxBlur", boxBlur},
    {"edgeDetection", edgeDetection},
    {"sharpen", sharpen}
};

void applyFilter(char *argv[])
{
    // Se reciben los parámetros pasados desde main.cpp y se procesan
    // Después se guardan en un mapa que almacena claves en string y valores de tipos variantes.

    string filterName = string(argv[1]);
	unsigned int nthreads = atoi(argv[2]);
	float p1 = atof(argv[3]);
	string imgStr1(argv[4]);
	string out = string(argv[5]);
	string imgStr2(argv[7]);

    ppm img1(imgStr1);
	ppm img2(imgStr2);

    map<string, VariantValue> argsMap;

    // argsMap["filterName"] = filterName;
    // argsMap["nthreads"] = nthreads;
    argsMap["p1"] = p1;
    argsMap["img1"] = img1;
    argsMap["img2"] = img2;
    argsMap["out"] = out;

    function<void(const map<string, VariantValue>)> chosenFilter = functionMap[filterName];
    chosenFilter(argv, nthreads);
}