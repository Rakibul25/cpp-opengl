
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include<math.h>
#endif

int dir=0;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPointSize(10.0);
    glBegin(GL_TRIANGLES);
        glVertex2d(10, 20);
        glVertex2d(20, 20);
        glVertex2d(15, 28.6);

    glEnd();
    glFlush();



}

void reshape(int h, int w)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 50, 0, 50);
    glMatrixMode(GL_MODELVIEW);

}



void init()
{
    glClearColor(0, 0, 0, 0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("CSI422");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    init();
    glutMainLoop();
}



