#ifndef STATE_H
#define STATE_H

#include <vector>
#include <memory>


#include <SFML/System/Time.hpp>
#include <Particle.h>
#include <Rectangle.h>

enum class State {on,off};

template <class T>
class ObjInfo
{
    public:
        ObjInfo<T> sendObjInfo(std::vector<std::shared_ptr<T>>& vector, int id);
        std::shared_ptr<T> obj;
        int index;
        bool isAlive;
};

class LaunchState
{
    public:
        LaunchState() : _numbParticleBegin(1), _launchWindowState(State::off) {};
        void setNumbParticleBegin(int &&n);
        void setLaunchWindowState(State state);
        int getNumbParticleBegin();
        State getLaunchWindowState();

    private:
        int _numbParticleBegin;
        State _launchWindowState;
};

class SimulationState
{
    public:
    //Overloading pushBack function
        void pushBack(std::shared_ptr<Particle>& particle,std::vector<std::shared_ptr<Particle>>& vec);
        void pushBack(std::shared_ptr<Rectangle>& rectangle,std::vector<std::shared_ptr<Rectangle>>& vec);
    ///////////////////////////////////////////////////////////
        std::vector<std::shared_ptr<Particle>>& getParticleVec();
        std::shared_ptr<Particle> getParticle(int index);
        std::vector<std::shared_ptr<Rectangle>>& getRectangleVec();
        std::shared_ptr<Rectangle> getRectangleByIndex(int index);
        int getNumbParticleMutated();
        void setNumbCyles(int cycle);
        void setParticleVec(std::vector<std::shared_ptr<Particle>>&& vec);
        void setRectangleVec(std::vector<std::shared_ptr<Rectangle>>&& vec);
        void setNumbParticleMutated(int numbParticleMutated);
        void setNumbParticleGene(int numbParticleGene);
        void setGlobalRateMutation(int&& rate);
        int getNumbCylces();
        int getGlobalRateMutation();
        int getNumbParticleGene();
        std::shared_ptr<Particle> getParticleByIndex(int index);
        void setCycleTime(int &&time);
        void addCycleTime(int &&time);
        void addCycle();
        bool isCycleTimeReached();
        void checkParticleSurvived();
        //Overload deleteEl
        void deleteEl(std::vector<std::shared_ptr<Rectangle>>& vector, int id);
        void deleteEl(std::vector<std::shared_ptr<Particle>>& vector, int id);
        //
        int updateNumbParticle();
        void ResetTimeCycle();
        int getCycleTime();
        void setNumbParticle(int particles);
        int getNumbParticles();
        void eraseAll(std::vector<std::shared_ptr<Rectangle>>& vec);
        State getSimulationState();
        void setSimulationState(State state);
    private:
        std::vector<std::shared_ptr<Particle>> _particleVec;
        std::vector<std::shared_ptr<Rectangle>> _rectangleVec;
        int _numbCycles{1};
        int _cycleTime{0};
        int _numbParticle;
        int _numbParticleMutated{0};
        int _numbParticleGene{0};
        int _globalRateMutation;
        State _simulationState;
    
};

#endif