#include <string>
#include <fstream>
#include <iostream>
#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include<SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <LaunchWindow.h>
#include <Button.h>
#include <InputBox.h>


LaunchWindow::LaunchWindow(unsigned int width, unsigned int height,std::vector<sf::Uint32> color)
{
    _width = width;
    _height = height;
    _color = color;
    _text = LaunchWindow::getText();
}

void LaunchWindow::init(LaunchState &state)  {
    this->create(sf::VideoMode(_width,_height), "Ecosystem - Launch Simulation");
    state.setLaunchWindowState(State::on);
    sf::Font font;
    sf::Text text;
    std::unique_ptr<Button> addButton = std::make_unique<Button>("../fonts/coolvetica.ttf",ButtonType::plusButton,15,15,600,400,sf::Color( 3, 103, 166));
    std::unique_ptr<Button> minusButton = std::make_unique<Button>("../fonts/coolvetica.ttf",ButtonType::minusButton,15,15,500,400,sf::Color( 3, 103, 166));

    std::unique_ptr<InputBox> numbParticleBox = std::make_unique<InputBox>(530,325,sf::Vector2f(30,30));
    std::unique_ptr<InputBox> launchBox = std::make_unique<InputBox>(445,500,sf::Vector2f(215,40));

    font.loadFromFile("../fonts/coolvetica.ttf");
    text.setFont(font);
    text.setString(_text);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(15);
    text.setLineSpacing(1.5);
    text.setPosition(0,100);


    while(this->isOpen())
    {
        sf::Event event;
        while (this->pollEvent(event))
        {
            // Request for closing the window
            if (event.type == sf::Event::Closed)
                this->close();
            addButton->buttonBehaviour(this,state,event);
            minusButton->buttonBehaviour(this,state,event);
            if(launchBox->addInteractivity(this,event))
            {
                this->shutDown(state);
                
            }
        }

        this->clear(sf::Color(_color[0],_color[1],_color[2]));
        this->draw(text);
        this->draw(addButton->defineShapeButton());
        this->draw(addButton->defineText());
        this->draw(minusButton->defineShapeButton());
        this->draw(minusButton->defineText());
        this->draw(numbParticleBox->_shapeBox);
        this->draw(numbParticleBox->displayText(std::move(numbParticleBox->convertIntoText(state.getNumbParticleBegin()))));
        this->draw(launchBox->_shapeBox);
        this->draw(launchBox->displayText("Launch Simulation"));
        this->display();
    }

}

std::string LaunchWindow::getText() {
    std::string line;
    std:: string text;
    std::ifstream filestream("../text/instructions.txt");
    if(filestream.is_open())
    {
        while(std::getline(filestream,line))
        {
            text.append(line);
            text.append("\n");
        }
    }

    return text;

}

void LaunchWindow::shutDown(LaunchState &state)
{
    this->close();
    state.setLaunchWindowState(State::off);

}