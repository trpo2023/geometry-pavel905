#include "geometry.h"
#include <math.h>

// Вспомогательная функция для вычисления расстояния между двумя точками
double distance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

double triangle_perimeter(Triangle t) {
    double side1 = distance(t.p1, t.p2);
    double side2 = distance(t.p2, t.p3);
    double side3 = distance(t.p3, t.p1);
    return side1 + side2 + side3;
}

double triangle_area(Triangle t) {
    double side1 = distance(t.p1, t.p2);
    double side2 = distance(t.p2, t.p3);
    double side3 = distance(t.p3, t.p1);
    double s = (side1 + side2 + side3) / 2.0; // Полупериметр
    return sqrt(s * (s - side1) * (s - side2) * (s - side3)); // Формула Герона
}