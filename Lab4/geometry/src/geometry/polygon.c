#include "../../include/geometry.h"
#include <math.h>

    double polygon_perimeter(Polygon p)
    {
        double perimeter = 0.0;
    if (p.n < 2) return 0.0; // Периметр не определен для полигонов с < 2 вершинами
    for (int i = 0; i < p.n; i++) {
        int j = (i + 1) % p.n;
        double dx = p.vertices[j].x - p.vertices[i].x;
        double dy = p.vertices[j].y - p.vertices[i].y;
        perimeter += sqrt(dx * dx + dy * dy);
    }
    return perimeter;
    }


    double polygon_area(Polygon p)
    {
         double area = 0.0;
    if (p.n < 3) return 0.0; // Площадь не определена для полигонов с < 3 вершинами
    for (int i = 0; i < p.n; i++) {
        int j = (i + 1) % p.n;
        area += (p.vertices[i].x * p.vertices[j].y - p.vertices[j].x * p.vertices[i].y);
    }
    return 0.5 * fabs(area);
    }