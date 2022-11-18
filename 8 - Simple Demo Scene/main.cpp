#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <iostream>

GLfloat ballPosY = 0;
GLfloat ballPosX = 0;
GLfloat ballVelY = 0;
GLfloat ballVelX = 2;

GLfloat paddle1Y = 0;
GLfloat paddle2Y = 0;

int p1Points = 0;
int p2Points = 0;

int oldTimeSinceStart = 0;

const GLfloat pi = 3.14159;
GLfloat ballSpeed = 3;
GLfloat paddleSpeed = 3;

bool wDown = false;
bool sDown = false;
bool upDown = false;
bool downDown = false;

namespace Paddle {

    void draw(GLfloat x, GLfloat y) {

        glBegin(GL_QUADS);

        glVertex3f(x - .5, y + 1, 0);
        glVertex3f(x - .5, y - 1, 0);
        glVertex3f(x, y - 1, 0);
        glVertex3f(x, y + 1, 0);

        glEnd();
    }
}

namespace Ball {

    void draw(GLfloat x, GLfloat y) {
        
        glBegin(GL_QUADS);

        glVertex3f(x - .25, y + .25, 0);
        glVertex3f(x - .25, y - .25, 0);
        glVertex3f(x + .25, y - .25, 0);
        glVertex3f(x + .25, y + .25, 0);

        glEnd();
    }
}

namespace Board {

    void draw() {

        glBegin(GL_LINES);

        glVertex3f(0, 5, 0);
        glVertex3f(0, -5, 0);

        glVertex3f(-10, 5, 0);
        glVertex3f(10, 5, 0);

        glVertex3f(-10, -5, 0);
        glVertex3f(10, -5, 0);

        glEnd();
    }

}

namespace ScoreBoard {

  void draw(int p1, int p2)
    {
      glBegin(GL_LINE_LOOP);

      glVertex3f(0, 5, 0);
      glVertex3f(-5, 5, 0);
      glVertex3f(-5, 6, 0);
      glVertex3f(0, 6, 0);
      glVertex3f(5, 6, 0);
      glVertex3f(5, 5, 0);
      glVertex3f(0, 5, 0);
      glVertex3f(0, 6, 0);

      glEnd();

      glBegin(GL_QUADS);

      // Player 1 Scoreboard
      glVertex3f(-5 + p1, 5, 0);
      glVertex3f(-5 + p1, 6, 0);
      glVertex3f(-5, 6, 0);
      glVertex3f(-5, 5, 0);
      
      // Player 2 Scoreboard
      glVertex3f(5, 5, 0);
      glVertex3f(5, 6, 0);
      glVertex3f(5 - p2, 6, 0);
      glVertex3f(5 - p2, 5, 0);

      glEnd();
    }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  Board::draw();

  //paddle 1
  Paddle::draw(-10, paddle1Y);
  //paddle 2
  Paddle::draw(10.5, paddle2Y);

  Ball::draw(ballPosX, ballPosY);

  ScoreBoard::draw(p1Points, p2Points);

  glFlush();
  glutSwapBuffers();
}

void timer(int v) {
  int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
  int deltaTime = timeSinceStart - oldTimeSinceStart;
  oldTimeSinceStart = timeSinceStart;

  GLfloat dt = (GLfloat)deltaTime/1000;

  if (wDown)
  {
    paddle1Y += dt * paddleSpeed;
    if (paddle1Y > 4)
      paddle1Y = 4;
  }
  if (sDown)
  {
    paddle1Y -= dt * paddleSpeed;
    if (paddle1Y < -4)
      paddle1Y = -4;
  }
  if (upDown)
  {
    paddle2Y += dt * paddleSpeed;
    if (paddle2Y > 4)
      paddle2Y = 4;
  }
  if (downDown)
  {
    paddle2Y -= dt * paddleSpeed;
    if (paddle2Y < -4)
      paddle2Y = -4;
  }

    if (ballPosY >= 4.75 || ballPosY <= -4.75)
    {
        ballVelY = -ballVelY;
        ballPosY = 4.75 * (ballPosY/abs(ballPosY));
    }
    if (ballPosX >= 9.75)
    {
        // Inside paddle
        if (abs(paddle2Y - ballPosY) <= 1.25)
        {
            ballSpeed += 0.2;
            GLfloat a = pi*120*(ballPosY - paddle2Y)/360;
            ballVelX = -cos(a) * ballSpeed;
            ballVelY = sin(a) * ballSpeed;
            ballPosX = 9.74;
        }
        else
        {
            p1Points++;
            ballSpeed = 3;
            ballPosY = 0;
            ballPosX = 5;
            ballVelY = 0;
            ballVelX = -ballSpeed;
        }
    }
    else if (ballPosX <= -9.75)
    {
        // Inside paddle
        if (abs(paddle1Y - ballPosY) <= 1.25)
        {
            ballSpeed += 0.2;
            GLfloat a = pi*120*(ballPosY - paddle1Y)/360;
            ballVelX = cos(a) * ballSpeed;
            ballVelY = sin(a) * ballSpeed;
            ballPosX = -9.74;
        }
        else
        {
            p2Points++;
            ballSpeed = 3;
            ballPosY = 0;
            ballPosX = -5;
            ballVelY = 0;
            ballVelX = ballSpeed;
        }
    }

    ballPosY += ballVelY*.03;
    ballPosX += ballVelX*.03;

  glutPostRedisplay();
  glutTimerFunc(1000/60.0, timer, v);
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.5, 40.0);
  glMatrixMode(GL_MODELVIEW);
}

void init() {
  glEnable(GL_CULL_FACE);

  glCullFace(GL_BACK);

  gluLookAt(0, 0.5, 10, 0, 0.5, 0, 0, 1, 0);

  glColor3f(1, 1, 1);
  glLineWidth(1);

}

void keyDown (unsigned char key, int x, int y)
{
  //printf("%i", key);
  if (key == 27) //escape
		exit(0);
  if (key == 119) //w
    wDown = true;
  if (key == 115) //s
    sDown = true;
  if (key == 117) //u
    upDown = true;
  if (key == 106) //j
    downDown = true;
}

void keyUp (unsigned char key, int x, int y)
{
  if (key == 119) //w
    wDown = false;
  if (key == 115) //s
    sDown = false;
  if (key == 117) //u
    upDown = false;
  if (key == 106) //j
    downDown = false;
}

// The usual main for a GLUT application.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1000, 500);
  glutCreateWindow("Pong");
  glutReshapeFunc(reshape);
  glutTimerFunc(100, timer, 0);
  glutDisplayFunc(display);
  init();
  glutKeyboardFunc(keyDown);
  glutKeyboardUpFunc(keyUp);
  glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

  glutMainLoop();
}