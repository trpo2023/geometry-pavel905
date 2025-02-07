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
        } else {
            printf("Incorrect circle format\n");
            return 1;
        }
    } else if (strncmp(input, "TRIANGLE(", 9) == 0) {
        Triangle triangle;
        if (parse_triangle_wkt(input, &triangle) == 0) {
            print_triangle_wkt(&triangle);
        } else {
            printf("Incorrect triangle format\n");
            return 1;
        }
    } else if (strncmp(input, "POLYGON((", 9) == 0) {
        Polygon polygon;
        if (parse_polygon_wkt(input, &polygon) == 0) {
            print_polygon_wkt(&polygon);
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