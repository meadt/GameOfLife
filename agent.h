/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   agent.h
 * Author: meadt
 *
 * Created on 21 May 2019, 11:17
 */



#ifndef AGENT_H
#define AGENT_H

#include <tuple>

// -- Class declarations -- //

class Agent {
private:
    bool m_isAlive;
    int m_posx;
    int m_posy;
public:
    Agent(int x, int y); 
    bool checkState();
    std::tuple<int, int> getPos();
    void switchState();
};

#endif /* AGENT_H */

