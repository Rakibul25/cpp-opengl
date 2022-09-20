#undef __STRICT_ANSI__
#include <cmath>
#include <windows.h>
#include<stdio.h>

#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>

#define pi (2*acos(0.0))

#define sqrt2 (sqrt(2))

typedef struct point
{
	double x,y,z;
}Point;

bool drawGridFlag = false;
float boxAngle = 0;
bool drawAxes = true;
float tyreAngle = 0;
float quadAngle = 0;
float boxLightAngle = 0;
float boxCarAngle = 90;
float boxTyreAngle = 0;
bool carMove = false;
float yMove = 0;
float boxScaleFactor = 0;
float boxScaleFactorX = 1;
float boxScaleFactorY = 1;
float boxScaleFactorZ = 1;

float tyreScaleFactor = 1;

float translateAmount = 0;

float tinyBoxAngle = 0;
float lightBoxAngle = 90;
float background = 0;
float posx = 0;
float posy = 0;
float posz = 0;


bool transitionFlag = false;
bool lightFlag = true;

bool standardDimensionFlag = false;
bool roadFlag = false;
float color = 0;

void backGroundColorTransition();

int homeKeyCounter = 0, endKeyCounter = 0;

int dstTime = 0; // milliseconds

struct Color
{
    float r, g, b;
};

Color makeColor(float r, float g, float b)
{
    Color c = { r, g, b };
    return c;
};

Color lerp(Color a, Color b, float t)
{
    Color c;
    c.r = (1-t)*a.r + t*b.r;
    c.g = (1-t)*a.g + t*b.g;
    c.b = (1-t)*a.b + t*b.b;

    return c;
}

float lightRotatingDegree = 0;

Point pos, u, r, l;

void displayAxes()
{
	if(drawAxes)
	{
		glBegin(GL_LINES);
		{
		    glColor3f(1.0, 0, 0);

			glVertex3f( 500,0,0); // a point on pos x axis
			glVertex3f(-500,0,0); // a point on neg x axis

			glColor3f(0, 1.0, 0);

			glVertex3f(0,-500,0); // a point on pos y axis
			glVertex3f(0, 500,0); // a point on neg y axis

			glColor3f(0, 0, 1.0);

			glVertex3f(0,0, 500);  // a point on pos z axis
			glVertex3f(0,0,-500);   // a point on neg z axis
		}
		glEnd();
	}
}






Point func(Point vect, Point perp, int dir)
{
    double c = cos(pi/180);
    double s = dir * sin(pi/180);
    Point point;
    point.x = c * vect.x + s * perp.x;
    point.y = c * vect.y + s * perp.y;
    point.z = c * vect.z + s * perp.z;
    c = sqrt(point.x*point.x + point.y*point.y + point.z*point.z);
    point.x /= c;
    point.y /= c;
    point.z /= c;
    return point;
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){
		case '1': {
            Point l1 = func(l, r, -1);
            r = func(r, l, 1);
            l = l1;
            break;
		}
		case '2': {
            Point l1 = func(l, r, 1);
            r = func(r, l, -1);
            l = l1;
            break;
		}

		case '3': {
            Point u1 = func(u, l, -1);
            l = func(l, u, 1);
            u = u1;
            break;
        }
        case '4': {
            Point u1 = func(u, l, 1);
            l = func(l, u, -1);
            u = u1;
            break;
        }
        case '5': {
            Point r1 = func(r, u, -1);
            u = func(u, r, 1);
            r = r1;
            break;
        }
        case '6':{
            Point r1 = func(r, u, 1);
            u = func(u, r, -1);
            r = r1;
            break;
        }
        case '7':{
            tyreScaleFactor += 0.2;
            break;
        }
        case '8':{
            tyreScaleFactor -= 0.2;
            break;
        }
		default:
			break;
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN: // down arrow
		    {
		        posx += 5;
		        quadAngle += 5;
		        printf("Quad Angle %f\n", quadAngle);
		        break;
		    }

		case GLUT_KEY_UP:   // up arrow
		    {
		        posx -= 5;
		        quadAngle -= 5;
		        printf("Quad Angle %f\n", quadAngle);
		        break;
		    }

		case GLUT_KEY_RIGHT:    // right arrow
		    {
		        posy += 5;
		        printf("Box Angle %f\n", boxAngle);
		        break;
		    }

		case GLUT_KEY_LEFT:     // left arrow
		    {
		        posy -= 5;
		        printf("Box Angle %f\n", boxAngle);
		        break;
		    }

		case GLUT_KEY_PAGE_UP:
		    {
                posz += 5;
                break;
		    }

		case GLUT_KEY_PAGE_DOWN:
		    {
		        posz -= 5;
                break;
		    }

        case GLUT_KEY_HOME:
		    {
		        boxScaleFactor -= 0.2;
		        break;
		    }

        case GLUT_KEY_END:
            {
                tyreAngle -= 5;
                break;
            }

		default:
			break;
	}

}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN) // 2 times?? in ONE click? -- solution is checking DOWN or UP
            {
                if(drawAxes==true){
                    drawAxes = false;
                }else if(drawAxes==false){
                    drawAxes = true;
                }

                printf("Mouse Left Button Clicked\n");
			}
			else if(state == GLUT_UP)
            {
                printf("Mouse Left Button Released\n");
            }
            break;
		default:
			break;
	}
}

