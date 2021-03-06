#ifndef Particle_H
#define Particle_H


//#include <string>
#include <vector>
#include <random>
#include <memory>

#include <SFML/Graphics/CircleShape.hpp>
class SimulationWindow;
class SimulationState;

class Particle : public sf::CircleShape {
    public:
    //Constructor
        Particle(int id, float radius, size_t pointCount, double x, double y, int&& rate, bool geneOfMutation);
        ~Particle();
    //Initializer list
        Particle() : _survived(false) {};
    //Getters functions
        int getId();
        bool getMutated();
        bool getSurvived();
        int getType();
        double getX();
        double getY();
        double getDx();
        double getDy();
        int getLifeSpan();
        sf::CircleShape getCircleShape();
        int getNearestRectangleId();
        int getRateOfMutation();
    //Setter Functions
        void setId(int id);
        void setMutated(bool mutated);
        void setSurvived(bool survived);
        void setType(int type);
        void setX(double x);
        void setY(double y);
        void setDx(double dx);
        void setDy(double dy);
        void setNearestRectangleId(int idRect);
        void setLifeSpan(int lifeSpan);
        void setRateOfMutation(int rate);
    //Functionality
        void moveParticle(size_t n,SimulationState &state, SimulationWindow* window);
        void moveParticleTowardRect(SimulationState &state);
        void moveParticleRand(SimulationWindow* window);
        bool detectCollisionRect(SimulationState &state);
        void defineCircleShape();
        void FindNearestRectangle(SimulationState &state);
        double calculateDistance(std::shared_ptr<Particle>&& particle);
    //Variables
    private:
        int _id;
        bool _mutated;
        bool _survived;
        bool _geneOfMutation;
        int _type;
        int _lifeSpan;
        double _x;
        double _y;
        double _dx;
        double _dy;
        double _dxToRect;
        double _dyToRect;
        double _distance;
        int _nearestRectangleId;
        int _nearestParticleId;
        sf::CircleShape _circleShape;
        sf::Color _color;
        int _rateOfMutation;
        

};
#endif