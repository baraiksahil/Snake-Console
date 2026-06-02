#include <iostream>
#include <unistd.h>
#include "helpers.h"

int main()
{

    srand(time(0));

    // Initial snake
    snakeX.push_back(xSnake);
    snakeY.push_back(ySnake);

    foodSpawn();

    // Clear screen once
    std::cout << "\033[2J";

    while (!gameOver)
    {
        draw();
        input();
        logic();
        usleep(150000); // 150ms delay for standard normal gameplay speed
    }
    // Clear screen
    std::cout << "\033[2J\033[H";
    std::cout << "Game Over!!!\n";
    std::cout << "Final Score: " << score << "\n";

    return 0;
}