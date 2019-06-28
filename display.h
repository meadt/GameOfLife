/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   display.h
 * Author: meadt
 *
 * Created on 20 June 2019, 09:57
 */

#ifndef DISPLAY_H
#define DISPLAY_H

void myGlutIdle();
void myGlutReshape( int x, int y );
void myGlutDisplay();
int displayGlui(int argc, char* argv[]);
void drawSquare(float x_start, float y_start, Agent agent);

#endif /* DISPLAY_H */

