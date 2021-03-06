#include <iostream>
#include <math.h>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include<SFML/Window/Event.hpp>
#include <Button.h>



Button::Button(std::string  font, ButtonType typeButton, float radius, size_t pointCount,float x, float y, sf::Color color) {
    _typeFont = font;
    _typeButton = typeButton;
    typeButton == ButtonType::plusButton ? _text="+" : _text="-";
    _radius = radius;
    _pointCount = pointCount;
    _x = x;
    _y = y;
    _color = color;

}

sf::Text Button::defineText() {
    sf::Text text;
    _font.loadFromFile(_typeFont);
    text.setFont(_font);
    text.setString(_text);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(25);
    text.setPosition(_x,_y);
    sf::FloatRect rectBound = text.getLocalBounds();
    //Center text
    text.setOrigin(sf::Vector2f(rectBound.width / 2.0 + rectBound.left, rectBound.height / 2.0 + rectBound.top));
    return text;
}

sf::CircleShape Button::defineShapeButton() {
    sf::CircleShape circle(_radius,_pointCount);
    circle.setFillColor(_color);
    circle.setPosition(_x,_y);
    circle.setOrigin(_radius,_radius);

    sf::FloatRect rectBound = circle.getLocalBounds();
    _centerX = _x;
    _centerY = _y;

    //std::cout << _centerX << " " << _centerY << std::endl;

    return circle;
}

void Button::buttonBehaviour(LaunchWindow *window, LaunchState &state, sf::Event &event ) {
    //std::cout << "distance: " << sqrt(pow(sf::Mouse::getPosition().x - _centerX,2) + pow(sf::Mouse::getPosition().y - _centerY,2)) << " radius^2: " << _radius << std::endl;
    //If the mouse is under the circle coords
    if(sqrt(pow(event.mouseButton.x - _centerX,2) + pow(event.mouseButton.y - _centerY,2)) <= _radius)
    {
        if(buttonPressed(window, event))
        {
            _typeButton == ButtonType::plusButton ? addButton(state) : minusButton(state);
        }
    }
}

void Button::addButton(LaunchState &state) {
    int i = state.getNumbParticleBegin();
    state.setNumbParticleBegin(i+1);
    //std::cout << *state.getNumbParticleBegin() << std::endl;
}

void Button::minusButton(LaunchState &state) {
    int i = state.getNumbParticleBegin();
    state.setNumbParticleBegin(i-1);
    //std::cout << *state.getNumbParticleBegin() << std::endl;
    
}

bool Button::buttonPressed(LaunchWindow *window, sf::Event &event) {
    
        if(event.type == sf::Event::MouseButtonPressed)
        {
            if(event.mouseButton.button == sf::Mouse::Left)
            {
                _color.a=100;
                return true;
            }
                
        }
        else if(event.type == sf::Event::MouseButtonReleased)
        {
            _color.a = 255;
            return false;
        }
        
    return false;
}
