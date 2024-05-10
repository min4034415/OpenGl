//
//  main.c
//  testGl
//
//  Created by Ouimin Lee on 4/5/24.
//
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
//이거 아니면 윈도우 생성이 안됨
//int main(int argc, char** argv) {
//    glutInit(&argc, argv); // Initialize GLUT
#include <stdbool.h>
#include <stdlib.h>

//GLboolean IsSphere = GL_TRUE;
//GLboolean IsSmall = GL_TRUE;
#include <math.h>
#include <stdio.h>




int shoulder = 20, elbow = 0;
int shoulder1 = 20, elbow1 = 0;
int shoulder2 = 20, elbow2 = 0;
int shoulder3 = 20, elbow3 = 0;

void funky(float number){
    glPushMatrix();
    glTranslatef (number, 0.0, 0.0);
    switch ((int)number) {
        case -1:
            glRotatef ((GLfloat) shoulder, 1.0, 0.0, 0.0);
            break;
        case -2:
            glRotatef ((GLfloat) shoulder1, 1.0, 0.0, 0.0);
            break;
        case -3:
            glRotatef ((GLfloat) shoulder2, 1.0, 0.0, 0.0);
            break;
        case -4:
            glRotatef ((GLfloat) shoulder3, 1.0, 0.0, 0.0);
            break;
            
        default:
            break;
    }
    
    glTranslatef (1.0, 0.0, 0.0);
    
    glPushMatrix();
    glScalef (1.0, 0.2, 1.0);
    glutWireCube (1.0);
    
    glPopMatrix();
    
    
    glTranslatef (-1.0, 0.0, -1.0);
    switch ((int)number) {
        case -1:
    glRotatef ((GLfloat) elbow, 1.0, 0.0, 0.0);
            break;
        case -2:    
            glRotatef ((GLfloat) elbow1, 1.0, 0.0, 0.0);
            break;
        case -3:            
            glRotatef ((GLfloat) elbow2, 1.0, 0.0, 0.0);
            break;
        case -4:
            glRotatef ((GLfloat) elbow3, 1.0, 0.0, 0.0);
            break;
        default:
            break;
    }
//    glRotatef ((GLfloat) elbow, 1.0, 0.0, 0.0);
    glTranslatef (1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef (1.0, 0.2, 1.0);
    glutWireCube (1.0);
    glPopMatrix();
    
    glPopMatrix();
}
void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);  // glShadeModel(GL_FLAT);
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
        
    glPushMatrix();
   glTranslatef (-1.0, 0.0, 2.0);
    glRotatef ((GLfloat) 20, 1.0, 0.0, 0.0);
    
    /*draws palm*/
    glPushMatrix();
    glTranslatef (0.0, 0.7, 3.5);
       glScalef (-1.5, 0.2, 1.7);
       glutWireCube (1.0); // Draw the palm
    
       glPopMatrix();
    
////    glPushMatrix();
//    glScalef (-4.0, 0.2, 4.0);
//    glutWireCube (1.0);
//    
//    glRotatef ((GLfloat) shoulder, 1.0, 0.0, 0.0);
//    
//    glPopMatrix();
//    
    
    
    funky(-1.0);
    funky(-2.0);
    funky(-3.0);
    funky(-4.0);
        glPopMatrix();
        
        glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 7.0);
    //   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 5.5);
    //   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 5.4);
    //glOrtho(-4.0, 4.0, -4.0, 4.0, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0., 0., 6., 0., 0., 0., 0., 1., 0.);
}
void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
        case 'y':
            shoulder = (shoulder + 5) % 360;
            glutPostRedisplay();         break;
        case 'Y':
            shoulder = (shoulder - 5) % 360;
            glutPostRedisplay();         break;
        case 'h':
            elbow = (elbow + 5) % 360;
            glutPostRedisplay();         break;
        case 'H':
            elbow = (elbow - 5) % 360;
            glutPostRedisplay();         break;
            
        case 'u':
            shoulder1 = (shoulder1 + 5) % 360;
            glutPostRedisplay();         break;
        case 'U':
            shoulder1 = (shoulder1 - 5) % 360;
            glutPostRedisplay();         break;
        case 'j':
            elbow1 = (elbow1 + 5) % 360;
            glutPostRedisplay();         break;
        case 'J':
            elbow1 = (elbow1 - 5) % 360;
            glutPostRedisplay();            break;
            
        case 'i':
            shoulder2 = (shoulder2 + 5) % 360;
            glutPostRedisplay();         break;
        case 'I':
            shoulder2 = (shoulder2 - 5) % 360;
            glutPostRedisplay();         break;
        case 'k':
            elbow2 = (elbow2 + 5) % 360;
            glutPostRedisplay();         break;
        case 'K':
            elbow2 = (elbow2 - 5) % 360;
            glutPostRedisplay(); break;
            
        case 'o':
            shoulder3 = (shoulder3 + 5) % 360;
            glutPostRedisplay();         break;
        case 'O':
            shoulder3 = (shoulder3 - 5) % 360;
            glutPostRedisplay();         break;
        case 'l':
            elbow3 = (elbow3 + 5) % 360;
            glutPostRedisplay();         break;
        case 'L':
            elbow3 = (elbow3 - 5) % 360;
            glutPostRedisplay(); break;
            
        case 27:
            exit(0);         break;
        default:         break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Robot Arm");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}

