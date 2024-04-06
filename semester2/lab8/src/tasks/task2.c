#include "task_utils.h"

int WIDTH2 = 500;
int HEIGHT2 = 500;

void task2_error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void task2_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void task2_framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    WIDTH2 = width;
    HEIGHT2 = height;
}

int int_cmp(void *a, void *b)
{
    if (*(int *)a == *(int *)b)
        return 0;

    return *(int *)a > *(int *)b ? 1 : -1;
}

void task2()
{
    GLFWwindow *window;

    glfwSetErrorCallback(task2_error_callback);

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    window = glfwCreateWindow(WIDTH2, HEIGHT2, "lab 8 task 1", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, task2_key_callback);

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(err));
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, task2_framebuffer_size_callback);

    // Your OpenGL initialization code here
    // Ініціалізація FreeType
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        fprintf(stderr, "Failed to initialize FreeType\n");
        return -1;
    }

    // Завантаження шрифта
    FT_Face face;
    if (FT_New_Face(ft, "assets/JetBrainsMonoNerdFontMono-Regular.ttf", 0, &face)) {
        fprintf(stderr, "Failed to load font\n");
        return -1;
    }

    // Встановлення режиму відображення тексту
    // glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    char *text = "Hello, World!";
    DrawTextSettings s = {
        .face=face,
        .width=&WIDTH2,
        .height=&HEIGHT2,
    };


    int data[] = {33, 13, 41, 17, 84, 7, 14, 37, 69, 21, 60, 27, 83, 6, 85};
    int elem = 7;
    int delete[] = {33, 60, 84};
    BST *tree = bst_create(int_cmp);
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        bst_insert(tree, &data[i]);

    bst_print(tree, "int", true);

    int min = *(int *)bst_min(tree);
    int max = *(int *)bst_max(tree);

    GLHighlightPair highlights[6];
    highlights[0] = gl_highlight_pair(&min, color_rgb(0.4f, 0.4f, 1.0f));
    highlights[0].text = "min";
    highlights[1] = gl_highlight_pair(&max, color_rgb(1.0f, 0.4f, 0.4f));
    highlights[1].text = "max";
    highlights[2] = gl_highlight_pair(&delete[0], color_rgb(1.0f, 0.7f, 0.7f));
    highlights[2].text = "root";
    highlights[3] = gl_highlight_pair(&delete[1], color_rgb(1.0f, 0.7f, 0.7f));
    highlights[4] = gl_highlight_pair(&delete[2], color_rgb(1.0f, 0.7f, 0.7f));
    highlights[5] = gl_highlight_pair(&elem, color_rgb(0.7f, 1.0f, 0.7f));
    

    int padding = 20;

    while (!glfwWindowShouldClose(window))
    {
        // Your rendering code here
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        draw_bst_with_highlights(tree, padding, padding, WIDTH2-padding, HEIGHT2-padding, WIDTH2, HEIGHT2, face, highlights, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Звільнення ресурсів
    bst_destroy(tree);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    glfwDestroyWindow(window);
    glfwTerminate();
}
