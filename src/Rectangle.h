#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SFML/Graphics.hpp>
#include <vector>

class Rectangle : public sf::RectangleShape {
    public:
        Rectangle(int id, double width, double heigth, double x, double y, std::vector<sf::Uint32> color);
        ~Rectangle();
        void defineRectangleShape();
        sf::RectangleShape getRectangleShape();
        int getId();
        double getX();
        double getY();
        double getWidth();
        double getHeight();
        std::vector<sf::Uint32> getColor();
        void setId(int id);
        void setX(double x);
        void setY(double y);
        void setColor(std::vector<sf::Uint32> color);
    private:
        int _id;
        double _width;
        double _height;
        double _x;
        double _y;
        std::vector<sf::Uint32> _color;     
        sf::RectangleShape _rectangleShape;
};
#endif