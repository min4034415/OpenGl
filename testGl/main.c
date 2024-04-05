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
#include <stdio.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
//이거 아니면 윈도우 생성이 안됨
//int main(int argc, char** argv) {
//    glutInit(&argc, argv); // Initialize GLUT

GLint     Init_width = 300,
    Init_height = 300;
GLdouble Width_factor = 1.0,     Height_factor = 1.0;

void MyDisplay() {
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0, 0.0, 1.0);
glBegin(GL_POLYGON);
glVertex3f(-0.5, -0.5, 0.0);
glVertex3f(0.5, -0.5, 0.0);
glVertex3f(0.5, 0.5, 0.0);
glVertex3f(-0.5, 0.5, 0.0);
glEnd();
glFlush();
printf("calling MyDisplay...\n");
}

void MyReshape(int NewWidth, int NewHeight) {
glViewport(0, 0, NewWidth,  NewHeight );

Width_factor = NewWidth /(GLdouble)Init_width;
Height_factor = NewHeight / (GLdouble)Init_height;

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(     -1.0*Width_factor, 1.0*Width_factor,
        -1.0*Height_factor, 1.0*Height_factor,
        -1.0, 1.0); // 직교 투영 함수
printf("calling MyReshape...\n");
}


int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT

    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(Init_width, Init_height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("My OGL");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutMainLoop();
    return 0;
    }
