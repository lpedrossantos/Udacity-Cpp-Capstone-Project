#include <iostream>
#include <State.h>

template <class T>
ObjInfo<T> ObjInfo<T>::sendObjInfo(std::vector<std::shared_ptr<T>>& vector, int id)
{
    ObjInfo obj;
    for(int i = 0; i < size(vector); i++)
    {
        if(vector[i]->getId() == id)
        {
            obj.obj = vector[i];
            obj.index = i;
            obj.isAlive = true;
            return obj;
        }

    }
    obj.isAlive = false;
    return obj;
}

/*
RectObjInfo::RectObjInfo(std::shared_ptr<Rectangle> rect, int index, bool alive)
{
    _rect = rect;
    _index = index;
    _isAlive = alive;
}

RectObjInfo RectObjInfo::sendObjInfo(std::vector<std::shared_ptr<Rectangle>>& vector, int id)
{
    for(int i = 0; i < size(vector); i++)
    {
        if(vector[i]->getId() == id)
        {
            RectObjInfo obj(vector[i],i,true);
            return obj;
        }
    }
    RectObjInfo obj;
    return obj;
}*/

int LaunchState::getNumbParticleBegin() {return _numbParticleBegin;}
void LaunchState::setNumbParticleBegin(int &&n) {
    try 
    {
        if(n >0 && n <=5)
            _numbParticleBegin = n;
           
        else
            throw "Number must be  between 1 and 5";
    }catch(const std::string err)
    {
        std::cerr << err << std::endl;
    }
}

void LaunchState::setLaunchWindowState(State state)
{
    _launchWindowState = state;
}

State LaunchState::getLaunchWindowState()
{
    return _launchWindowState;
}

void SimulationState::pushBack(std::shared_ptr<Particle>& particle, std::vector<std::shared_ptr<Particle>>& vec)
{
    vec.emplace_back(std::move(particle));
}

void SimulationState::pushBack(std::shared_ptr<Rectangle>& rectangle, std::vector<std::shared_ptr<Rectangle>>& vec)
{
    vec.emplace_back(std::move(rectangle));
}

std::vector<std::shared_ptr<Particle>>& SimulationState::getParticleVec() { return _particleVec; }

std::shared_ptr<Particle> SimulationState::getParticle(int index) { return _particleVec[index]; }

std::vector<std::shared_ptr<Rectangle>>& SimulationState::getRectangleVec() {return _rectangleVec;}

std::shared_ptr<Rectangle> SimulationState::getRectangleByIndex(int index)
{
    return _rectangleVec[index];
}


void SimulationState::setParticleVec(std::vector<std::shared_ptr<Particle>>&& vec) {_particleVec = vec;}

void SimulationState::setRectangleVec(std::vector<std::shared_ptr<Rectangle>>&& vec) {_rectangleVec = vec;}

void SimulationState::setNumbCyles(int cycle) { _numbCycles = cycle;}

int SimulationState::getNumbCylces() {return _numbCycles;}

void SimulationState::setCycleTime(int &&time) {_cycleTime = time;}

int SimulationState::getCycleTime() {return _cycleTime;}

void SimulationState::addCycleTime(int &&time) 
{
        _cycleTime+=time;  
}

void SimulationState::ResetTimeCycle()
{
    if(_cycleTime > 5)
        _cycleTime = 0;
}

bool SimulationState::isCycleTimeReached()
{
    if(_cycleTime > 5)
        return true;
    else
        return false;
}

void SimulationState::deleteEl(std::vector<std::shared_ptr<Rectangle>>& vector, int id)
{
    ObjInfo<Rectangle> obj;
    int index = obj.sendObjInfo(vector,id).index;

    vector.erase(vector.begin()+index);
}

void SimulationState::deleteEl(std::vector<std::shared_ptr<Particle>>& vector, int id)
{
    ObjInfo<Particle> obj;
    int index = obj.sendObjInfo(vector,id).index;

    vector.erase(vector.begin()+index);
}

void SimulationState::addCycle(){ _numbCycles++; }

void SimulationState::setNumbParticle(int particles) {_numbParticle = particles;}

