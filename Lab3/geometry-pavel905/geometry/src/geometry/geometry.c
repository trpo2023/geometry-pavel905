#include "geometry.h"
#include <malloc.h>
#include <math.h>  // Для M_PI и sqrt

TriangleMetrics calculate_triangle_metrics(const Triangle* triangle) {
    TriangleMetrics metrics = {0.0, 0.0}; // Инициализируем значениями по умолчанию

    if (triangle == NULL) {
        return metrics; // Возвращаем нулевые значения, если треугольник недействителен
    }

    // Вычисляем длины сторон
    double a = sqrt(pow(triangle->p2.x - triangle->p1.x, 2) + pow(triangle->p2.y - triangle->p1.y, 2));
    double b = sqrt(pow(triangle->p3.x - triangle->p2.x, 2) + pow(triangle->p3.y - triangle->p2.y, 2));
    double c = sqrt(pow(triangle->p1.x - triangle->p3.x, 2) + pow(triangle->p1.y - triangle->p3.y, 2));

    // Вычисляем периметр
    metrics.perimeter = a + b + c;

    // Вычисляем площадь (формула Гаусса/шнуровки)
    metrics.area = 0.5 * fabs((triangle->p1.x * (triangle->p2.y - triangle->p3.y) +
                                 triangle->p2.x * (triangle->p3.y - triangle->p1.y) +
                                 triangle->p3.x * (triangle->p1.y - triangle->p2.y)));

    return metrics;
}

// ---------- Circle ----------

double circle_perimeter(Circle circle) {
   // if (circle == NULL) return 0.0;
    return 2 * M_PI * circle.radius;
}

double circle_area(Circle circle) {
//    if (circle == NULL) return 0.0;
    return M_PI * circle.radius * circle.radius;
}

// ---------- Polygon ----------

// Вспомогательная функция для вычисления расстояния между двумя точками
double distance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

double polygon_perimeter(Polygon polygon) {
  //  if (polygon == NULL || polygon->vertices == NULL || polygon->num_vertices < 3) return 0.0;

    double perimeter = 0.0;
    for (int i = 0; i < polygon.n - 1; i++) {
        perimeter += distance(polygon.vertices[i], polygon.vertices[i + 1]);
    }
    perimeter += distance(polygon.vertices[polygon.n - 1], polygon.vertices[0]); // Замыкаем многоугольник

    return perimeter;
}

double polygon_area(Polygon polygon) {
//    if (polygon == NULL || polygon->vertices == NULL || polygon->num_vertices < 3) return 0.0;

    double area = 0.0;
    for (int i = 0; i < polygon.n - 1; i++) {
        area += (polygon.vertices[i].x * polygon.vertices[i + 1].y - polygon.vertices[i + 1].x * polygon.vertices[i].y);
    }
    area += (polygon.vertices[polygon.n - 1].x * polygon.vertices[0].y - polygon.vertices[0].x * polygon.vertices[polygon.n - 1].y); // Замыкаем
    return 0.5 * fabs(area);
}

static Polygon triangle_to_polygon(const Triangle* triangle) 
{
    Polygon polygon;
    polygon.vertices = (Point*)malloc(3 * sizeof(Point));
    
        polygon.vertices[0] = triangle->p1;
        polygon.vertices[1] = triangle->p2;
        polygon.vertices[2] = triangle->p3;
        polygon.n = 3;

    return polygon;
}

double triangle_perimeter(Triangle triangle) {
//     if (triangle == NULL) return 0.0;

 //   if(polygon.vertices == NULL){
   //     return 0.0;
    //}

 Polygon polygon = triangle_to_polygon(&triangle);
    double perimeter = polygon_perimeter(polygon);
    free(polygon.vertices); // Освобождаем выделенную память
    return perimeter;
}

double triangle_area(Triangle triangle) {
//    if (triangle == NULL) return 0.0;
    //if(polygon.vertices == NULL){
      //  return 0.0;
   // }
Polygon polygon = triangle_to_polygon(&triangle);
    double area = polygon_area(polygon);
    free(polygon.vertices); // Освобождаем выделенную память
    return area;
}