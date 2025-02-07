#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// Функция для проверки, является ли строка числом с плавающей точкой
int is_valid_float(const char *str) {
    char *endptr;
    strtod(str, &endptr);
    if (*endptr != '\0' && *endptr != '\n') {
        return 0;  // Не число
    }
    return 1;  // Число
}

// Структура для представления окружности
typedef struct {
  double x;
  double y;
  double r;
} Circle;

// Функция для разбора строки WKT
int parse_circle_wkt(const char *wkt_str, Circle *circle) {
  const char *prefix = "CIRCLE(";
    size_t prefix_len = strlen(prefix);
    
    if(strncmp(wkt_str, prefix, prefix_len) != 0) {
        return 1; // Неверный формат
    }

    const char *start = wkt_str + prefix_len;
    char *end;

    // Разбор x
    circle->x = strtod(start, &end);
    if(end == start || *end != ' '){
        return 1;
    }


start = end + 1;

    // Разбор y
    circle->y = strtod(start, &end);
    if(end == start || *end != ','){
        return 1;
    }
    start = end + 1;

    // Разбор r
    circle->r = strtod(start, &end);
    if (end == start || *end != ')') {
        return 1;
    }
    if(end[1] != '\0' && end[1] !='\n'){
        return 1;
    }

  return 0;
}

// Функция для вывода окружности в формате WKT
void print_circle_wkt(const Circle *circle) {
  printf("CIRCLE(%.2f %.2f, %.2f)\n", circle->x, circle->y, circle->r);
}

int main() {
  char input[256];
  Circle circle;

  printf("Enter circle WKT (e.g., CIRCLE(0.0 0.0, 5.0)): ");
  if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

  // Удаление символа новой строки, если он есть
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    if (parse_circle_wkt(input, &circle) == 0) {
      print_circle_wkt(&circle);
      return 0;
    } else {
      printf("Incorrect input format\n");
      return 1;
  }
}