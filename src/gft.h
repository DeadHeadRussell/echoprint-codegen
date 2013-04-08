/*
 *  gft.h
 *  GFT Framework
 *
 *  Created by Robert Brown on 30/05/08.
 *  Copyright 2008 Robert Brown. All rights reserved.
 *
 */

typedef void (gftWindowFunction)(double*,int,int);

// Windows
void gft_gaussian(double *win, int N, int freq);
void gft_box(double *win, int N, int freq);

// GFT partition and window screen generators
int gft_1dSizeOfPartitions(unsigned int N);
int *gft_1dPartitions(unsigned int N);
int *gft_1dMusicPartitions(unsigned int N, float samplerate, int cents);
double *gft_windows(int N, gftWindowFunction *window);
double *gft_windowsFromPars(int N, gftWindowFunction *window, int *pars);

// 1D GFT Functions
void gft_1dComplex64(double *signal, unsigned int N, double *win, int *pars, int stride);

// 2D GFT Functions
void gft_2dComplex64(double *signal, unsigned int N, unsigned int M, gftWindowFunction *window);

// Interpolation functions
double *gft_1d_interpolateNN(double *signal, unsigned int N, unsigned int M);

