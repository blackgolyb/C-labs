#include "task_utils.h"

ColorRGB color_rgb(float r, float g, float b)
{
    ColorRGB res = {r, g, b};
    return res;
}

Axis axis(char *name, float angle, ColorRGB color)
{
    Axis res = {.name = name, .angle = angle, .color = color};
    return res;
}

Point point(float x, float y)
{
    Point res = {.x = x, .y = y};
    return res;
}

Function *function(float (*f)(float))
{
    Function *res = malloc(sizeof(Function));
    ColorRGB color = {0.0f, 0.0f, 0.0f};
    res->color = color;
    res->discretization = 0.01f;
    res->name = "f";
    res->f = f;
    return res;
}

Mouse *create_mouse()
{
    Mouse *res = malloc(sizeof(Mouse));
    res->x = 0;
    res->y = 0;
    res->right_button_pressed = false;
    res->left_button_pressed = false;
    res->middle_button_pressed = false;
    return res;
}

Scene *create_scene(float width, float height)
{
    Scene *res = malloc(sizeof(Scene));
    res->functions = da_create(10, 2, sizeof(Function *));
    res->origin = point(0, 0);
    res->scale = point(10, 10);
    res->show_axes = true;
    res->show_grid = false;
    res->width = width;
    res->height = height;
    res->scale_factor = 1.01f;
    return res;
}

void free_scene(Scene *scene)
{
    da_free(scene->functions);
    free(scene);
}
void scene_add(Scene *scene, Function *function)
{
    da_append(scene->functions, function);
}

void draw_function(Function *function, Scene *scene)
{
    float xmin = -scene->width / (2.0f * scene->scale.x) - scene->origin.x;
    float xmax = scene->width / (2.0f * scene->scale.x) - scene->origin.x;
    int n = ceilf((xmax - xmin) / function->discretization);
    float x, y;

    glLoadIdentity();
    glScalef(2.0f / scene->width * scene->scale.x, 2.0f / scene->height * scene->scale.y, 1.0f);
    glTranslatef(scene->origin.x, scene->origin.y, 0.0f);

    glBegin(GL_LINE_STRIP);
    glColor3f(function->color.r, function->color.g, function->color.b);
    for (int i = 0; i < n; i++)
    {
        x = xmin + function->discretization * i;
        y = function->f(x);
        glVertex2f(x, y);
    }
    glEnd();
}

void draw_axis(Axis axis, Scene *scene)
{
    float arrow_size = 10.0f;
    float angle_rad = (axis.angle * PI) / 180;
    float w = (scene->width / 2.0f * cos(angle_rad) + scene->height / 2.0f * sin(angle_rad));

    glLoadIdentity();
    glScalef(2.0f / scene->width, 2.0f / scene->height, 1.0f);
    glRotatef(axis.angle, 0.0f, 0.0f, 1.0f);

    float t = -scene->scale.x * scene->origin.x * sin(angle_rad) + scene->scale.y * scene->origin.y * cos(angle_rad);

    // glBegin(GL_LINES);
    // glColor3f(0.0f, 0.0f, 0.0f);
    // glVertex2f(-w, 0);
    // glVertex2f(w, 0);
    // glEnd();

    glTranslatef(0.0f, t, 0.0f);

    glBegin(GL_LINES);
    glColor3f(axis.color.r, axis.color.g, axis.color.b);
    glVertex2f(-w, 0);
    glVertex2f(w, 0);
    glEnd();

    glTranslatef(w, 0.0f, 0.0f);

    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    glColor3f(axis.color.r, axis.color.g, axis.color.b);
    glVertex2f(-arrow_size, -arrow_size);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-arrow_size, arrow_size);
    glEnd();

    glLoadIdentity();
}

void draw_axes(Scene *scene)
{
    draw_axis(axis("X", 0.0f, color_rgb(1.0f, 0.0f, 0.0f)), scene);
    draw_axis(axis("Y", 90.0f, color_rgb(0.0f, 1.0f, 0.0f)), scene);
}

