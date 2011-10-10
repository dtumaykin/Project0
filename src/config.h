#ifndef P0_CONFIG_H
#define P0_CONFIG_H

#include <iostream>
#include <fstream>
#include "structures.h"

enum OPCODES 
{
	RESO,
	SIZE,
	SPHR,
	POLY,
	LGHT,
	MATR,
	PLNE,
	AAMX,
	UNKN
};

int loadConfig(char * path, scene_t &scene); // return line number in case of bad config, otherwise 0

int getOpcode(std::ifstream &ifs);

//scene_t config(); // loads default "config.cfg" file and returns a scene, implemented by secco92


#endif
