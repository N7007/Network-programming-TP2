#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "filters.h" // Incluye el archivo de encabezado "filters.h"
#include <thread>
#include <unistd.h>
#include <fstream>
#include <any>

#define ONE_OVER_BILLION 1E-9 // Define una constante con el valor 1E-9 (1 dividido por mil millones)

using namespace std;

// El siguiente es un template básico que pueden usar como base

int main(int argc, char *argv[])
{

	// Asumimos que los filtros sin p1 se escriben primero (por lo tanto, el primer p1 no es nulo)
	// Asumimos que Zoom no se puede encadenar

	if (string(argv[1]) == "-help")
	{
		cout << "Uso: ./main <filtro> <nthreads> <[p1]> <img1> <custom_output> <[p2]> <img2>" << endl;
		return 0;
	}

	string filter = string(argv[1]); 		// Almacena el primer argumento en una variable de tipo string llamada "filter"
	unsigned int nthreads = atoi(argv[2]);	// Convierte el segundo argumento a un entero sin signo y lo almacena en "n"
	float p1 = atof(argv[3]);		 		// Convierte el tercer argumento a un número de punto flotante y lo almacena en "p1"
	string img1(argv[4]);			 		// Crea un objeto de tipo string llamado "img1" inicializado con el cuarto argumento
	string img2(argv[7]);
	string out = string(argv[5]); // Crea un objeto de tipo string llamado "out" inicializado con el quinto argumento

	ppm img(img1); // Crea un objeto de tipo "ppm" llamado "img" y lo inicializa con el valor de "img1"
	ppm img_2(img2);

	cout << "Aplicando filtros" << endl;

	if (nthreads = 1) {
		if (filter == "plain")
		{
			plain(img, (unsigned char)p1); // Aplica el filtro "plain" a la imagen utilizando el valor de "p1" como parámetro
		}
		else if (filter == "blackWhite")
		{
			blackWhite(img);
		}
		else if (filter == "shades")
		{
			shades(img, p1);
		}
		else if (filter == "brightness")
		{
			brightness(img, p1, 0, 0);
		}
		else if (filter == "merge")
		{
			merge(img, img_2, p1);
		}
		else if (filter == "boxBlur")
		{
			boxBlur(img);
		}
		else if (filter == "edgeDetection")
		{
		edgeDetection(img);
		}
		else if (filter == "sharpen")
		{
		sharpen(img);
		}
		else if (filter == "contrast")
		{
			contrast(img, p1);
		}
	} else if (nthreads > 1) {
		vector<ppm> vecImages = threadsImageDivision(img, nthreads);
		for (int threads; threads < nthreads; threads++) {
			thread thread(applyFilter, img);
		}
	} else {
		cout << "error bla bla 0";
	}
	// cout << std::thread::hardware_concurrency();
	cout << "Escribiendo imagen" << endl;
	img.write(out); // Escribe la imagen resultante en el archivo especificado por "out"

	cout << "Listo" << endl;
	return 0;
}

// #include <iostream>
// #include <functional>
// #include <map>

// // Declaración de funciones
// void funcion1() {
//     std::cout << "Llamando a la función 1" << std::endl;
// }

// void funcion2() {
//     std::cout << "Llamando a la función 2" << std::endl;
// }

// void funcion3() {
//     std::cout << "Llamando a la función 3" << std::endl;
// }

// int main() {
//     std::map<std::string, std::function<void()>> funciones;

//     // Asociar nombres de funciones con punteros a funciones
//     funciones["funcion1"] = funcion1;
//     funciones["funcion2"] = funcion2;
//     funciones["funcion3"] = funcion3;

//     // Obtener el nombre de la función desde el usuario
//     std::string nombreFuncion;
//     std::cout << "Ingrese el nombre de la función: ";
//     std::cin >> nombreFuncion;

//     // Buscar el nombre de la función en el mapa y llamarla si se encuentra
//     auto iter = funciones.find(nombreFuncion);
//     if (iter != funciones.end()) {
//         std::function<void()> funcion = iter->second;
//         funcion();
//     } else {
//         std::cout << "Función no encontrada" << std::endl;
//     }

//     return 0;
// }