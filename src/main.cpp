#include "Diagnostics.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <iostream>

void mouse_position_callback(GLFWwindow* window, double xpos,double ypos);
void handleInput(GLFWwindow* window);

float x = 1.0f;
float y = 1.0f;
int main()
{

// Inicialize GLFW
if( !glfwInit() )
{
    std::cout << "Error to initialize GLFW\n" ;
    return -1;
}


glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Queremos OpenGL 3.3
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Para hacer feliz a MacOS
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //No queremos el viejo OpenGL 

//Crete window and OpenGL context
GLFWwindow* window = glfwCreateWindow( 1024, 768, "YEAh", NULL, NULL);
if( window == NULL ){
    std::cout << "Fail to create window GLFW. not compatible with 3.3. trye other version GLFW 2.1\n";
    glfwTerminate();
    return -1;
}
glfwMakeContextCurrent(window); // Inicialize GLEW
glewExperimental=true; // base profile .
if (glewInit() != GLEW_OK) {
    std::cout <<  "Failed to initialize GLEW\n";
    return -1;
}

glfwSetCursorPosCallback(window,mouse_position_callback);

//Create shader program
GLuint ShaderProgram = glCreateProgram();
GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

std::ifstream vertexFile("/home/aitor/Desktop/Projects/c++/OpenGLProject/shaders/vertex.sh");
std::ifstream fragmentFile("/home/aitor/Desktop/Projects/c++/OpenGLProject/shaders/fragment.sh");

if(!vertexFile.is_open() || !fragmentFile.is_open()) 
{
    std::cerr << "failed to open the file\n";
    return -1;
}

std::string vertexSource{std::istreambuf_iterator<char>(vertexFile),std::istreambuf_iterator<char>()};
std::string fragmentSource{std::istreambuf_iterator<char>(fragmentFile),std::istreambuf_iterator<char>()};
const char* vert = vertexSource.c_str();
const char* frag = fragmentSource.c_str();

glShaderSource(VertexShader,1,&vert,0);
glShaderSource(FragmentShader,1,&frag,0);
glCompileShader(VertexShader);
DebugShaderCompileStatus(VertexShader, "vertex");
glCompileShader(FragmentShader);
DebugShaderCompileStatus(FragmentShader, "fragment");
glAttachShader(ShaderProgram,VertexShader);
glAttachShader(ShaderProgram,FragmentShader);
glLinkProgram(ShaderProgram);
glDetachShader(ShaderProgram,VertexShader);
glDetachShader(ShaderProgram,FragmentShader);
glDeleteShader(VertexShader);
glDeleteShader(FragmentShader);
glUseProgram(ShaderProgram);


//cube

	float cube[36*6] =
	{
		//back face - orange
	   -0.5f, -0.5f, -0.5f,     0.9f, 0.5f,0.0f,
		0.5f, -0.5f, -0.5f,     0.9f, 0.5f,0.0f,
		0.5f,  0.5f, -0.5f,     0.9f, 0.5f,0.0f,
		0.5f,  0.5f, -0.5f,     0.9f, 0.5f,0.0f,
	   -0.5f,  0.5f, -0.5f,     0.9f, 0.5f,0.0f,
	   -0.5f, -0.5f, -0.5f,     0.9f, 0.5f,0.0f,
	   //front face -- green
	   -0.5f, -0.5f,  0.5f,     0.0f, 1.0f,0.0f,
		0.5f, -0.5f,  0.5f,     1.0f, 0.0f,0.0f,
		0.5f,  0.5f,  0.5f,     0.0f, 0.0f,1.0f,
		0.5f,  0.5f,  0.5f,     0.0f, 1.0f,0.0f,
	   -0.5f,  0.5f,  0.5f,     0.0f, 1.0f,0.0f,
	   -0.5f, -0.5f,  0.5f,     0.0f, 1.0f,0.0f,
	   //left face--- blue
	   -0.5f,  0.5f,  0.5f,     0.0f, 0.0f,1.0f,
	   -0.5f,  0.5f, -0.5f,     0.0f, 0.0f,1.0f,
	   -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,1.0f,
	   -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,1.0f,
	   -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,1.0f,
	   -0.5f,  0.5f,  0.5f,     0.0f, 0.0f,1.0f,
	   //right face
		0.5f,  0.5f,  0.5f,     1.0f, 0.0f,1.0f,
		0.5f,  0.5f, -0.5f,     1.0f, 0.0f,1.0f,
		0.5f, -0.5f, -0.5f,     1.0f, 0.0f,1.0f,
		0.5f, -0.5f, -0.5f,     1.0f, 0.0f,1.0f,
		0.5f, -0.5f,  0.5f,     1.0f, 0.0f,1.0f,
		0.5f,  0.5f,  0.5f,     1.0f, 0.0f,1.0f,
		//buttom  
	   -0.5f, -0.5f, -0.5f,     0.5f, 0.5f,1.0f,
		0.5f, -0.5f, -0.5f,     0.5f, 0.5f,1.0f,
		0.5f, -0.5f,  0.5f,     0.5f, 0.5f,1.0f,
		0.5f, -0.5f,  0.5f,     0.5f, 0.5f,1.0f,
	   -0.5f, -0.5f,  0.5f,     0.5f, 0.5f,1.0f,
	   -0.5f, -0.5f, -0.5f,     1.0f, 1.0f,1.0f,
	   //top                    red
	   -0.5f,  0.5f, -0.5f,     1.0f, 0.0f,0.0f,
		0.5f,  0.5f, -0.5f,     1.0f, 0.0f,0.0f,
		0.5f,  0.5f,  0.5f,     1.0f, 0.0f,0.0f,
		0.5f,  0.5f,  0.5f,     1.0f, 0.0f,0.0f,
	   -0.5f,  0.5f,  0.5f,     1.0f, 0.0f,0.0f,
	   -0.5f,  0.5f, -0.5f,     1.0f, 0.0f,0.0f
	};

   GLuint VAO,VBO;

   glGenVertexArrays(1,&VAO);
   glGenBuffers(1,&VBO);
   glBindVertexArray(VAO);
   glBindBuffer(GL_ARRAY_BUFFER,VBO);
   glBufferData(GL_ARRAY_BUFFER,sizeof(cube),cube,GL_STATIC_DRAW);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),0);
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(void*)(3*sizeof(float)));
   


   GLuint scaleLoc = glGetUniformLocation(ShaderProgram,"scale");
   GLuint rotaLoc = glGetUniformLocation(ShaderProgram,"rotate");
   GLuint transLoc = glGetUniformLocation(ShaderProgram,"translate");

   glm::mat4 model(1.0f);
   model = glm::scale(model,glm::vec3(1.5f,1.5f,1.5f));
   glUniformMatrix4fv(scaleLoc,1,GL_FALSE,glm::value_ptr(model));
  // model = glm::rotate(model,glm::radians(45.f),glm::vec3(0.0f,0.0f,0.0f));
   //glUniformMatrix4fv(rotaLoc,1,GL_FALSE,glm::value_ptr(model));
   model = glm::translate(model,glm::vec3(0.0f,0.0f,-6.5f));
   glUniformMatrix4fv(transLoc,1,GL_FALSE,glm::value_ptr(model));

while(!glfwWindowShouldClose(window))
{
    handleInput(window);
    glClearColor(0.5f,0.5f,0.9f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    model = glm::rotate(model,glm::radians(x/100.f),glm::vec3(0.0f,1.f,0.0f));
    glUniformMatrix4fv(rotaLoc,1,GL_FALSE,glm::value_ptr(model));
    glDrawArraysInstanced(GL_TRIANGLES,0,36,10);
    glfwSwapBuffers(window);
    glfwPollEvents();
    
}

glDeleteProgram(ShaderProgram);
glfwDestroyWindow(window);
glfwTerminate();

   
   return 0;
}
void mouse_position_callback([[maybe_unused]]GLFWwindow* window, double xpos,double ypos)
{
    
    std::cout << '\r'<< xpos <<" : " <<ypos<<std::flush;
    x  = xpos;
    y = ypos;

}

void handleInput(GLFWwindow* window)
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);
}