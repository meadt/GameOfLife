/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "board.h"
#include "agent.h"
#include "random.h"
#include <assert.h>
#include <tuple>
#include <iostream>


Board::Board(int width, int depth) {
    m_width = width;
    m_depth = depth;
    m_rProb = 0.0;
}

Board::Board(int width, int depth, double prob) {
    m_width = width;
    m_depth = depth;
    m_rProb = prob;
}

int Board::convertPos(int x, int y) {
    //Get index number for "2D" array.
    return x + m_width * y;
}

Board* Board::returnPointer() {
    return this;
}

void Board::init() {
    //Creates board and populates with random agents.
    
    //Checks that board hasn't already been initialised.
    assert(m_initialised);
            
    for (int i = 0; i < m_depth; i++)
        for (int j = 0; j < m_width; j++)
            m_matrix.push_back(new Agent(i, j));

    m_initialised = true;
}

void Board::init(double prob) {
    // Creates board, populates with random agents using a set probability
    // and sets the global board point to the board that was just created.
    
    //Checks that board hasn't already been initialised.
            
    for (int i = 0; i < m_depth; i++)
        for (int j = 0; j < m_width; j++)
            m_matrix.push_back(new Agent(i, j, prob));
    
    m_initialised = true;
}

bool Board::getInitState() {
    //Checks whether the board has been set up (i.e. initialised).
    return m_initialised;
}

int Board::getWidth() {
    return m_width;
}

int Board::getDepth() {
    return m_width;
}

Agent* Board::getAgent(int x, int y) {
    return m_matrix.at(convertPos(x, y));
}

void Board::printLine() {
    // Pretty prints horizontal edges of board.
    // (Vertical component handled in printBoard()).
    std::cout << " ";
    
    for (int i = 0; i < m_depth; i++)
        std::cout << "-";
    
    std::cout << "\n";
}

void Board::printBoard() {
    //Prints board. 
    
    //Top line:
    printLine();
    
    //Main board:
    for (int i = 0; i < m_width; i++) {
        std::cout << "|";
        for (int j = 0; j < m_depth; j++)
            if (getAgent(i, j)->checkState() == 0)
                std::cout << " ";
            else
                std::cout << "#";
        std::cout << "|";
        std::cout << "\n"; 
    }
        
    //Bottom line:
    printLine();
}

bool Board::checkLeftNeigh(std::tuple<int, int> pos_tuple) {
    //Checks whether left (x - 1) neighbour is alive and returns true if yes.
    if (std::get<0>(pos_tuple) == 0) { // Checks if at left boundary, i.e. x = 0.
            if(m_matrix.at(convertPos(m_width - 1, //If yes, wraps to right boundary (sets x = m_width - 1).
                    std::get<1>(pos_tuple)))->checkState() == true)
                return true;
        } else {
            if(m_matrix.at(convertPos(std::get<0>(pos_tuple) - 1, 
                    std::get<1>(pos_tuple)))->checkState() == true)
                return true;
        }
    return false;
};

bool Board::checkRightNeigh(std::tuple<int, int> pos_tuple) {
    //Checks whether right (x + 1) neighbour is alive and returns true if yes.
    if (std::get<0>(pos_tuple) == m_width - 1) { // Checks if at right boundary, i.e. x = m_width - 1.
            if(m_matrix.at(convertPos(0, //If yes, wrap to left boundary (sets x = 0).
                    std::get<1>(pos_tuple)))->checkState() == true)
                return true;
        } else {
            if(m_matrix.at(convertPos(std::get<0>(pos_tuple) + 1, 
                    std::get<1>(pos_tuple)))->checkState() == true)
                return true;
        }
    return false;
};

bool Board::checkUpperNeigh(std::tuple<int, int> pos_tuple) {
    //Checks whether upper (y - 1) neighbour is alive and returns true if yes.
    if (std::get<1>(pos_tuple) == 0) { // Checks if at upper boundary, i.e. y = 0.
            if(m_matrix.at(convertPos(std::get<0>(pos_tuple),
                    m_depth - 1))->checkState() == true) //If yes, wrap to lower boundary (sets y = m_depth - 1).
                return true;
        } else {
            if(m_matrix.at(convertPos(std::get<0>(pos_tuple), 
                    std::get<1>(pos_tuple) - 1))->checkState() == true)
                return true;
        }
    return false;
};

bool Board::checkLowerNeigh(std::tuple<int, int> pos_tuple) {
    //Checks whether lower (y + 1) neighbour is alive and returns true if yes.
    if (std::get<1>(pos_tuple) == m_depth - 1) { // Checks if at lower boundary, i.e. y = m_depth - 1.
            if(m_matrix.at(convertPos(std::get<0>(pos_tuple), 
                    0))->checkState() == true) //If yes, wrap to upper boundary (sets y = 0).
                return true;
        } else {
            if(m_matrix.at(convertPos(std::get<0>(pos_tuple), 
                    std::get<1>(pos_tuple) + 1))->checkState() == true)
                return true;
        }
    return false;
};

void Board::updateState() {
    std::vector<Agent*> matrix_copy = m_matrix;
    
     //Check every state and neighbours for all agents in the matrix
    for (int i = 0; i < m_width; i++)
        for (int j = 0; j < m_depth; j++) {
            int alive_neighs{0};
            auto pos_tuple = std::make_tuple(i, j);
            
            if (checkLeftNeigh(pos_tuple))
                alive_neighs++;
            if (checkRightNeigh(pos_tuple))
                alive_neighs++;
            if (checkUpperNeigh(pos_tuple))
                alive_neighs++;
            if (checkLowerNeigh(pos_tuple))
                alive_neighs++;
            
            if (m_matrix.at(i + m_width * j)->checkState()) // Current cell is alive.
                if (alive_neighs == 0 || alive_neighs == 4) // Too few or too many neighbours?
                    matrix_copy.at(i + m_width * j)->switchState(); // If yes, kill cell.
            else // Current cell is dead.
                if (alive_neighs == 2) // Two neighbours?
                    matrix_copy.at(i + m_width * j)->switchState(); // If yes, resurrect cell.
                
            //Resurrects cells based on pre-determined rProb
            //TODO: MOVE TO OWN FUNCTION
            // i.e. if cell is still dead at this point
            if (!m_matrix.at(i + m_width * j)->checkState()) {
                if (generateRandomProb() < m_rProb) // If rProb is zero, then no cells are resurrected.
                    matrix_copy.at(i + m_width * j)->switchState();
            }
        }
    //Replaces current matrix with updated copy.
    m_matrix = matrix_copy;
}
