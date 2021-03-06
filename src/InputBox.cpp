#include <InputBox.h>
#include<string.h>

#include <iostream>


InputBox::InputBox(double x, double y, sf::Vector2f vector) {
    _x = x;
    _y= y;
    _shapeBox.setSize(vector);
    _shapeBox.setPosition(_x,_y);
    _shapeBox.setFillColor(sf::Color(3, 103, 166,100));

}

std::string InputBox::convertIntoText(int &&n)
{
    return std::to_string(n);
}

sf::Text InputBox::displayText(std::string &&str) {
    sf::Text text;
    if(!_font.loadFromFile("../fonts/coolvetica.ttf"))
        return text;
    text.setFont(_font);
    text.setString(str);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(25);
    text.setPosition(_x+13,_y);

    //std::cout << n << std::endl;

    return text;
}

bool InputBox::addInteractivity(LaunchWindow *window, sf::Event &event)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            if(event.mouseButton.x >= _x && event.mouseButton.x <= (_x+_shapeBox.getSize().x) && event.mouseButton.y >= _y && event.mouseButton.y <= (_y+_shapeBox.getSize().y))
            {
                return true;
            }
        }
    }else
        return false;
}