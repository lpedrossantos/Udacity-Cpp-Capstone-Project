#ifndef TIMER_H
#define TIMER_H

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <State.h>

class Timer : public sf::Time {
    public:
        int setTimer();
        std::string convertTime(SimulationState &state);
        sf::Clock _clock;
        sf::Time _time;
}; 

#endif