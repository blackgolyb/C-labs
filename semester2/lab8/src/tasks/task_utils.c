#include "task_utils.h"

ColorRGB color_rgb(float r, float g, float b)
{
    ColorRGB res = {r, g, b};
    return res;
}

ColorRGB color_mix(ColorRGB c1, ColorRGB c2, float t)
{
    ColorRGB res = {
        c1.r + t * (c2.r - c1.r),
        c1.g + t * (c2.g - c1.g),
        c1.b + t * (c2.b - c1.b),
    };
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
    res->scale = point(DEFAULT_SCENE_SCALE, DEFAULT_SCENE_SCALE);
    res->show_axes = true;
    res->show_grid = false;
    res->width = width;
    res->height = height;
    res->scale_factor = 1.01f;
    ColorRGB c = {0.8f, 0.8f, 0.8f};
    // ColorRGB c = {0.5f, 0.5f, 0.5f};
    res->grid_color = c;
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
    float ymin = -scene->height / (2.0f * scene->scale.y) - scene->origin.y;
    float ymax = scene->height / (2.0f * scene->scale.y) - scene->origin.y;
    int n = ceilf((xmax - xmin) / function->discretization);
    float x, y;

    glLoadIdentity();
    glScalef(2.0f / scene->width * scene->scale.x, 2.0f / scene->height * scene->scale.y, 1.0f);
    glTranslatef(scene->origin.x, scene->origin.y, 0.0f);

    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    glColor3f(function->color.r, function->color.g, function->color.b);

    bool skip = false;
    for (int i = 0; i < n; i++)
    {
        x = xmin + function->discretization * i;
        y = function->f(x);

        if (y > ymax || y < ymin)
        {
            glVertex2f(x, y);
            skip = true;
            glEnd();
        }
        else if (skip)
        {
            skip = false;
            glBegin(GL_LINE_STRIP);
            glVertex2f(x - function->discretization, function->f(x - function->discretization));
        }

        if (!skip)
            glVertex2f(x, y);
    }
    glEnd();
    glLineWidth(1.0f);
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
    glLineWidth(1.0f);

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

    ColorRGB c;
    float grid_desc = 5.0f;
    float grid_size = floorf(log(fmax((ymax - ymin), (xmax - xmin))) / log(grid_desc));
    float grid_s1 = powf(grid_desc, grid_size - 1);
    float grid_s2 = powf(grid_desc, grid_size - 2);

    glLoadIdentity();
    glScalef(2.0f / scene->width * scene->scale.x, 2.0f / scene->height * scene->scale.y, 1.0f);
    glTranslatef(scene->origin.x, scene->origin.y, 0.0f);
    glLineWidth(1.0f);

    glBegin(GL_LINES);
    ColorRGB w = {1.0f, 1.0f, 1.0f};
    c = color_mix(w, scene->grid_color, 0.3);
    glColor3f(c.r, c.g, c.b);
    y = 0;
    while (y <= ymax)
    {
        glVertex2f(xmin, y);
        glVertex2f(xmax, y);
        y += grid_s2;
    }

    y = 0;
    while (y >= ymin)
    {
        glVertex2f(xmin, y);
        glVertex2f(xmax, y);
        y -= grid_s2;
    }

    x = 0;
    while (x <= xmax)
    {
        glVertex2f(x, ymin);
        glVertex2f(x, ymax);
        x += grid_s2;
    }

    x = 0;
    while (x >= xmin)
    {
        glVertex2f(x, ymin);
        glVertex2f(x, ymax);
        x -= grid_s2;
    }

    c = scene->grid_color;
    glColor3f(c.r, c.g, c.b);
    y = 0;
    while (y <= ymax)
    {
        glVertex2f(xmin, y);
        glVertex2f(xmax, y);
        y += grid_s1;
    }

    y = 0;
    while (y >= ymin)
    {
        glVertex2f(xmin, y);
        glVertex2f(xmax, y);
        y -= grid_s1;
    }

    x = 0;
    while (x <= xmax)
    {
        glVertex2f(x, ymin);
        glVertex2f(x, ymax);
        x += grid_s1;
    }

    x = 0;
    while (x >= xmin)
    {
        glVertex2f(x, ymin);
        glVertex2f(x, ymax);
        x -= grid_s1;
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

    glPushMatrix();
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
    glPopMatrix();
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

void draw_line(float x1, float y1, float x2, float y2, ColorRGB color, float size, int width, int height)
{
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);
    glLineWidth(size);
    glBegin(GL_LINES);
    glColor3f(color.r, color.g, color.b);

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);

    glEnd();
    glLineWidth(1);
    glPopMatrix();
}

