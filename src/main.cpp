#include <iostream>

#include "structures.h"
#include "util.h"
#include "config.h"
#include "tracer.h"
#include "easybmp\EasyBMP.h"

#define _CRT_SECURE_NO_WARNINGS // no warnings for fscanf(), fopen()

void main()
{
	int status; // need it for crash messages

	// config - una funzione che da un file di configurazione prende i valori e ritorna una scena completa
	scene_t scene;

	status = loadConfig("config.cfg", scene);
	if(!status)
	{
		printf("\nBad config!");
		std::cin.get();
		return;
	}

	// render - trasforma scena completa in un array di pixel



	// output - array di pixel diventa un immagine

}
