/*
*	 ______             _                    _____  
*	(_____ \           (_)              _   (_____) 
*	 _____) )____ ___   _ _____  ____ _| |_ _  __ _ 
*	|  ____// ___) _ \ | | ___ |/ ___|_   _) |/ /| |
*	| |    | |  | |_| || | ____( (___  | |_|   /_| |
*	|_|    |_|   \___/_| |_____)\____)  \__)\_____/ 
*					 (__/ 
*
*	Project0 - simple C/C++ raytracer
*	created by Danil Tumaykin, Alessandro Carlin, Marco Cauzzi, Marco Begnozzi
*
*	P0 was intended as learning project, so feel free to modify and reuse our code :P
*	
*	want to contibute - email me - d.tumaykin@gmail.com
*
*/


#include <iostream>
#include <math.h>
#include <time.h>

#include "structures.h"
#include "util.h"
#include "config.h"
#include "tracer.h"
#include "easybmp\EasyBMP.h"

#define _CRT_SECURE_NO_WARNINGS // no warnings for fscanf(), fopen()

void main()
{
	int status; // need it for crash messages

	//loading config
	scene_t scene;

	std::cout<<"Welcome to Project0, a really slow raytracer!\n";
	std::cout<<"Loading config...\n";
	status = loadConfig("config.cfg", scene);
	if(status)
	{
		printf("\nBad config: line %d!", status);
		std::cin.get();
		return;
	}

	BMP output;
	output.SetSize(scene.screenResX, scene.screenResY);

	int percentDone, perc = 0;
	for(int i = 0; i < scene.screenResX; i++)
	{
		for(int j = 0; j < scene.screenResY; j++)
		{
			color_t r = getColor(i, j, scene);

			//pseudo photo exposure
			//r.r = (1.0f - exp(r.r * -1.0f));
			//r.g = (1.0f - exp(r.g * -1.0f));
			//r.b = (1.0f - exp(r.b * -1.0f));
			
			//color must be in range 0 - 255
			r.r *= 255.0f;
			r.g *= 255.0f;
			r.b *= 255.0f;

			if(r.r > 255) r.r = 255;
			if(r.g > 255) r.g = 255;
			if(r.b > 255) r.b = 255;

			//write pixels to buffer
			output(i, j)->Red	= ebmpBYTE(r.r);
			output(i, j)->Green = ebmpBYTE(r.g);
			output(i, j)->Blue	= ebmpBYTE(r.b);

		}
		percentDone = int(i/(double)scene.screenResX * 100.0f);
		if(perc != percentDone)
		{
			std::cout<<"\r"<<perc<<"\% done."<<" It took "<<double(clock())/CLOCKS_PER_SEC<<" seconds.";
			perc = percentDone;
		}
	}

	//writing output image
	output.WriteToFile("output.bmp");
	std::cin.get();

}
