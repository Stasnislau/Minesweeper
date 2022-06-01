#include "miner_func.cpp"
#ifndef HEADER
#define HEADER
int input_x();
int input_y();
struct tile **new_map(int x, int y);
void init(struct tile **map, int x, int y);
int map_generator(struct tile **map, int x, int y);
void show_map(struct tile **map, int x, int y, bool win);
int uncovered_counter(struct tile **map, int x, int y);
int check_around_tile(struct tile **map, int x, int y);
bool turn(struct tile **map, int x, int y, int *flags, int *mines);
int action_options();
int action_tile_input(int x, int y, int option);
void winning(bool win);
#endif