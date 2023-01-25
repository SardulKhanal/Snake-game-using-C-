#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool Game_over;
const int width = 40;
const int height = 20;
int x, y, fX, fY, score; //fX,fY--fruitX & fruitY
int tailX[100], tailY[100];
int nTail;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN};
Direction directing;
void Game_Setup()
{
    Game_over = false;
    directing = STOP;
    x = width / 2;
    y = height / 2;
    fX = rand() % width;
    fY = rand() % height;
    score = 0;
}
void Making_game_frame()
{
    // system("clear"); //system("clear");
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0}); 
    for (int i = 0; i < width+2; i++)
        cout << "*";
    cout << endl;
 
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "*";
            if (i == y && j == x)
                cout << "O";
            else if (i == fY && j == fX)
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
                 
 
            if (j == width - 1)
                cout << "*";
        }
        cout << endl;
    }
 
    for (int i = 0; i < width+2; i++)
        cout << "*";
    cout << endl;
    cout << "Score:" << score << endl;
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            directing = LEFT;
            break;
        case 'd':
            directing = RIGHT;
            break;
        case 'w':
            directing = UP;
            break;
        case 's':
            directing = DOWN;
            break;
        case 'x':
            Game_over = true;
            break;
        }
    }
}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (directing)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    //if (x > width || x < 0 || y > height || y < 0)
    //  gameOver = true;
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;
 
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            Game_over = true;
 
    if (x == fX && y == fY)
    {
        score += 10;
        fX = rand() % width;
        fY = rand() % height;
        nTail++;
    }
}
int main()
{
    Game_Setup();
    while (!Game_over)
    {
        Making_game_frame();
        Input();
        Logic();
        Sleep(10);
    }
    return 0;
}
