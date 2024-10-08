#include <bits/stdc++.h>
#include <GL/glut.h>
#include "game.h"

#define FPS 45
using namespace std;
Game flappyBird;

void init(){
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(flappyBird.getWidth(), flappyBird.getHeight());
    glutInitWindowPosition(25, 50);
    glutCreateWindow("Flappy_Bird");
    glClearColor(0.43, 0.30, 0.21, 0.0);
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

void keyboard(unsigned char key, int x, int y){
    flappyBird.handleInput(key);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}

