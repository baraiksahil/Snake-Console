#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <vector>

#ifdef _WIN32
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

// Screen size
int xWidth = 60;
int yHeight = 20;

// Snake head position
int xSnake = 20;
int ySnake = 10;

// Snake body
std::vector<int> snakeX;
std::vector<int> snakeY;

// Food position
int xFood;
int yFood;

// Game state
bool gameOver = false;

// Snake direction
char direction = 'D';

// Score
int score = 0;

// Speed (microseconds delay)
int delay = 150000;

void foodSpawn()
{
    // xFood = rand() % (xWidth - 2) + 1;
    // yFood = rand() % (yHeight - 2) + 1;

    bool insideSnake;

    do
    {
        insideSnake = false;
        xFood = rand() % (xWidth - 2) + 1;
        yFood = rand() % (yHeight - 2) + 1;

        // check all snake body parts
        for (int i = 0; i < snakeX.size(); i++)
        {
            if (xFood == snakeX[i] && yFood == snakeY[i])
            {
                insideSnake = true;
                break;
            }
        }
    } while (insideSnake);
}

void draw()
{
    // Use ANSI escape code to move cursor home instead of system("cls") to prevent flickering
    std::string frame = "\033[H";

    // Score
    frame += "Score: " + std::to_string(score) + "\n";

    for (int y = 0; y < yHeight; y++)
    {
        for (int x = 0; x < xWidth; x++)
        {
            // draw snake body
            bool isSnake = false;
            for (int i = 0; i < snakeX.size(); i++)
            {
                if (x == snakeX[i] && y == snakeY[i])
                {
                    isSnake = true;
                    break;
                }
            }

            // Snake position
            if (isSnake)
            {
                frame += "X";
            }
            // Food
            else if (x == xFood && y == yFood)
            {
                frame += "O";
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

    // add new head position
    snakeX.insert(snakeX.begin(), xSnake);
    snakeY.insert(snakeY.begin(), ySnake);

    // food collision
    if (xSnake == xFood && ySnake == yFood)
    {
        score += 10;
        foodSpawn();

        // SPEED INCREASE
        if (delay > 50000)
            delay -= 5000;
    }
    else
    {
        // remove tail
        snakeX.pop_back();
        snakeY.pop_back();
    }

    // wall collision
    if (xSnake <= 0 || xSnake >= xWidth - 1 || ySnake <= 0 || ySnake >= yHeight - 1)
        gameOver = true;

    // self collision
    for (int i = 1; i < snakeX.size(); i++)
    {
        if (xSnake == snakeX[i] && ySnake == snakeY[i])
        {
            gameOver = true;
        }
    }
}