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
    if(dir == 0){
    glBegin(GL_TRIANGLES);
        glVertex2d(10, 20);
        glVertex2d(20, 20);
        glVertex2d(15, 28.6);
    glEnd();
    glFlush();
    }
    else{
        glBegin(GL_TRIANGLES);
            glVertex2d(10, 20);
            glVertex2d(20, 20);
            glVertex2d(15, 14);
        glEnd();
        glFlush();
    }


}

void reshape(int h, int w)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 50, 0, 50);
    glMatrixMode(GL_MODELVIEW);

}

void my_mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON){
        if(dir==0){
            display();
            dir = 1;
        }
        if(dir==1){
            display();
            dir = 0;
        }
    }
}

void keyboard( char key, int x, int y)
{
    if(key == 'a'){
        dir = 1;
        display();
    }
    else if (key == 'A'){
        dir = 0;
        display();
    }
}

void special(int key, int x, int y)
{
    if(key == GLUT_KEY_UP){
        dir = 0;
        display();
    }
    else if(key == GLUT_KEY_DOWN){
        dir = 1;
        display();
    }
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

    glutSpecialFunc(keyboard);
    init();
    glutMainLoop();
}



