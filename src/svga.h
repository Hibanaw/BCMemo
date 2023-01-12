#ifndef _WIN32
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <dir.h>
#include <dos.h>
#include <bios.h>
#include <graphics.h>
#include"SVGA256.H"
#include"SVGAUTIL.H"

int huge detectSVGA256(void); 
int initsvga256(void);
int closesvga256(void);
#endif
#endif