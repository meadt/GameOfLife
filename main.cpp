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
#include <cstdlib>
#include <iostream> 

int main(int argc, char** argv) {
    
    int width{5};
    int depth{10};
    
    //Remember to delete board!
    Board board(width, depth);
    
    board.init();
    
    board.printBoard();
    
    return 0;
}


