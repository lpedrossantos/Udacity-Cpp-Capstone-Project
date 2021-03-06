#include <Rectangle.h>
#include <iostream>

Rectangle::Rectangle(int id, double width, double heigth, double x, double y, std::vector<sf::Uint32> color)
{
    _id = id;
    _width=width;
    _height=heigth;
    _x=x;
    _y=y;
    _color=color;
    Rectangle::defineRectangleShape();
}
Rectangle::~Rectangle() {
    //std::cout << "Rectangle deleted id:" << _id << std::endl;
}

int Rectangle::getId() {return _id;}
double Rectangle::getX() {return _x;}
double Rectangle::getY() {return _y;}
std::vector<sf::Uint32> Rectangle::getColor(){return _color;}

void Rectangle::defineRectangleShape()
{
    _rectangleShape.setSize(sf::Vector2f(_width,_height));
    _rectangleShape.setPosition(_x,_y);
    _rectangleShape.setFillColor(sf::Color(_color[0],_color[1],_color[2]));
}

sf::RectangleShape Rectangle::getRectangleShape()
{
    return _rectangleShape;
}

double Rectangle::getWidth() {return _width;}
double Rectangle::getHeight() {return _height;}

void Rectangle::setId(int id) {_id = id;}
void Rectangle::setColor(std::vector<sf::Uint32> color) {_color = color;}