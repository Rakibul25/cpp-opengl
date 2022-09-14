#include<GL/glut.h>
#include<math.h>
float x = 0.5;
float y = 0.5;
int dir = 1;
int dir1 = 1;

float p = 0;
float q = 0;
void display()
{
    float angle;
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //glPointSize(15);
    glPushMatrix();
    glTranslatef(p, 0, 0);
    glBegin(GL_POLYGON);
    for(int i = 0; i<360; i++)
    {
        angle = i*3.1416/180;
        glVertex2f(x+cos(angle)*2, 25+y+sin(angle)*2);
    }
    glEnd();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, q, 0);
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(10, 0);
    glVertex2f(10, 10);
    glVertex2f(0, 10);
    glEnd();

    glPopMatrix();

    if(dir==1){
        if(p<48){
            p=p+0.01;
        }
        else{
            dir=2;
        }
    }
    else if(dir==2){
        if(p>2){
            p=p-0.01;
        }
        else{
            dir=1;
        }
    }

    if(dir1==1){
        if(q<40){
            q=q+0.01;
        }
        else{
            dir1=2;
        }
    }
    else if(dir1==2){
        if(q>0){
            q=q-0.01;
        }
        else{
            dir1=1;
        }
    }
    glFlush();
    glutPostRedisplay();
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
