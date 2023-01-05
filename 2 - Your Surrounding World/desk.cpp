// GLUT, include glu.h and gl.h
#include <GL/glut.h>
// GLFW
#include <GLFW/glfw3.h>
 
#include <iostream>
#include <cmath>

char title[] = "desk";

int WIDTH = 640; int HEIGHT = 480;

float posx = 0;
float posy = 25;
float posz = -10.0;

float centerx = 0;
float centery = 20;
float centerz = 0;

float upx = 0;
float upy = 1;
float upz = 0;

const float TWOPI = 2 * 3.14159;

/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}
 
/*void renderPyramid(GLfloat x, GLfloat y, GLfloat z)
{
    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(x - 1.0f, y, z - 1.0f);
    glVertex3f(x + 1.0f, y, z - 1.0f);
    glVertex3f(x, y + 1.0f, z);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(x - 1.0f, y, z - 1.0f);
    glVertex3f(x, y, z + 1.0f);
    glVertex3f(x, y + 1.0f, z);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(x + 1.0f, y, z - 1.0f);
    glVertex3f(x, y, z+ 1.0f);
    glVertex3f(x, y + 1.0f, z);

    glEnd();
}*/

void drawCircle(GLfloat x, GLfloat y, GLfloat z, //location
                GLfloat r, GLfloat g, GLfloat b, //color
                GLfloat rad, GLfloat oscale, bool standing, bool hollow)        //radius, oval, standing/lying, hollow/filled
{
    if (hollow)
    {
        glBegin(GL_LINE_LOOP);
    }
    else
    {
       glBegin(GL_POLYGON);
    }

    glColor3f(r, g, b);

    if (standing)
    {
        for (int i = 0; i <= 100; i++)
        {
            GLfloat thisx = x + rad*cos(((float)i/100)*TWOPI);
            GLfloat thisy = y + oscale*rad*sin(((float)i/100)*TWOPI);

            //printf("%f, %f\n", thisx, thisy, z);

            glVertex3f(thisx, thisy, z);

        }
    }
    else
    {
        for (int i = 0; i <= 100; i++)
        {
            GLfloat thisx = x + rad*cos(((float)i/100)*TWOPI);
            GLfloat thisz = z + oscale*rad*sin(((float)i/100)*TWOPI);

            //printf("%f, %f\n", thisx, thisy, z);

            glVertex3f(thisx, y, thisz);

        }
    }
    
    glEnd();
}

void desk(GLfloat x, GLfloat y, GLfloat z)
{
    glBegin(GL_POLYGON);

    glColor3f(.4, .3, .2);
    glVertex3f(x - 25.0f, y, z + 10.0f);
    glVertex3f(x + 25.0f, y, z + 10.0f);
    glVertex3f(x + 25.0f, y, z - 10.0f);
    glVertex3f(x - 25.0f, y, z - 10.0f);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3f(.32, .24, .16);
    glVertex3f(x - 25.0f, y, z - 10.0f);
    glVertex3f(x + 25.0f, y, z - 10.0f);
    glVertex3f(x + 25.0f, y - 3, z - 10.0f);
    glVertex3f(x - 25.0f, y - 3, z - 10.0f);

    glEnd();
}

void walls(GLfloat x, GLfloat y, GLfloat z)
{
    glBegin(GL_POLYGON);

    glColor3f(1, 1, .9);
    glVertex3f(x - 25.0f, y - 25.0f, z);
    glVertex3f(x - 25.0f, x + 25.0f, z);
    glVertex3f(x + 25.0f, y + 25.0f, z);
    glVertex3f(x + 25.0f, y - 25.0f, z);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3f(.95, .95, .855);
    glVertex3f(x - 25.0f, y - 25.0f, z);
    glVertex3f(x - 25.0f, x + 25.0f, z);
    glVertex3f(x - 25.0f, y + 25.0f, z - 40.0f);
    glVertex3f(x - 25.0f, y - 25.0f, z - 40.0f);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3f(.9, .9, .81);
    glVertex3f(x + 25.0f, y - 25.0f, z);
    glVertex3f(x + 25.0f, x + 25.0f, z);
    glVertex3f(x + 25.0f, y + 25.0f, z - 40.0f);
    glVertex3f(x + 25.0f, y - 25.0f, z - 40.0f);

    glEnd();
}