void displayTyre(float tyreRadius, float tyreWidth)
{
    int tyreSlices = 36;
    float sliceWidth = (2 * M_PI * tyreRadius) / tyreSlices;
    float sliceAngle = 360 / tyreSlices;

    float halfTyreWidth = tyreWidth / 2, quartTyreWidth = halfTyreWidth / 2;
    float halfSliceWidth = sliceWidth / 2;


    glColor3f(1, 0, 0);
    glBegin(GL_QUADS); //Tire support quads
    {
        glVertex3f(halfSliceWidth+3, tyreRadius, 0);
        glVertex3f(-halfSliceWidth+1, tyreRadius, 0);
        glVertex3f(-halfSliceWidth+1, -tyreRadius, 0);
        glVertex3f(halfSliceWidth+3, -tyreRadius, 0);
    }
    glEnd();

    glColor3f(1, 0, 0);
    glBegin(GL_QUADS); //Tire support quads
    {
        glVertex3f(-halfSliceWidth+2, tyreRadius, 0);
        glVertex3f(-halfSliceWidth-3, tyreRadius, 0);
        glVertex3f(-halfSliceWidth-3, -tyreRadius, 0);
        glVertex3f(-halfSliceWidth+2, -tyreRadius, 0);
    }
    glEnd();

    //Tyre support vertical
    glPushMatrix();
    glColor3f(1, 0, 0);
    glRotatef(90,0,1,0);
    glBegin(GL_QUADS); //Tire support quads
    {
        glVertex3f(tyreRadius, 0, halfSliceWidth+2);
        glVertex3f(tyreRadius, 0, -halfSliceWidth+3);
        glVertex3f(-tyreRadius, 0, -halfSliceWidth+3);
        glVertex3f(-tyreRadius, 0, halfSliceWidth+2);
    }
    glEnd();

    glPopMatrix();

    for(int i=0, j=1; i<tyreSlices; i++)
    {

        glPushMatrix();
        glRotatef(sliceAngle*i, 1, 0, 0);
        glTranslatef(0, tyreRadius, 0);
        if(j==1)
        {
            glColor3f(1, 0, 0);
            j--;
        }
        else
        {
            glColor3f(1, 1, 1);
            j++;
        }

        glBegin(GL_QUADS);
        {
            glVertex3f(halfTyreWidth/3, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth/3, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth/3, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth/3, 0, halfSliceWidth);
        }
        glEnd();
        glPopMatrix();

    }
}

void displayQuad(float quadLength, float quadWidth) // width along x axis, length along z axis
{
    float halfQuadWidth = quadWidth / 2, halfQuadLength = quadLength / 2;

    glBegin(GL_QUADS);
    {

        glColor3f(1, 1, 0);

        glVertex3f(halfQuadWidth, 0, halfQuadLength);
        glVertex3f(halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, halfQuadLength);

        glColor3f(1, 1, 0);

        glVertex3f(halfQuadWidth, 0, halfQuadLength);
        glVertex3f(halfQuadWidth, 0, -halfQuadLength);

        glColor3f(0, 1, 1);

        glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, halfQuadLength);

    }
    glEnd();
}

