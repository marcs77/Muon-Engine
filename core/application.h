#ifndef APPLICATION_H
#define APPLICATION_H

#include "graphics/window.h"
#include "util/timer.h"

namespace muon {

class Application
{
    public:
        Application(graphics::Window* window);

        void run();
        graphics::Window* window;

    private:

        virtual void loadResources();
        virtual void init();

        virtual void update(double deltaTime);
        virtual void render();

        virtual void dispose();

        Timer delta;
        Timer fps;
        double deltaTime;
        int frames;
};

    void printError(int error, const char* description);

}

#endif // APPLICATION_H
