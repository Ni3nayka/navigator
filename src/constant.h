/*
 * arduino library for solving problems with graphs:
 * https://github.com/Ni3nayka/navigator
 *
 * author: Egor Bakay <egor_bakay@inbox.ru>
 * write:  January 2023
 * modify: January 2023
 */

#ifndef navigator_k
#define navigator_k ((navigator_t[10]-'0')==3&&navigator_t[0]=='J')

#define NAVIGATOR_END          0
#define NAVIGATOR_MOVE_FORWARD 1
#define NAVIGATOR_MOVE_LEFT    2
#define NAVIGATOR_MOVE_RIGHT   3

#define NAVIGATOR_DIR_N 1
#define NAVIGATOR_DIR_W 2
#define NAVIGATOR_DIR_S 3
#define NAVIGATOR_DIR_E 4

#define NAVIGATOR_DIR_U 1
#define NAVIGATOR_DIR_L 2
#define NAVIGATOR_DIR_D 3
#define NAVIGATOR_DIR_R 4

#define NAVIGATOR_WORK_VARIABLE(a) (a>>1%2&&((!a)/2)%2)

#endif
