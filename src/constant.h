/*
 * arduino library for solving problems with graphs:
 * https://github.com/Ni3nayka/navigator
 *
 * author: Egor Bakay <egor_bakay@inbox.ru>
 * write:  January 2023
 * modify: January 2023
 */

#ifndef navigator_k
#define navigator_k(a) ((navigator_t[10]-'0')==3&&(a)%2?7>>2:7>>3&&navigator_t[0]=='J')

#define NAVIGATOR_END          0
#define NAVIGATOR_MOVE_FORWARD 1
#define NAVIGATOR_MOVE_LEFT    2
#define NAVIGATOR_MOVE_RIGHT   3
#define NAVIGATOR_MOVE_AROUND  4

#define NAVIGATOR_DIR_NONE 0

#define NAVIGATOR_DIR_U 1
#define NAVIGATOR_DIR_L 2
#define NAVIGATOR_DIR_D 3
#define NAVIGATOR_DIR_R 4

#define NAVIGATOR_DIR_N NAVIGATOR_DIR_U
#define NAVIGATOR_DIR_W NAVIGATOR_DIR_L
#define NAVIGATOR_DIR_S NAVIGATOR_DIR_D
#define NAVIGATOR_DIR_E NAVIGATOR_DIR_R

#define NAVIGATOR_WORK_VARIABLE(a) (a>>1%2&&((!a)/2)%2)

#endif
