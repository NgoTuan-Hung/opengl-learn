#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    std::cout << "Width: " << width << " Height: " << height << std::endl;
}  

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 geoColor;\n"
    "void main()\n"
    "{\n"
    "   geoColor = aColor;\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *geometryShaderSource = "#version 330 core\n"
"layout (triangles) in;\n"
"layout (triangle_strip, max_vertices = 3) out;\n"
"\n"
"in vec3 geoColor[];\n"
"out vec3 ourColor;\n"
"vec3 center;\n" // Added declaration for center
"\n"
"void main() {\n"
"    center = (gl_in[0].gl_Position.xyz + gl_in[1].gl_Position.xyz + gl_in[2].gl_Position.xyz) / 3;\n"
"    \n"
"    gl_Position = vec4(center + (gl_in[0].gl_Position.xyz - center) * 1.0/3.0, gl_in[0].gl_Position.w);\n"
"    ourColor = geoColor[0];\n"
"    EmitVertex();\n"
"    gl_Position = vec4(center + (gl_in[1].gl_Position.xyz - center) * 1.0/3.0, gl_in[1].gl_Position.w);\n"
"    ourColor = geoColor[1];\n"
"    EmitVertex();\n"
"    gl_Position = vec4(center + (gl_in[2].gl_Position.xyz - center) * 1.0/3.0, gl_in[2].gl_Position.w);\n"
"    ourColor = geoColor[2];\n"
"    EmitVertex();\n"
"    \n"
"    EndPrimitive();\n"
"}\n";

const char *fragmentShaderSource =
    "#version 330 core\n"
    "in vec3 ourColor;\n"
    "out vec4 FragColor;\n\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(ourColor, 1.0f);\n"
    "}"; 

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 
    
    float vertices[] = {
     // positions         // colors
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,    // top 
    0.5f,  0.5f, 0.0f,  0.3f, 0.3f, .3f   // top left 
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,   // first triangle
        1, 2, 3    // second triangle
    };  

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int geometryShader;
    geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryShader, 1, &geometryShaderSource, NULL);
    glCompileShader(geometryShader);

    glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, geometryShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) 
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(geometryShader);
    glDeleteShader(fragmentShader);

    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    GLuint timeLocation = glGetUniformLocation(shaderProgram, "time");
    // for getting the maximum number of vertex attributes
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glUniform1f(timeLocation, glfwGetTime());
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();   
        processInput(window); 
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
  
    return 0;
}