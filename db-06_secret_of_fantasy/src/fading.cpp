/*
 * Copyright (c) 2007, Olof Naessen and Per Larsson
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 *    * Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright notice, 
 *      this list of conditions and the following disclaimer in the documentation 
 *      and/or other materials provided with the distribution.
 *    * Neither the name of the Darkbits nor the names of its contributors may be 
 *      used to endorse or promote products derived from this software without 
 *      specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <allegro.h>
#include <math.h>

#include "music.hpp"
#include "fading.hpp"
#include "timer.hpp"

void stripesFade(BITMAP *bmp) {
	int *lines = new int[bmp->w];
	int x, i;

	for (x = 0; x < bmp->w; x++) {
		lines[x] = rand() % 128;
	}

	for (i = 0; i < 128; i++) {
		for (x = 0; x < bmp->w; x++) {
			if (lines[x] == i) {
                line(bmp, x, 0, x, bmp->h - 1, makecol(255, 255, 255));
			}
		}

		pollMusic();
		vsync();
		stretch_blit(bmp, screen, 0, 0, 320, 240, 0, 0, 640, 480);
	}
	delete[] lines;
}

void spiralFade(BITMAP *bmp) {
	int w2 = bmp->w / 2;
	int h2 = bmp->h / 2;
	int l = (int)sqrt((double)(w2 * w2 + h2 * h2)) + 50;
	
	int i, j;	
	for (i = 0; i < 128; i++) {
		for (j = 0; j < 10; j++)
		{
			int t = i * 10 + j;
			int d1 = (l * t) / 1280;
			int d2 = (l * t) / 1500;
			int x1 = cos(t / 50.0) * d1 + w2;
			int y1 = sin(t / 50.0) * d1 + h2;
			int x2 = sin(t / 50.0) * d2 + w2;
			int y2 = -cos(t / 50.0) * d2 + h2;
			triangle(bmp, w2, h2, x1, y1, x2, y2, makecol(255, 255, 255));
		}

		pollMusic();
		vsync();
		stretch_blit(bmp, screen, 0, 0, 320, 240, 0, 0, 640, 480);
	}
}


void circlesFade(BITMAP *bmp) {
	int x, y, i;
	for (i = 0; i < 128; i++) {
		for (x = 0; x < bmp->w; x += 64) {
			for (y = 0; y < bmp->h; y += 64) {
				circlefill(bmp, x + 32, y + 16, (i * 2) / 5, makecol(255, 255, 255));
			}
		}

		pollMusic();
		vsync();
		stretch_blit(bmp, screen, 0, 0, 320, 240, 0, 0, 640, 480);
	}
}

void sweepFade(BITMAP *bmp) {
	int i, y;

	for (i = 0; i < 64; i++) {
		for (y = 0; y < bmp->h; y += 32) {
			triangle(bmp, 0, y, 0, y + 31, (i * bmp->w) / 64, y + 16, makecol(255, 255, 255));
		}

		pollMusic();
		vsync();
		stretch_blit(bmp, screen, 0, 0, 320, 240, 0, 0, 640, 480);
	}

	for (i = 0; i < 64; i++) {
		for (y = 0; y < bmp->h; y += 32) {
			triangle(bmp, (i * bmp->w) / 64, y, (i * bmp->w) / 64, y + 31, bmp->w, y + 16, 0);
		}
		rectfill(bmp, 0, 0, (i * bmp->w) / 64, bmp->h, makecol(255, 255, 255));

		pollMusic();
		vsync();
		stretch_blit(bmp, screen, 0, 0, 320, 240, 0, 0, 640, 480);
	}
}

void squaresFade(BITMAP *bmp) {
	int i, x, y;
	
	for (i = 0; i < 128; i++) {
		for (x = 0; x < bmp->w; x++) {
			y = ((x * 3) / 4) ^ (i * 2);
			putpixel(bmp, x, y, makecol(255, 255, 255));
			y = ((x * 3) / 4) ^ (i * 2 + 1);
			putpixel(bmp, x, y, makecol(255, 255, 255));
		}

		pollMusic();
		vsync();
		stretch_blit(bmp, screen, 0, 0, 320, 240, 0, 0, 640, 480);
	}
}

void fadeOut(BITMAP *bmp, unsigned int type) {
    switch (type) {
	case CIRCLES:
		circlesFade(bmp);
		break;
	}
}
