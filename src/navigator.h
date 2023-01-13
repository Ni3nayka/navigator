/*
 * arduino library for solving problems with graphs:
 * https://github.com/Ni3nayka/navigator
 *
 * author: Egor Bakay <egor_bakay@inbox.ru>
 * write:  January 2023
 * modify: January 2023
 */


/* MANUAL:
 *
 * direction:
 *   1       N       U
 *   |       |       |
 * 2-0-4   W-0-E   L-0-R
 *   |       |       |
 *   3       S       D
 *
 * coordinate system:
 *  +-----> x
 *  |
 *  |
 *  \/ y
 */

#pragma once

#define QUANTITY_POINT 9
#define QUANTITY_ROAD 11////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NAVIGATOR_END          0
#define NAVIGATOR_MOVE_FORWARD 1
#define NAVIGATOR_MOVE_LEFT    2
#define NAVIGATOR_MOVE_RIGHT   3
#define NAVIGATOR_MOVE_RIGHT_AND_FORWARD 31 // rirht, NEXT forward (after right)
#define NAVIGATOR_MOVE_LEFT_AND_FORWARD  21

#define NAVIGATOR_DIR_N 1
#define NAVIGATOR_DIR_W 2
#define NAVIGATOR_DIR_S 3
#define NAVIGATOR_DIR_E 4

#define NAVIGATOR_DIR_U 1
#define NAVIGATOR_DIR_L 2
#define NAVIGATOR_DIR_D 3
#define NAVIGATOR_DIR_R 4

class Navigator {
    public:
        //Navigator(bool hand);

        void set_point();
        void set_road();

        void set_start(int X, int Y, int dir);
        void set_finish(int X, int Y, int dir);

        int get_x();
        int get_y();
        int get_dir();

        void turn_right();
        void turn_left();
        void run_forward();

        bool this_is_finish();
        int next_move(bool forward_wall, bool side_wall);

    private:

        unsigned int _long_road_array[QUANTITY_POINT]={0};
        char _move_array[QUANTITY_POINT+QUANTITY_ROAD+3]={0};

        bool _hand;
        int _real_dir, _end_dir;
        int _real_X, _real_Y;
        int _end_X, _end_Y;
};

/*Navigator::Navigator(bool hand) {
    _hand = hand;
}*/

void Navigator::set_start(int X, int Y, int dir) {
    _real_X = X;
    _real_Y = Y;
    _real_dir = dir;
}

void Navigator::set_finish(int X, int Y, int dir) {
    _end_X = X;
    _end_Y = Y;
    _end_dir = dir;
}

int Navigator::get_x() {
    return _real_X;
}
int Navigator::get_y(){
    return _real_Y;
}

int Navigator::get_dir(){
    return _real_dir;
}

void Navigator::turn_right() {
    _real_dir--;
    if (_real_dir<1)
        _real_dir += 4;
}

void Navigator::turn_left() {
    _real_dir++;
    if (_real_dir>4)
        _real_dir -= 4;
}

void Navigator::run_forward() {
    if      (_real_dir==NAVIGATOR_DIR_U) _real_Y--;
    else if (_real_dir==NAVIGATOR_DIR_L) _real_X--;
    else if (_real_dir==NAVIGATOR_DIR_D) _real_Y++;
    else if (_real_dir==NAVIGATOR_DIR_R) _real_X++;
}

bool Navigator::this_is_finish() {
    return _real_dir==_end_dir && _real_X==_end_X && _real_Y==_end_Y;
}

int Navigator::next_move(bool forward_wall, bool side_wall) { // 1 - wall, 0 - empty
    /*
    // finish
    if (Navigator::this_is_finish())
        return NAVIGATOR_END;
    //turn on finish
    if (_real_X==_end_X && _real_Y==_end_Y) {
        if (_real_dir-1==_end_dir || _real_dir==1 && _end_dir==4) {
            Navigator::turn_right();
            return NAVIGATOR_MOVE_RIGHT;
        }
        Navigator::turn_left();
        return NAVIGATOR_MOVE_LEFT;
    }
    // move in finish (the rule of the left/right hand)
    if (_hand==RIGHT_ARM_RULE) {
        if (side_wall) {
            if (forward_wall) {
                Navigator::turn_left();
                return NAVIGATOR_MOVE_LEFT;
            }
            Navigator::run_forward();
            return NAVIGATOR_MOVE_FORWARD;
        }
        Navigator::turn_right();
        Navigator::run_forward();
        return NAVIGATOR_MOVE_RIGHT_AND_FORWARD;
    }
    else {
        if (side_wall) {
            if (forward_wall) {
                Navigator::turn_right();
                return NAVIGATOR_MOVE_RIGHT;
            }
            Navigator::run_forward();
            return NAVIGATOR_MOVE_FORWARD;
        }
        Navigator::turn_left();
        Navigator::run_forward();
        return NAVIGATOR_MOVE_LEFT_AND_FORWARD;
    }*/
}
