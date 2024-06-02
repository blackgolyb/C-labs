#include "task_utils.h"

Scene *scene1;
Mouse *mouse1;

void task1_error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void task1_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        scene1->origin.x = 0.0f;
        scene1->origin.y = 0.0f;
        scene1->scale.x = DEFAULT_SCENE_SCALE;
        scene1->scale.y = DEFAULT_SCENE_SCALE;
    }
}

void task1_scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    float scale = scene1->scale_factor;
    scale = (yoffset > 0 ? scale : -1 / scale) * yoffset;

    float x_window = mouse1->x - scene1->width / 2.0f;
    float y_window = mouse1->y - scene1->height / 2.0f;

    float b_scale_origin_x = x_window / scene1->scale.x - scene1->origin.x;
    float b_scale_origin_y = -y_window / scene1->scale.y - scene1->origin.y;

    float a_scale_origin_x = x_window / scene1->scale.x * scale - scene1->origin.x;
    float a_scale_origin_y = -y_window / scene1->scale.y * scale - scene1->origin.y;

    if ((scene1->scale.x * scale) != 0 && (scene1->scale.y * scale) != 0)
    {
        scene1->scale.x *= scale;
        scene1->scale.y *= scale;

        scene1->origin.x -= a_scale_origin_x - b_scale_origin_x;
        scene1->origin.y -= a_scale_origin_y - b_scale_origin_y;
    }
}

void task1_cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (mouse1->left_button_pressed)
    {
        float dx = xpos - mouse1->x;
        float dy = ypos - mouse1->y;

        dx = dx / scene1->scale.x;
        dy = -dy / scene1->scale.y;

        scene1->origin.x += dx;
        scene1->origin.y += dy;
    }

    mouse1->x = xpos;
    mouse1->y = ypos;
}

void task1_mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_RIGHT:
        if (action == GLFW_PRESS)
            mouse1->right_button_pressed = true;
        else if (action == GLFW_RELEASE)
            mouse1->right_button_pressed = false;
        break;

    case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS)
            mouse1->left_button_pressed = true;
        else if (action == GLFW_RELEASE)
            mouse1->left_button_pressed = false;
        break;

    case GLFW_MOUSE_BUTTON_MIDDLE:
        if (action == GLFW_PRESS)
            mouse1->middle_button_pressed = true;
        else if (action == GLFW_RELEASE)
            mouse1->middle_button_pressed = false;
        break;

    default:
        break;
    }
}

void task1_framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    scene1->width = width;
    scene1->height = height;
}

float func(float x)
{
    // return 1.0f / x;
    return 1.0f / (x * x);
}

void task1()
{
    GLFWwindow *window;
    int WIDTH = 500;
    int HEIGHT = 500;

    FT_Library ft;
    if (FT_Init_FreeType(&ft) != 0)
        exit(1);

    glfwSetErrorCallback(task1_error_callback);

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return;
    }

    window = glfwCreateWindow(WIDTH, HEIGHT, "lab 8 task 1", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, task1_key_callback);
    glfwSetCursorPosCallback(window, task1_cursor_position_callback);
    glfwSetMouseButtonCallback(window, task1_mouse_button_callback);
    glfwSetScrollCallback(window, task1_scroll_callback);

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(err));
        return;
    }

    glfwSetFramebufferSizeCallback(window, task1_framebuffer_size_callback);

    // Your OpenGL initialization code here
    mouse1 = create_mouse();
    scene1 = create_scene(WIDTH, HEIGHT);
    scene1->show_grid = true;
    // scene_add(scene1, function(cosf));
    // scene_add(scene1, function(sinf));
    // scene_add(scene1, function(tanf));
    scene_add(scene1, function(func));

    while (!glfwWindowShouldClose(window))
    {
        // Your rendering code here
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        plot(scene1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    free_scene(scene1);

    glfwDestroyWindow(window);
    glfwTerminate();

    FT_Done_FreeType(ft);
}
