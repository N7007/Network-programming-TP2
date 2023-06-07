#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "filters.h" // Incluye el archivo de encabezado "filters.h"
#include <thread>
#include <unistd.h>
#include <fstream>
#include <any>
#include <map>
#include "filters.cpp"

using namespace std;

int main(int argc, char *argv[])
{
	if (string(argv[1]) == "-help")
	{
		cout << "Uso: ./main <filtro> <nthreads> <[p1]> <img1> <custom_output> <[p2]> <img2>" << endl;
		return 0;
	}

	string filter = string(argv[1]);
	unsigned int nthreads = atoi(argv[2]);
	float p1 = atof(argv[3]);
	string imgStrOne(argv[4]);
	string out = string(argv[5]);
	string imgStrTwo(argv[7]);

	ppm img(imgStrOne);
	ppm img2(imgStrTwo);

	//map<string, void> map;
	//map["blackWhite"] = blackWhite;

	cout << "Aplicando filtros" << endl;
	
	applyFilter(argv, nthreads);

	cout << "Escribiendo imagen" << endl;
	img.write(out); 

	cout << "Listo" << endl;
	return 0;
}

