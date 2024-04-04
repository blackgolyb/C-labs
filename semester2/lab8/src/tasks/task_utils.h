#ifndef TASKS_UTILS_H_INCLUDED
#define TASKS_UTILS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <freetype/freetype.h>

#include "dyn_array.h"
#include "utils.h"

#define PI 3.141592654

#define DEFAULT_SCENE_SCALE 20.0f

typedef struct ColorRGB
{
    float r;
    float g;
    float b;
} ColorRGB;

ColorRGB color_rgb(float r, float g, float b);

typedef struct Axis
{
    char *name;
    float angle;

    ColorRGB color;
} Axis;

Axis axis(char *name, float angle, ColorRGB color);

typedef struct Point
{
    float x;
    float y;
} Point;

Point point(float x, float y);

typedef struct Function
{
    char *name;
    float discretization;
    ColorRGB color;
    float (*f)(float);
} Function;

Function *function(float (*f)(float));

typedef struct Mouse
{
    int x;
    int y;
    bool right_button_pressed;
    bool left_button_pressed;
    bool middle_button_pressed;
} Mouse;

Mouse *create_mouse();

typedef struct Scene
{
    DynArray *functions;
    Point origin;
    Point scale;
    ColorRGB grid_color;
    bool show_axes;
    bool show_grid;
    float width;
    float height;
    float scale_factor;
} Scene;

Scene *create_scene(float width, float height);
void free_scene(Scene *scene);
void scene_add(Scene *scene, Function *function);
void draw_function(Function *function, Scene *scene);
void draw_axis(Axis axis, Scene *scene);
void draw_axes(Scene *scene);
void draw_grid(Scene *scene);
void plot(Scene *scene);

void draw_circle(float x, float y, float radius, ColorRGB color, bool fill, int width, int height);
void draw_ellipse(float x, float y, float rw, float rh, ColorRGB color, bool fill, int width, int height);
void draw_rect(float x, float y, float rw, float rh, ColorRGB color, bool fill, int width, int height);
void draw_diamond(float x, float y, float rw, float rh, ColorRGB color, bool fill, int width, int height);
// End uitls.c

#endif