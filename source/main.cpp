// main.cpp
#include "game.h"
#include <iostream>

// This is where the whole application starts
int main()
{
    try
    {
        Game game;
        game.run();
    }
    // Catch any errors
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        std::cout << "Press enter to exit...";
        std::cin.get();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}