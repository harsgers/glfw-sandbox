#define GL_SILENCE_DEPRECATION
/* Ask for an OpenGL Core Context */
#define GLFW_INCLUDE_GLCOREARB
#include "GLFW/glfw3.h"
#include <stdio.h>
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

const char *vertex_shader = "#version 400\n"
                            "in vec3 vp;"
                            "void main() {"
                            "  gl_Position = vec4(vp, 1.0);"
                            "}";

const char *fragment_shader = "#version 400\n"
                              "out vec4 frag_colour;"
                              "void main() {"
                              "  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
                              "}";

int main(int argc, char **argv) {
  float points[] = {0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};
  float pointsTwo[] = {0.0f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f};
  float pointsThree[] = {1.0f, 1.0f, 1.0f, 1.0f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit()) {
    return -1;
  }

#ifdef __APPLE__
  /* We need to explicitly ask for a 3.2 context on OS X */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  const GLubyte *renderer = glGetString(GL_RENDERER); // get renderer string
  const GLubyte *version = glGetString(GL_VERSION);   // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);
  // declaring and binding vertex buffer obj
  GLuint verbo = 0;
  glGenBuffers(1, &verbo);
  glBindBuffer(GL_ARRAY_BUFFER, verbo);
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
  // declare and bind verte array obj
  // second buffer obj
  GLuint verboTwo = 1;
  glGenBuffers(1, &verboTwo);
  glBindBuffer(GL_ARRAY_BUFFER, verboTwo);
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), pointsTwo, GL_STATIC_DRAW);

  GLuint vboThree = 2;
  glGenBuffers(1, &vboThree);
  glBindBuffer(GL_ARRAY_BUFFER, vboThree);
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), pointsThree, GL_STATIC_DRAW);


  GLuint verao = 0;
  glGenVertexArrays(1, &verao);
  glBindVertexArray(verao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, verbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  // second
  GLuint second = 1;
  glGenVertexArrays(1, &second);
  glBindVertexArray(second);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, verboTwo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  GLuint third = 2;
  glGenVertexArrays(1, &third);
  glBindVertexArray(third);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vboThree);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  // create shader in GL and load shader fragments above
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);

  // attach and link shaders
  GLuint shader_programme = glCreateProgram();
  glAttachShader(shader_programme, fs);
  glAttachShader(shader_programme, vs);
  glLinkProgram(shader_programme);

  /* Loop until the user closes the window */
  glClearColor(.2, .2, .2, 1);
  while (!glfwWindowShouldClose(window)) {
    // wipe the drawing surface clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_programme);
    glBindVertexArray(verao);
    // draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(second);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(third);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // update other events like input handling
    glfwPollEvents();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}
