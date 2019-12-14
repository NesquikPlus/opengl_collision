#include "Game.h"
#include "GameObject.h"


int main()
{
    Game game;
  
    GameObject g1("objFolder/ball/ball.obj", glm::vec3(5.0f, 0.4f, -0.3f), glm::vec3(-1.0f, -0.1f, 0.1f), 10);
    GameObject g2("objFolder/ball/ball.obj", glm::vec3(-5.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.1f, 0.2f), 50);
    GameObject g3("objFolder/ball/ball.obj", glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.1f, 0.2f), 30);

    game.AddGameObject(g1);
    game.AddGameObject(g2);


    game.Start();
    
    return 0;
}

