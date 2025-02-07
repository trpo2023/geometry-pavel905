#include <stdio.h>
#include <geometry.h>

int main()
{
      // Circle
      Circle circle;
      circle.radius = 5.0;
      printf("Circle: Perimeter = %f, Area = %f\n", circle_perimeter(&circle), circle_area(&circle));

      // Triangle
      Triangle triangle;
      triangle.a = 3.0;
      triangle.b = 4.0;
      triangle.c = 5.0;
      printf("Triangle: Perimeter = %f, Area = %f\n", triangle_perimeter(&triangle), triangle_area(&triangle));

      Polygon polygon;
      polygon.sides = 4;
      polygon.side_length = 5.0;
      printf("Polygon: Perimeter = %f, Area = %f\n", polygon_perimeter(&polygon), polygon_area(&polygon));
      return 0;
}