void floor(GLfloat x, GLfloat y, GLfloat z)
{
    glBegin(GL_POLYGON);

    glColor3f(.2, .15, .1);
    glVertex3f(x - 25.0f, y, z - 25.0f);
    glVertex3f(x - 25.0f, y, z + 25.0f);
    glVertex3f(x + 25.0f, y, z + 25.0f);
    glVertex3f(x + 25.0f, y, z - 25.0f);

    glEnd();
}

void ds(GLfloat x, GLfloat y, GLfloat z)
{
    // ---- Bottom DS ---- //

    glBegin(GL_POLYGON);

    //front end
    glColor3f(.3, .3, .3);
    glVertex3f(x + 2.5, y, z + 1);
    glVertex3f(x + 2.5, y + 0.5, z + 1);
    glVertex3f(x - 2.5, y + 0.5, z - 1);
    glVertex3f(x - 2.5, y, z - 1);

    glEnd();

    glBegin(GL_POLYGON);
    
    //right end
    glColor3f(.2, .2, .2);
    glVertex3f(x - 2.5, y, z - 1);
    glVertex3f(x - 3, y, z + 2);
    glVertex3f(x - 3, y + 0.5, z + 2);
    glVertex3f(x - 2.5, y + 0.5, z - 1);

    glEnd();

    glBegin(GL_POLYGON);

    //top face
    glColor3f(.4, .4, .4);
    glVertex3f(x + 2.5, y + 0.5, z + 1);
    glVertex3f(x + 2, y + 0.5, z + 4);
    glVertex3f(x - 3, y + 0.5, z + 2);
    glVertex3f(x - 2.5, y + 0.5, z - 1);// z range: 3, x range: .5

    glEnd();

    // ---- Middle DS ---- //

    glBegin(GL_POLYGON);

    //front end
    glColor3f(1, .6, .8);
    glVertex3f(x + 2.5 - .1, y + 0.5, z + 1 + .6);
    glVertex3f(x + 2.5 - .1, y + 1, z + 1 + .6);
    glVertex3f(x - 2.5 + 1 - .1, y + 1, z - 1 + .4 + .6);
    glVertex3f(x - 2.5 + 1 - .1, y + 0.5, z - 1 + .4 + .6);

    glEnd();

    glBegin(GL_POLYGON);

    //right end
    glColor3f(.5, .3, .4);
    glVertex3f(x - 2.5 + 1 - .1, y + 1, z - 1 + .4 + .6);
    glVertex3f(x - 2.5 + 1 - .1, y + 0.5, z - 1 + .4 + .6);
    glVertex3f(x - 2.5 - .4 + 1 - .1, y + 0.5, z - 1 + .4 + .6 + 2.4);
    glVertex3f(x - 2.5 - .4 + 1 - .1, y + 1, z - 1 + .4 + .6 + 2.4);
    
    glEnd();

    // ---- Top DS ---- //

    glBegin(GL_POLYGON);

    //front end
    glColor3f(.15, .15, .15);
    glVertex3f(x + 2.5 - .1, y + 1, z + 1 + .6);
    glVertex3f(x + 2.5 - .1, y + 1.5, z + 1 + .6);
    glVertex3f(x - 2.5 + 1 - .1, y + 1.5, z - 1 + .4 + .6);
    glVertex3f(x - 2.5 + 1 - .1, y + 1, z - 1 + .4 + .6);

    glEnd();

    glBegin(GL_POLYGON);

    //right end
    glColor3f(.1, .1, .1);
    glVertex3f(x - 2.5 + 1 - .1, y + 1.5, z - 1 + .4 + .6);
    glVertex3f(x - 2.5 + 1 - .1, y + 1, z - 1 + .4 + .6);
    glVertex3f(x - 2.5 - .4 + 1 - .1, y + 1, z - 1 + .4 + .6 + 2.4);
    glVertex3f(x - 2.5 - .4 + 1 - .1, y + 1.5, z - 1 + .4 + .6 + 2.4);

    glEnd();

    glBegin(GL_POLYGON);

    //top face
    glColor3f(.2, .2, .2);
    glVertex3f(x + 2.5 - .1, y + 1.5, z + 1 + .6);

    glVertex3f(x - 2.5 + 1 - .1, y + 1.5, z - 1 + .4 + .6);

    glVertex3f(x - 2.5 - .4 + 1 - .1, y + 1.5, z - 1 + .4 + .6 + 2.4);

    glVertex3f(x + 2, y + 1.5, z + 4);

    glEnd();
}