int ft_text_len(char *text, int size, FT_Face face)
{
    FT_Set_Pixel_Sizes(face, 0, size);
    int len = 0;
    while (*text != '\0')
    {
        FT_Load_Char(face, *text, FT_LOAD_NO_BITMAP);
        len += face->glyph->advance.x >> 6;
        text++;
    }
    return len;
}

unsigned char *bitmap_to_rgba(FT_Bitmap bitmap)
{
    unsigned char *image = malloc(bitmap.width * bitmap.rows * 3 * sizeof(unsigned char));

    // for (int i = 0; i < bitmap.width; i++)
    // {
    //     for (int j = 0; j < bitmap.rows; j++)
    //     {
    //         printf("%c", bitmap.buffer[j * bitmap.width + i]? '#' : ' ');
    //         for (int k = 0; k < 4; k++)
    //             image[i + j * bitmap.width + k] = bitmap.buffer[j * bitmap.width + i];
    //     }
    //     putchar('\n');
    // }
    // printf("%d\n", sizeof(unsigned char));
    for (int i = 0; i < bitmap.rows; i++)
    {
        for (int j = 0; j < bitmap.width; j++)
        {
            // printf("%c ", bitmap.buffer[i * bitmap.width + j]? '#' : ' ');
            // printf("%d ", bitmap.buffer[i * bitmap.width + j]);
            // for (int k = 0; k < 3; k++)
            //     image[i * bitmap.width + j + k] = 255;
            // image[i * bitmap.width + j + 3] = bitmap.buffer[i * bitmap.width + j];
            for (int k = 0; k < 3; k++)
                image[i * bitmap.width + j + k] = bitmap.buffer[i * bitmap.width + j];
            // image[i * bitmap.width + j + 3] = bitmap.buffer[i * bitmap.width + j];
        }
        // putchar('\n');
    }

    return image;
}

void draw_text(char *text, int x, int y, int size, TextAlignment align, DrawTextSettings *settings)
{
    if (align == ALIGN_CENTER)
        x -= ft_text_len(text, size, settings->face) / 2;
    else if (align == ALIGN_RIGHT)
        x -= ft_text_len(text, size, settings->face);

    glPushMatrix();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    FT_Set_Pixel_Sizes(settings->face, 0, size);
    glLoadIdentity();
    glOrtho(0, *settings->width, *settings->height, 0, 0, 1);

    FT_GlyphSlot slot = settings->face->glyph;

    for (const char *p = text; *p; p++)
    {
        if (FT_Load_Char(settings->face, *p, FT_LOAD_RENDER))
            continue;

        glRasterPos2i(x + slot->bitmap_left, y + size - slot->bitmap_top);
        glPixelZoom(1, -1);
        glDrawPixels(slot->bitmap.width, slot->bitmap.rows, GL_ALPHA, GL_UNSIGNED_BYTE, slot->bitmap.buffer);

        x += slot->advance.x >> 6; // Додавання ширини літери та проміжку між ними
        y += slot->advance.y >> 6; // Додавання ширини літери та проміжку між ними
    }
    glPopMatrix();
}

void draw_text2(char *text, int x, int y, int size, TextAlignment align, DrawTextSettings *settings)
{
    if (align == ALIGN_CENTER)
        x -= ft_text_len(text, size, settings->face) / 2;
    else if (align == ALIGN_RIGHT)
        x -= ft_text_len(text, size, settings->face);

    glPushMatrix();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    FT_Set_Pixel_Sizes(settings->face, 0, size);
    // Відображення тексту
    // glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, *settings->width, *settings->height, 0, 0, 1);

    // glMatrixMode(GL_MODELVIEW);
    // glColor3f(1.0, 0.0, 0.0); // Білий колір тексту

    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // glPixelTransferi(GL_MAP_COLOR, 1); // использоваь карту
    // const int map_size = 2;
    // float map[] = {1.0f, 0.0f};             // пусть...
    // //...все единицы закрашивают в чёрный, а все нули - в белый цвета...
    // glPixelMapfv(GL_PIXEL_MAP_I_TO_R, map_size, map);
    // glPixelMapfv(GL_PIXEL_MAP_I_TO_G, map_size, map);
    // glPixelMapfv(GL_PIXEL_MAP_I_TO_B, map_size, map);
    // //...и все нули будут прозрачными
    // map[0] = 0, map[1] = 1;
    // glPixelMapfv(GL_PIXEL_MAP_I_TO_A, map_size, map);

    FT_GlyphSlot slot = settings->face->glyph;

    for (const char *p = text; *p; p++)
    {
        if (FT_Load_Char(settings->face, *p, FT_LOAD_RENDER))
            continue;

        // printf("c: %c x: %d y: %d\n", *p, x + slot->bitmap_left, y - slot->bitmap_top);

        // glRasterPos2i(x + slot->bitmap_left, y + slot->bitmap.rows - slot->bitmap_top); //
        glRasterPos2i(x + slot->bitmap_left, y + size - slot->bitmap_top);
        glPixelZoom(1, -1);
        glDrawPixels(slot->bitmap.width, slot->bitmap.rows, GL_ALPHA, GL_UNSIGNED_BYTE, slot->bitmap.buffer);

        x += slot->advance.x >> 6; // Додавання ширини літери та проміжку між ними
        y += slot->advance.y >> 6; // Додавання ширини літери та проміжку між ними
    }
    glPopMatrix();
}

