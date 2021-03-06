#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <string>

#include <State.h>
#include <LaunchWindow.h>
#include<SFML/Graphics.hpp>

class InputBox : public sf::RectangleShape
{
    public:
        InputBox(double x,double y,sf::Vector2f vector);
        std::string convertIntoText(int &&n);
        sf::Text displayText(std::string &&str);
        bool addInteractivity(LaunchWindow *window, sf::Event &event);
        //Variables
        sf::RectangleShape _shapeBox;
        double _x;
        double _y;
        sf::Font _font;
};



#endif