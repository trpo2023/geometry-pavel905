#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "wkt_parser.h"
#include "geometry.h"

void print_circle_wkt(const Circle *circle) {
    if (circle == NULL) {
        printf("CIRCLE(EMPTY)\n");
        return;
    }

    printf("CIRCLE((%f %f), %f)\n", circle->x, circle->y, circle->radius);
}

void print_triangle_wkt(const Triangle *triangle) {
    printf("TRIANGLE(%.2f %.2f, %.2f %.2f, %.2f %.2f)\n",
           triangle->p1.x, triangle->p1.y,
           triangle->p2.x, triangle->p2.y,
           triangle->p3.x, triangle->p3.y);
}

void print_polygon_wkt(const Polygon *polygon) {
    printf("POLYGON((");
    for (int i = 0; i < polygon->n; i++) {
        printf("%.2f %.2f", polygon->vertices[i].x, polygon->vertices[i].y);
        if (i < polygon->n - 1) {
            printf(", ");
        }
    }
    printf("))\n");
}

//Вспомогательная функция
int parse_point(const char *str, Point *point, char **end) {
    double x = strtod(str, end);
    if (*end == str || !isspace(**end)) return 1;
    str = *end + 1;

    double y = strtod(str, end);
    if (*end == str) return 1;

    point->x = x;
    point->y = y;
    return 0;
}

int parse_triangle_wkt(const char *wkt_str, Triangle *triangle) {
    const char *prefix = "TRIANGLE(";
    size_t prefix_len = strlen(prefix);

    if (strncmp(wkt_str, prefix, prefix_len) != 0) return 1;

    const char *start = wkt_str + prefix_len;
    char *end;

    if (parse_point(start, &triangle->p1, &end) || *end != ',') return 1;
    start = end + 1;

    if (parse_point(start, &triangle->p2, &end) || *end != ',') return 1;
    start = end + 1;

    if (parse_point(start, &triangle->p3, &end) || *end != ')') return 1;
    if (end[1] != '\0' && end[1] != '\n') return 1;

    return 0;
}

int parse_polygon_wkt(const char *wkt_str, Polygon *polygon) {
    const char *prefix = "POLYGON((";
    size_t prefix_len = strlen(prefix);

    if (strncmp(wkt_str, prefix, prefix_len) != 0) return 1;

    const char *start = wkt_str + prefix_len;
    char *end;
    int n = 1;
    const char *ptr = start;

    while (*ptr != '\0' && *ptr != ')') {
        if (*ptr == ',') n++;
        ptr++;
    }

    polygon->n = n;
    polygon->vertices = (Point*)malloc(n * sizeof(Point));
    if (polygon->vertices == NULL) return 1;

    for (int i = 0; i < n; i++) {
        if (parse_point(start, &polygon->vertices[i], &end)) {
            free(polygon->vertices);
            return 1;
        }
        start = end + 1;
        if (i < n - 1 && *end != ',')
        {
          free(polygon->vertices);
          return 1;
        }
    }
        if (*end != ')')
        {
          free(polygon->vertices);
          return 1;
        }

    return 0;
}

int parse_circle_wkt(const char *wkt_str, Circle *circle) {
    const char *prefix = "CIRCLE(";
    size_t prefix_len = strlen(prefix);

    if (strncmp(wkt_str, prefix, prefix_len) != 0) {
        return 1; // Неверный формат
    }

    const char *start = wkt_str + prefix_len;
    char *end;

    double x, y, r; // Объявляем локальные переменные для x, y и r

    // Разбор x
    end = NULL;
    x = strtod(start, &end);
    if (end == start || !isspace(*end)) { // Проверяем, что после x есть пробел
        return 1; // Ошибка: x не является числом или нет пробела
    }
    start = end + 1; // Передвигаем указатель

    // Разбор y
    end = NULL;
    y = strtod(start, &end);
    if (end == start || *end != ',') { // Проверяем, что после y есть запятая
        return 1; // Ошибка: y не является числом или нет запятой
    }
    start = end + 1; // Передвигаем указатель

    // Разбор радиуса
    end = NULL;
    r = strtod(start, &end);
    if (end == start || *end != ')') { // Проверяем, что после радиуса есть закрывающая скобка
        return 1; // Ошибка: радиус не является числом или нет закрывающей скобки
    }
    if (end[1] != '\0' && end[1] != '\n') {
        return 1; // Ошибка: после закрывающей скобки есть лишние символы
    }

    // Записываем значения в структуру
    circle->x = x;
    circle->y = y;
    circle->radius = r;

    return 0; // Успешный разбор
}