#include "./player.h"
#include "./animator.h"

void Player::init()
{
    playerModel = new Model("game/models/player/vampire/vampire.dae");
    // danceAnimation = new Animation("game/models/player/vampire/vampire.dae", playerModel);
    // animator = new Animator(danceAnimation);
    // animator->PlayAnimation(danceAnimation);

    // player = new Model("game/models/player/player.obj", 1);
    playerModel->position = glm::vec3(0.0f, 0.0f, 0.0f);

    this->addChild(playerModel, this->scene);

    RenderObject::init();
}

void Player::renderScene(float delta, Shader *shader, bool isShadowRender)
{
    // std::cout << "render floor \n";
    playerModel->renderScene(delta, shader, isShadowRender);
}
