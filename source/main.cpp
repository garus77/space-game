#include "game.h"
#include <iostream>

int main()
{
    try
    {
        Game game;
        game.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}