void draw_grid(Scene *scene)
{
    float xmin = -scene->width / (2.0f * scene->scale.x) - scene->origin.x;
    float xmax = scene->width / (2.0f * scene->scale.x) - scene->origin.x;
    float ymin = -scene->height / (2.0f * scene->scale.y) - scene->origin.y;
    float ymax = scene->height / (2.0f * scene->scale.y) - scene->origin.y;
    float x, y;
    float xn, yn;

    glLoadIdentity();
    glScalef(2.0f / scene->width * scene->scale.x, 2.0f / scene->height * scene->scale.y, 1.0f);
    glTranslatef(scene->origin.x, scene->origin.y, 0.0f);

    // float grid_size = log(fmax((ymax - ymin), (xmax - xmin)));
    float grid_size = fmax((ymax - ymin), (xmax - xmin)) / 10;

    glBegin(GL_LINES);
    glColor3f(0.8f, 0.8f, 0.8f);
    y = 0;
    while (y <= ymax)
    {
        glVertex2f(xmin, y);
        glVertex2f(xmax, y);
        y += grid_size;
    }

    y = 0;
    while (y >= ymin)
    {
        glVertex2f(xmin, y);
        glVertex2f(xmax, y);
        y -= grid_size;
    }

    x = 0;
    while (x <= xmax)
    {
        glVertex2f(x, ymin);
        glVertex2f(x, ymax);
        x += grid_size;
    }

    x = 0;
    while (x >= xmin)
    {
        glVertex2f(x, ymin);
        glVertex2f(x, ymax);
        x -= grid_size;
    }

    glEnd();
}

void plot(Scene *scene)
{
    if (scene->show_grid)
        draw_grid(scene);

    if (scene->show_axes)
        draw_axes(scene);

    for (int i = 0; i < da_size(scene->functions); i++)
        draw_function(da_get(scene->functions, i), scene);
}

void draw_circle(float x, float y, float radius, ColorRGB color, bool fill, int width, int height)
{
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);
    if (fill)
    {
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(color.r, color.g, color.b);
        glVertex2f(x, y);
    }
    else
        glBegin(GL_LINE_LOOP);

    glColor3f(color.r, color.g, color.b);

    float discretization = 1.0f;
    int n = radius / discretization * 8;
    float d = 2 * PI / n;

    for (int i = 0; i <= n; i++)
    {
        glVertex2f(x + radius * cos(d * i), y + radius * sin(d * i));
    }

    glEnd();
}

void draw_ellipse(float x, float y, float rw, float rh, ColorRGB color, bool fill, int width, int height)
{
    float discretization = 1.0f;
    int n = 2 * (rw + rh) / discretization;
    float d = 2 * PI / n;
    float cx = x + rw / 2.0f;
    float cy = y + rh / 2.0f;

    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);
    if (fill)
    {
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(color.r, color.g, color.b);
        glVertex2f(cx, cy);
    }
    else
        glBegin(GL_LINE_LOOP);

    glColor3f(color.r, color.g, color.b);

    for (int i = 0; i <= n; i++)
    {
        glVertex2f(cx + rw / 2.0f * cos(d * i), cy + rh / 2.0f * sin(d * i));
    }

    glEnd();
}

void draw_rect(float x, float y, float rw, float rh, ColorRGB color, bool fill, int width, int height)
{
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);
    glBegin(fill ? GL_TRIANGLE_FAN : GL_LINE_LOOP);

    glColor3f(color.r, color.g, color.b);

    glVertex2f(x, y);
    glVertex2f(x + rw, y);
    glVertex2f(x + rw, y + rh);
    glVertex2f(x, y + rh);

    glEnd();
}

void draw_diamond(float x, float y, float rw, float rh, ColorRGB color, bool fill, int width, int height)
{
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);
    glBegin(fill ? GL_TRIANGLE_FAN : GL_LINE_LOOP);

    glColor3f(color.r, color.g, color.b);

    glVertex2f(x + rw / 2.0f, y);
    glVertex2f(x + rw, y + rh / 2.0f);
    glVertex2f(x + rw / 2.0f, y + rh);
    glVertex2f(x, y + rh / 2.0f);

    glEnd();
}