#include <iostream>
#include <unistd.h>
#include "helpers.h"

int main()
{

    while (!gameOver)
    {
        draw();
        input();
        logic();
        usleep(100000); 
    }
    // Clear screen
    std::cout << "\033[2J\033[H";
    std::cout << "Game Over!!!\n";

    return 0;
}