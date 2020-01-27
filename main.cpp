#include "Game.h"
#include "GameObject.h"


int main()
{
    Game game;
  
    GameObject g1("objFolder/ball/ball.obj", glm::vec3(5.0f, 0.4f, -0.6f), glm::vec3(-1.0f, -0.1f, 0.1f), 100);
    GameObject g2("objFolder/ball/ball.obj", glm::vec3(-5.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.1f, 0.2f), 10);
    GameObject g3("objFolder/ball/ball.obj", glm::vec3(-4.0f, -1.0f, -2.0f), glm::vec3(0.0f, 0.1f, 0.2f), 200);
    GameObject g4("objFolder/ball/ball.obj", glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.5f, 0.1f, 0.2f), 30);

    game.AddGameObject(g1);
    game.AddGameObject(g2);
    game.AddGameObject(g3);
    game.AddGameObject(g4);
    game.Start();
    
    return 0;
}

