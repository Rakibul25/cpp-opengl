#include<GL/glu.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<stdio.h>

#define window_height 600
#define window_width 600

void init()
{
    glClearColor(0.0f,0.0f,0.0f,0.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1,1,-1,1,2,10);
    glMatrixMode(GL_MODELVIEW);
}

void face (float A[], float B[], float C[], float D[])
{
    glBegin(GL_POLYGON);
      glVertex3f(A[0], A[1], A[2]); ///glVertex3fv(A) [Array]
      glVertex3fv(B);
      glVertex3fv(C);
      glVertex3fv(D);
    glEnd();

}

void cube(float V0[],float V1[],float V2[],float V3[],float V4[],float V5[],float V6[], float V7[] )
{
    ///Front(0,1,2,3) Red
    glColor3f(1.0,0.0,0.0);
    face(V0,V1,V2,V3);
    ///Back (4,5,6,7) Green
    glColor3f(0.0,1.0,0.0);
    face(V4,V5,V6,V7);
    ///Left (4,0,3,7)
    glColor3f(0.0,0.0,1.0);
    face(V4,V0,V3,V7);
    ///Right (5,1,2,6)
    glColor3f(1.0,1.0,0.0);
    face(V5,V1,V2,V6);
    ///Bottom (7,6,2,3)
    glColor3f(0.0,1.0,1.0);
    face(V7,V6,V2,V3);
    ///Top (5,1,0,4)
    glColor3f(1.0,0.0,1.0);
    face(V5,V1,V0,V4);
}

float T =0.0;
float Cx=0.0, Cy=0.0, Cz=3.0;
void spin ()
{
    T+=0.01;
       if(T>360)
           T=0;
    glutPostRedisplay();
}

void display()
{
    float V[8][3]={
        {-0.5,0.5,0.5},
        {0.5,0.5,0.5},
        {0.5,-0.5,0.5},
        {-0.5,-0.5,0.5},

        {-0.5,0.5,-0.5},
        {0.5,0.5,-0.5},
        {0.5,-0.5,-0.5},
        {-0.5,-0.5,-0.5},
    };
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Draw A cube and Spin it
    glLoadIdentity();
    gluLookAt(Cx,Cy,Cz,0,0,0,0,1,0);
    glRotatef(T,1,1,0);
    cube(V[0],V[1],V[2],V[3],V[4],V[5],V[6],V[7]);



    glutSwapBuffers();
}

/*
void custom_special ()
{
    //Switch():
        //Case UP_arrow GlutIdleFunc();
}
*/

void custom_keyboard(unsigned char ch, int x, int y)
{
    switch(ch)
    {
        ///We will control the camera Position (Increase or Decrease)
        ///Decrease in X Coordinate
    case 'x':
        Cx-=0.5;
        printf(" Camera at position: %f %f %f \n", Cx,Cy,Cz);
        break;
        ///Increase in X coordinate
    case 'X':
        Cx+=0.5;
        printf(" Camera at position: %f %f %f \n", Cx,Cy,Cz);
        break;
        ///Decrease in Y Coordinate
    case 'y':
        printf(" Camera at position: %f %f %f \n", Cx,Cy,Cz);
        Cy-=0.5;

        break;
        ///Increase in Y coordinate
    case 'Y':
        Cy+=0.5;
        printf(" Camera at position: %f %f %f \n", Cx,Cy,Cz);
        break;

        ///Decrease in Z Coordinate
    case 'z':
        printf(" Camera at position: %f %f %f \n", Cx,Cy,Cz);
        Cz-=0.5;

        break;
        ///Increase in Z coordinate
    case 'Z':
        Cz+=0.5;
        printf(" Camera at position: %f %f %f \n", Cx,Cy,Cz);
        break;

    default:
        break;

    }
   glutPostRedisplay();

}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(window_height,window_width);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutCreateWindow("3D First Class");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(spin);
    glutKeyboardFunc(custom_keyboard);

    //glutSpecialFunc(custom_special);
    glutMainLoop();
    return 0;
}

