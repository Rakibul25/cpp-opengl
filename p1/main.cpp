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
    //glColor3f(0.0, 1.0, 1.0);
    glPointSize(10.0);

    /*glBegin(GL_POINTS);
        glVertex3f(-0.5, 0.5, 0);
        glVertex3f(0.5, 0.5, 0);
    glEnd();*/

    //glLineWidth(10);


    int x=10;
    glBegin(GL_TRIANGLES);
        glVertex2d(10, 20);
        glVertex2d(20, 20);
        glVertex2d(15, 28.6);
    glEnd();
    //glFlush();
    //glTranslatef(x, 0, 0);
    /*glScalef(2, 1, 0);
    glBegin(GL_TRIANGLES);
        glVertex2d(10, x+20);
        glVertex2d(20, x+20);
        glVertex2d(15, x+28.6);
    glEnd();*/

    glRotatef(30, 0, 0, 1);
    glBegin(GL_QUADS);
        glVertex2d(10, x+20);
        glVertex2d(20, x+20);
        glVertex2d(20, x+28.6);
        glVertex2d(10, x + 28.6);
    glEnd();
    glFlush();
    /*glBegin(GL_QUADS);
        glVertex2d(25, 20);
        glVertex2d(35, 20);
        glVertex2d(25, 30);
        glVertex2d(35, 30);
    glEnd();*/

    /*glBegin(GL_POLYGON);
        glVertex2d(25, 40);
        glVertex2d(35, 40);
        glVertex2d(40, 45);
        glVertex2d(35, 49);
        glVertex2d(25, 49);
        glVertex2d(20, 45);

    glEnd();
    */

    /*double angle;
    glBegin(GL_POLYGON);
    for(int i = 0; i <360; i++){
        angle = i*3.1416/180;
        if(i < 180)
            glColor3f(1.0, 1.0, 1.0);
        else
            glColor3f(0.0, 1.0, 1.0);
        glVertex2d(20+10*cos(angle), 40+10*sin(angle));
    }
    glEnd();*/


}

void reshape(int h, int w)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50, 50, -50, 50);
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

void keyboard(unsigned char key, int x, int y)
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
    //glutMouseFunc(my_mouse);
    //glutKeyboardFunc(keyboard);
    //glutSpecialFunc(special);
    init();
    glutMainLoop();
}
