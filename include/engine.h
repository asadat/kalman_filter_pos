#pragma once

#include <memory>
#include "robot.h"
#include <map>

class engine
{
public:

    static std::shared_ptr<engine> get_instance()
    {
        if(!instance_)
            instance_ = std::shared_ptr<engine>(new engine());

        return instance_;
    }

    virtual ~engine();

    void initialize();
    void draw();

    void mouse_click(const int &x, const int &y);
    void keyboard_event(std::map<unsigned char, bool>& keys_pressed);
private:

    engine();

    robot robot_;
    static std::shared_ptr<engine> instance_;

};
