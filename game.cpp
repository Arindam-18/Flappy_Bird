#include <bits/stdc++.h>
#include <GL/glut.h>
#include "game.h"

void Rotate(float theta, std::vector<int> *pts){
    float t = theta * acos(-1) / 180.0;
    float c = cos(t), s = sin(t);
    float M[3][3] = {{c, -s, 0}, {s, c, 0}, {0, 0, 1}};
    float result[3][4];
    for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
            result[i][j] = 0.0;
            for(int k=0; k<3; k++){
                result[i][j] += M[i][k] * pts[k][j];
            }
        }
    }

    for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
            pts[i][j] = round(result[i][j]);
        }
    }
}

Game::Game(){
    screenWidth = 1500;
    screenHeight = 750;
    acceleration = -0.5;

    birdHeight = 40;
    birdWidth = 50;

    srand((unsigned int)time(nullptr));
    init();
    gameOver = true;
}

int Game::getHeight(){
    return screenHeight;
}

int Game::getWidth(){
    return screenWidth;
}

void Game::init(){
    birdY = (float)screenHeight/2;
    birdVelocity = 0.0;
    score = 0;
    gameOver = false;

    pipePositions.clear();
    pipeGap = 300;
    pipeSpeed = 7;
    pipeWidth = 75;
}

void Game::handleInput(unsigned char key){
    if(key==32 && !gameOver){
        birdVelocity = 8.5;
    }
    else if(key==32 && gameOver){
        init();
    }
    else if(key==27 && gameOver){
        exit(0);
    }
}

bool Game::checkCollision(){
    int top = round(birdY + birdHeight/2);
    int bottom = round(birdY - birdHeight/2);
    int left = 100 - birdWidth/2;
    int right = 100 + birdWidth/2;
    int bY = round(birdY);

    bool result = false;
    if(bottom <= 25 || top >= screenHeight - 25){
        return true;
    }
    for(auto x: pipePositions){
        int ptop = x.second + pipeGap/2;
        int pbottom = x.second - pipeGap/2;
        int pleft = x.first - pipeWidth/2;
        int pright = x.first + pipeWidth/2;
        for(int i=0; i<4; i++){
            if((right <= pright && right >= pleft) || (left <= pright && left >= pleft)){
                if(bottom <= pbottom && left>= pleft){
                    result = true;
                }
                if(top >= ptop && left <= pright){
                    result = true;
                }
            }
        }
    }

    return result;    
}

void Game::drawScore(){
    std::string s = "Score: " + std::to_string(score);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(25,screenHeight-21);
    for(int i=0; i<s.length(); i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    }
}

void Game::drawStart(){
    unsigned char s[] = "Press [Space] to Start";
    int w = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, s);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(screenWidth/2 - w/2 + 50,screenHeight/2);
    for(unsigned char *c = s; *c != '\0'; c++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}

void Game::update(){
    if(!gameOver){
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

        birdY += birdVelocity;
        birdVelocity += acceleration;
        birdY = std::max(0.0, (double)birdY);
        birdVelocity = std::max(-10.0, (double)birdVelocity);

        gameOver = checkCollision();

        score++;
        if(score%1500 == 0)
            pipeSpeed += 1;
        theta = 1.5 * birdVelocity;
    }
    else{
        birdY = (float)screenHeight/2;
        theta = 0.0;
        pipePositions.clear();
    }
}

void Game::generatePipes(){
    std::pair<int, int> p(screenWidth + pipeWidth/2, (rand() % (screenHeight - pipeGap - 150)) + pipeGap/2 + 75);
    pipePositions.push_back(p);
}

void Game::drawTunnel(){
    glColor3i(92,64,51);
    glBegin(GL_QUADS);
    glVertex2i(0, 25);
    glVertex2i(screenWidth, 25);
    glVertex2i(screenWidth, 0);
    glVertex2i(0, 0);
    
    glVertex2i(0, screenHeight);
    glVertex2i(screenWidth, screenHeight);
    glVertex2i(screenWidth, screenHeight-25);
    glVertex2i(0, screenHeight-25);
    glEnd();
}

void Game::drawScene(){
    drawBird();
    for(auto position : pipePositions){
        drawPipe(position.first, position.second);
    }
    drawTunnel();
    drawScore();
    if(gameOver)
        drawStart();
}

void Game::drawBird(){
    int top = round(birdY + birdHeight/2);
    int bottom = round(birdY - birdHeight/2);
    int left = 100 - birdWidth/2;
    int right = 100 + birdWidth/2;
    int bY = round(birdY);
    std::vector<int> pts[3] = {{left-100, right-100, right-100, left-100}, {bottom-bY, bottom-bY, top-bY, top-bY}, {1,1,1,1}};

    Rotate(theta, pts);
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2i(100+pts[0][0], bY+pts[1][0]);
    glVertex2i(100+pts[0][1], bY+pts[1][1]);
    glVertex2i(100+pts[0][2], bY+pts[1][2]);
    glVertex2i(100+pts[0][3], bY+pts[1][3]);
    glEnd();
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