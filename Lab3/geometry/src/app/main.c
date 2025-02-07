#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <wkt_parser.h> // Подключаем wkt_parser.h
#include <geometry.h>    // Подключаем geometry.h

int main() {
    char input[256];

    printf("Enter figure WKT (e.g., CIRCLE(x y, radius), TRIANGLE(x1 y1, x2 y2, x3 y3), POLYGON((x1 y1, x2 y2, ..., xn yn))): ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        perror("Error reading input");
        return 1;
    }
    input[strcspn(input, "\n")] = 0; // Удаляем символ новой строки

    if (strncmp(input, "CIRCLE(", 7) == 0) {
        Circle circle;
        if (parse_circle_wkt(input, &circle) == 0) {
            print_circle_wkt(&circle);
		 printf("  Perimeter: %f\n", circle_perimeter(circle));
		    printf("  Area: %f\n", circle_area(circle));
        } else {
            printf("Incorrect circle format\n");
            return 1;
        }
    } else if (strncmp(input, "TRIANGLE(", 9) == 0) {
        Triangle triangle;
        if (parse_triangle_wkt(input, &triangle) == 0) {
            print_triangle_wkt(&triangle);

             TriangleMetrics metrics = calculate_triangle_metrics(&triangle);

             printf("Triangle:\n");
             printf("  Perimeter: %f\n", metrics.perimeter);
             printf("  Area: %f\n", metrics.area);
	    //printf("  Perimeter: %f\n", triangle_perimeter(triangle));
	   // printf("  Area: %f\n", triangle_area(triangle));
        } else {
            printf("Incorrect triangle format\n");
            return 1;
        }
    } else if (strncmp(input, "POLYGON((", 9) == 0) {
        Polygon polygon;
        if (parse_polygon_wkt(input, &polygon) == 0) {
            print_polygon_wkt(&polygon);
 printf("  Perimeter: %f\n", polygon_perimeter(polygon));
        printf("  Area: %f\n", polygon_area(polygon));

        // Освобождаем выделенную память
        polygon.vertices = NULL;
        polygon.n = 0;
            free(polygon.vertices);
        } else {
            printf("Incorrect polygon format\n");
            return 1;
        }
    } else {
        printf("Unknown figure type\n");
        return 1;
    }

    return 0;
}