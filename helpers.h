#include <iostream>
#include <unistd.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>

// Custom implementation of _kbhit() for macOS/Linux
int _kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

// Custom implementation of _getch() for macOS/Linux
int _getch()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

int xWidth = 60; 
int yHeight = 20;

int xSnake = 30;
int ySnake = 10;

bool gameOver = false;

char direction = 'D';

void draw()
{
    // Use ANSI escape code to move cursor home instead of system("cls") to prevent flickering
    std::string frame = "\033[H";

    for (int y = 0; y < yHeight; y++)
    {
        for (int x = 0; x < xWidth; x++)
        {
            // Snake
            if (x == xSnake && y == ySnake)
            {
                frame += "X";
            }
            // Walls
            else if (x == 0 || x == xWidth - 1 || y == 0 || y == yHeight - 1)
            {
                frame += "#";
            }
            // Blank Space
            else
            {
                frame += " ";
            }
        }
        frame += "\n";
    }
    std::cout << frame << std::flush;
}

void input()
{
    if (_kbhit())
    {
        char key = _getch();
        if (key == 'w')
            direction = 'W';
        if (key == 'a')
            direction = 'A';
        if (key == 's')
            direction = 'S';
        if (key == 'd')
            direction = 'D';
    }
}

void logic()
{
    // direction of snake
    if (direction == 'D')
        xSnake++;
    if (direction == 'A')
        xSnake--;
    if (direction == 'S')
        ySnake++;
    if (direction == 'W')
        ySnake--;

    // wall collision
    if (xSnake <= 0 || xSnake >= xWidth - 1 || ySnake <= 0 || ySnake >= yHeight - 1)
        gameOver = true;
}