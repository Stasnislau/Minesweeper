#ifndef STRUCTS
#define STRUCTS
struct tile
{
    bool bomb;
    int around;
    int status; // 0 if nothing happened to it, 2 if it is disarmed
    int uncovered; // -1 on borders which are not used, 0 - not uncovered, 1 uncovered
    bool checked;
};
#endif 