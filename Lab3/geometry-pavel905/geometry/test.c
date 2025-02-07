#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "wkt_parser.h" // Включаем заголовочный файл

// Функция для тестирования parse_polygon_wkt
void test_parse_polygon_wkt() {
    Polygon polygon;
    const char *wkt_string = "POLYGON((0 0, 1 0, 1 1, 0 1, 0 0))";

    if (parse_polygon_wkt(wkt_string, &polygon)) {
        printf("test_parse_polygon_wkt: Polygon parsed successfully\n");
        assert(polygon.n == 5);  // Проверяем количество вершин
        assert(polygon.vertices[0].x == 0.0 && polygon.vertices[0].y == 0.0); // Проверяем координаты первой вершины
        assert(polygon.vertices[1].x == 1.0 && polygon.vertices[1].y == 0.0);
        assert(polygon.vertices[2].x == 1.0 && polygon.vertices[2].y == 1.0);
        assert(polygon.vertices[3].x == 0.0 && polygon.vertices[3].y == 1.0);
        assert(polygon.vertices[4].x == 0.0 && polygon.vertices[4].y == 0.0);

        free(polygon.vertices); // Не забываем освободить память
        polygon.vertices = NULL;
        polygon.n = 0;
    } else {
        printf("test_parse_polygon_wkt: Error parsing polygon\n");
        assert(0); // Тест провален
    }
}

// Функция для тестирования print_polygon_wkt (проверяем только, что не происходит ошибок)
void test_print_polygon_wkt() {
    Polygon polygon;
    const char *wkt_string = "POLYGON((0 0, 1 0, 1 1, 0 1, 0 0))";
    if (parse_polygon_wkt(wkt_string, &polygon)) {
        printf("test_print_polygon_wkt: Printing polygon...\n");
        print_polygon_wkt(&polygon);

        free(polygon.vertices); // Не забываем освободить память
        polygon.vertices = NULL;
        polygon.n = 0;
    } else {
        printf("test_print_polygon_wkt: Error parsing polygon\n");
        assert(0); // Тест провален
    }
}

int main() {
    printf("Running tests...\n");
    test_parse_polygon_wkt();
    test_print_polygon_wkt();
    printf("All tests passed!\n");

    return 0;
}