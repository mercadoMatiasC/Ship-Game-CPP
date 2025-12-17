#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <list>

using namespace std;

#define Up 'w'
#define Down 's'
#define Left 'a'
#define Right 'd'

class Spaceship
{
public:
    int x, y;
    int lives = 4, score = 0;

    Spaceship(int _x, int _y)
    {
        x = _x;
        y = _y;
    }

    void paint();
    void remove();
    void move();
    void displayLives();
    void displayScore();
    void gameOverScreen();
};

class Asteroid
{
private:
    int x, y;

public:
    Asteroid(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    void paint();
    void move(Spaceship *sp);
    void collision(Spaceship *sp);
};

void gotoxy(int x, int y);
void hideCursor();
void scene();

int x = 0, y = 0;
char op = 's';

int main()
{
    system("color d");
    do
    {
        system("CLS");
        hideCursor();
        scene();
        gotoxy(10, 10);
        system("pause");
        gotoxy(10, 10);
        printf("                                ");

        Spaceship protoShip(24, 27);
        Asteroid protoAsteroid1(27, 5);
        Asteroid protoAsteroid2(18, 10);
        Asteroid protoAsteroid3(10, 15);
        protoShip.paint();

        bool gameOver = false;

        while (!gameOver)
        {
            protoShip.displayLives();
            protoShip.displayScore();
            protoShip.move();

            protoAsteroid1.move(&protoShip);
            protoAsteroid1.collision(&protoShip);
            protoAsteroid2.move(&protoShip);
            protoAsteroid2.collision(&protoShip);
            protoAsteroid3.move(&protoShip);
            protoAsteroid3.collision(&protoShip);
            Sleep(25);

            if (protoShip.lives < 1)
            {
                gameOver = true;
            }
        }

        protoShip.gameOverScreen();
        gotoxy(18, 13);
        printf("Play again? s/n: ");

        cin >> op;
    } while (op != 'n');

    return 0;
}

void Spaceship::paint()
{
    gotoxy(x, y);
    printf("   ^    ");
    gotoxy(x, y + 1);
    printf("  / \\  ");
    gotoxy(x, y + 2);
    printf(" / ^ \\ ");
    gotoxy(x, y + 3);
    printf("/     \\ ");
    gotoxy(x, y + 4);
    printf("v-----v ");
}
void Spaceship::remove()
{
    gotoxy(x, y);
    printf("         ");
    gotoxy(x, y + 1);
    printf("         ");
    gotoxy(x, y + 2);
    printf("         ");
    gotoxy(x, y + 3);
    printf("         ");
    gotoxy(x, y + 4);
    printf("         ");
}
void Spaceship::move()
{
    if (kbhit())
    {
        char pressedKey = getch();
        remove();
        if (x > 6 && pressedKey == Left)
            x -= 2;
        if (x < 40 && pressedKey == Right)
            x += 2;
        if (y > 4 && pressedKey == Up)
            y--;
        if (y < 27 && pressedKey == Down)
            y++;

        paint();
    }
}
void Spaceship::displayLives()
{
    gotoxy(53, 9);
    printf("Lives:  ");
    gotoxy(60, 9);
    printf("    ");

    for (int i = 0; i < lives; i++)
    {
        gotoxy(60 + i, 9);
        printf("*");
    }
}
void Spaceship::displayScore()
{
    gotoxy(53, 7);
    printf("Score:  ");
    gotoxy(60, 7);
    printf("%d", score);
}
void Spaceship::gameOverScreen()
{
    system("CLS");
    scene();
    gotoxy(18, 7);
    printf("<-- GAME OVER -->");
    gotoxy(18, 10);
    printf("Score: %d", score);
}

void Asteroid::paint()
{
    gotoxy(x, y);
    printf("O");
}
void Asteroid::move(Spaceship *sp)
{
    gotoxy(x, y);
    printf(" ");

    y++;
    if (y > 31)
    {
        sp->score += 500;
        x = rand() % 41 + 5;
        y = 4;
    }
    paint();
}
void Asteroid::collision(Spaceship *sp)
{
    if (x >= sp->x && x < sp->x + 6 && y >= sp->y && y <= sp->y + 5)
    {
        sp->lives -= 1;
        x = rand() % 41 + 5;
        y = 4;
        sp->remove();
        sp->paint();
    }
}

void gotoxy(int x, int y)
{
    HANDLE handling = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handling, pos);
}
void hideCursor()
{
    HANDLE handling = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO actualCursor;
    actualCursor.dwSize = 50;
    actualCursor.bVisible = false;

    SetConsoleCursorInfo(handling, &actualCursor);
}
void scene()
{
    for (int i = 3; i < 78; i++)
    {
        gotoxy(i, 3);
        printf("-");
        gotoxy(i, 32);
        printf("-");
    }

    for (int i = 4; i < 32; i++)
    {
        gotoxy(2, i);
        printf("|");
        gotoxy(50, i);
        printf("|");
        gotoxy(78, i);
        printf("|");
    }

    gotoxy(54, 5);
    printf("<< PROTO-SPACESHIP >>");
    gotoxy(53, 30);
    printf("Murasaki TM 2020 - 2021");
}