void draw_text1(char *text, int x, int y, int size, DrawTextSettings *settings)
{
    FT_Set_Pixel_Sizes(settings->face, 0, 48);
    // Відображення тексту
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, *settings->width, *settings->height, 0, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glColor3f(1.0, 1.0, 1.0); // Білий колір тексту

    // FT_GlyphSlot slot = settings->face->glyph;
    FT_GlyphSlot g = settings->face->glyph;

    // for (const char *p = text; *p; p++)
    // {
    //     if (FT_Load_Char(settings->face, *p, FT_LOAD_RENDER))
    //     {
    //         continue;
    //     }

    //     // printf("c: %c x: %d y: %d\n", *p, x + slot->bitmap_left, y - slot->bitmap_top);

    //     glRasterPos2i(x + slot->bitmap_left, y - slot->bitmap_top);
    //     glPixelZoom(1, -1);
    //     // glDrawPixels(slot->bitmap.width, slot->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, slot->bitmap.buffer);
    //     glColor3f(1.0f, 0.5f, 0.5f);
    //     printf("\n");
    //     for (int i = 0; i < slot->bitmap.rows; i++)
    //     {
    //         for (int j = 0; j < slot->bitmap.width; j++)
    //         {
    //             char c = slot->bitmap.buffer[i * slot->bitmap.rows + j];
    //             printf("%d", c);
    //         }
    //         printf("\n");
    //     }
    //     return;
    //     glDrawPixels(slot->bitmap.width, slot->bitmap.rows, GL_RGB, GL_UNSIGNED_BYTE, slot->bitmap.buffer);

    //     // x += slot->advance.x >> 6; // Додавання ширини літери та проміжку між ними
    //     x += slot->advance.x >> 6; // Додавання ширини літери та проміжку між ними
    // }

    int length = strlen(text);
    GLuint *textures;
    textures = (GLuint *)malloc(sizeof(GLuint) * length);

    glGenTextures(length, textures);

    // FreeType glyphs are 1-byte greyscale, so we can't use alignment.

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    int i;
    for (i = 0; i < length; ++i)
    {
        // if (FT_Load_Char(settings->face, *p, FT_LOAD_RENDER))
        // {
        //     continue;
        // }
        // Render this particular character using FreeType.

        if (FT_Load_Char(settings->face, text[i], FT_LOAD_RENDER))
            continue;

        // Make the current glyph's texture active.

        glActiveTexture(textures[i]);
        glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, textures[i]);

        /*
         * To prevent artifacts when a character is not rendered exactly on
         * pixel boundaries, clamp the texture to edges, and enable linear
         * interpolation.
         */

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

        // Load the texture.

        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, g->bitmap.width,
                     g->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE,
                     g->bitmap.buffer);

        // Render the texture on the screen.

        glBegin(GL_TRIANGLE_STRIP);

        glTexCoord2i(0, 0);
        glVertex2i(x + 0, y + 0);

        glTexCoord2i(g->bitmap.width, 0);
        glVertex2i(x + g->bitmap.width, y + 0);

        glTexCoord2i(0, g->bitmap.rows);
        glVertex2i(x + 0, y + g->bitmap.rows);

        glTexCoord2i(g->bitmap.width, 0);
        glVertex2i(x + g->bitmap.width, y + 0);

        glTexCoord2i(g->bitmap.width, g->bitmap.rows);
        glVertex2i(x + g->bitmap.width, y + g->bitmap.rows);

        glTexCoord2i(0, g->bitmap.rows);
        glVertex2i(x + 0, y + g->bitmap.rows);

        glEnd();
    }

    glDeleteTextures(length, textures);
    free(textures);
}

