#pragma once

#include <memory>
#include "robot.h"

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

private:

    engine();

    robot robot_;
    static std::shared_ptr<engine> instance_;

};
