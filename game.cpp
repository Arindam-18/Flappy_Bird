#include <bits/stdc++.h>
#include <GL/glut.h>
#include "game.h"

Game::Game(){
    screenWidth = 800;
    screenHeight = 600;

    srand((unsigned int)time(nullptr));
    init();
}

int Game::getHeight(){
    return screenHeight;
}

int Game::getWidth(){
    return screenWidth;
}

void Game::init(){
    birdY = screenHeight/2;
    birdVelocity = 0;
    gameOver = true;

    pipePositions.clear();
    pipeGap = 200;
    pipeSpeed = 5;
    pipeWidth = 75;
}

void Game::handleInput(unsigned char key){
    if(key==32 && !gameOver){
        birdVelocity = 10;
    }
    else if(key==32 && gameOver){
        // Implement Game Start
    }
}

void Game::update(){
    if(pipePositions.empty() || screenWidth - pipePositions.back().first >= 350){
        generatePipes();
    }

    for(int i=0; i<pipePositions.size(); i++){
        pipePositions[i].first -= pipeSpeed;
            if (pipePositions[i].first + pipeWidth <= 0) {
                pipePositions.erase(pipePositions.begin() + i);
                --i;
            }
    }
}

void Game::generatePipes(){
    std::pair<int, int> p(screenWidth + pipeWidth/2, (rand() % (screenHeight - pipeGap - 150)) + pipeGap/2 + 75);
    pipePositions.push_back(p);
}

void Game::drawScene(){
    for(auto position : pipePositions){
        drawPipe(position.first, position.second);
    }
}

void Game::drawPipe(int pos, int gap){
    int top = gap + pipeGap/2;
    int bottom = gap - pipeGap/2;
    int left = pos - pipeWidth/2;
    int right = pos + pipeWidth/2;

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2i(left, screenHeight);
    glVertex2i(left, top);
    glVertex2i(right, top);
    glVertex2i(right, screenHeight);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(left, 0);
    glVertex2i(left, bottom);
    glVertex2i(right, bottom);
    glVertex2i(right, 0);
    glEnd();

}