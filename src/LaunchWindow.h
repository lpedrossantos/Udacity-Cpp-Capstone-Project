#ifndef LAUNCHWINDOW_H
#define LAUNCHWINDOW_H

#include <sstream>
#include <vector>
#include<BaseWindow.h>
#include <State.h>

class LaunchWindow : public BaseWindow  {
    public:
        LaunchWindow(unsigned int width, unsigned int height,std::vector<sf::Uint32> color);
        std::string getText();
        void init(LaunchState &state);
        void shutDown(LaunchState &state);
        //Variables
        std::string _text;

};

#endif