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
 *  NAVIGATOR_DIR_N
 *  NAVIGATOR_DIR_W
 *  NAVIGATOR_DIR_S
 *  NAVIGATOR_DIR_E
 *  
 *  NAVIGATOR_DIR_U
 *  NAVIGATOR_DIR_L
 *  NAVIGATOR_DIR_D
 *  NAVIGATOR_DIR_R
 *
 * coordinate system:
 *  +-----> x
 *  |
 *  |
 *  \/ y
 */

#define QUANTITY_POINT 9 // количесвто точек на карте (обязательно с таким именем)
#define QUANTITY_ROAD 10 // количество связей (дорог) между этими точками (обязательно с таким именем)

#include <navigator.h> // подключаем библиотеку
Navigator navigator; // создаем объект навигатора

int point_array[QUANTITY_POINT][3] = { // массив точек
    // {number_point, x_coordinate, y_coordinate},
    {1,0,0},
    {2,1,0},
    {3,2,0},
    {4,0,1},
    {5,1,1},
    {6,2,1},
    {70,0,2},
    {8,1,2},
    {9,2,2}
};

int road_array[QUANTITY_ROAD][3] = { // массив связей (дорог)
    // {point_a, point_b, long_road>0},
    {1,4,1},
    {2,5,1},
    {2,3,1},
    {3,6,1},
    {4,70,1},
    {4,5,1},
    {5,8,3},
    {6,9,100},
    {70,8,3},
    {8,9,10},
};

/*
map:
(number_point)
-long_point-
0-------------------> x
| (1)     (2)--1--(3)
|  |       |       |
|  1       1       1
|  |       |       |
| (4)--1--(5)     (6)
|  |       |       |
|  1       3      100
|  |       |       |
| (70)-1--(8)--10-(9)
\/ y
*/

void setup() {
  // запустим монитр порта
  Serial.begin(9600); 

  // добавить в навигатор карту
  navigator.set_point(point_array); // добавить в навигатор массив точек (обязательно перед всеми остальными опциями)
  navigator.set_road(road_array); // добавить в навигатор массив связей (дорог) (обязательно перед всеми остальными опциями)
  
  // задать точку старта и направление
  navigator.set_start_coordinate(0,0,NAVIGATOR_DIR_R); // в координатах
  //navigator.set_start_point(1,NAVIGATOR_DIR_R) // по номеру точки

  // задать точку финиша и направление (не обязательно задавать навправление)
  navigator.set_finish_coordinate(2,2,NAVIGATOR_DIR_U); // в координатах
  //navigator.set_finish_coordinate(2,2); // в координатах
  //navigator.set_finish_point(9,NAVIGATOR_DIR_U); // по номеру точки
  //navigator.set_finish_point(9); // по номеру точки

  // если необходимо отъехать от точки "старта", мы можем отметить это в навигаторе для анализа движений из другой точки:
  navigator.turn_right();
  navigator.run_forward();
  navigator.turn_left();
  navigator.run_forward();
  navigator.turn_left();
  navigator.run_forward();
  // т.е. мы приехали в точку 2, направление NAVIGATOR_DIR_U, и отсюда можем начать анализ
  
  // сделать анализ необходимых движений (чтобы из нашего местоположения доехать до точки финиша)
  navigator.operating();
  //navigator.operating_long_road(); // если нам нужно просчитать только расстояния до точек, без просчета движений

  // вывести наиктратчайшие расстояния до всех точек
  Serial.println("long to points:");
  for (int i=0; i<QUANTITY_POINT; i++) {
    int number_point = point_array[i][0];
    int long_road_to_point = navigator.get_long_road_to_point(number_point);
    Serial.print("point: ");
    Serial.print(number_point);
    Serial.print("  long to point: ");
    Serial.println(long_road_to_point);
  }
  
  Serial.println("movies:");
  while (navigator.this_is_finish()==0) { // пока мы не достигли финиша
    int t = navigator.next_move(); // запрашиваем следующее действие
    if (t==NAVIGATOR_END) { // если доехали до конца (в данном примере это не будет вызвано, т.к. как только достигнем финиша выйдем из цикла)
      Serial.println("end"); 
    }
    if (t==NAVIGATOR_MOVE_FORWARD) { // двигаться вперед
      Serial.println("move forvard");
    }
    if (t==NAVIGATOR_MOVE_LEFT) { // повернуть налево
      Serial.println("turn left");
    }
    if (t==NAVIGATOR_MOVE_RIGHT) { // повернуть направо
      Serial.println("turn right");
    }
    if (t==NAVIGATOR_MOVE_AROUND) { // развернуться
      Serial.println("turn around");
    }
    // проверяем местоположение
    Serial.print("x: ");
    Serial.print(navigator.get_x());
    Serial.print("  y: ");
    Serial.print(navigator.get_y());
    Serial.print("  point: ");
    Serial.print(navigator.get_point());
    Serial.print("  direction: ");
    Serial.println(navigator.get_dir());
  }
  Serial.println("end");
}

void loop() {}
