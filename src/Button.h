#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics.hpp>
#include <State.h>
#include <LaunchWindow.h>
#include <string>


enum class ButtonType {plusButton, minusButton};

enum class ButtonFunc {particle, cycle};

class Button : public sf::CircleShape {
    public:
    //Constructor
        Button(std::string font, ButtonType typeButton, float radius, size_t pointCoint, float x, float y,sf::Color color);
    //Functionality
        sf::Text defineText();
        sf::CircleShape defineShapeButton();
        void buttonBehaviour(LaunchWindow *window, LaunchState &state, sf::Event &event);
        bool buttonPressed(LaunchWindow *window, sf::Event &event);
        void addButton(LaunchState &state);
        void minusButton(LaunchState &state);
    //Variables
        std::string _typeFont;
        sf::Font _font;
        std::string  _text;
        ButtonType _typeButton;
        float _radius;
        size_t _pointCount;
        float _x;
        float _y;
        sf::Color _color;
        double _centerX;
        double _centerY;
};
#endif
