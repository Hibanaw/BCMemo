/************************************************/
/* 						*/
/*     BGI common defines/utility functions	*/
/*		Copyright (c) 1994		*/
/*	    Jordan Hargraphix Software		*/
/*						*/
/************************************************/
#ifndef __SVGAUTIL_H__
#define __SVGAUTIL_H__

typedef unsigned char DacPalette256[256][3];
//
// extern "C"
// {
//#endif

/* Define palette functions */
void setvgapalette256(DacPalette256 *PalBuf);

//#ifdef __cplusplus
// };
//#endif

#endif /* __SVGAUTIL_H__ */
