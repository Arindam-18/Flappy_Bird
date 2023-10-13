#include <bits/stdc++.h>
#include <GL/glut.h>
#include "game.h"

#define FPS 60
using namespace std;
Game flappyBird;

void init(){
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(flappyBird.getWidth(), flappyBird.getHeight());
    glutInitWindowPosition(600, 100);
    glutCreateWindow("Flappy_Bird");
    glClearColor(0.0, 0.51, 0.5, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, flappyBird.getWidth(), 0, flappyBird.getHeight(), -1.0, 1.0);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    flappyBird.drawScene();
    glFlush();
    glutSwapBuffers();
}

void update(int value){
    flappyBird.update();
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, update, 0);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}

