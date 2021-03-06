#include <iostream>
#include <string>
#include <fstream>
#include <Timer.h>


std::string Timer::convertTime(SimulationState &state)
{
    //create filestream
    std::string line;
    std::string numbCycle = std::to_string(state.getNumbCylces());
    std::string cycleTimeSecs = std::to_string(state.getCycleTime());
    std::ifstream filestream("../text/timertext.txt");
    if(filestream.is_open())
    {
        while(std::getline(filestream,line))
        {
            //Replace $

            line.insert(13,numbCycle);
            //Replace $
            line.insert(size(line)-5,cycleTimeSecs);
            return line;
        }
    }

}