//
//  main.c
//  testGl
//
//  Created by Ouimin Lee on 4/5/24.
//
#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
    glVertex3f(-0.5, 0.5, 0.0);
    glEnd();
    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT

    glutCreateWindow("Hello OpenGL");
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    return 0;

}