void puff(GLfloat x, GLfloat y, GLfloat z)
{
    //left foot
    glBegin(GL_POLYGON);

    glColor3f(1, .48, .64);
    glVertex3f(x + 0.5, y - 2, z);
    glVertex3f(x + 0.5, y - 3.5, z);
    glVertex3f(x + 3, y - 3.5, z - 1);
    glVertex3f(x + 3, y - 2.5, z - 0.5);

    glEnd();

    //right foot
    glBegin(GL_POLYGON);

    glVertex3f(x - 0.5, y - 2, z);
    glVertex3f(x - 0.5, y - 3.5, z);
    glVertex3f(x - 3, y - 3.5, z - 1);
    glVertex3f(x - 3, y - 2.5, z - 0.5);

    glEnd();

    //body
    drawCircle(x, y, z,
                1, .6, .8,
                3, 1, true, false);

    //ears + mouth + arms
    glBegin(GL_TRIANGLES);
    
    //right ear
    glColor3f(1, .6, .8);
    glVertex3f(x - .5, y + 2.2, z);
    glVertex3f(x - 2.5, y + 1.7, z);
    glVertex3f(x - 2.2, y + 3.2, z);

    glColor3f(.1, .1, .1);
    glVertex3f(x - .5, y + 2.2 - .2, z);
    glVertex3f(x - 2.5, y + 1.7 - .2, z);
    glVertex3f(x - 2.2, y + 3.2 - .2, z);

    //left ear
    glColor3f(1, .6, .8);
    glVertex3f(x + .5, y + 2.2, z);
    glVertex3f(x + 2.5, y + 1.7, z);
    glVertex3f(x + 2.2, y + 3.2, z);

    glColor3f(.1, .1, .1);
    glVertex3f(x + .5, y + 2.2 - .2, z);
    glVertex3f(x + 2.5, y + 1.7 - .2, z);
    glVertex3f(x + 2.2, y + 3.2 - .2, z);

    //mouth
    glColor3f(.8, .1, .1);
    glVertex3f(x - .5, y - .5, z);
    glVertex3f(x + .5, y - .5, z);
    glVertex3f(x, y - 1.5, z);

    //rightarm
    glColor3f(1, .48, .64);
    glVertex3f(x - 2.3, y + .5 - .5, z);
    glVertex3f(x - 2, y - 1 - .5, z);
    glVertex3f(x - 3.8, y + .3 - .5, z);

    //leftarm
    glVertex3f(x + 2, y + .2 - .5, z);
    glVertex3f(x + 2.3, y - 1.3 - .5, z);
    glVertex3f(x + .8, y - .8 - .5, z);

    glEnd();

    //lefteye
    drawCircle(x + 1.25, y + .75, z,
                1, 1, 1,
                1, 1, true, false);
    drawCircle(x + 1.25, y + .75, z,
                .1, .7, .5,
                .7, 1, true, false);

    //righteye
    drawCircle(x - 1.25, y + .75, z,
                1, 1, 1,
                1, 1, true, false);
    drawCircle(x - 1.25, y + .75, z,
                .1, .7, .5,
                .7, 1, true, false);

}

void mouseArea(GLfloat x, GLfloat y, GLfloat z)
{
    glBegin(GL_POLYGON);

    glColor3f(.2, .2, .2);
    glVertex3f(x - 5, y, z - 4);
    glVertex3f(x + 5, y, z - 4);
    glVertex3f(x + 5, y, z + 4);
    glVertex3f(x - 5, y, z + 4);

    glEnd();

    drawCircle(x - 3, y, z - 1,
                .1, .1, .1,
                1, 2, false, false);
}

