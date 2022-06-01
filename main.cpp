#include <iostream>
#include "miner_func.hpp"
#include "structs.hpp"
#include <time.h>
#include "miner_func.cpp"
int main()
{
    srand(time(NULL));
    int x, y;
    bool end = false;
    x = input_x();
    y = input_y();
    struct tile **map = new_map(x, y);
    init(map, x, y);
    int uncovered_not_bombs;
    bool win = false;
    show_map(map, x, y, win);
    int mines;
    int *p_mines = &mines;
    end = turn(map, x, y, NULL, p_mines);
    int flags = mines;
    int *p_flags = &flags;
    while (end == false)
    {
        std::cout << "Remaining flags: " << flags << std::endl;
        uncovered_not_bombs = uncovered_counter(map, x, y);
        if (uncovered_not_bombs + mines == (x - 2) * (y - 2))
        {
            end = true;
            win = true;
        }
        else
        {
            show_map(map, x, y, win);
            end = turn(map, x, y, p_flags,p_mines);
        }
    }
    show_map(map, x, y, true);
    winning(win);
    system("PAUSE");
    return 0;
}