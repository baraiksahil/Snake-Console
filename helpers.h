#include <iostream>
#include <unistd.h>

void drawWall()
{
    int xWidth = 200;
    int yHeight = 40;

    int xSnake = 30;
    int ySnake = 15;

    while (true)
    {
        system("cls");
        for (int y = 0; y < yHeight; y++)
        {
            for (int x = 0; x < xWidth; x++)
            {
                // Snake
                if (x == xSnake && y == ySnake)
                {
                    std::cout << "O";
                }

                // Walls
                else if (
                    x == 0 ||
                    x == xWidth - 1 ||
                    y == 0 ||
                    y == yHeight - 1)
                {
                    std::cout << "#";
                }

                // Empty space
                else
                {
                    std::cout << " ";
                }
            }

            std::cout << "\n";
        }

        xSnake++;
        usleep(100000);
    }
}