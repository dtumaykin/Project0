#include <iostream>
#include "structures.h"
#include "util.h"

void main()
{
	scene_t scene;

	vector_t vect = { 1, 2, 3};
	std::cout << vect << "\n";
	std::cout << length(vect) << "\n";
	std::cout << dot(vect, vect) << "\n";
	std::cout << norm(vect);

	std::cin.get();


	// config - una funzione che da un file di configurazione prende i valori e ritorna una scena completa

	// render - trasforma scena completa in un array di pixel

	// output - array di pixel diventa un immagine

}