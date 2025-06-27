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
        std::cout << "Press enter to exit...";
        std::cin.get();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}