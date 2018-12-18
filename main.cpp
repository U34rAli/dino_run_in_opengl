#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

void drawGround();
void myTimer(int);
void myTimerDoNothing(int);

#define PI 3.1415
#define theta 90.0f

bool startGame = false;

float mX = 0;
float mY = 0;
float dinoPoints[2][32] = {{6, 6, 7, 7, 5, 5, 3, 3, 4, 4, 2, 2, 0, 2, 3, 5, 7, 7, 13, 13, 9, 9, 12, 12, 8, 8, 10, 10, 9, 9, 8, 8},
                           {3, 1, 1, 0, 0, 3, 3, 1, 1, 0, 0, 3, 6, 9, 7, 7, 10, 13, 13, 11, 11, 10, 10, 9, 9, 8, 8, 6, 6, 7, 7, 5}};
float tempDinoPoints[2][32] = {{6, 6, 7, 7, 5, 5, 3, 3, 4, 4, 2, 2, 0, 2, 3, 5, 7, 7, 13, 13, 9, 9, 12, 12, 8, 8, 10, 10, 9, 9, 8, 8},
                               {3, 1, 1, 0, 0, 3, 3, 1, 1, 0, 0, 3, 6, 9, 7, 7, 10, 13, 13, 11, 11, 10, 10, 9, 9, 8, 8, 6, 6, 7, 7, 5}};
float dinoEye[2] = {8, 12};
float tempDinoEye[2] = {8, 12};
void Draw_Figure()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    // float dinoEye[2] = {13,13,12,12}
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2d(tempDinoEye[0], tempDinoEye[1]);
    glEnd();

    // glPointSize(10.0);
    // glBegin(GL_POINTS);
    // glVertex2d(mX, mY);
    // glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 32; i++)
    {
        glVertex2f(tempDinoPoints[0][i], tempDinoPoints[1][i]);
    }
    // glVertex2d(6,3);
    // glVertex2d(6,1);
    // glVertex2d(7,1);
    // glVertex2d(7,0);
    // glVertex2d(5,0);
    // glVertex2d(5,3);
    glEnd();

    // glPushMatrix();
    // glLoadIdentity();
    // glTranslatef(0.5, 0.5, 0.0);
    // glRotatef(25.0, 0.0, 0.0, 1.0);
    // glutSolidCube(0.5);
    // glPopMatrix();
}

float groundDust[2][3] = {{100, 130, 170}, {-2, -2, -2}};
void drawGround()
{
    glBegin(GL_LINES);
    glVertex2f(-10, 0);
    glVertex2f(100, 0);
    glEnd();

    if (groundDust[0][0] < -10)
    {
        for (int i = 0; i < 2; i++)
        {
            groundDust[0][i] = groundDust[0][i + 1];
        }
        groundDust[0][2] = 100;
    }
    glBegin(GL_POINTS);
    for (int i = 0; i < 3; i++)
    {
        glVertex2f(groundDust[0][i], groundDust[1][i]);
        glVertex2f(groundDust[0][i] + 2, groundDust[1][i]);
        glVertex2f(groundDust[0][i] + 1, groundDust[1][i] - 1);
        groundDust[0][i] += -1;
    }
    glEnd();
}

void dinoPixels()
{
}

void display()
{

    Draw_Figure();
    drawGround();
    glutSwapBuffers();
}

int V = 20;

float VX = V * cos(theta * PI / 180);
float VY = V * sin(theta * PI / 180);
float time = 0.1;

void dontDoAnythingIdle()
{
}
void myIdleFunc()
{

    // glutPostRedisplay();
}

bool jump = false;

void jumpFunc(){
    if(jump){
        if (mY >= 0)
        {
            time = time + 0.05;
            // mX = VX * time;
            mY = VY * time + 0.5 * (-10) * time * time;

            // printf("%f--\n", mY);
            for (int i = 0; i < 32; i++)
            {
                tempDinoPoints[1][i] = dinoPoints[1][i] + mY;

                // printf("%f----\n",dinoPoints[1][i]);
            }
            // tempDinoEye[0] = dinoEye[0]+mY;
            tempDinoEye[1] = dinoEye[1] + mY;
            // glutTimerFunc(50, myTimerDoNothing, 0);
        }
        else
        {
            // glutIdleFunc(dontDoAnythingIdle); // 1 click == 1 jump
            // glutTimerFunc(50, myTimer, 0);
            time = 0.1;
            mY = 0;
            jump=false;
        }
    }
}

void myTimer(int value)
{
    // glutIdleFunc(myIdleFunc);
    if (startGame)
    {
        jumpFunc();
        glutPostRedisplay();
    }
    glutTimerFunc(50, myTimer, 0);
}
void myTimerDoNothing(int value)
{
}
void keyDown(int key, int x, int y)
{

    if (key == GLUT_KEY_UP)
    {
        if (startGame)
        {
            jump=true;
            glutTimerFunc(50, myTimer, 0);
            // glutIdleFunc(myIdleFunc);
        }
        else
        {
            startGame = true;
        }
    }
}

void myinit() //set attributes
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(1.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 100, -10, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // GLUT_DOUBLE
    glutInitWindowSize(900, 400);
    glutInitWindowPosition(100, 100);

    // int wid =GLUT_SCREEN_HEIGHT;
    // printf("%d",wid);

    glutCreateWindow("");

    glutDisplayFunc(display);

    // glutIdleFunc(myIdleFunc);
    // glutTimerFunc(50, myTimer, 0); // mili seconds , myTimer(int value), value
    // glutKeyboardFunc(myKeyboardFunc); // myKeyboardFunc(unsigned char key , int x , int y)
    // glutMouseFunc(myMouse); //  myMouse(int button , int state , int x , int y)
    glutSpecialFunc(keyDown); // keyDown(int key , int x , int y)
    // glutSpecialUpFunc(keyUp);   // keyUp(int key , int x , int y)
    glutPostRedisplay();
    // glutReshapeFunc(myReshape);

    myinit();
    glutMainLoop();
    return 0;
}
