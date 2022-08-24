#include <iostream>
#include "GLFW/glfw3.h"
#include "Config.h"

#ifdef USE_ADDER
    #include "adder.h"
#endif

int main(int argc, char* argv[]){
    std::cout << "hello,there\n";
#ifdef USE_ADDER
    std::cout <<"adder lib:"<< add(74.2, 56.6) << '\n';
#else
    std::cout <<"not lib:"<< 74.2 + 56.6 << '\n';
#endif
    std::cout << argv[0] << " VERSION " << HELLO_VERSION_MAJOR << '.' << HELLO_VERSION_MINOR << '\n';
    GLFWwindow* window;
    int width, height;

    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

    glfwWindowHint(GLFW_DEPTH_BITS, 16);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    window = glfwCreateWindow( 300, 300, "Gears", NULL, NULL );
    if (!window)
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

     while( !glfwWindowShouldClose(window) ){

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}