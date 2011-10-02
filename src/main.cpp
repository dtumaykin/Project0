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

	//loading config
	scene_t scene;

	status = loadConfig("config.cfg", scene);
	if(!status)
	{
		printf("\nBad config!");
		std::cin.get();
		return;
	}

	BMP output;
	output.SetSize(scene.screenResX, scene.screenResY);

	for(int i = 0; i < scene.screenResX; i++)
		for(int j = 0; j < scene.screenResY; j++)
		{
			color_t r = getColor(i, j, scene);
			
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

	//writing output image
	output.WriteToFile("output.bmp");

}
