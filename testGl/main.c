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

GLboolean IsSphere = true;
GLboolean IsSmall = true;

void MyDisplay( ){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.0, 0.5);
    
    if ((IsSphere) && (IsSmall))
        glutWireSphere(0.2, 15, 15);
    else if ((IsSphere) && (!IsSmall))
        glutWireSphere(0.4, 15, 15);
    else if ((!IsSphere) && (IsSmall))
        glutWireTorus(0.1, 0.3, 40, 20);
    else glutWireTorus(0.2, 0.5, 40, 20);
    glFlush( );
}
void MyMainMenu(int entryID){
    if(entryID == 1)    IsSphere = true;
    else if (entryID == 2)   IsSphere = false;
    else if(entryID == 3)    exit(0);
    glutPostRedisplay();
}
void MySubMenu(int entryID){
    if(entryID == 1) IsSmall = true;
    else if (entryID == 2)  IsSmall = false;
    glutPostRedisplay();
}



int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Example");
    glClearColor (1.0, 1.0, 1.0, 1.0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    
    GLint MySubMenuID = glutCreateMenu(MySubMenu);
    
    glutAddMenuEntry("Small One", 1);
    glutAddMenuEntry("Big One", 2);
    
    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
    glutAddMenuEntry("Draw Sphere", 1);
    glutAddMenuEntry("Draw Torus", 2);
    glutAddSubMenu("Change Size", MySubMenuID);
    glutAddMenuEntry("Exit", 3);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    glutDisplayFunc(MyDisplay);
    glutMainLoop( );
    return 0;
}