void displayBox(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
         glColor3f(1, 0, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0, 1, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0, 0, 1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void carupperBody(float boxLength, float boxWidth, float boxHeight)
{
float n=40;
    float m=35;
    float h=50;
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        //Car body right side
        glColor3f(1,0,0); //Yellow
        glVertex3f(halfBoxLength+n, halfBoxWidth+n, halfBoxHeight+n-h);
        glVertex3f(-halfBoxLength-n, halfBoxWidth+n, halfBoxHeight+n-h);
        glVertex3f(-halfBoxLength-n-30, halfBoxWidth+n, -halfBoxHeight-n);
        glVertex3f(halfBoxLength+n+30, halfBoxWidth+n, -halfBoxHeight-n);

        //Car body left side
        glColor3f(1,1,0); //Blue
        glVertex3f(halfBoxLength+n, -halfBoxWidth-n, halfBoxHeight+n-h);
        glVertex3f(-halfBoxLength-n, -halfBoxWidth-n, halfBoxHeight+n-h);
        glVertex3f(-halfBoxLength-n-30, -halfBoxWidth-n, -halfBoxHeight-n);
        glVertex3f(halfBoxLength+n+30, -halfBoxWidth-n, -halfBoxHeight-n);

        //Car body front side
        glColor3f(0,1,0);
        glVertex3f(halfBoxLength+n, halfBoxWidth+n, halfBoxHeight+n-h); //Top right corner
        glVertex3f(halfBoxLength+n, -halfBoxWidth-n, halfBoxHeight+n-h); //Top left corner
        glColor3f(0.188, 0.411, 0.752); //Gradient blue
        glVertex3f(halfBoxLength+n+30, -halfBoxWidth-n, -halfBoxHeight-n); //Bottom left corner
        glVertex3f(halfBoxLength+n+30, halfBoxWidth+n, -halfBoxHeight-n); //Bottom right corner

        //Car body back side
        glColor3f(1,0,0); //Pink ccolor
        glVertex3f(-halfBoxLength-n, halfBoxWidth+n, halfBoxHeight+n-h);
        glVertex3f(-halfBoxLength-n-30, halfBoxWidth+n, -halfBoxHeight-n);
        glVertex3f(-halfBoxLength-n-30, -halfBoxWidth-n, -halfBoxHeight-n);
        glVertex3f(-halfBoxLength-n, -halfBoxWidth-n, halfBoxHeight+n-h);

        //Car body Top side
        glColor3f(0, 0, 1);
        glVertex3f(halfBoxLength+n, halfBoxWidth+m+5, halfBoxHeight+n-h);
        glVertex3f(-halfBoxLength-n, halfBoxWidth+m+5, halfBoxHeight+n-h);
        glVertex3f(-halfBoxLength-n, -halfBoxWidth-m-5, halfBoxHeight+n-h);
        glVertex3f(halfBoxLength+n, -halfBoxWidth-m-5, halfBoxHeight+n-h);

        //Car body bottom side
        glVertex3f(halfBoxLength+n, halfBoxWidth+m+5, -halfBoxHeight-n);
        glVertex3f(-halfBoxLength-n, halfBoxWidth+m+5, -halfBoxHeight-n);
        glVertex3f(-halfBoxLength-n, -halfBoxWidth-m-5, -halfBoxHeight-n);
        glVertex3f(halfBoxLength+n, -halfBoxWidth-m-5, -halfBoxHeight-n);
    }
    glEnd();
}

void displayHeadLightBox(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(1, 1, 1);
        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displaylightBox(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(1, 1, 1);
        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glColor3f(1, 1, 1);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(1, 0, 0);
        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(1, 0, 0);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(1, 1, 1);
        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(1, 1, 1);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}


void displayScene()
{
     float quadLength = 250, quadWidth = 15;
    float largeBoxLength = 450, largeBoxWidth = 200, largeBoxHeight = 25;
    float smallBoxLength = 200, smallBoxWidth = 70, smallBoxHeight = 30;
    float tinyBoxLength = 10, tinyBoxWidth = 10, tinyBoxHeight = 10;
    float poleLength = 10, poleWidth = 10, poleHeight = 100;
    float lightboxLength = 30, lightboxWidth = 30, lightboxHeight = 30;


    float tyreRadius = 40, tyreWidth = 35;

    displayAxes();


    float allAnimationHeight = 40;


    glPushMatrix();

    glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);

    if(carMove)
        glTranslatef(0, yMove, 0);

    glTranslatef(0, 0, 60+allAnimationHeight);
    glRotatef(boxCarAngle, 0, 0, 1);
    displayBox(largeBoxLength, largeBoxWidth, largeBoxHeight); // large box
    glPopMatrix();

    glPushMatrix();

    glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);

    if(carMove)
        glTranslatef(0, yMove, 0);

    glTranslatef(0, 0, 100+(smallBoxHeight/2) + (largeBoxHeight/2)+allAnimationHeight); // places the small box on top of the large box
    glRotatef(boxCarAngle, 0, 0, 1);
    carupperBody(smallBoxLength, smallBoxWidth, smallBoxHeight); // small box
    glPopMatrix();

    glPushMatrix();

    glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);

    if(carMove)
        glTranslatef(0, yMove, 0);

    glTranslatef(60, 196, 60+allAnimationHeight);
    glRotatef(boxCarAngle, 0, 0, 1);
    displayHeadLightBox(10, 10, 10); // large box
    glPopMatrix();

    glPushMatrix();
    glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);
    if(carMove)
        glTranslatef(0, yMove, 0);

    glTranslatef(-60, 196, 60+allAnimationHeight);
    glRotatef(boxCarAngle, 0, 0, 1);
    displayHeadLightBox(10, 10, 10); // large box
    glPopMatrix();

    glPushMatrix();

    glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);
    if(carMove)
        glTranslatef(0, yMove, 0);

    glTranslatef(0, 0, 30+(smallBoxHeight/2) + (largeBoxHeight/2)+(poleHeight/2)+allAnimationHeight); // places the small box on top of the large box
    displayBox(poleLength, poleWidth, poleHeight); // small box
    glPopMatrix();
    glRotatef(boxLightAngle, 0, 0, 1);
    glPushMatrix();



    glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);

    if(carMove)
        glTranslatef(0, yMove, 0);
    glRotatef(lightRotatingDegree, 0, 0, 1);
    glTranslatef(0, 0, 30+(smallBoxHeight/2) + (largeBoxHeight/2)+poleHeight+(lightboxHeight/2)+allAnimationHeight); // places the small box on top of the large box
    displaylightBox(lightboxLength, lightboxWidth, lightboxHeight); // small box
    glPopMatrix();

    if(lightFlag==true)
    {

        int rotationDegree;
        int zAxisValue = 0;
        float lower = 20;

        /** !!!!!!light box er upper side er rays!!!!!!!!!!! **/
        rotationDegree = -80;
        zAxisValue = +(smallBoxHeight/2) + 60+(largeBoxHeight/2)+(poleHeight/2)+(lightboxHeight/2)+(quadLength/2)+allAnimationHeight-30;
        zAxisValue -= lower;
        glPushMatrix();



        glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);

        if(carMove)
            glTranslatef(0, yMove, 0);
        glRotatef(lightRotatingDegree, 0, 0, 1);

        glTranslatef(11, -8+(quadLength/2), zAxisValue);
        glRotatef(rotationDegree, 1, 0, 0);
        displayQuad(quadLength, quadWidth-5);
        glPopMatrix();

        glPushMatrix();



        glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);

        if(carMove)
            glTranslatef(0, yMove, 0);
        glRotatef(lightRotatingDegree, 0, 0, 1);
        glTranslatef(-11, -8+(quadLength/2), zAxisValue);
        glRotatef(rotationDegree, 1, 0, 0);
        displayQuad(quadLength, quadWidth-5);
        glPopMatrix();

        glPushMatrix();



        glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);
        if(carMove)
            glTranslatef(0, yMove, 0);
        glRotatef(lightRotatingDegree, 0, 0, 1);
        glTranslatef(0, -8+(quadLength/2), zAxisValue);
        glRotatef(rotationDegree, 1, 0, 0);

        displayQuad(quadLength, quadWidth-5);
        glPopMatrix();


        /** !!!!!!light box er bottom side er rays!!!!!!!!!! **/
        rotationDegree = -100;
        zAxisValue = (smallBoxHeight/2) + 60+(largeBoxHeight/2)+(poleHeight/2)+(lightboxHeight/2+50);
        zAxisValue -= lower;
        glPushMatrix();



        glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);
        if(carMove)
            glTranslatef(0, yMove, 0);
        glRotatef(lightRotatingDegree, 0, 0, 1);
        glTranslatef(11, -8+(quadLength/2), zAxisValue);
        glRotatef(rotationDegree, 1, 0, 0);
        displayQuad(quadLength, quadWidth-5);
        glPopMatrix();

        glPushMatrix();
        ///new s

        ///new e
        glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);
        if(carMove)
            glTranslatef(0, yMove, 0);
        glRotatef(lightRotatingDegree, 0, 0, 1);
        glTranslatef(0, -8+(quadLength/2), zAxisValue);
        glRotatef(rotationDegree, 1, 0, 0);
        displayQuad(quadLength, quadWidth-5);
        glPopMatrix();

        glPushMatrix();
        ///new s

        ///new e
        glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);
        if(carMove)
            glTranslatef(0, yMove, 0);
        glRotatef(lightRotatingDegree, 0, 0, 1);
        glTranslatef(-11, -8+(quadLength/2), zAxisValue);
        glRotatef(rotationDegree, 1, 0, 0);
        displayQuad(quadLength, quadWidth-5);
        glPopMatrix();

        /** !!!!!!light box er right side er rays!!!!!!!!!! **/
        rotationDegree = -90;
        zAxisValue = (smallBoxHeight/2) + 60+(largeBoxHeight/2)+(poleHeight/2)+(lightboxHeight/2+50+40);
        zAxisValue -= lower;
        glPushMatrix();
        ///new s

        glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);
        if(carMove)
            glTranslatef(0, yMove, 0);
        glRotatef(lightRotatingDegree, 0, 0, 1);
        glTranslatef(-25, -8+(quadLength/2), zAxisValue+1);
        glRotatef(rotationDegree+10, 0, 0, 1);
        glRotatef(rotationDegree, 0, 1, 0);
        displayQuad(quadLength, quadWidth-5);
        glPopMatrix();

        glPushMatrix();



        glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);
        if(carMove)
            glTranslatef(0, yMove, 0);
        glRotatef(lightRotatingDegree, 0, 0, 1);
        glTranslatef(-25, -8+(quadLength/2), zAxisValue-10);
        glRotatef(rotationDegree+10, 0, 0, 1);
        glRotatef(rotationDegree, 0, 1, 0);
        displayQuad(quadLength, quadWidth-5);
        glPopMatrix();

        glPushMatrix();


        glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);
        if(carMove)
            glTranslatef(0, yMove, 0);
        glRotatef(lightRotatingDegree, 0, 0, 1);
        glTranslatef(-25, -8+(quadLength/2), zAxisValue-21);
        glRotatef(rotationDegree+10, 0, 0, 1);
        glRotatef(rotationDegree, 0, 1, 0);
        displayQuad(quadLength, quadWidth-5);
        glPopMatrix();


        /** !!!!!!light box er left side er rays!!!!!!!!!! **/
        rotationDegree = -90;
        zAxisValue = (smallBoxHeight/2) + 60+(largeBoxHeight/2)+(poleHeight/2)+(lightboxHeight/2+50+40);
        zAxisValue -= lower;
        glPushMatrix();


        glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);
        if(carMove)
            glTranslatef(0, yMove, 0);
        glRotatef(lightRotatingDegree, 0, 0, 1);
        glTranslatef(25, -8+(quadLength/2), zAxisValue+1);
        glRotatef(rotationDegree-10, 0, 0, 1);
        glRotatef(rotationDegree, 0, 1, 0);
        displayQuad(quadLength, quadWidth-5);
        glPopMatrix();

        glPushMatrix();
        ///new s

        ///new e
        ///Task 31,32 S
        glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);
        if(carMove)
            glTranslatef(0, yMove, 0);
        glRotatef(lightRotatingDegree, 0, 0, 1);
        glTranslatef(25, -8+(quadLength/2), zAxisValue-10);
        glRotatef(rotationDegree-10, 0, 0, 1);
        glRotatef(rotationDegree, 0, 1, 0);
        displayQuad(quadLength, quadWidth-5);
        glPopMatrix();

        glPushMatrix();


        glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);
        if(carMove)
            glTranslatef(0, yMove, 0);
        glRotatef(lightRotatingDegree, 0, 0, 1);
        glTranslatef(25, -8+(quadLength/2), zAxisValue-21);
        glRotatef(rotationDegree-10, 0, 0, 1);
        glRotatef(rotationDegree, 0, 1, 0);
        displayQuad(quadLength, quadWidth-5);
        glPopMatrix();

    }

    glPushMatrix();
    glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);
    if(carMove)
        glTranslatef(0, yMove, 0);

    glTranslatef(50, 120, 0+allAnimationHeight); //Co-ordinate Sequence here (y,x,z)

    if(carMove)
        glRotatef(tyreAngle, 1, 0, 0); // check what happens to the tyre after exchanging the order of translation and roation

    glRotatef(boxTyreAngle, 0, 0, 1); // check what happens to the tyre after exchanging the order of translation and roation
    displayTyre(tyreRadius, tyreWidth); // tyre
    glPopMatrix();

    glPushMatrix();
    ///Task 31,32 S2 Removed the commented line
    glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);
    if(carMove)
        glTranslatef(0, yMove, 0);

    glTranslatef(-50,120, 0+allAnimationHeight); //Co-ordinate Sequence here (y,x,z)

    if(carMove)
        glRotatef(tyreAngle, 1, 0, 0); // check what happens to the tyre after exchanging the order of translation and roation

    glRotatef(boxTyreAngle, 0, 0, 1); // check what happens to the tyre after exchanging the order of translation and roation
    displayTyre(tyreRadius, tyreWidth); // tyre
    glPopMatrix();

    //Back left tyre
    glPushMatrix();

    glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);
    if(carMove)
        glTranslatef(0, yMove, 0);

    glTranslatef(50, -120, 0+allAnimationHeight); //Co-ordinate Sequence here (y,x,z)

    if(carMove)
        glRotatef(tyreAngle, 1, 0, 0); // check what happens to the tyre after exchanging the order of translation and roation

    glRotatef(boxTyreAngle, 0, 0, 1); // check what happens to the tyre after exchanging the order of translation and roation
    displayTyre(tyreRadius, tyreWidth); // tyre
    glPopMatrix();

    //Back right tyre
    glPushMatrix();
    ///Task 31,32 S2 Removed the commented line
    glScalef(boxScaleFactorX, boxScaleFactorY, boxScaleFactorZ);
    if(carMove)
        glTranslatef(0, yMove, 0);

    glTranslatef(-50,-120, 0+allAnimationHeight); //Co-ordinate Sequence here (y,x,z)

    if(carMove)
        glRotatef(tyreAngle, 1, 0, 0); // check what happens to the tyre after exchanging the order of translation and roation

    glRotatef(boxTyreAngle, 0, 0, 1); // check what happens to the tyre after exchanging the order of translation and roation
    displayTyre(tyreRadius, tyreWidth); // tyre
    glPopMatrix();


}

void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(background, background, background,0);	//sets background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // sets the current matrix to identity
    gluLookAt(pos.x+posx, pos.y+posy, pos.z+posz, pos.x+l.x+posx, pos.y+l.y+posy, pos.z+l.z+posz, u.x, u.y, u.z); // sets camera position and direction

    displayScene();

	glutSwapBuffers();
}

void animate(){
    tinyBoxAngle += 0.05;
	glutPostRedisplay();
}

void init(){
    glClearColor(background, background, background,0); 	//sets background color

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity(); // sets the current matrix to identity
    gluPerspective(80,	1,	1,	1000.0);

    // to understand the following values, read the specification pdf
	double d = 1 / sqrt2;
    pos = {300, 300, 150};
    u = {0, 0, 1};
    r = {-d, d, 0};
    l = {-d, -d, 0};
}

void subMenu(int id)
{
     if(id == 3)
    {
        background = 1;
    }
    else if(id == 4)
    {
        background = 0;
    }
}

void mainMenu(int id)
{
    if(id == 1)
    {
        drawAxes = true;
    }
    else if(id == 2)
    {
        drawAxes = false;
    }

}


int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);



	glutMainLoop();		//The main loop of OpenGL, this function never returns

	return 0;
}
