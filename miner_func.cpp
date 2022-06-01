#include <iostream>
#include "structs.hpp"
#include <iomanip>
#include <windows.h>
using namespace std;
int input_x()
{
    int x = -1;
    while (x < 5)
    {
        cout << "Enter x demension of the board: ";
        cin >> x;
        if (x < 5)
            cout << "wrong data, try again" << endl;
    }
    return x + 2;
}
int input_y()
{
    int y = -1;
    while (y < 5)
    {
        cout << "Enter y demension of the board: ";
        cin >> y;
        if (y < 5)
            cout << "wrong data, try again" << endl;
    }
    return y + 2;
}
struct tile **new_map(int x, int y)
{
    struct tile **map = (struct tile **)malloc(y * sizeof(struct tile *));
    for (int i = 0; i < y; i++)
    {
        map[i] = (struct tile *)malloc(x * sizeof(struct tile));
    }
    return map;
}
void init(struct tile **map, int x, int y)
{
    for (int j = 0; j < y; j++)
    {
        for (int i = 0; i < x; i++)
        {
            map[j][i].bomb = false;
            map[j][i].around = 0;
            map[j][i].status = 0;
            if (j == 0 || i == 0 || j == y - 1 || i == x - 1)
                map[j][i].uncovered = -1;
            else
                map[j][i].uncovered = 0;
        }
    }
}

void show_map(struct tile **map, int x, int y, bool win)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "     ";
    for (int i = 1; i < x - 1; i++)
    {
        cout << setw(2) << i; // x counter
        cout << " ";
    }
    cout << endl;
    for (int j = 1; j < y - 1; j++)
    {
        cout << left << setw(4) << j;
        for (int i = 1; i < x - 1; i++)
        {
            if (map[j][i].uncovered == 0)
            {
                cout << "|";
                SetConsoleTextAttribute(hConsole, 26);
                if (map[j][i].bomb == true && win == true)
                {
                    SetConsoleTextAttribute(hConsole, 20);
                    cout << " B";
                }
                else if (map[j][i].status == 0)
                    cout << "  ";
                else
                {
                    SetConsoleTextAttribute(hConsole, 20);
                    cout << "!!";
                }
                SetConsoleTextAttribute(hConsole, 15);
            }
            else
            {
                if (map[j][i].around > 0 && map[j][i].around < 4)
                {
                    cout << "|";
                    SetConsoleTextAttribute(hConsole, 2);
                    cout << setw(2) << map[j][i].around;
                    SetConsoleTextAttribute(hConsole, 15);
                }
                else if (map[j][i].around > 4)
                {
                    cout << "|";
                    SetConsoleTextAttribute(hConsole, 4);
                    cout << setw(2) << map[j][i].around;
                    SetConsoleTextAttribute(hConsole, 15);
                }
                else
                {
                    cout << "|";
                    cout << "  ";
                }
            }
        }
        SetConsoleTextAttribute(hConsole, 15);
        cout << "|" << endl;
    }
    SetConsoleTextAttribute(hConsole, 15);
    cout << endl;
}
void check_close_tiles(struct tile **map, int x, int y)
{
    if (map[y][x].uncovered != -1 && map[y][x].bomb == false && map[y][x].checked == false)
    {
        map[y][x].uncovered = 1;
        map[y][x].checked = true;
        if (map[y][x].around == 0)
        {
            check_close_tiles(map, x, y + 1);
            check_close_tiles(map, x, y - 1);
            check_close_tiles(map, x + 1, y);
            check_close_tiles(map, x - 1, y);
        }
    }
}
int check_around_tile(struct tile **map, int x, int y)
{
    int counter = 0;
    if (map[y + 1][x].bomb == true && map[y + 1][x].uncovered == 0)
        counter++;
    if (map[y - 1][x].bomb == true && map[y - 1][x].uncovered == 0)
        counter++;
    if (map[y][x + 1].bomb == true && map[y][x + 1].uncovered == 0)
        counter++;
    if (map[y][x - 1].bomb == true && map[y][x - 1].uncovered == 0)
        counter++;
    if (map[y + 1][x + 1].bomb == true && map[y + 1][x + 1].uncovered == 0)
        counter++;
    if (map[y - 1][x + 1].bomb == true && map[y - 1][x + 1].uncovered == 0)
        counter++;
    if (map[y + 1][x - 1].bomb == true && map[y + 1][x - 1].uncovered == 0)
        counter++;
    if (map[y - 1][x - 1].bomb == true && map[y - 1][x - 1].uncovered == 0)
        counter++;
    return counter;
}
int map_generator(struct tile **map, int x, int y)
{
    int mines = (int)((x - 2) * (y - 2) / 5);
    int counter = 0;
    int temp_x = 0;
    int temp_y = 0;
    while (counter < mines)
    {
        temp_x = rand() % (x - 2) + 1;
        temp_y = rand() % (y - 2) + 1;
        if (map[temp_y][temp_x].bomb == false && map[temp_y][temp_x].uncovered == 0)
        {
            map[temp_y][temp_x].bomb = true;
            counter++;
        }
    }
    for (int j = 1; j < y - 1; j++)
    {
        for (int i = 1; i < x - 1; i++)
        {
            if (map[j][i].bomb == false && map[j][i].uncovered == 0)
            {
                map[j][i].around = check_around_tile(map, i, j);
            }
        }
    }
    return mines;
}
int uncovered_counter(struct tile **map, int x, int y)
{
    int counter = 0;
    for (int j = 1; j < y - 1; j++)
    {
        for (int i = 1; i < x - 1; i++)
        {
            map[j][i].checked = false;
            if (map[j][i].bomb == false && map[j][i].uncovered == 1)
            {
                counter++;
            }
        }
    }
    return counter;
}
int action_tile_input(int x, int y, int option)
{
    int border;
    if (option == 1)
        border = x - 1;
    else
        border = y - 1;
    int cord = -1;
    while (cord > border || cord < 1)
    {
        if (option == 1)
            cout << "Enter x coordinate of the tile you want to act upon: ";
        else
            cout << "Enter y coordinate of the tile you want to act upon: ";
        cin >> cord;
        if (cord > border || cord < 1)
            cout << "Wrong input, try again." << endl;
    }
    return cord;
}
int action_options()
{
    int option = -1;
    while (option < 1 || option > 4)
    {
        cout << "1 - uncover the tile " << endl;
        cout << "2 - set a flag on it(consider it a dicovered bomb) " << endl;
        cout << "3 - delete the flag " << endl;
        cout << "4 - back " << endl;
        cout << "Enter what you want to do with the tile: ";
        cin >> option;
        if (option < 1 && option > 4)
            cout << "Wrong value, try again: " << endl;
    }
    return option;
}

