#include <iostream>
#include <stdlib.h> // for EXIT_SUCCESS/FAILURE

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

void error_callback(int code, const char *description);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods);
void mouse_button_callback(GLFWwindow *window, int button, int action,
                           int mods);

struct Window {
  int width{};
  int height{};
};
Window window{480, 480};

struct Mouse {
  double x{};
  double y{};
};
Mouse mouse{0.0, 0.0};

int main() {

  glfwSetErrorCallback(error_callback);

  /* Initialize the library */
  if (!glfwInit()) {
    std::cout << "Unable to initialise GLFW\n";
    return EXIT_FAILURE;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);

  // glfwWindowHint(GLFW_DECORATED, false);

  /* Create a windowed mode window and its OpenGL context */
  GLFWwindow *glfwWindow = glfwCreateWindow(window.width, window.height,
                                            "PomoApp", nullptr, nullptr);
  if (!glfwWindow) {
    glfwTerminate();
    std::cout << "Unable to create GLFW window\n";
    return EXIT_FAILURE;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(glfwWindow);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return EXIT_FAILURE;
  }

  glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);
  glfwSetKeyCallback(glfwWindow, key_callback);
  glfwSetMouseButtonCallback(glfwWindow, mouse_button_callback);

  const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

  int startingX = (mode->width / 2) - (window.width / 2);
  int startingY = (mode->height / 2) - (window.height / 2);

  glfwSetWindowPos(glfwWindow, startingX, startingY);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(glfwWindow)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2f, 0.4f, 0.35f, 1.0f);

    /* Swap front and back buffers */
    glfwSwapBuffers(glfwWindow);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return EXIT_SUCCESS;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void mouse_button_callback(GLFWwindow *window, int button, int action,
                           int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    double xpos{};
    double ypos{};
    glfwGetCursorPos(window, &mouse.x, &mouse.y);
    std::cout << "Mouse X: " << mouse.x << ", Mouse Y: " << mouse.y << '\n';
  }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void error_callback(int code, const char *description) {
  switch (code) {
  case GLFW_NO_ERROR:
    break;
  case GLFW_NOT_INITIALIZED:
    std::cout << "GLFW_NOT_INITIALISED\n";
    break;
  case GLFW_NO_CURRENT_CONTEXT:
    std::cout << "GLFW_NO_CURRENT_CONTEXT\n";
    break;
  case GLFW_INVALID_ENUM:
    std::cout << "GLFW_INVALID_ENUM\n";
    break;
  case GLFW_INVALID_VALUE:
    std::cout << "GLFW_INVALID_VALUE\n";
    break;
  case GLFW_OUT_OF_MEMORY:
    std::cout << "GLFW_OUT_OF_MEMORY\n";
    break;
  case GLFW_API_UNAVAILABLE:
    std::cout << "GLFW_API_UNAVAILABLE\n";
    break;
  case GLFW_VERSION_UNAVAILABLE:
    std::cout << "GLFW_VERSION_UNAVAILABLE\n";
    break;
  case GLFW_PLATFORM_ERROR:
    std::cout << "GLFW_PLATFORM_ERROR\n";
    break;
  case GLFW_FORMAT_UNAVAILABLE:
    std::cout << "GLFW_FORMAT_UNAVAILABLE\n";
    break;
  case GLFW_NO_WINDOW_CONTEXT:
    std::cout << "GLFW_NO_WINDOW_CONTEXT\n";
    break;
  default:
    std::cout << "Invalid GLFW error code\n";
    break;
  }

  std::cout << description << '\n';
}
