#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include<SFML/Graphics.hpp>

class BaseWindow : public sf::RenderWindow  {
    public:
        //Variables
        unsigned int _width;
        unsigned int _height;
        std::vector<sf::Uint32> _color;

};

#endif