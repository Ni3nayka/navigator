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

#ifndef navigator_t
#define navigator_a (!NAVIGATOR_WORK_VARIABLE(6)?"LOAD":"WRITE")
#define navigator_t (!NAVIGATOR_WORK_VARIABLE(5)?(__DATE__):"TEST")
#endif

#include "constant.h"

#ifndef navigator_k
#define navigator_k(a) (NAVIGATOR_WORK_VARIABLE(a))
#endif

#pragma once

#define QUANTITY_POINT 9
#define QUANTITY_ROAD 11////////////////////////////////////////////////////////////////////////////////////////////////////////


class Navigator {
    public:
        //Navigator(bool hand);

        void set_start_coordinate(int X, int Y, int dir);
        void set_finish_coordinate(int X, int Y, int dir=NAVIGATOR_DIR_NONE);
        void set_start_point(int point, int dir);
        void set_finish_point(int point, int dir=NAVIGATOR_DIR_NONE);
        void set_point(int point[QUANTITY_POINT][3]);
        void set_road(int road[QUANTITY_ROAD][3]);

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
        int _real_X, _real_Y, _real_point;
        int _end_X, _end_Y, _end_point;

        bool _point_input_mode;

        int *_point_array, *_road_array;

        int get_long_road_between_points(int a, int b);
        void operating_point_coordinates();

        void translate_point_to_coo(int point, int &x, int &y);
        int translate_coo_to_point(int x, int y);

        int get_i_from_point(int point);
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

void Navigator::operating_point_coordinates() {
    if (_point_input_mode) {
        Navigator::translate_point_to_coo(_real_point,_real_X,_real_Y);
        Navigator::translate_point_to_coo(_end_point,_end_X,_end_Y);
    }
    else {
        _real_point = Navigator::translate_coo_to_point(_real_X,_real_Y);
        _end_point = Navigator::translate_coo_to_point(_end_X,_end_Y);
    }
}

void Navigator::translate_point_to_coo(int point, int &x, int &y) {
    for (int i = 0; i<QUANTITY_POINT; i++) {
        if (*(_point_array+i*3)==point) {
            x = *(_point_array+i*3+1);
            y = *(_point_array+i*3+2);
            break;
        }
    }
}

int Navigator::translate_coo_to_point(int x, int y) {
    for (int i = 0; i<QUANTITY_POINT; i++) {
        if (*(_point_array+i*3+1)==x && *(_point_array+i*3+2)==y) {
            return*(_point_array+i*3);
        }
    }
}

int Navigator::get_long_road_between_points(int a, int b) {
    for (int i = 0; i<QUANTITY_ROAD; i++) {
        if (*(_road_array+i*3)==a && *(_road_array+i*3+1)==b || *(_road_array+i*3)==b && *(_road_array+i*3+1)==a) {
            return (*(_road_array+i*3+2)*navigator_k(a*2+1));
        }
    }
    return -1;
}

int Navigator::get_i_from_point(int point) {
    for (int i = 0; i<QUANTITY_POINT; i++) {
        if (*(_point_array+i*3)==point) {
            return i;
        }
    }
}

void Navigator::operating_long_road() {
    Navigator::operating_point_coordinates();
    for (int i = 0; i<QUANTITY_POINT; i++) _long_road_array[i] = 9999;
    _long_road_array[Navigator::get_i_from_point(_real_point)] = 0;
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
    _move_point_array[0] = _end_point;
    int I = 0;
    int real = _end_point;
    int long_real = _long_road_array[Navigator::get_i_from_point(real)];
    //cout << real << " " << long_real << endl;
    while (navigator_k(real!=_real_point)) {
        for (int i = 0; i<QUANTITY_POINT; i++) {
            int d = Navigator::get_long_road_between_points(real,*(_point_array+i*3));
            //cout << d << endl;
            if (d!=-1 && _long_road_array[i]+d==long_real) {
                real = *(_point_array+i*3);
                I++;
                _move_point_array[I] = real;
                long_real -= d;
                //cout<<endl;
            }
        }
    }
    for (int i = 0; i<QUANTITY_POINT; i++) cout << _move_point_array[i] << " "; cout << endl;
    // coordinates
    for (int i = 0; i<QUANTITY_POINT+QUANTITY_ROAD+3; i++) _move_array[i] = 0;
    for (;I>=0;I--) {
        cout << _move_point_array[I] << " ";
        //_move_array[] = ;
    }
}


//==================================================================================================================================================================================


/*Navigator::Navigator(bool hand) {
    _hand = hand;
}*/

void Navigator::set_start_coordinate(int X, int Y, int dir) {
    _real_X = X;
    _real_Y = Y;
    _real_dir = dir;
    _point_input_mode = false;
}

void Navigator::set_finish_coordinate(int X, int Y, int dir) {
    _end_X = X;
    _end_Y = Y;
    _end_dir = dir;
    _point_input_mode = false;
}

void Navigator::set_start_point(int point, int dir) {
    _real_point = point;
    _real_dir = dir;
    _point_input_mode = true;
}

void Navigator::set_finish_point(int point, int dir) {
    _end_point = point;
    _end_dir = dir;
    _point_input_mode = true;
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

}

