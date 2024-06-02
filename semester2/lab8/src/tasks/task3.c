#include "task_utils.h"

int WIDTH3 = 500;
int HEIGHT3 = 500;

void task3_error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void task3_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void task3_framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    WIDTH3 = width;
    HEIGHT3 = height;
}

void draw_elephant(float x, float y)
{
    ColorRGB c = {0.0f, 0.0f, 0.0f};
    ColorRGB c1 = {1.0f, 1.0f, 1.0f};
    glLineWidth(2);

    for (int i = 1; i >= 0; i--)
    {
        if (i)
        {
            c.r = 0.5859375f;
            c.g = 0.6015625f;
            c.b = 0.64453125f;
        }
        else
        {
            c.r = 0.0f;
            c.g = 0.0f;
            c.b = 0.0f;
        }
        // body
        draw_rect(71 + x, 4 + y, 100, 80, c, i, WIDTH3, HEIGHT3);

        // foots
        draw_rect(71 + x, 84 + y, 17, 28, c, i, WIDTH3, HEIGHT3);
        draw_rect(88 + x, 84 + y, 17, 28, c, i, WIDTH3, HEIGHT3);
        draw_rect(137 + x, 84 + y, 17, 28, c, i, WIDTH3, HEIGHT3);
        draw_rect(154 + x, 84 + y, 17, 28, c, i, WIDTH3, HEIGHT3);

        // head
        draw_ellipse(9 + x, 0 + y, 63, 63, c, i, WIDTH3, HEIGHT3);
        draw_diamond(37 + x, 12 + y, 34, 41, c, i, WIDTH3, HEIGHT3);
        draw_ellipse(26 + x, 42 + y, 6, 6, c1, i, WIDTH3, HEIGHT3);
        draw_ellipse(12 + x, 57 + y, 21, 21, c, i, WIDTH3, HEIGHT3);
        draw_ellipse(23 + x, 74 + y, 17, 17, c, i, WIDTH3, HEIGHT3);
        draw_ellipse(19 + x, 89 + y, 14, 14, c, i, WIDTH3, HEIGHT3);
        draw_ellipse(10 + x, 95 + y, 12, 12, c, i, WIDTH3, HEIGHT3);
        draw_ellipse(6 + x, 89 + y, 10, 10, c, i, WIDTH3, HEIGHT3);
        draw_ellipse(4 + x, 83 + y, 8, 8, c, i, WIDTH3, HEIGHT3);
        draw_ellipse(0 + x, 82 + y, 6, 6, c, i, WIDTH3, HEIGHT3);
    }
}

void task3()
{
    GLFWwindow *window;

    glfwSetErrorCallback(task3_error_callback);

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return;
    }

    window = glfwCreateWindow(WIDTH3, HEIGHT3, "lab 8 task 1", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, task3_key_callback);

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(err));
        return;
    }

    glfwSetFramebufferSizeCallback(window, task3_framebuffer_size_callback);

    // Your OpenGL initialization code here

    // Ініціалізація FreeType
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        fprintf(stderr, "Failed to initialize FreeType\n");
        return;
    }

    // Завантаження шрифта
    FT_Face face;
    if (FT_New_Face(ft, "assets/JetBrainsMonoNerdFontMono-Regular.ttf", 0, &face))
    {
        fprintf(stderr, "Failed to load font\n");
        return;
    }

    // Встановлення режиму відображення тексту
    // glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    char *text = "KN-1023b Omelnitskyi A.M.";
    int fsize = 24;
    DrawTextSettings s = {
        .face = face,
        .width = &WIDTH3,
        .height = &HEIGHT3,
    };

    while (!glfwWindowShouldClose(window))
    {
        // Your rendering code here
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        draw_elephant(100, 100);
        draw_text(text, WIDTH3 - 20, HEIGHT3 - fsize - 20, fsize, ALIGN_RIGHT, &s);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
}
