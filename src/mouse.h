/**
 * @file mouse.h
 * @author dengshuumin, Hibanaw Hu (hibanaw@qq.com)
 * @brief Header file of mouse under DOS with no global variables.
 * @date 2023-02-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __mouse_h__
#define __mouse_h__

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
    enum ClickStatus click;//按键状态，0为未按下
	bool visibility;//可见性

	int _flag;
}Mouse;

Mouse *mouse();
void mouse_init();
void mouse_update();
int mouse_isClickedInBox(int x1, int y1, int x2, int y2);
void mouse_setVisibility(bool);

void _mouse_draw(int x, int y);
void _mouse_read(int *nx,int *ny,int*nclick);
void _mouse_saveBackground(int nx,int ny);
void _mouse_clrmous(int x,int y);
void _mouse_drawmous(int x,int y);


#endif
