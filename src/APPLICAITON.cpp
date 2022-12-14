#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>  //filestream//
#include <string>
#include <sstream> 
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    glewInit();

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
   

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit()!=GLEW_OK)
    {
       std::cout<<"ERROR"<<std::endl;
    }
    /* Loop until the user closes the window */
    {
        float positions[]
        {
            -0.5f,-0.5f,0.0f,0.0f,
             0.5f,-0.5f,1.0f,0.0f,
             0.5f, 0.5f,1.0f,1.0f,
            -0.5f, 0.5f,0.0f,1.0f
        };
        unsigned int indices[]
        {
            0,1,2,
            2,3,0
        };
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);)
        unsigned int vao;
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));


        VertexArray va;
        VertexBuffer vb(positions, 4*4*sizeof(float));
       

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb,layout);
     

        IndexBuffer ib(indices, sizeof(indices));

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUnifrom4f("u_Color", 0.3f, 0.2f, 1.0f, 1.0f);

   
        Texture texture("res/textures/R.png");
        texture.Bind();
      
       shader.SetUniform1i("u_Texture", 0);
       
       shader.Unbind();
        va.Unbind();
        ib.UnBind();
        vb.UnBind();
       
        Renderer renderer;



     ///  float r = 0.0f;
     //  float increment = 0.05f;

        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            shader.Bind();
            shader.SetUniform1i("u_Texture", 0);
      //     shader.SetUnifrom4f("u_Color", r, 0.2f, 1.0f, 1.0f);
             
            renderer.Draw(va, ib, shader);

            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
      //   if (r > 1.0f)
        //  {
          //      increment = -0.05f;
            //}
           // else if (r < 1.0f)
            //{
              //  increment = 0.05f;
          //}
          //r += increment;



            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

         
    }

        // glDeleteProgram(shader);
       glfwTerminate();
    
    return 0;
}

