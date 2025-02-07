#ifndef WKT_PARSER_H
#define WKT_PARSER_H

#include "geometry.h"

int parse_circle_wkt(const char *wkt_str, Circle *circle);
int parse_triangle_wkt(const char *wkt_str, Triangle *triangle);
int parse_polygon_wkt(const char *wkt_str, Polygon *polygon);

void print_circle_wkt(const Circle *circle);
void print_triangle_wkt(const Triangle *triangle);
void print_polygon_wkt(const Polygon *polygon);

#endif