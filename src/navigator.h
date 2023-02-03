/*
 * arduino library for solving problems with graphs:
 * https://github.com/Ni3nayka/navigator
 *
 * author: Egor Bakay <egor_bakay@inbox.ru>
 * write:  January 2023
 * modify: February 2023
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

class Navigator {

    public:
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
        int get_point();

        void turn_right();
        void turn_left();
        void turn_around();
        void run_forward();

        bool this_is_finish();
        int next_move();

    private:

        char _move_array[QUANTITY_POINT+QUANTITY_ROAD+3]={0};
        int _move_array_i;
        int _move_point_array[QUANTITY_POINT]={0};
        int _long_road_array[QUANTITY_POINT]={0};

        int _real_dir, _end_dir;
        int _real_X, _real_Y, _real_point;
        int _end_X, _end_Y, _end_point;

        int *_point_array, *_road_array;

        int get_long_road_between_points(int a, int b);

        void translate_point_to_coo(int point, int &x, int &y);
        int translate_coo_to_point(int x, int y);

        int get_i_from_point(int point);
};

void Navigator::set_point(int point[QUANTITY_POINT][3]) {
    _point_array = point[0];
}

void Navigator::set_road(int road[QUANTITY_ROAD][3]) {
    _road_array = road[0];
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
            return *(_road_array+i*3+2);
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
    return -1;
}

void Navigator::operating_long_road() {
    for (int i = 0; i<QUANTITY_POINT; i++) _long_road_array[i] = 9999;
    int t = Navigator::get_i_from_point(_real_point);
    if (t==-1) return;
    _long_road_array[t] = 0;
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
    //for (int i = 0; i<QUANTITY_POINT; i++) cout << _long_road_array[i] << " "; cout << endl;
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
    while (real!=_real_point) {
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
    //for (int i = 0; i<QUANTITY_POINT; i++) cout << _move_point_array[i] << " "; cout << endl;
    // coordinates
    for (int i = 0; i<QUANTITY_POINT+QUANTITY_ROAD+3; i++) _move_array[i] = 0;
    _move_array_i = 0;
    int x0 = _real_X, y0 = _real_Y, dir = _real_dir;
    for (;I>0;I--) {
        //cout << _move_point_array[I] << " " << _move_point_array[I-1] << " " << x0 << " " << y0 << " " <<dir << endl;
        int x1,y1;
        Navigator::translate_point_to_coo(_move_point_array[I-1], x1, y1);
        if (x0==x1) {
            if (y1<y0) { // up
                if      (dir==NAVIGATOR_DIR_L) _move_array[_move_array_i++] = NAVIGATOR_MOVE_RIGHT;
                else if (dir==NAVIGATOR_DIR_R) _move_array[_move_array_i++] = NAVIGATOR_MOVE_LEFT;
                else if (dir==NAVIGATOR_DIR_D) _move_array[_move_array_i++] = NAVIGATOR_MOVE_AROUND;
                dir = NAVIGATOR_DIR_U;
            }
            else { // down
                if      (dir==NAVIGATOR_DIR_L) _move_array[_move_array_i++] = NAVIGATOR_MOVE_LEFT;
                else if (dir==NAVIGATOR_DIR_R) _move_array[_move_array_i++] = NAVIGATOR_MOVE_RIGHT;
                else if (dir==NAVIGATOR_DIR_U) _move_array[_move_array_i++] = NAVIGATOR_MOVE_AROUND;
                dir = NAVIGATOR_DIR_D;
            }
        }
        else if (x0>x1) { // left
            if      (dir==NAVIGATOR_DIR_U) _move_array[_move_array_i++] = NAVIGATOR_MOVE_LEFT;
            else if (dir==NAVIGATOR_DIR_R) _move_array[_move_array_i++] = NAVIGATOR_MOVE_AROUND;
            else if (dir==NAVIGATOR_DIR_D) _move_array[_move_array_i++] = NAVIGATOR_MOVE_RIGHT;
            dir = NAVIGATOR_DIR_L;
        }
        else { // right
            if      (dir==NAVIGATOR_DIR_U) _move_array[_move_array_i++] = NAVIGATOR_MOVE_RIGHT;
            else if (dir==NAVIGATOR_DIR_L) _move_array[_move_array_i++] = NAVIGATOR_MOVE_AROUND;
            else if (dir==NAVIGATOR_DIR_D) _move_array[_move_array_i++] = NAVIGATOR_MOVE_LEFT;
            dir = NAVIGATOR_DIR_R;
        }
        _move_array[_move_array_i++] = NAVIGATOR_MOVE_FORWARD;
        x0 = x1;
        y0 = y1;
    }
    if (_end_dir==NAVIGATOR_DIR_U) {
        if      (dir==NAVIGATOR_DIR_L) _move_array[_move_array_i++] = NAVIGATOR_MOVE_RIGHT;
        else if (dir==NAVIGATOR_DIR_R) _move_array[_move_array_i++] = NAVIGATOR_MOVE_LEFT;
        else if (dir==NAVIGATOR_DIR_D) _move_array[_move_array_i++] = NAVIGATOR_MOVE_AROUND;
    }
    else if (_end_dir==NAVIGATOR_DIR_D) {
        if      (dir==NAVIGATOR_DIR_L) _move_array[_move_array_i++] = NAVIGATOR_MOVE_LEFT;
        else if (dir==NAVIGATOR_DIR_R) _move_array[_move_array_i++] = NAVIGATOR_MOVE_RIGHT;
        else if (dir==NAVIGATOR_DIR_U) _move_array[_move_array_i++] = NAVIGATOR_MOVE_AROUND;
    }
    else if (_end_dir==NAVIGATOR_DIR_L) {
        if      (dir==NAVIGATOR_DIR_U) _move_array[_move_array_i++] = NAVIGATOR_MOVE_LEFT;
        else if (dir==NAVIGATOR_DIR_R) _move_array[_move_array_i++] = NAVIGATOR_MOVE_AROUND;
        else if (dir==NAVIGATOR_DIR_D) _move_array[_move_array_i++] = NAVIGATOR_MOVE_RIGHT;
    }
    else if (_end_dir==NAVIGATOR_DIR_R) {
        if      (dir==NAVIGATOR_DIR_U) _move_array[_move_array_i++] = NAVIGATOR_MOVE_RIGHT;
        else if (dir==NAVIGATOR_DIR_L) _move_array[_move_array_i++] = NAVIGATOR_MOVE_AROUND;
        else if (dir==NAVIGATOR_DIR_D) _move_array[_move_array_i++] = NAVIGATOR_MOVE_LEFT;
    }
    _move_array_i = 0;
    //for (int i = 0; i<QUANTITY_POINT+QUANTITY_ROAD+3; i++) cout << (int)_move_array[i] << " "; cout << endl;
}


//==================================================================================================================================================================================

void Navigator::set_start_coordinate(int X, int Y, int dir) {
    _real_X = X;
    _real_Y = Y;
    _real_dir = dir;
    _real_point = Navigator::translate_coo_to_point(_real_X,_real_Y);
}

void Navigator::set_finish_coordinate(int X, int Y, int dir) {
    _end_X = X;
    _end_Y = Y;
    _end_dir = dir;
    _end_point = Navigator::translate_coo_to_point(_end_X,_end_Y);
}

void Navigator::set_start_point(int point, int dir) {
    _real_point = point;
    _real_dir = dir;
    Navigator::translate_point_to_coo(_real_point,_real_X,_real_Y);
}

void Navigator::set_finish_point(int point, int dir) {
    _end_point = point;
    _end_dir = dir;
    Navigator::translate_point_to_coo(_end_point,_end_X,_end_Y);
}

int Navigator::get_x() {
    return _real_X;
}
int Navigator::get_y() {
    return _real_Y;
}

int Navigator::get_dir() {
    return _real_dir;
}

int Navigator::get_point() {
    return _real_point;
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

void Navigator::turn_around() {
    Navigator::turn_left();
    Navigator::turn_left();
}

void Navigator::run_forward() {
    if      (_real_dir==NAVIGATOR_DIR_U) _real_Y--;
    else if (_real_dir==NAVIGATOR_DIR_L) _real_X--;
    else if (_real_dir==NAVIGATOR_DIR_D) _real_Y++;
    else if (_real_dir==NAVIGATOR_DIR_R) _real_X++;
    _real_point = Navigator::translate_coo_to_point(_real_X,_real_Y);
}

bool Navigator::this_is_finish() {
    return (_real_dir==_end_dir || _end_dir==0) && _real_X==_end_X && _real_Y==_end_Y;
}

int Navigator::next_move() {
    if (_move_array[_move_array_i]==NAVIGATOR_END) return 0;
    if (_move_array[_move_array_i]==NAVIGATOR_MOVE_FORWARD) Navigator::run_forward();
    if (_move_array[_move_array_i]==NAVIGATOR_MOVE_LEFT) Navigator::turn_left();
    if (_move_array[_move_array_i]==NAVIGATOR_MOVE_RIGHT) Navigator::turn_right();
    if (_move_array[_move_array_i]==NAVIGATOR_MOVE_AROUND) Navigator::turn_around();
    return _move_array[_move_array_i++];
}
