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
//이거 아니면 윈도우 생성이 안됨
//int main(int argc, char** argv) {
//    glutInit(&argc, argv); // Initialize GLUT


GLint W=600, H=400;

void DrawNearProjPlane() // Near 투영면 그리기 ==> 실제로 겹치는 부분을 보기 위해
{
glColor4f(1.0, 1.0, 1.0, 0.5); // blending 시키기
glBegin(GL_POLYGON);
glVertex3f(-0.5, -0.5, 1.0);
glVertex3f(0.5, -0.5, 1.0);
glVertex3f(0.5, 0.5, 1.0);
glVertex3f(-0.5, 0.5, 1.0);
glEnd();
}

void MyDisplay() {
glClear(GL_COLOR_BUFFER_BIT);

//아래 코드는 현재 빨갛게 일부 보이는 두 경우의 그림에 대해 각각 3개 뷰포트를 이용해 그려본 것임
// 위 두 경우 모두 네 개의 점이 한 평면에 있지 않기 때문에 내부적으로 이를 처리할 때는 점의 정의되는 순서에 따라
// 세 개씩 모아서 삼각형 단위로 그리는 것으로 파악됨
// 따라서
// 1. 원래 사각형을 그린 결과와
// 2. 이를 두 개의 삼각형으로 나누어 각각 그린 결과를 비교해보면 일치하는 것을 알 수 있음
// 참고로, 뷰볼륨을 벗어난(짤리는) 부분을 확실히 보기 위해 투영면을 추가로 그려 보았음
// 정사영 개념처럼 잘린 부분이 그려짐
// 특별한 경우가 아니라면 뷰볼륨을 충분히 크게 잡고 짤리지 않게 사용할 것
glViewport(0, 0, W/3, H/2);
glColor4f(1.0, 0.0, 0.0, 0.5);
glBegin(GL_POLYGON); // 원래 사각형: 왼쪽 하단
glVertex3f(-0.5, -0.5, 2.0);
glVertex3f(0.5, -0.5, 0.0);
glVertex3f(0.5, 0.5, 2.0);
glVertex3f(-0.5, 0.5, 0.0);
glEnd();
//=====================
glViewport(W / 3, 0, W / 3, H / 2); // 중앙 하단
glColor4f(1.0, 0.0, 0.0, 0.5);
glBegin(GL_POLYGON);
glVertex3f(-0.5, -0.5, 2.0); // 위 사각형을 구성하는 첫번째 삼각형
glVertex3f(0.5, -0.5, 0.0);
glVertex3f(0.5, 0.5, 2.0);
glEnd();
DrawNearProjPlane(); // 투영면 그리기
//=====================
glViewport(2*W / 3, 0, W / 3, H / 2);
glColor4f(0.0, 1.0, 0.0, 0.5);
glBegin(GL_POLYGON); // 오른쪽 하단
glVertex3f(0.5, 0.5, 2.0); // 위 사각형을 구성하는 두번째 삼각형
glVertex3f(-0.5, 0.5, 0.0);
glVertex3f(-0.5, -0.5, 2.0);
glEnd();
DrawNearProjPlane(); // 투영면 그리기

    //=====================
    glViewport(0, H / 2, W / 3, H / 2);
    glColor4f(1.0, 0.0, 0.0, 0.5);
    glBegin(GL_POLYGON); // 원래 사각형: 왼쪽 상단
    glVertex3f(-0.5, -0.5, 2.0);
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
    glVertex3f(-0.5, 0.5, 0.0);
    glEnd();
    //=====================
    glViewport(W / 3, H / 2, W / 3, H / 2);
    glColor4f(1.0, 0.0, 0.0, 0.5);
    glBegin(GL_POLYGON);  // 중앙 상단
    glVertex3f(-0.5, -0.5, 2.0); // 위 사각형을 구성하는 첫번째 삼각형
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
    glEnd();
    DrawNearProjPlane(); // 투영면 그리기
    //=====================
    glViewport(2 * W / 3, H / 2, W / 3, H / 2); // 오른쪽 상단
    glColor4f(0.0, 1.0, 0.0, 0.5);
    glBegin(GL_POLYGON);
    glVertex3f(0.5, 0.5, 0.0); // 위 사각형을 구성하는 두번째 삼각형
    glVertex3f(-0.5, 0.5, 0.0);
    glVertex3f(-0.5, -0.5, 2.0);
    glEnd();
    DrawNearProjPlane(); // 투영면 그리기

    glFlush();
    }
    void MyReshape(int newWidth, int newHeight) {
    glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);
    W = newWidth; H = newHeight; // 확대해서 크게 보기 바람
    }



int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(W, H);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("My OGL");
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);

    // 다각형-투영면이 걸치는 부분을 보기 위해 블랜딩 기능 활성화
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutMainLoop();

    return 0;
    }

