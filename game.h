#ifndef GAME_H
#define GAME_H
#include <vector>
#include <utility>
#include <string>

class Game{
    public:
        Game();
        void init();
        void handleInput(unsigned char key);
        void update();
        void drawScene();
        int getHeight();
        int getWidth();

    private:
        int screenWidth;
        int screenHeight;
        float acceleration;       //

        int score;
        int birdWidth;          //
        int birdHeight;         //
        float birdY;
        float birdVelocity;       //
        float theta;

        std::vector<std::pair<int ,int>> pipePositions;
        int pipeWidth;
        int pipeGap;
        int pipeSpeed;
        
        bool gameOver;

        void generatePipes();
        void drawTunnel();
        void drawBird();
        void drawPipe(int pos, int gap);
        bool checkCollision();
        void drawScore();
        void drawStart();

};

void Rotate(float theta, std::vector<int> *pts);

#endif //GAME_H