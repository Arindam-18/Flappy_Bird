#ifndef GAME_H
#define GAME_H
#include <vector>
#include <utility>

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
        int acceleration;       //
        int score;

        int birdY;
        int birdWidth;          //
        int birdHeight;         //
        int birdVelocity;       //

        std::vector<std::pair<int ,int>> pipePositions;
        int pipeWidth;
        int pipeGap;
        int pipeSpeed;
        
        bool gameOver;

        void generatePipes();
        // void drawBird();
        void drawPipe(int, int);
        // bool checkCollision();
        // void resetGame();

};

#endif //GAME_H