#include "geometry.h"
#include <malloc.h>
#include <math.h>  // Для M_PI и sqrt
#include <algorithm> // Для std::min и std::max
#include <stdlib.h> // Для NULL

// Функция для вычисления расстояния между двумя точками
double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

bool intersect_circle_circle(Circle c1, Circle c2) {
    double dist = distance(c1.x, c1.y, c2.x, c2.y);
    return dist <= (c1.r + c2.r);
}

// Вспомогательная функция для вычисления знака ориентированной площади
// Это позволяет определить, лежит ли точка справа или слева от прямой
double cross_product(double x1, double y1, double x2, double y2, double x3, double y3) {
    return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
}

// Функция для вычисления расстояния от точки до отрезка
double dist_point_to_segment(double px, double py, double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;

    if (dx == 0 && dy == 0) { // Точки совпадают
        return distance(px, py, x1, y1);
    }

    double t = ((px - x1) * dx + (py - y1) * dy) / (dx * dx + dy * dy);
    t = fmax(0.0, fmin(1.0, t)); // Ограничиваем t от 0 до 1

    double closest_x = x1 + t * dx;
    double closest_y = y1 + t * dy;
    return distance(px, py, closest_x, closest_y);
}

bool intersect_circle_triangle(Circle c, Triangle t) {
    // 1. Проверка, находится ли центр окружности внутри треугольника
    // Используем проверку знаков ориентированных площадей
    bool inside = true;
    inside = inside && (cross_product(t.x1, t.y1, t.x2, t.y2, c.x, c.y) >= 0);
    inside = inside && (cross_product(t.x2, t.y2, t.x3, t.y3, c.x, c.y) >= 0);
    inside = inside && (cross_product(t.x3, t.y3, t.x1, t.y1, c.x, c.y) >= 0);
    if (inside) return true;

    // 2. Проверка пересечения окружности со сторонами треугольника
    if (dist_point_to_segment(c.x, c.y, t.x1, t.y1, t.x2, t.y2) <= c.r) return true;
    if (dist_point_to_segment(c.x, c.y, t.x2, t.y2, t.x3, t.y3) <= c.r) return true;
    if (dist_point_to_segment(c.x, c.y, t.x3, t.y3, t.x1, t.y1) <= c.r) return true;

    // 3. Проверка, находится ли хотя бы одна из вершин треугольника внутри окружности
    double dist_v1 = distance(c.x, c.y, t.x1, t.y1);
    double dist_v2 = distance(c.x, c.y, t.x2, t.y2);
    double dist_v3 = distance(c.x, c.y, t.x3, t.y3);

    if (dist_v1 <= c.r || dist_v2 <= c.r || dist_v3 <= c.r) {
        return true;
    }

    return false;
}

bool intersect_circle_polygon(const Circle& c, const Polygon& p) {
    if (p.num_vertices < 3 || p.x == nullptr || p.y == nullptr) { // Полигон должен иметь минимум 3 вершины
        return false;
    }

    // 1. Проверка, находится ли центр окружности внутри полигона (алгоритм заливки)
    int winding_number = 0;
    for (int i = 0; i < p.num_vertices; ++i) {
        int j = (i + 1) % p.num_vertices;

        if (p.y[i] <= c.y) {
            if (p.y[j] > c.y) {
                if (cross_product(p.x[i], p.y[i], p.x[j], p.y[j], c.x, c.y) > 0) {
                    winding_number++;
                }
            }
        } else {
            if (p.y[j] <= c.y) {
                if (cross_product(p.x[i], p.y[i], p.x[j], p.y[j], c.x, c.y) < 0) {
                    winding_number--;
                }
            }
        }
    }
    if (winding_number != 0) return true; // Центр внутри

    // 2. Проверка пересечения окружности со сторонами полигона
    auto dist_point_to_segment = [&](double px, double py, double x1, double y1, double x2, double y2) -> double {
      double dx = x2 - x1;
      double dy = y2 - y1;

      if (dx == 0 && dy == 0) { // Точки совпадают
        return distance(px, py, x1, y1);
      }

      double t = ((px - x1) * dx + (py - y1) * dy) / (dx * dx + dy * dy);
      t = std::max(0.0, std::min(1.0, t)); // Ограничиваем t от 0 до 1

      double closest_x = x1 + t * dx;
      double closest_y = y1 + t * dy;
      return distance(px, py, closest_x, closest_y);
    };

    for (int i = 0; i < p.num_vertices; ++i) {
        int j = (i + 1) % p.num_vertices;
        if (dist_point_to_segment(c.x, c.y, p.x[i], p.y[i], p.x[j], p.y[j]) <= c.r) {
            return true; // Пересечение со стороной
        }
    }

    // 3. Если ни одно из условий не выполнено, пересечения нет
    return false;
}

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