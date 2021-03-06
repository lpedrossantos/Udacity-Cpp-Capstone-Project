#include <iostream>
#include <random>
#include <vector>

#include <SimulationWindow.h>
#include <Timer.h>
#include <Particle.h>

class SimulationState;

SimulationWindow::SimulationWindow(unsigned int width, unsigned int height,std::vector<sf::Uint32> color)
{
    _width = width;
    _height = height;
    _color = color;
}

void SimulationWindow::init(SimulationState &state)
{
    state.setSimulationState(State::on);
    this->create(sf::VideoMode(_width,_height), "Ecosystem Simulation");
    Timer timer;
    sf::Font font;
    sf::Text text;
    font.loadFromFile("../fonts/coolvetica.ttf");
    text.setFont(font);
    text.setPosition(10,10);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);


    int numbParticles = state.getNumbParticles();
    state.setGlobalRateMutation(2);
    SimulationWindow::createRectangles(state);
    SimulationWindow::createParticles(state,numbParticles);

    while(this->isOpen())
    {
        sf::Event event;
        while (this->pollEvent(event))
        {
            // Request for closing the window
            if (event.type == sf::Event::Closed)
                this->close();
        }

        /*if(state.getParticleVec().empty())
        {
            state.setSimulationState(State::off);
            this->close();
        }*/

        timer._time = timer._clock.getElapsedTime();
        //Count Time
        
        //Check if is cycletime reached, if true set new cycle
        if(timer._time.asSeconds() >= 1)
        {
            //state.ResetTimeCycle();
            state.addCycleTime(1);
            if(state.isCycleTimeReached())
            {
                state.ResetTimeCycle();
                int newNumbParticle = state.updateNumbParticle();
                int numbParticleMutated = 0;
                int numbParticleGene = 0;
                //std::cout << "new particles: " << newNumbParticle << std::endl;
                for(int i = 0; i <size(state.getParticleVec()); i++)
                {
                    state.getParticleByIndex(i).get()->setLifeSpan(state.getParticle(i).get()->getLifeSpan()-1);
                    if(state.getParticleByIndex(i).get()->getMutated())
                    {
                        numbParticleMutated++;
                        numbParticleGene++;
                    }     
                }

                if(numbParticleMutated > 0 || numbParticleGene > 0)
                {
                    if(state.getGlobalRateMutation() <= 100)
                        state.setGlobalRateMutation(state.getGlobalRateMutation()+1);
                    state.setNumbParticleGene(numbParticleGene);
                }

                state.setNumbParticleMutated(numbParticleMutated); 
                //Reset
                state.checkParticleSurvived();
                state.getRectangleVec().clear();
                state.addCycle();
                SimulationWindow::createRectangles(state);
                if(newNumbParticle > 0)
                {
                    //std::cout << "Create New Particle" << std::endl;
                    SimulationWindow::createParticles(state,newNumbParticle);
                }
            }
            timer._clock.restart();
        }

        //Display time
        this->clear(sf::Color(_color[0],_color[1],_color[2]));

        text.setString(timer.convertTime(state));
        this->draw(text);

    if(!state.getParticleVec().empty())
    {
        for(int i = 0; i < size(state.getParticleVec()); i++)
        {
            auto particle = state.getParticle(i).get();
            particle->moveParticle(size(state.getRectangleVec()), state,this);
            this->draw(particle->getCircleShape());
        }
    }
        

    if(!state.getRectangleVec().empty())
    {
        for(int i = 0; i < size(state.getRectangleVec()); i++)
        {
            auto rectangle = state.getRectangleByIndex(i).get();
            this->draw(rectangle->getRectangleShape());
        }
    }
        
        this->display();
    }
}

void SimulationWindow::createParticles(SimulationState &state, int &numbParticles)
{
    std::shared_ptr<Particle> particle;   
    std::uniform_real_distribution<double> dist(100.0, 600.0);
    int id;
    int numbParticleMutated = state.getNumbParticleMutated();
    int numbParticleGene = state.getNumbParticleGene();
    for(int i = 0; i < numbParticles; i++)
    {
        if(!size(state.getParticleVec()))
            id = 0;
        else
            id = state.getParticleByIndex(size(state.getParticleVec())-1).get()->getId() + 1;
        
        if(numbParticleMutated >= 1 || numbParticleGene >= 1)
        {
            particle = std::make_shared<Particle>(id,20,20,dist(mt),dist(mt),state.getGlobalRateMutation(),true);
            numbParticleMutated--;
            numbParticleGene--;
        }else
        {
            particle = std::make_shared<Particle>(id,20,20,dist(mt),dist(mt),2,false);
        }
        
        //particle->setPosition(particle->getX(),particle->getY());
        //particle->setFillColor(sf::Color::Red);
        particle->FindNearestRectangle(state);
        //particle->Mutate();
        state.pushBack(particle,state.getParticleVec());
    }
}

void SimulationWindow::createRectangles(SimulationState &state)
{
    std::uniform_real_distribution<double> distY(100.0, 600.0);
    std::uniform_real_distribution<double> distX(50.0, 1000.0);
    std::uniform_real_distribution<double> distSize(5, 15);
    std::uniform_real_distribution<double> distNumb(state.getNumbParticles()*1/2, state.getNumbParticles()*10);

    int numbRect = distNumb(mt);
    std::vector<sf::Uint32> vecColor = {255,255,255};
    for(int i = 0; i <= numbRect; i++)
    {
        std::shared_ptr<Rectangle> rectangle = std::make_shared<Rectangle>(i,distSize(mt),distSize(mt),distX(mt),distY(mt),vecColor);   
        state.pushBack(rectangle,state.getRectangleVec());
    }
}