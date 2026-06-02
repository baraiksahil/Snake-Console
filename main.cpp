#include <iostream>
#include <unistd.h>
#include "helpers.h"

int main()
{

    srand(time(0));

    setup();

    // Clear screen once
    std::cout << "\033[2J";

    while (!gameOver)
    {
        draw();
        input();
        logic();
        usleep(delay);
    }
    // Clear screen
    std::cout << "\033[2J\033[H";
    std::cout << "Game Over!!!\n";
    std::cout << "Final Score: " << score << "\n";

    return 0;
}