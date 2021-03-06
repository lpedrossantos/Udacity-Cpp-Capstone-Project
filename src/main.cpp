#include <SFML/Graphics.hpp>
#include <iostream>

#include <LaunchWindow.h>
#include <SimulationWindow.h>
#include <State.h>

int main()
{
    LaunchWindow launchWindow(1200,800,{73, 177, 242});
    LaunchState launchState;
    SimulationState simulationState;

    launchWindow.init(launchState);

    if(launchState.getLaunchWindowState()==State::off)
    {
        //Set number of particles to begin on the Simulation State
        simulationState.setNumbParticle(launchState.getNumbParticleBegin());
        //Launch Simulation
        SimulationWindow simulationWindow(1200,800,{119, 185, 242});
        simulationWindow.init(simulationState);
    }

    if(simulationState.getSimulationState() == State::off)
    {
        //Launch End Window
    }

}