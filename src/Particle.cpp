#include <math.h>
#include <iostream>
#include <Particle.h>
#include <State.h>
#include <SimulationWindow.h>

class SimulationWindow;
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> distVelocity(0.1, 0.2);



Particle::Particle(int id,float radius, size_t pointCount, double x, double y, int&& rate,bool geneOfMutation) {
    this->setPointCount(pointCount);
    this->setRadius(radius);
    _id =id;
    _x = x;
    _y = y;
    _dx = distVelocity(mt);
    _dy = distVelocity(mt);
    _rateOfMutation = rate;
    _geneOfMutation = geneOfMutation;
    //Define type, 50% chance of being type 0 or type 1
    rand() % 100 > 50 ? _type = 1 : _type = 0;
    //Define Color based on type
    _type == 0 ? _color = sf::Color(217, 165, 102) : _color = sf::Color(185, 191, 4);
    //set lifeSpan for 5 cycles
    _lifeSpan = 5;
    //Verify if particle is already mutated
    //Each particle has 5% chance of getting mutated
    rand() % 100 < _rateOfMutation ? _mutated = true : _mutated = false;
    std::cout << "gene of mutation: " << _geneOfMutation << std::endl;
    std::cout << "rate of mutation " << _rateOfMutation << std::endl;
    std::cout << "mutate:" << _mutated << std::endl;
    if(_mutated)
    {
        //if does a particle got a mutation or was passed a mutation add more speed and change color
        std::cout << "particle mutated id: " << _id << " mutated: " << _mutated << std::endl;
        _dx+= 0.05;
        _dy+= 0.05;
        _type == 0 ? _color = sf::Color(245,177,66) : _color = sf::Color(3, 166, 120);
        _geneOfMutation = true;

    }
    Particle::defineCircleShape();
};

Particle::~Particle() {
    //std::cout <<"Particle id  deleted: " << _id << std::endl;
}

int Particle::getId() {return _id;}
int Particle::getType() {return _type;}
bool Particle::getMutated() {return _mutated;}
bool Particle::getSurvived() {return _survived;}
double Particle::getX() {return _x;}
double Particle::getY() {return _y;}
int Particle::getLifeSpan() {return _lifeSpan;}
int Particle::getRateOfMutation() {return _rateOfMutation;}

void Particle::setId(int id) {_id = id;}
void Particle::setMutated(bool mutated) {_mutated = mutated;}
void Particle::setSurvived(bool survived) {_survived = survived;}
void Particle::setType(int type) {_type = type;}
void Particle::setX(double x) {_x=x;}
void Particle::setY(double y) {_y=y;}
void Particle::setNearestRectangleId(int idRect) {_nearestRectangleId = idRect;}
void Particle::setLifeSpan(int lifeSpan) {_lifeSpan = lifeSpan;}
void Particle::setRateOfMutation(int rate) {_rateOfMutation = rate;}

void Particle::defineCircleShape()
{
    _circleShape.setRadius(this->getRadius());
    _circleShape.setPointCount(this->getPointCount());
    _circleShape.setPosition(_x,_y);
    _circleShape.setOrigin(_circleShape.getRadius(),_circleShape.getRadius());
    _circleShape.setFillColor(_color);
}

sf::CircleShape Particle::getCircleShape() {return _circleShape;}
int Particle::getNearestRectangleId() {return _nearestRectangleId;}

/*TODO Implement getter and setter for dx and dy, implement the move function and detectedCollision function*/
void Particle::moveParticle(size_t n,SimulationState &state, SimulationWindow* window)
{
    ObjInfo<Rectangle> obj;

    if(obj.sendObjInfo(state.getRectangleVec(),_nearestRectangleId).isAlive)
    {
        if(this->detectCollisionRect(state))
        {
            //std::cout << "rectangle collided id: " << _nearestRectangleId << std::endl;
            state.deleteEl(state.getRectangleVec(),_nearestRectangleId);
            _survived = true;
            this->FindNearestRectangle(state);
        }
        this->moveParticleTowardRect(state);
    }else
    {
        if(!state.getRectangleVec().empty())
        {
            this->FindNearestRectangle(state);
        }else
        {
            this->moveParticleRand(window);
        }
        
    }

    
    _x = _circleShape.getPosition().x;
    _y = _circleShape.getPosition().y;
    this->FindNearestRectangle(state);
    

}

