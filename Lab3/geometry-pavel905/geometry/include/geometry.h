#ifndef GEOMETRY_H
#define GEOMETRY_H

// Для Circle
typedef struct {
    double radius;
} Circle;

double circle_perimeter(const Circle *c);
double circle_area(const Circle *c);

// Для Triangle
typedef struct {
    double a;
    double b;
    double c;
} Triangle;

double triangle_perimeter(const Triangle *t);
double triangle_area(const Triangle *t);


// Для Polygon (простая реализация, можно расширить)
typedef struct {
    int sides;
    double side_length;
} Polygon;

double polygon_perimeter(const Polygon *p);
double polygon_area(const Polygon *p);


#endif