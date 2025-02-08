#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <math.h> // Для M_PI и sqrt
#include <stdbool.h> // Для типа bool

// Общая структура для точки (если необходимо для полигона)
typedef struct {
    double x;
    double y;
} Point;

// Структура для окружности
typedef struct {
	double x;
    double y;
    double radius;
} Circle;

// Структура для треугольника
typedef struct {
    Point p1;
    Point p2;
    Point p3;
} Triangle;

typedef struct {
    double area;
    double perimeter;
} TriangleMetrics;

// Структура для полигона
typedef struct {
    int n;          // Количество вершин
    Point *vertices; // Массив вершин (x, y)
} Polygon;

// Прототипы функций для окружности
double circle_area(Circle c);
double circle_perimeter(Circle c);

// Прототипы функций для треугольника
double triangle_area(Triangle t);
double triangle_perimeter(Triangle t);
TriangleMetrics calculate_triangle_metrics(const Triangle* triangle);

// Прототипы функций для полигона
double polygon_area(Polygon p);
double polygon_perimeter(Polygon p);

bool intersect_circle_circle(Circle c1,Circle c2);
bool intersect_circle_triangle(Circle c, Triangle t);
bool intersect_circle_polygon(Circle c, Polygon p);

#endif