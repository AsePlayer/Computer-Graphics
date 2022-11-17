// This program is a flyby around the RGB color cube.  One intersting note
// is that because the cube is a convex polyhedron and it is the only thing
// in the scene, we can render it using backface culling only. i.e., there
// is no need for a depth buffer.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>

bool rotate = true;
int oldTimeSinceStart = 0;
double moveVert = 0;
double moveZ = 1;
bool action = true;

double cube1vel = 1;
double cube2vel = -1;
double cube1pos = 0;
double cube2pos = 0;

// The cube has opposite corners at (0,0,0) and (1,1,1), which are black and
// white respectively.  The x-axis is the red gradient, the y-axis is the
// green gradient, and the z-axis is the blue gradient.  The cube's position
// and colors are fixed.
namespace Cube {

const int NUM_VERTICES = 8;
const int NUM_FACES = 6;

GLint vertices[NUM_VERTICES][3] = {
  {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
  {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

GLint faces[NUM_FACES][4] = {
  {1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6},
  {3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}};

GLfloat vertexColors[NUM_VERTICES][3] = {
  {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0},
  {1.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}};

void draw(GLfloat x, double pos) {
  glPushMatrix();
  glTranslatef(x, pos, 0);

  glBegin(GL_QUADS);
  for (int i = 0; i < NUM_FACES; i++) {
    for (int j = 0; j < 4; j++) {
      glColor3fv((GLfloat*)&vertexColors[faces[(i + (int) (x/2))%3][j]]);
      glVertex3iv((GLint*)&vertices[faces[i][j]]);
    }
  }
  glEnd();
  glPopMatrix();
}
}

// Display and Animation. To draw we just clear the window and draw the cube.
// Because our main window is double buffered we have to swap the buffers to
// make the drawing visible. Animation is achieved by successively moving our
// camera and drawing. The function nextAnimationFrame() moves the camera to
// the next point and draws. The way that we get animation in OpenGL is to
// register nextFrame as the idle function; this is done in main().
void display() {
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (cube1pos > 8)
    cube1vel = -0.1;
  else if (cube1pos < -8)
    cube1vel = 0.1;
  if (cube2pos > 8)
    cube2vel = -0.1;
  else if (cube2pos < -8)
    cube2vel = 0.1;

  if (action)
  {
    cube1pos += cube1vel;
    cube2pos += cube2vel;
  }

  glBegin(GL_QUADS);
  {
    glColor3f(.5, .5, 1);

    glVertex3f(-10, 10, 10);
    glVertex3f(-10, 10, -10);
    glVertex3f(10, 10, -10);
    glVertex3f(10, 10, 10);

    glVertex3f(-10, -10, 10);
    glVertex3f(-10, -10, -10);
    glVertex3f(10, -10, -10);
    glVertex3f(10, -10, 10);
  }
  glEnd();

  Cube::draw(0, 0);
  Cube::draw(2, cube1pos);
  Cube::draw(-2, cube2pos);

  glFlush();
  glutSwapBuffers();
}

// We'll be flying around the cube by moving the camera along the orbit of the
// curve u->(8*cos(u), 7*cos(u)-1, 4*cos(u/3)+2).  We keep the camera looking
// at the center of the cube (0.5, 0.5, 0.5) and vary the up vector to achieve
// a weird tumbling effect.
void timer(int v) {
  static GLfloat u = 0.0;
  if (rotate)
  {
    u += 0.01;
  }
  glLoadIdentity();
  gluLookAt(.5 - moveZ*(8*cos(u)), .5 - moveZ*(7*cos(u)-1) + moveVert, .5 - moveZ*(4*cos(u/3)+2), .5, .5 + moveVert, .5, cos(u), 1, 0);
  glutPostRedisplay();
  glutTimerFunc(1000/60.0, timer, v);
}

// When the window is reshaped we have to recompute the camera settings to
// match the new window shape.  Set the viewport to (0,0)-(w,h).  Set the
// camera to have a 60 degree vertical field of view, aspect ratio w/h, near
// clipping plane distance 0.5 and far clipping plane distance 40.
void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.5, 40.0);
  glMatrixMode(GL_MODELVIEW);
}

// Application specific initialization:  The only thing we really need to do
// is enable back face culling because the only thing in the scene is a cube
// which is a convex polyhedron.
void init() {
  glEnable(GL_CULL_FACE | GL_DEPTH_TEST);

  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LESS);
  glDepthRange(-1.0f, 1.0f);
  glCullFace(GL_BACK);
}

void processNormalKeys(unsigned char key, int x, int y) {

  int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
  int deltaTime = timeSinceStart - oldTimeSinceStart;
  oldTimeSinceStart = timeSinceStart;

  GLfloat dt = (GLfloat)deltaTime/100;

	if (key == 27) //escape
		exit(0);
  if (key == 117) //u
    moveVert += dt / 10;
  if (key == 100) //d
    moveVert -= dt / 10;
  if (key == 115) //s
    action = false;
  if (key == 99) //c
    action = true;
  if (key == 61) // =
    moveZ += (2/(moveZ + 1))/10;
  if (key == 45) // -
    moveZ -= moveZ/20;
  if (key == 114) // r
    rotate = !rotate;
  }

// The usual main for a GLUT application.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutCreateWindow("The RGB Color Cube");
  glutReshapeFunc(reshape);
  glutTimerFunc(100, timer, 0);
  glutDisplayFunc(display);
  init();
  glutKeyboardFunc(processNormalKeys);
  glutMainLoop();
}