void Particle::moveParticleTowardRect(SimulationState& state)
{
    if(!state.getRectangleVec().empty())
    {
        ObjInfo<Rectangle> obj;
        auto rectangle = obj.sendObjInfo(state.getRectangleVec(),_nearestRectangleId).obj;
        if(_x < rectangle->getX() && _y < rectangle->getY())
        {
            _dx = abs(_dx);
            _dy = abs(_dy);
        }else if(_x > rectangle->getX() && _y < rectangle->getY())
        {
            _dx = abs(_dx)*-1;
            _dy = abs(_dy);
        }else if(_x > rectangle->getX() && _y > rectangle->getY())
        {
            _dx = abs(_dx)*-1;
            _dy = abs(_dy)*-1;
        }else if(_x < rectangle->getX() && _y > rectangle->getY())
        {
            _dx = abs(_dx);
            _dy = abs(_dy)*-1;
        }
        //std::cout << "id: " << _id << " dx: " << _dx << " _dy: " << _dy << std::endl;
        _circleShape.move(_dx,_dy);
    }
    
}

void Particle::moveParticleRand(SimulationWindow* window)
{
    if(_x> window->getSize().x - 100 || _x < 0)
    {
        _dx = _dx*-1;
    }

    if(_y > window->getSize().y - 100 || _y < 100)
    {
        _dy = _dy*-1;
    }
    _circleShape.move(_dx,_dy);
}

void Particle::FindNearestRectangle(SimulationState &state)
{
    //Iterate over all the rectangles and find which one is the most near of the circle
    if(!state.getRectangleVec().empty())
    {
        //initialize min to a "trash value" in order to proceed to the comparison;
        double distance;
        double min = -1;
        for(int i = 0; i < size(state.getRectangleVec()); i++)
        {
            //Check distance
            auto rectangle = state.getRectangleByIndex(i).get();
            
            distance = abs(rectangle->getX() - _x) + abs(rectangle->getY() - _y);
            //std::cout << "particle id: " << _id << " rectangle id: " << rectangle->getId() << " distance: " << distance << std::endl;
            if(distance < min || min == -1)
            {
                min = distance;
                //std::cout << "particle id: " << _id << " rectangle id: " << rectangle->getId() << " min: " << min << std::endl;
                _nearestRectangleId = rectangle->getId();
            }
        }
    }
    
}

bool Particle::detectCollisionRect(SimulationState &state)
{
    //Get rectangle
    ObjInfo<Rectangle> obj;
    auto rectangle = obj.sendObjInfo(state.getRectangleVec(),_nearestRectangleId).obj;
    /***code adapted from this stackoverflow post -> 
    https://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection***/

    double circleDistanceX = abs(_x - (rectangle->getX() + rectangle->getWidth()/2));
    double circleDistanceY = abs(_y- (rectangle->getY() + rectangle->getHeight()/2));

    if (circleDistanceX > (rectangle->getWidth()/2 + this->getRadius())) { return false; }
    if (circleDistanceY > (rectangle->getHeight()/2 + this->getRadius())) { return false; }

    if (circleDistanceX <= (rectangle->getWidth()/2)) {
        return true; 
    } 
    if (circleDistanceY <= (rectangle->getHeight()/2)) {
        return true; 
    }

    double cornerDistance_sq = pow(circleDistanceX- rectangle->getWidth()/2,2) +
                         pow(circleDistanceY - rectangle->getHeight()/2,2);

    return (cornerDistance_sq <= (pow(this->getRadius(),2)));
    
}


double Particle::calculateDistance(std::shared_ptr<Particle>&& particle)
{
    double distanceX = _x - particle.get()->getX();
    double distanceY = _y - particle.get()->getY();
    double distance = sqrt(distanceX * distanceX + distanceY * distanceY);
}