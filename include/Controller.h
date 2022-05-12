#pragma once

#include "Bear.h"
#include "Window.h"

class Controller
{
public:
    Controller();
    void play();
    void restartLevel();
    void run();

private:
    void draw();

    Bear m_bear;
    Window m_window;
};