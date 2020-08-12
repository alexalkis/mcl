// A control is an invisible window, probably catching keypresses
#include "Window.h"

class Control : public Window
{
public:
    Control(Window *_parent) : Window (_parent,0,0)
    {
        show(false);
    };
};

