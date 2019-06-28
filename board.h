/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   board.h
 * Author: meadt
 *
 * Created on 21 May 2019, 11:12
 */


#ifndef BOARD_H
#define BOARD_H

#include "agent.h"
#include <tuple>
#include <vector>

class Board {
private:
    bool m_initialised;
    int  m_width;
    int  m_depth;
    double m_rProb;
    std::vector <Agent*> m_matrix;
public:
    Board(int width, int depth);
    Board(int width, int depth, double res);
    int convertPos(int x, int y);
    Board* returnPointer();
    void init();
    void init(double prob);
    bool getInitState();
    int getWidth();
    int getDepth();
    Agent* getAgent(int x, int y);
    void printBoard();
    void printLine();
    void updateState();
    bool checkLeftNeigh(std::tuple<int, int> pos_tuple);
    bool checkRightNeigh(std::tuple<int, int> pos_tuple);
    bool checkUpperNeigh(std::tuple<int, int> pos_tuple);
    bool checkLowerNeigh(std::tuple<int, int> pos_tuple);
};

#endif /* BOARD_H */