void monitor(GLfloat x, GLfloat y, GLfloat z)
{
    //stand
    glBegin(GL_TRIANGLES);

    glColor3f(.15, .15, .15);
    glVertex3f(x - 2, y, z);
    glVertex3f(x - 1, y, z - 1);
    glVertex3f(x - 5, y, z - 4);

    glVertex3f(x + 2, y, z);
    glVertex3f(x + 1, y, z - 1);
    glVertex3f(x + 5, y, z - 4);

    glVertex3f(x - 2, y, z);
    glVertex3f(x - 1, y, z + 1);
    glVertex3f(x - 5, y, z + 4);

    glVertex3f(x + 2, y, z);
    glVertex3f(x + 1, y, z + 1);
    glVertex3f(x + 5, y, z + 4);

    glEnd();

    glBegin(GL_POLYGON);

    glVertex3f(x - 2, y, z);
    glVertex3f(x - 1, y, z - 1);
    glVertex3f(x + 1, y, z - 1);
    glVertex3f(x + 2, y, z);
    glVertex3f(x + 1, y, z + 1);
    glVertex3f(x - 1, y, z + 1);

    glEnd();

    //stand cont. + screen
    glBegin(GL_QUADS);
    
    glVertex3f(x - 2, y, z);
    glVertex3f(x - 1, y, z - 1);
    glVertex3f(x + 1, y, z - 1);
    glVertex3f(x + 2, y, z);

    glColor3f(.1, .1, .1);
    glVertex3f(x - 1, y, z);
    glVertex3f(x + 1, y, z);
    glVertex3f(x + 1, y + 5, z);
    glVertex3f(x - 1, y + 5, z);

    glColor3f(.15, .15, .15);
    glVertex3f(x - 8, y + 2, z);
    glVertex3f(x - 8, y + 11, z);
    glVertex3f(x + 8, y + 11, z);
    glVertex3f(x + 8, y + 2, z);

    glEnd();
}

void scissors(GLfloat x, GLfloat y, GLfloat z)
{
    //blade
    glBegin(GL_QUADS);
    
    glColor3f(.6, .6, .6);
    glVertex3f(x + 0.7, y, z + 1);
    glVertex3f(x + 0.3, y, z + 1);
    glVertex3f(x + 0.3, y, z + 2);
    glVertex3f(x + 0.7, y, z + 2);

    glColor3f(.8, .8, .8);
    glVertex3f(x - 0.7, y, z + 1);
    glVertex3f(x - 0.3, y, z + 1);
    glVertex3f(x + 0.3, y, z + 2);
    glVertex3f(x + 0.7, y, z + 2);

    glEnd();

    glBegin(GL_TRIANGLES);

    glVertex3f(x + 0.3, y, z + 2);
    glVertex3f(x + 0.7, y, z + 2);
    glVertex3f(x + 0.5, y, z + 6);

    glEnd();

    //handles
    glLineWidth(3.0);
    drawCircle(x + 0.5, y, z,
                .15, .15, .15,
                .5, 2, false, true);

    drawCircle(x - 0.5, y, z + 0.4,
                .15, .15, .15,
                .5, 1.25, false, true);
}

void torchic(GLfloat x, GLfloat y, GLfloat z)
{
    //feet
    drawCircle(x + .5, y, z - .5,
                1, .8, .6,
                1, .5, false, false);

    drawCircle(x + .5, y, z + .5,
                1, .8, .6,
                1, .5, false, false);

    //body
    drawCircle(x, y + 1.5, z,
                .8, .48, 0,
                1.5, 1, true, false);

    //arms
    glBegin(GL_QUADS);

    glColor3f(1, .8, 0);
    glVertex3f(x + .5, y + 2.5, z);
    glVertex3f(x - 1.5, y + 2.5, z);
    glVertex3f(x - 2, y + 1.5, z);
    glVertex3f(x, y + 1.5, z);

    glEnd();

    //head
    drawCircle(x, y + 4, z,
                1, .6, 0,
                2.5, .75, true, false);

    glBegin(GL_TRIANGLES);

    glColor3f(1, .8, 0);
    glVertex3f(x, y + 6 - .3, z + 1);
    glVertex3f(x, y + 6 - .3, z - 1);
    glVertex3f(x, y + 8 - .3, z);

    glVertex3f(x, y + 6 - .3, z);
    glVertex3f(x, y + 5 - .3, z + 2);
    glVertex3f(x, y + 7 - .3, z + 1.5);

    glVertex3f(x, y + 6 - .3, z);
    glVertex3f(x, y + 5 - .3, z - 2);
    glVertex3f(x, y + 7 - .3, z - 1.5);

    glEnd();

    //eyes
    drawCircle(x + 1.5, y + 4.5, z,
                .15, .15, .15,
                .4, 2, true, false);

    drawCircle(x, y + 4, z,
                .15, .15, .15,
                .4, 2, true, false);

    //beak
    drawCircle(x + 1.5, y + 3.75, z,
                1, .8, .6,
                .8, .6, true, false);
}

