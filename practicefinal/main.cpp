#include<GL/glut.h>
#include<math.h>
float x = 0.5;
float y = 0.5;
int dir = 1;
int dir1 = 1;

float p = 0;
float q = 0;

void rectangle()
{
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(3, 0);
    glVertex2f(3, 3);
    glVertex2f(0, 3);
    glEnd();
}

void body()
{
    glBegin(GL_POLYGON);
    glVertex2f(15, 15);
    glVertex2f(40, 15);
    glVertex2f(40, 25);
    glVertex2f(15, 25);
    glEnd();
}

void circle()
{
    float angle;
    glBegin(GL_POLYGON);
    for(int i = 0; i<360; i++)
    {
        angle = i*3.1416/180;
        glVertex2f(2*cos(angle), 2*sin(angle));
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(1, 0, 0);
    body();



    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(18, 19, 0);
    rectangle();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(23, 19, 0);
    rectangle();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(28, 19, 0);
    rectangle();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(33, 19, 0);
    rectangle();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(20, 15, 0);
    circle();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(35, 15, 0);
    circle();
    glPopMatrix();

    //glColor3f(1, 1, 1);
    //top();

    glPushMatrix();
    glColor3f(1, 1,1);
    glScalef(0.7, 0.5, 0);
    glTranslatef(12, 35, 0);
    body();
    glPopMatrix();


    glFlush();

}

void reshape(int h, int w)
{
    //view port
    glViewport(0, 0, w, h);

    //projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 50, 0, 50);
    glMatrixMode(GL_MODELVIEW);
}

void init ()
{
    glClearColor(0, 0, 0, 0);
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/60.0, timer, 0);
    if(dir==1)
    {
        if(x<48){
            x = x + 0.25;
        }
        else
            dir = 2;
    }
    else if(dir == 2){
        if(x>2){
            x = x - 0.25;
        }
        else
            dir = 1;
    }
}

int main (int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Test1");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    //glutTimerFunc(0, timer, 0);
    glutMainLoop();
}

