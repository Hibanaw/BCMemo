/**
 * @file mouse.h
 * @author dengshuumin, Hibanaw Hu (hibanaw@qq.com)
 * @brief Header file of mouse under DOS with no global variables.
 * @date 2023-02-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include "svga.h"
#include "global.h"

/**
 * @brief Cursor styles.
 * 
 */
enum CursorStyle{
	CURSORPOINTER = 0,
	CURSORSELECT,
	CURSORTEXT,
	CURSORCROSS
};

/**
 * @brief Mouse Click status.
 * 
 */
enum ClickStatus{
	ClickUnclick,
	ClickLeft,
	ClickRight
};

/**
 * @brief Struct of mouse.
 * 
 */
typedef struct{
    int posX, posY;
    enum CursorStyle style;
	void *buffer;
    enum ClickStatus click;
	bool visibility;

	int _flag;
}Mouse;

Mouse *mouse();
void mouse_init();
void mouse_update();
void mouse_show();
void mouse_hide();
int mouse_isClickedInBox(int, int, int, int);

void _mouse_draw(int, int);
void _mouse_read(int *,int *,int *);
void _mouse_saveBackground(int,int);
void _mouse_clrmous(int, int);
void _mouse_drawmous(int,int);

#endif