void desktop(GLfloat x, GLfloat y, GLfloat z)
{
    glBegin(GL_QUADS);

    glColor3f(.2, .2, .2);
    glVertex3f(x + 8, y, z);
    glVertex3f(x + 8, y + 18, z);
    glVertex3f(x + 8, y + 18, z - 15);
    glVertex3f(x + 8, y, z - 15);

    glColor3f(.15, .15, .15);
    glVertex3f(x + 8, y + 18, z);
    glVertex3f(x + 8, y + 18, z - 15);
    glVertex3f(x, y + 18, z - 15);
    glVertex3f(x, y + 18, z);

    glEnd();
}

void wireCoil(GLfloat x, GLfloat y, GLfloat z)
{
    for (int i = 0; i < 10; i++)
    {
        float r = 1 + ((float) rand()/RAND_MAX)*.5;

        glLineWidth(3.0);
        drawCircle(x, y, z,
                    .1*r, .2*r, .5*r,
                    4.0 + (float) i/10, 1, false, true);
    }
}

void keyboard(GLfloat x, GLfloat y, GLfloat z)
{
    glBegin(GL_QUADS);

    glColor3f(.15, .15, .15);//8
    glVertex3f(x + 6, y, z - 1.5);
    glVertex3f(x - 6, y, z);
    glVertex3f(x - 5.375, y, z + 5);
    glVertex3f(x + 6.625, y, z + 3.5);

    glEnd();
}

void headphones(GLfloat x, GLfloat y, GLfloat z)
{
    //ring
    glLineWidth(5.0);
    for (int i = 0; i < 50; i++)
    {
        drawCircle(x, y + (float) i/30, z,
                    .15, .15, .15,
                    3, 1, false, true);
    }

    //cups
    drawCircle(x - 1, y + 1, z - 3.5,
                .2, .2, .2,
                1.2, 1.5, true, false);

    drawCircle(x + 1, y + 1, z - 3.5,
                .2, .2, .2,
                1.2, 1.5, true, false);

    //mic
    glLineWidth(3.0);
    glBegin(GL_LINES);

    glColor3f(.3, .3, .3);
    glVertex3f(x - 1, y + 1, z - 3.5);
    glVertex3f(x - 1, y + 5, z - 3.5);

    glEnd();

    drawCircle(x - 1, y + 5, z - 3.5,
                .1, .1, .1,
                .5, 1, true, false);
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
 
   glLoadIdentity();

   gluLookAt(
      posx, posy, posz,
      centerx, centery, centerz,
      upx, upy, upz
   );
   
   // Scene goes from x = 25 to -25 (25 left -25 right)
   // Desk goes from z = 50 to z = 30 (50 far, 30 close)
   // Desk top is y = 0, Floor is y = -25

   floor(0.0f, -25.0f, 25.0f);
   walls(0.0f, 0.0f, 50.0f);
   wireCoil(-18.0f, -25.0f, 40.0f);
   desktop(-25.0f, -25.0f, 30.0f);
   desk(0.0f, 0.0f, 40.0f);
   puff(-13.0f, 3.5f, 48.0f);
   ds(16.0f, 0.0f, 40.0f);
   monitor(0.0f, 0.0f, 43.0f);
   headphones(8.0f, 0.0f, 40.0f);
   mouseArea(-5.0f, 0.0f, 34.0f);
   scissors(20.0f, 0.0f, 33.0f);
   torchic(-23.0f, 0.0f, 35.0f);
   keyboard(6.0f, 0.0f, 31.5f);
 
   glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}
 
/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}
 
void moveCamera(float x, float y, float z)
{
   posx += x;
   posy += y;
   posz += z;

   gluLookAt(
      posx, posy, posz,
      centerx, centery, centerz,
      upx, upy, upz
   );
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {

   /*/ Create a GLFWwindow object that we can use for GLFW's functions
   GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Keyboard with Delta Time", nullptr, nullptr);
   glfwMakeContextCurrent(window);*/

   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the infinite event-processing loop

   return 0;
}