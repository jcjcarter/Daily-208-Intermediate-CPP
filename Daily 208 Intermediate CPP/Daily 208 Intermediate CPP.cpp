// Daily 208 Intermediate CPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <dlfcn.h>

char radial(char *colors, int ncolors, int x, int y, int *args) {
	int dx = x - args[0];

	int dy = y - args[1];

	double dist = sqrt(dx * dx + dy * dy);

	if (dist > args[2])
		return colors[ncolors - 1];
	else
		return colors[(int)(dist * (ncolors - 1) / args[2])];
}

char linear(char *colors, int ncolors, int x, int y, int *args) {
	
	double ax = args[0] - x;
	double ay = args[1] - y;
	double bx = args[0] - args[2];
	double by = args[1] - args[3];

	double normb = sqrt(bx * bx + by * by);

	double ubx = bx / normb;
	double uby = by / normb;

	double dist = ax * ubx + ay * uby;

	if (dist < 0)
		return colors[0];
	else if (dist > normb)
		return colors[ncolors - 1];
	else
		return colors[(int)(dist * (ncolors - 1) / normb)];

}


int main(void)
{

	/* Read side and colors. */

	int width, height;

	scanf("%d %d", &width, &height);

	while (getchar() != '\n'); // Kill remaining line.

	char colors[256];

	fgets(colors, sizeof(colors), stdin);

	int ncolors = strlen(colors) -1;

	/* Select sampler function. */
	char sampler_name[32];
	scanf("31s", sampler_name);
	char(*sampler)(char *, int, int, int, int *);
	sampler = dlsym(dlopen(NULL, RTLD_NOW, sampler_name);

	/* Read in arguments. */
	int args[8];
	int nargs = 0;

	while (scanf("%d", &args[nargs]) == 1 && nargs < 8)
		nargs++;

	/* Render gradient. */
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			fputc(sampler(colors, ncolors, x, y, args), stdout);
		}
		fputc('\n', stdout);
	}


    return 0;
}

