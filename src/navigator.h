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

        void set_start(int X, int Y, int dir);
        void set_finish(int X, int Y, int dir);
        void set_point(int point[QUANTITY_POINT][3]);
        void set_road(int road[QUANTITY_ROAD][3]);

        void set_finish_and_operating(int X, int Y, int dir);

        void operating();
        void operating_long_road(); // get long 1 road

        int get_long_road_to_point(int point);

        int get_x();
        int get_y();
        int get_dir();

        void turn_right();
        void turn_left();
        void run_forward();

        bool this_is_finish();
        int next_move(bool forward_wall, bool side_wall);

    private:

        char _move_array[QUANTITY_POINT+QUANTITY_ROAD+3]={0};
        int _move_point_array[QUANTITY_POINT]={0};
        int _long_road_array[QUANTITY_POINT]={0};

        //bool _hand;
        int _real_dir, _end_dir;
        int _real_X, _real_Y;
        int _end_X, _end_Y;

        int *_point_array, *_road_array;

        int get_long_road_between_points(int a, int b);
};



/*void Navigator::set_point(int **point) {
    _point_array = point;
}*/

void Navigator::set_point(int point[QUANTITY_POINT][3]) {
    _point_array = point[0];
}

void Navigator::set_road(int road[QUANTITY_ROAD][3]) {
    _road_array = road[0];
}

void Navigator::set_finish_and_operating(int X, int Y, int dir) {
    Navigator::set_finish(X,Y,dir);
    Navigator::operating();
}

int Navigator::get_long_road_between_points(int a, int b) {
    for (int i = 0; i<QUANTITY_ROAD; i++) {
        if (*(_road_array+i*3)==a && *(_road_array+i*3+1)==b || *(_road_array+i*3)==b && *(_road_array+i*3+1)==a) {
            return *(_road_array+i*3+2);
        }
    }
    return -1;
}

void Navigator::operating_long_road() {
    for (int i = 0; i<QUANTITY_POINT; i++) _long_road_array[i] = 9999;
    for (int i = 0; i<QUANTITY_POINT; i++) {
        if (*(_point_array+i*3+1)==_real_X && *(_point_array+i*3+2)==_real_Y) {
            _long_road_array[i] = 0;
            _move_point_array[0] = *(_point_array+i*3);
            break;
        }
    }
    bool gg;
    do {
        gg = false;
        for (int a = 0; a<QUANTITY_POINT; a++) {
            for (int b = 0; b<QUANTITY_POINT; b++) {
                if (a!=b) {
                    int d = Navigator::get_long_road_between_points(*(_point_array+a*3),*(_point_array+b*3));
                    if (d!=-1) {
                        //cout << a << " " << b << " " << d << endl;
                        if (_long_road_array[a]+d < _long_road_array[b]) {
                            _long_road_array[b] = _long_road_array[a]+d;
                            gg = true;
                        }
                        if (_long_road_array[b]+d < _long_road_array[a]) {
                            _long_road_array[a] = _long_road_array[b]+d;
                            gg = true;
                        }
                    }
                }
            }
        }

    } while (gg);
    for (int i = 0; i<QUANTITY_POINT; i++) cout << _long_road_array[i] << " "; cout << endl;
}

int Navigator::get_long_road_to_point(int point) {
    for (int i = 0; i<QUANTITY_POINT; i++) {
        if (*(_point_array+i*3)==point) {
            return _long_road_array[i];
        }
    }
    return -1;
}

void Navigator::operating() {
    Navigator::operating_long_road();
    //deikstra
    for (int i = 1; i<QUANTITY_POINT; i++) _move_point_array[i] = -30000;
    int real = _move_point_array[0];
    int I = 1;
    int finish = -30000;
    int long_finish = 0;
    for (int i = 0; i<QUANTITY_POINT; i++) {
        if (*(_point_array+i*3+1)==_end_X && *(_point_array+i*3+2)==_end_Y) {
            finish = *(_point_array+i*3);
            long_finish = _long_road_array[i];
            break;
        }
    }
    while real!=finish {
        for (int i = 0; i<QUANTITY_POINT; i++) {
            int d = Navigator::get_long_road_between_points(real,*(_point_array+i*3));
            if (d!=-1 && _long_road_array[i]+d==) {
                real = *(_point_array+i*3);
                _move_point_array[I] = real;
                I++;
            }
        }
    }
    for (int i = 0; i<QUANTITY_POINT; i++) cout << _move_point_array[i] << " "; cout << endl;
    // coordinates
}


//==================================================================================================================================================================================


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

