#include<GL/glut.h>
#include<math.h>
float x = 0.5;
float y = 0.5;
int dir = 1;
void display()
{
    float angle;
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //glPointSize(15);
    glBegin(GL_POLYGON);
    for(int i = 0; i<360; i++)
    {
        angle = i*3.1416/180;
        glVertex2f(x+cos(angle)*2, y+sin(angle)*2);
    }
    glEnd();
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
        if(y<48){
            x = x + 0.25;
            y = y + 0.25;
        }
        else
            dir = 2;
    }
    else if(dir == 2){
        if(x<48){
            x = x + 0.25;
            y = y - 0.25;
        }
        else
            dir = 3;
    }
    else if(dir == 3){
        if(y > 2){
            x = x - 0.25;
            y = y - 0.25;
        }
        else
            dir = 4;
    }
    else if(dir ==4){
        if(x > 2){
            x = x - 0.25;
            y = y + 0.25;
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
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
}


