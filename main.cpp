#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

class Snake
{
public:
    bool gameOver;
    const int width = 20;
    const int height = 20;
    int x, y, fruitX, fruitY, score;
    int tailX[100], tailY[100];
    int Tail_lenght;
    enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
    eDirecton dir, dir_1;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    Tail_lenght = 0;
    score = 0;
}
void Draw()
{
    system("cls");

    cout << "*Gyvatele*" << endl;
    cout << " " << endl;
    cout << "Valdykite gyvatele su 'W A S D' mygtukais" << endl;
    cout << "Norint sustabdyti zaidima spauskite X klavisa" << endl;
    cout << " " << endl;
    cout << "Taskai:" << score << endl;

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < Tail_lenght; k++)
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
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

}
void Input()
{
    dir_1 = dir;

    if (_kbhit())
    {
        switch (_getch())
        {
        case 'A':
        case 'a':
            dir = LEFT;
            break;

        case 'D':
        case 'd':
            dir = RIGHT;
            break;

        case 'W':
        case 'w':
            dir = UP;
            break;

        case 'S':
        case 's':
            dir = DOWN;
            break;

        case 'X':
        case 'x':
            gameOver = true;
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
    for (int i = 1; i < Tail_lenght; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
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

    }
    //visos tokios eilutes tikrina ar neatsitrenkia i save, kai gyvatele yra suvalgiusi viena vaisiu
    if (Tail_lenght == 1 && dir_1 == UP)
	{
		if (dir == DOWN)
		{
			gameOver = true;
		}
	}

    if (Tail_lenght == 1 && dir_1 == DOWN)
	{
		if (dir == UP)
		{
			gameOver = true;
		}
	}

    if (Tail_lenght == 1 && dir_1 == RIGHT)
	{
		if (dir == LEFT)
		{
			gameOver = true;
		}
	}

    if (Tail_lenght == 1 && dir_1 == LEFT)
	{
		if (dir == RIGHT)
		{
			gameOver = true;
		}
	}
	//


    //kodas, kuris padarytu, jog atsitrenkus i siena zaidimas baigtusi
    //if (x > width || x < 0 || y > height || y < 0)
    //  gameOver = true;

    //kodo dalis, kuri leidzia eiti kiaurai sienas
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;
    //

    //jei atsitrenkia i save
    for (int i = 0; i < Tail_lenght; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            gameOver = true;
        }
    }
    //

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        Tail_lenght++;
    }
}
};
int main()
{
    Snake q;

    q.Setup();

    while (!q.gameOver)
    {
        q.Draw();
        q.Input();
        q.Logic();
        //Sleep(10); //norint suletinti gyvatele ivedamas didesnis skaicius
    }

    return 0;
}
