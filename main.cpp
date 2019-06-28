/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: meadt
 *
 * Created on 20 May 2019, 15:07
 */


#include "random.h"
#include "agent.h"
#include "board.h"
#include "display.h"
#include <cstdlib>
#include <iostream> 

int width{5};
int depth{5};

Board* board = new Board(width, depth, 0.15);
    
extern Board *BOARDPOINTER = board;

int main(int argc, char** argv) {
    
    //Remember to delete board!
    
    // Create agents with a probability of 50%
    board->init(0.5);
    
    displayGlui(argc, argv);
    
    return EXIT_SUCCESS;
}


