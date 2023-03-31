#include <GL/glut.h>
#include <math.h>
#include <stdlib.h> 

#define PI 3.14159265

GLfloat angle = 0.0f; // Current angle of the jet
GLfloat x = 0.0f;     // Current x position of the jet
GLfloat y = 0.0f;     // Current y position of the jet
GLfloat flameX = 0.0f; // X position of the flame
GLfloat flameY = 0.0f; // Y position of the flame
GLfloat flameSize = 0.02f; // Size of the flame

void display() {
   glClear(GL_COLOR_BUFFER_BIT);

   glPushMatrix();

   glTranslatef(x, y, 0.0f);
   glRotatef(angle, 0.0f, 0.0f, 1.0f);

   // Draw the jet
   glColor3f(1.0f, 0.0f, 0.0f);
   glBegin(GL_POLYGON);
      glVertex2f(-0.2f, 0.0f);
      glVertex2f(0.2f, 0.0f);
      glVertex2f(0.0f, 0.5f);
   glEnd();

   // Draw the jet's wings
   glColor3f(0.0f, 1.0f, 0.0f);
   glBegin(GL_POLYGON);
      glVertex2f(-0.2f, 0.0f);
      glVertex2f(-0.3f, -0.3f);
      glVertex2f(-0.2f, -0.3f);
   glEnd();
   glBegin(GL_POLYGON);
      glVertex2f(0.2f, 0.0f);
      glVertex2f(0.3f, -0.3f);
      glVertex2f(0.2f, -0.3f);
   glEnd();

   // Draw the flame
   glColor3f(1.0f, 1.0f, 0.0f);
   glBegin(GL_POINTS);
      for(int i = 0; i < 10; i++) {
         GLfloat xOffset = (rand() / (GLfloat)RAND_MAX * 0.1f - 0.05f) * flameSize;
         GLfloat yOffset = (rand() / (GLfloat)RAND_MAX * 0.1f - 0.05f) * flameSize;
         glVertex2f(flameX + xOffset, flameY + yOffset);
      }
   glEnd();

   glPopMatrix();

   // Render the registration number
   glColor3f(1.0f, 1.0f, 1.0f);
   glRasterPos2f(-0.95f, -0.95f);
   const char* regNumber = "11914859";
   for(int i = 0; i < strlen(regNumber); i++) {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, regNumber[i]);
   }

   glutSwapBuffers();
}

void update(int value) {
   // Update the jet's angle and position
   angle += 2.0f;
   if (angle > 360.0f) {
      angle -= 360.0f;
   }
   x = cos(angle * PI / 180.0f) * 0.5f;
   y = sin(angle * PI / 180.0f) * 0.5f;

// Update the flame position and size
flameX = cos(angle * PI / 180.0f) * -0.2f;
flameY = sin(angle * PI / 180.0f) * -0.2f;
flameSize = 0.02f + (rand() / (GLfloat)RAND_MAX * 0.01f);

glutPostRedisplay(); // Tell GLUT to redraw the screen
glutTimerFunc(25, update, 0); // Call update again in 25 milliseconds
}

int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize(500, 500);
glutCreateWindow("Jet");
glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
glutDisplayFunc(display);
glutTimerFunc(25, update, 0); // Call update every 25 milliseconds
glutMainLoop();
return 0;
}

