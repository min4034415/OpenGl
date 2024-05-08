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

GLvoid  initgfx( GLvoid );
GLvoid  drawScene( GLvoid );
GLvoid  reshape( GLsizei, GLsizei );
GLvoid  mouse( GLint, GLint, GLint, GLint );
GLvoid  motion( GLint, GLint );

GLfloat segSize=1.0, joint12Radius=1.0, joint3Radius=0.4, jointOrg=-4.0,
           seg1ScaleSize=4.0, seg2ScaleSize=2.0, rotAngle=45.0;

void resetView( GLvoid );
void polarView( GLfloat, GLfloat, GLfloat, GLfloat );

enum             actions { MOVE_EYE, TWIST_EYE, ZOOM, MOVE_NONE };
static GLint     action;
static GLdouble    xStart = 0.0, yStart = 0.0;
static GLfloat     fovy, nearClip, farClip, distance, twistAngle, incAngle, azimAngle;

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    GLsizei width, height;    glutInit( &argc, argv );

    width = glutGet( GLUT_SCREEN_WIDTH );
    height = glutGet( GLUT_SCREEN_HEIGHT );
    glutInitWindowPosition( width / 4, height / 4 );
    glutInitWindowSize( (width / 2) - 4, height / 2 );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    glutCreateWindow( argv[0] );

    initgfx();

    glutMouseFunc( mouse );    glutMotionFunc( motion );    glutReshapeFunc( reshape );
    glutDisplayFunc( drawScene );

    glutMainLoop();
}

GLvoid  initgfx( GLvoid )
{
    glClearColor( 0.0, 0.0, 0.0, 1.0 );

    glEnable( GL_DEPTH_TEST );
    fovy = 60.0;
    nearClip = 3.0;
    farClip  = 12.0;
    resetView();
    glEnable( GL_LIGHT0 );
}

GLvoid  mouse( GLint button, GLint state, GLint x, GLint y )
{
    static GLint buttons_down = 0;

    if (state == GLUT_DOWN) {
         switch (button) {
         case GLUT_LEFT_BUTTON:    action = MOVE_EYE; break;
         case GLUT_MIDDLE_BUTTON:    action = TWIST_EYE; break;
         case GLUT_RIGHT_BUTTON:    action = ZOOM;    break;
         }
         xStart = x;         yStart = y;
    } else {
         if (--buttons_down == 0)  action = MOVE_NONE;
    }
}

GLvoid  motion( GLint x, GLint y )
{
    switch (action) {
    case MOVE_EYE:
         azimAngle += (GLdouble) (x - xStart);
         incAngle -= (GLdouble) (y - yStart);         break;
    case TWIST_EYE:
         twistAngle = fmod(twistAngle+(x - xStart), 360.0);         break;
    case ZOOM:
         distance -= (GLdouble) (y - yStart)/10.0;         break;
    default:
         printf("unknown action %d\n", action);
    }
    
    xStart = x;    yStart = y;
    glutPostRedisplay();
}

void  resetView( GLvoid )
{
    distance = nearClip + (farClip - nearClip) / 2.0;
    twistAngle = 0.0;    /* rotation of viewing volume (camera) */
    incAngle = 0.0;    azimAngle = 0.0;    fovy = 90.0;
}

GLvoid   reshape( GLsizei width, GLsizei height )
{
    GLdouble     aspect;
    glViewport( 0, 0, width, height );
    aspect = (GLdouble) width / (GLdouble) height;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( fovy, aspect, nearClip, farClip );
    glMatrixMode( GL_MODELVIEW );
}

void   polarView( GLfloat distance, GLfloat azimuth, GLfloat incidence,
              GLfloat twist)
{
    glTranslatef( 0.0, 0.0, -distance);
    glRotatef( -twist, 0.0, 0.0, 1.0);
    glRotatef( -incidence, 1.0, 0.0, 0.0);
    glRotatef( -azimuth, 0.0, 0.0, 1.0);
}

GLvoid   drawScene( GLvoid )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glPushMatrix();
      polarView( distance, azimAngle, incAngle, twistAngle );
      glEnable( GL_LIGHTING );
         
      glPushMatrix();
           glTranslatef( jointOrg, 0.0, 0.0 );
           glutSolidSphere( joint12Radius, 31, 31 );
      glPopMatrix();

      glPushMatrix();
           glTranslatef( jointOrg+joint12Radius +
                                  (seg1ScaleSize*segSize)/2.0, 0.0, 0.0 );
          
           glPushMatrix();
                     glScalef ( seg1ScaleSize, 1.0, 1.0 );
                     glutSolidCube( segSize );
           glPopMatrix();
          
    
    glPushMatrix();
                         glTranslatef( seg1ScaleSize/2.0+joint12Radius, 0.0, 0.0 );
                         // if not, jointOrg+joint12Radius+
                         // seg1ScaleSize/2.0+seg1ScaleSize/2.0+joint12Radius
                         glutSolidSphere( joint12Radius, 31, 31 );

                         glPushMatrix();
          glRotatef( rotAngle, 0.0, 0.0, 1.0 );
          glTranslatef( joint12Radius +
                                                   (segSize*seg2ScaleSize)/2.0, 0.0, 0.0 );
                  
          glPushMatrix();
                                          glScalef ( seg2ScaleSize, 1.0, 1.0 );
                                          glutSolidCube( segSize );
          glPopMatrix();
          glPushMatrix();
                   glTranslatef( (segSize*seg2ScaleSize)/2.0 +
                                                                  joint3Radius, 0.0, 0.0 );
                   glutSolidSphere( joint3Radius, 31, 31 );
          glPopMatrix();

                         glPopMatrix();
                  glPopMatrix();
             glPopMatrix();

             glDisable( GL_LIGHTING );
        glPopMatrix();
        glutSwapBuffers();
    }


