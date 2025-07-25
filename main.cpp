#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<cmath>
#include <fstream>
#include <string>




void drawFilledCircle(float centerX, float centerY, float radius, int numSegments) {//draw circle
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.5f, 0.2f);

    // vertex
    glVertex2f(centerX, centerY);

    for (int i = 0; i <= numSegments; ++i) {
        float angle = 2.0f * 3.14 * i / numSegments;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex2f(x, y);
    }

    glEnd();
}

int main(void)
{
    
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
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
    
    //block 1
    float xPos = -0.5f; // Initial x-position
    float yPos = -0.4f;
    float xSpeed = 0.5f; // Speed of movement
    float ySpeed = -0.5f;
    double lastTime = glfwGetTime();
    bool jumped = false;
    int score=0;
    int highScore = 0;

    //enemy block
    float xPos2 = 0.8f;
    float xSpeed2 = 0.5f;//enemy speed
    float yPos2 = -0.4f;
    
    //circle
    float xPosCircle = 0.9f;
    float xSpeedCircle = 0.0f;
    float yPosCircle = -0.4f;

    //meteor
    float xPosMeteor = 0.0f;
    float xSpeedMeteor = 0.4f;
    float yPosMeteor = 1.3f;
    float ySpeedMeteor = 0.0f;


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        
        if (xPos >= xPosMeteor - 0.15 && xPos <= xPosMeteor + 0.15)//enemy collision
        {
            if (yPos >= yPosMeteor - 0.15 && yPos <= yPosMeteor + 0.15)
            {
                if (yPos < yPosMeteor + 0.1)
                {
                    std::ifstream iFile;
                    std::string line = "";
                    iFile.open("HighScore.txt");//opens the csv file


                    if (!iFile.is_open())
                    {
                        std::cout << "not opened";
                    }

                    getline(iFile, line);//skip the header line

                    while (getline(iFile, line))//goes through the whole list and sets the line of info to the line variable
                    {

                        int int_num = std::stoi(line);
                        if (int_num > highScore)
                        {
                            
                            highScore = int_num;
                        }
                    }

                    std::ofstream file;
                    file.open("HighScore.txt", std::ios::app);
                    if (file.is_open()) {
                        //std::cout << "storing";
                        file << score << std::endl;
                        //std::cout << "stored";
                        file.close();
                    }

                    
                    if (score > highScore)
                    {
                        std::cout << "NEW HIGH SCORE!!\n";
                    }
                    std::cout << "Game Over\n";
                    std::cout << "Score: " << score<<"\n";
                    std::cout << "High score: " << highScore << std::endl;
                    std::cout << "You were hit by a meteor.";
                    glfwTerminate();

                    return 0;
                }

            }
            
        }
        if(xPos >= xPos2-0.15 && xPos <= xPos2 + 0.15)//enemy collision
        {
            if (yPos > yPos2)
            {
                if (yPos < yPos2 + 0.1)
                {
                    xPos2 = 0.8;
                    score = score + 1;
                }
                    
            }
            else
            {
                std::ifstream iFile;
                std::string line = "";
                iFile.open("HighScore.txt");//opens the csv file


                if (!iFile.is_open())
                {
                    std::cout << "not opened";
                }

                getline(iFile, line);//skip the header line

                while (getline(iFile, line))//goes through the whole list and sets the line of info to the line variable
                {

                    int int_num = std::stoi(line);
                    if (int_num > highScore)
                    {
                        highScore = int_num;

                    }
                }
                
                std::ofstream file;
                file.open("HighScore.txt", std::ios::app);
                if (file.is_open()) {
                    //std::cout << "storing";
                    file << score<<std::endl;
                    //std::cout << "stored";
                    file.close();
                }
                

                if (score > highScore)
                {
                    std::cout<<"NEW HIGH SCORE!!\n";
                }
                
                std::cout << "Game Over\n";
                std::cout << "Score: " << score<<"\n";
                std::cout << "High score: " << highScore<<std::endl;
                std::cout << "you got ran over by a square.";
                glfwTerminate();

                return 0;
            }
        }

        //
        
        //std:: cout << yPos;
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        /* Render here */
        //player 1
        xPos += xSpeed * deltaTime;
        yPos += ySpeed * deltaTime;
        
        if (yPos > -0.4f)//gravity
        {
            ySpeed = ySpeed - 0.2;
        }
        else
        {
            ySpeed = 0;
            jumped = false;
        }

        //enemy
        xPos2 += xSpeed2 * deltaTime*(currentTime/10+1);
        if (xPos2 > 0.8f) { // Bounce back
            xPos2 = 0.8f;
            xSpeed2 *= -1;
        }
        else if (xPos2 < -1.0f) {
            xPos2 = 1.0f;
            yPos2 = -0.4f;
            xSpeed2 *= -1;
        }

        //meteor
        xPosMeteor += xSpeedMeteor * deltaTime;
        yPosMeteor += ySpeedMeteor * deltaTime;
        if (xPosMeteor > 1.0f) { // Bounce back
            xPosMeteor = 1.0f;
            xSpeedMeteor *= -1;
        }
        else if (xPosMeteor < -1.0f) {
            xPosMeteor = -1.0f;
            xSpeedMeteor *= -1;
        }
        
        if (yPosMeteor < -0.3f) {
            yPosMeteor = 1.0;
            
            
        }
        if (currentTime > 5)
        {
            ySpeedMeteor = -0.3;
        }
       


        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the shapea
        glBegin(GL_QUADS);//player
        glColor3f(0.0f, 0.0f, 1.0f); // blue color
        glVertex2f(xPos - 0.1f, yPos - 0.1f);
        glVertex2f(xPos + 0.1f, yPos - 0.1f);
        glVertex2f(xPos + 0.1f, yPos + 0.1f);
        glVertex2f(xPos - 0.1f, yPos + 0.1f);
        glEnd();

        drawFilledCircle(xPosCircle, yPosCircle, 0.35f, 360);//circle
        
        glBegin(GL_QUADS);//mouth
        glColor3f(0.0f, 0.0f, 0.0f); // blue color
        glVertex2f(xPosCircle -0.2f, yPosCircle-0.1f);
        glVertex2f(xPosCircle + 0.0f, yPosCircle - 0.1f);
        glVertex2f(xPosCircle + 0.0f, yPosCircle + 0.1f);
        glVertex2f(xPosCircle - 0.2f, yPosCircle + 0.1f);
        glEnd();

        glBegin(GL_QUADS);//enemy
        glColor3f(1.0f, 0.0f, 0.0f); // Red color
        glVertex2f(xPos2 - 0.1f, yPos2 - 0.1f);
        glVertex2f(xPos2 + 0.1f, yPos2 - 0.1f);
        glVertex2f(xPos2 + 0.1f, yPos2 + 0.1f);
        glVertex2f(xPos2 - 0.1f, yPos2 + 0.1f);
        glEnd();

        glBegin(GL_QUADS);//ground
        glColor3f(1.0f, 1.0f, 1.0f); // white color
        glVertex2f(-1.0f,-1.0f);
        glVertex2f(1.0f,-1.0f);
        glVertex2f(1.0f, -0.5f);
        glVertex2f(-1.0f, -0.5f);
        glEnd();

        glBegin(GL_TRIANGLES);//meteor
        glColor3f(1.0f, 0.0f, 0.0f); // white color
        glVertex2f(xPosMeteor - 0.1f, yPosMeteor - 0.1f);
        glVertex2f(xPosMeteor + 0.0f, yPosMeteor + 0.1f);
        glVertex2f(xPosMeteor + 0.1f, yPosMeteor - 0.1f);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        
        if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) && (jumped == false)) {
            ySpeed=6;
            jumped = true;
        }
        
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            xSpeed = -2;
        }
        else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
            xSpeed = 0;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            xSpeed = 2;
        }
        else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
            xSpeed = 0;
        }

        
    }

    glfwTerminate();
    return 0;
}
