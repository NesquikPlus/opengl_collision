#include "Game.h"
#include "GameObject.h"


int main()
{
    Game game(1600, 900, glm::vec3(0,0,12));
  
    GameObject w1("objFolder/wall/wall.obj", glm::vec3(0.0f, 0.0f, -4.4f), glm::vec3(0.0f, 0.0f, 0.0f), 1000, glm::vec3(0,1,0), 0.0f);
    GameObject w2("objFolder/wall/wall.obj", glm::vec3(-4.4f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1000, glm::vec3(0,1,0), 1.57f);
    GameObject w3("objFolder/wall/wall.obj", glm::vec3(4.4f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1000, glm::vec3(0,1,0), 1.57f);
    GameObject w4("objFolder/wall/wall.obj", glm::vec3(0.0f, 4.4f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1000, glm::vec3(1,0,0), 1.57f);
    GameObject w5("objFolder/wall/wall.obj", glm::vec3(0.0f, -4.4f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1000, glm::vec3(1,0,0), 1.57f);

    GameObject g1("objFolder/ball/earth.obj", glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(-0.5f, -3.8f, 5.4f), 10);
    GameObject g2("objFolder/ball/earth.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(5.7f, 1.0f, -1.0f), 10);
    GameObject g3("objFolder/ball/earth.obj", glm::vec3(-3.0f, -3.0f, -3.0f), glm::vec3(1.3f, 1.0f, -1.0f), 10);
    GameObject g4("objFolder/ball/earth.obj", glm::vec3(3.0f, -3.0f, 3.0f), glm::vec3(-1.2f, 0.1f, 1.2f), 10);
    GameObject g5("objFolder/ball/earth.obj", glm::vec3(-3.0f, 3.0f, -1.0f), glm::vec3(1.5f, -4.2f, 2.2f), 10);


    game.AddWall(w1);
    game.AddWall(w2);
    game.AddWall(w3);
    game.AddWall(w4);
    game.AddWall(w5);

    game.AddGameObject(g1);
    game.AddGameObject(g2);
    game.AddGameObject(g3);
    game.AddGameObject(g4);
    game.AddGameObject(g5);

    game.Start();
    
    return 0;
}