int SimulationState::getNumbParticles() {return _numbParticle;}

int SimulationState::updateNumbParticle()
{
    //Create new particles on base of pair types(0 and 1)
    int type0 = 0;
    int type1 = 0;
    int particlesToCreate = 0;
    //std::cout << "size particleVec: " << size(_particleVec) << std::endl;
    for(int i = 0; i < size(_particleVec); i++)
    {
        //std::cout << "id: " << this->getParticle(i).get()->getId() << " type: " << this->getParticle(i).get()->getType() << std::endl;
        if(this->getParticle(i).get()->getType() == 0)
            type0++;
        else if(this->getParticle(i).get()->getType() == 1)
            type1++;

    }
    /*std::cout << "type 0: " << type0 << std::endl;
    std::cout << "type 1: " << type1 << std::endl;*/

    if(type0 % 2 == 0 && type1 % 2 == 0 && type0 > 0 && type1 > 0)
    {
        particlesToCreate = ceil((type0+type1) / 2);
    }else if((type0 == 1 || type1 == 1) && type0 > 0 && type1 > 0)
    {
        particlesToCreate = 1;
    }
    else if((type0 % 2 != 0 || type1 % 2 != 0) && type0 > 0 && type1 > 0)
    {
        particlesToCreate = ceil((type0+type1 - 1) / 2);
    }

    //std::cout << "particlesToCreate: " << particlesToCreate << std::endl;
    return particlesToCreate;
}

void SimulationState::checkParticleSurvived()
{
    int numbParticleToDelete = 0;
    std::vector<std::shared_ptr<Particle>> particlesIdsToDelete;
    ObjInfo<Particle> obj;
    for(int i = 0; i < size(_particleVec) ; i++)
    {
        if((this->getParticle(i).get()->getSurvived()) && (this->getParticle(i).get()->getLifeSpan() >= 1))
        {
            //std::cout << "Still Alive: particle id: " << this->getParticle(i).get()->getId() << " lifeSpan: " << this->getParticle(i).get()->getLifeSpan() << " has eaten: " << this->getParticle(i).get()->getSurvived() <<  std::endl;
            this->getParticle(i).get()->setSurvived(false);
        }else if((this->getParticle(i).get()->getSurvived() == false) || (this->getParticle(i).get()->getLifeSpan() < 1))
        {
            numbParticleToDelete++;
            auto particle = this->getParticle(i);
            this->pushBack(particle,particlesIdsToDelete);
        }
            
    }

    for(int j = 0; j < numbParticleToDelete; j++)
    {
        //std::cout << "To Delete: particle id: " << particlesIdsToDelete[j].get()->getId() << " lifeSpan: " << particlesIdsToDelete[j].get()->getLifeSpan() << " has eaten: " << particlesIdsToDelete[j].get()->getSurvived() <<  std::endl;   
        this->deleteEl(_particleVec,particlesIdsToDelete[j].get()->getId());
    }
            
}

void SimulationState::eraseAll(std::vector<std::shared_ptr<Rectangle>>& vec)
{
    for(int i = 0; i < size(vec); i++)
    {
        this->deleteEl(vec,vec[i].get()->getId());
    }
}

std::shared_ptr<Particle> SimulationState::getParticleByIndex(int index)
{
    return _particleVec[index];
}

State SimulationState::getSimulationState() {return _simulationState;}
void SimulationState::setSimulationState(State state) {_simulationState = state;}

int SimulationState::getNumbParticleMutated()
{
    return _numbParticleMutated;
}

void SimulationState::setNumbParticleMutated(int numbParticleMutated)
{
    _numbParticleMutated = numbParticleMutated;
}

void SimulationState::setGlobalRateMutation(int&& rate)
{
    _globalRateMutation = rate;
}

int SimulationState::getGlobalRateMutation()
{
    return _globalRateMutation;
}

void SimulationState::setNumbParticleGene(int numbParticleGene)
{
    _numbParticleGene = numbParticleGene;
}

int SimulationState::getNumbParticleGene()
{
    return _numbParticleGene;
}