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

    danceAnimation = new Animation("game/models/player/vampire/vampire.dae", playerModel);
    animator = new Animator(danceAnimation);
    animator->PlayAnimation(danceAnimation);

    this->addChild(playerModel, this->scene);

    RenderObject::init();
}

void Player::update(float delta)
{
std::cout << "udpate floor \n";
    animator->UpdateAnimation(delta);

    RenderObject::update(delta);
}

void Player::renderScene(float delta, Shader *shader, bool isShadowRender)
{
    auto transforms = animator->GetPoseTransforms();
    for (int i = 0; i < transforms.size(); ++i)
    {
        shader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
    }

    // std::cout << "render floor \n";
    playerModel->renderScene(delta, shader, isShadowRender);
}
