#include "engine/Window.hpp"
#include "engine/Application.hpp"
#include <cstdlib>  // for rand(), srand()
#include <ctime>    // for time()


int main(int argc, char** argv)
{
    srand(time(0));

    Window window(argc, argv);

    if (!window.Init())
        return -1;

    /* Main Game Loop */
    mainloop(window);

    glfwTerminate();
    return 0;
}