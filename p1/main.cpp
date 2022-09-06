#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include<math.h>
#endif

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200,100);
    glutInitWindowSize(500,500);

    glutCreateWindow("Hello");

    glutDisplayFunc(display);

    glutMainLoop();
}