int render_text(const char *t, int x, int y, FT_Face f)
{
    int ret = 0;

    GLuint *textures;

    size_t i;
    size_t length = strlen(t);

    FT_GlyphSlot g = f->glyph;

    // Allocate a texture for each character.

    textures = (GLuint *)malloc(sizeof(GLuint) * length);

    if (textures == NULL)
    {
        ret = -ENOMEM;
        goto done;
    }

    glGenTextures(length, textures);

    // FreeType glyphs are 1-byte greyscale, so we can't use alignment.

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Render each character...

    for (i = 0; i < length; ++i)
    {
        // Render this particular character using FreeType.

        if (FT_Load_Char(f, t[i], FT_LOAD_RENDER))
            continue;

        // Make the current glyph's texture active.

        glActiveTexture(textures[i]);
        glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, textures[i]);

        /*
         * To prevent artifacts when a character is not rendered exactly on
         * pixel boundaries, clamp the texture to edges, and enable linear
         * interpolation.
         */

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

        // Load the texture.

        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, g->bitmap.width,
                     g->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE,
                     g->bitmap.buffer);

        // Render the texture on the screen.

        glBegin(GL_TRIANGLE_STRIP);

        glTexCoord2i(0, 0);
        glVertex2i(x + 0, y + 0);

        glTexCoord2i(g->bitmap.width, 0);
        glVertex2i(x + g->bitmap.width, y + 0);

        glTexCoord2i(0, g->bitmap.rows);
        glVertex2i(x + 0, y + g->bitmap.rows);

        glTexCoord2i(g->bitmap.width, 0);
        glVertex2i(x + g->bitmap.width, y + 0);

        glTexCoord2i(g->bitmap.width, g->bitmap.rows);
        glVertex2i(x + g->bitmap.width, y + g->bitmap.rows);

        glTexCoord2i(0, g->bitmap.rows);
        glVertex2i(x + 0, y + g->bitmap.rows);

        glEnd();
    }

    // Free our textures and we're done.

    glDeleteTextures(length, textures);
    free(textures);
done:
    return ret;
}

GLHighlightPair gl_highlight_pair(void *data, ColorRGB color)
{
    GLHighlightPair h = {
        .data = data,
        .color = color,
        .text = "",
    };

    return h;
}

void __bst__draw_bst(BST *tree, BSTNode *node, float x, float y, float width, float height, int lvl, float lvl_dy, int w, int h, FT_Face face, GLHighlightPair *elems, int en)
{
    if (!node)
        return;

    float s = 50;
    // ColorRGB c = {1.0f, 1.0f, 0.0f};
    ColorRGB c = {0.0f, 0.0f, 0.0f};
    ColorRGB cn = {1.0f, 1.0f, 1.0f};

    DrawTextSettings st = {
        .face = face,
        .width = &w,
        .height = &h,
    };

    if (node->left)
        draw_line(x, y + lvl_dy * lvl + s / 2, x - width / 4, y + lvl_dy * (lvl + 1) + s / 2, c, 4, w, h);
    if (node->right)
        draw_line(x, y + lvl_dy * lvl + s / 2, x + width / 4, y + lvl_dy * (lvl + 1) + s / 2, c, 4, w, h);

    for (int i = 0; i < en; i++)
    {
        if (tree->cmp(elems[i].data, node->data) == 0)
        {
            int l = ft_text_len(elems[i].text, s / 2, face);
            cn = elems[i].color;
            draw_text(elems[i].text, x, y + lvl_dy * lvl + s * (5 / 4), s / 2, ALIGN_CENTER, &st);
            break;
        }
    }

    draw_ellipse(x - s / 2, y + lvl_dy * lvl, s, s, cn, true, w, h);
    glLineWidth(2);
    draw_ellipse(x - s / 2, y + lvl_dy * lvl, s, s, c, false, w, h);
    glLineWidth(1);
    char *text = int_to_string(*(int *)node->data);
    draw_text(text, x, y + lvl_dy * lvl + s / 4, s / 2, ALIGN_CENTER, &st);
    // draw_text(text, x, y + lvl_dy * lvl + s / 4, s / 2, &st);
    free(text);

    __bst__draw_bst(tree, node->right, x + width / 4, y, width / 2, height / 2, lvl + 1, lvl_dy, w, h, face, elems, en);
    __bst__draw_bst(tree, node->left, x - width / 4, y, width / 2, height / 2, lvl + 1, lvl_dy, w, h, face, elems, en);
}

void draw_bst(BST *tree, float x, float y, float width, float height, int w, int h, FT_Face face)
{
    float lvl_dy = height / bst_depth(tree);
    __bst__draw_bst(tree, tree->root, x + width / 2, y, width, height, 0, lvl_dy, w, h, face, NULL, 0);
}

void draw_bst_with_highlights(BST *tree, float x, float y, float width, float height, int w, int h, FT_Face face, GLHighlightPair *elems, int en)
{
    float lvl_dy = height / bst_depth(tree);
    __bst__draw_bst(tree, tree->root, x + width / 2, y, width, height, 0, lvl_dy, w, h, face, elems, en);
}