/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "agent.h"
#include "random.h"
#include <tuple>

Agent::Agent(int x, int y) {
    if (getRandomNumber(0,1) == 0)
        m_isAlive = false;
    else
        m_isAlive = true;
    
    m_posx = x;
    m_posy = y;
}
    
bool Agent::checkState() {
    return m_isAlive;
}

void Agent::switchState() {
    if (!m_isAlive)
        m_isAlive = true;
    else
        m_isAlive = false;
}


