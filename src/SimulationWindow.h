#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include <random>

#include<BaseWindow.h>
#include <State.h>


class SimulationWindow : public BaseWindow {
    public:
        SimulationWindow(unsigned int width, unsigned int height,std::vector<sf::Uint32> color);
        void init(SimulationState &state);
        void createParticles(SimulationState &state, int &numbParticles);
        void createRectangles(SimulationState &state);
        //void createTimer(SimulationState &state, Timer &timer);
        sf::Text _text;
        std::random_device rd;
        std::mt19937 mt;
        
};



#endif