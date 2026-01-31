/*
TO-DO: (Does not handle acceleration)
    - Remove hardcoded (0,0) coords for circle center
    - Use Pos vector instead (x, y)
    - Define velocity (vx, vy)
    - Compute deltatime each frame
    - Add velocity to Pos times deltatime ([x += vx]*deltatime, [y += vy]*deltatime)
    - Check for collisions with the window 
    - If (Pos + Radius) hits wall, bounce (-x for vert wall, -y for horz wall)
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>

using namespace std;

// create struct to hold 2D vectors
struct Vec2 {
    float x, y;
};

// Global parameters
int WINDOW_WIDTH = 1560;
int WINDOW_HEIGHT = 840;
int RADIUS = 50;
int SEGMENTS = 100;
std::string WINDOW_TITLE = "Physics Test";

Vec2 VELOCITY = {-10.0f, -10.0f};
Vec2 position = {0, 0};

double lastFrameTime = glfwGetTime();

// Initialize the window
void myInit (void) {
    glClearColor(0.0, 0.0, 0.0, 1.0); // rgba
    glColor3f(1.0, 1.0, 1.0); // rgb
    glPointSize(1.0); // point size
    glMatrixMode(GL_PROJECTION); // projection matrix
    glLoadIdentity(); // load identity matrix
    
    int halfWidth = (int)(WINDOW_WIDTH/2);
    int halfHeight = (int)(WINDOW_HEIGHT/2);
    glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, -1, 1); // orthographic projection
}

// Draw the circle
void drawCircle(float center_x, float center_y, float radius, int num_segments) {
    float angle_step = 3.1415926 * 2 / float(num_segments);
    float tangent_length = tanf(angle_step);
    float radius_correction = cosf(angle_step);

    float current_x = radius;
    float current_y = 0;
    
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    for (int segment = 0; segment < num_segments; segment++)
    {
        glVertex2f(current_x + center_x, current_y + center_y);

        float tangent_x = -current_y;
        float tangent_y = current_x;

        current_x += tangent_x * tangent_length;
        current_y += tangent_y * tangent_length;

        current_x *= radius_correction;
        current_y *= radius_correction;
    }
    glEnd();
}

// find deltatime
double computeDeltatime() {
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime; // update last frame time
    return deltaTime;
}

// check if collides with wall, if yes return -1 otherwise returns 1
int checkCollisionForX(float x) {
    int halfWidth = (int)(WINDOW_WIDTH/2);
    // wall coordinates
    float leftWall = -halfWidth;
    float rightWall = halfWidth;
    // ball coordinates
    float leftEdge = x - RADIUS;
    float rightEdge = x + RADIUS;

    if (rightEdge >= rightWall || leftEdge <= leftWall) {
        return -1;
    }

    return 1;
}

// check if collides with wall, if yes return -1 otherwise returns 1
int checkCollisionForY(float y) {
    int halfHeight = (int)(WINDOW_HEIGHT/2);
    // wall coordinates
    float topWall = halfHeight;
    float bottomWall = -halfHeight;
    // ball coordinates
    float topEdge = y + RADIUS;
    float bottomEdge = y - RADIUS;

    if (topEdge >= topWall || bottomEdge <= bottomWall) {
        return -1;
    }

    return 1;
}

// Main function
int main() {
    glfwInit();
    
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE.c_str(), NULL, NULL); // generate window pointer
    glfwMakeContextCurrent(window);
    
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    myInit();

    double deltatime;
    float x = position.x;
    float y = position.y;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        drawCircle(x, y, RADIUS, SEGMENTS);

        // update velocity based on collision
        VELOCITY.x = VELOCITY.x * checkCollisionForX(x);
        VELOCITY.y = VELOCITY.y * checkCollisionForY(y);

        cout << "Velocity Y: " << VELOCITY.y << endl;

        // change position vector based on velocity
        deltatime = computeDeltatime();
        x += (x + VELOCITY.x) * deltatime;
        y += (y + VELOCITY.y) * deltatime;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}