bool turn(struct tile **map, int x, int y, int *flags, int *mines)
{
    int x_act;
    int y_act;
    for (;;)
    {
        x_act = action_tile_input(x, y, 1);
        y_act = action_tile_input(x, y, 2);
        if (map[y_act][x_act].uncovered == 0)
            break;
        else
            cout << "the tile is already ucovered, try another one" << endl;
    }
    int option;
    if (flags == NULL)
    {
        map[y_act][x_act].uncovered = 1;
        (*mines) = map_generator(map, x, y);
        option = 1;
    }
    else
    option = action_options(); // 1 unc, 2 flag, 3, del flag, 4 back
    switch (option)
    {
    case 1:
    {
        if (map[y_act][x_act].bomb == false && map[y_act][x_act].status == 0)
        {
            map[y_act][x_act].uncovered = 1;
            check_close_tiles(map, x_act, y_act);
        }
        else if (map[y_act][x_act].status == 2)
        {
            cout << "There's a flag on it, delete it first" << endl;
        }
        else
        {
            return true;
        }
        break;
    }
    case 2:
    {
        if (map[y_act][x_act].status != 2 || *flags != 0)
        {
            map[y_act][x_act].status = 2;
            (*flags)--;
        }
        else
            cout << "A flag is already there or you don't have any flags left" << endl;
        break;
    }
    case 3:
    {
        if (map[y_act][x_act].status != 0)
        {
            map[y_act][x_act].status = 0;
            (*flags)++;
        }
        else
            cout << "There's no flag on it" << endl;
        break;
    }
    case 4:
    {
        break;
    }
    }

    return false;
}
void winning(bool win)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (win == true)
    {
        SetConsoleTextAttribute(hConsole, 2);
        cout << "CONGRATS!!! YOU'VE WON, GREAT JOB!" << endl;
    }
    else
    {
        SetConsoleTextAttribute(hConsole, 4);
        cout << "You've underestimated the difficulty of this game and that is why You've lost! LOOSER!" << endl;
    }
    SetConsoleTextAttribute(hConsole, 15);
}
