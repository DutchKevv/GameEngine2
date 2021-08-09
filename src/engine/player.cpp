#include "./model.h"
#include "./player.h"
#include "./context.h"
#include "./animation.h"
#include "./animator.h"

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

Player::Player(string const &path, unsigned int amount, bool gamma): Model(path, amount, gamma) {
}

void Player::init()
{
    //  std::cout << "init player \n";

    glfwSetCursorPosCallback(context->display->window, mouse_callback);

    Model::init();
}

void Player::update(float delta)
{
    //  std::cout << "render player \n";

    keyPressed = false;

    if (glfwGetKey(context->display->window, GLFW_KEY_LEFT) == GLFW_PRESS)
        this->processKeyboard(LEFT, delta);
    if (glfwGetKey(context->display->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        this->processKeyboard(RIGHT, delta);
    if (glfwGetKey(context->display->window, GLFW_KEY_UP) == GLFW_PRESS)
        this->processKeyboard(UP, delta);
    if (glfwGetKey(context->display->window, GLFW_KEY_DOWN) == GLFW_PRESS)
        this->processKeyboard(DOWN, delta);
    if (glfwGetKey(context->display->window, GLFW_KEY_W) == GLFW_PRESS)
        this->processKeyboard(W, delta);
    if (glfwGetKey(context->display->window, GLFW_KEY_S) == GLFW_PRESS)
        this->processKeyboard(S, delta);
    if (glfwGetKey(context->display->window, GLFW_KEY_A) == GLFW_PRESS)
        this->processKeyboard(A, delta);
    if (glfwGetKey(context->display->window, GLFW_KEY_D) == GLFW_PRESS)
        this->processKeyboard(D, delta);

    if (!keyPressed)
    {
        animator->StopAnimation(animation);

        for (unsigned int i = 0; i < meshes.size(); i++)
        {
            SetVertexBoneDataToDefault(meshes[i].vertices[0]);
        }
    }

    Model::update(delta);
}

void Player::renderScene(float delta, Shader *shader, bool isShadowRender)
{
    // std::cout << "render player \n";

    Model::renderScene(delta, shader, isShadowRender);
}

int Player::processKeyboard(Camera_Movement direction, float velocity)
{
    keyPressed = true;

    switch (direction)
    {
    case W:
        position.z += velocity * -5.0f;
        break;
    case S:
        position.z += velocity * 5.0f;
        break;
    case A:
        position.x += velocity * -5.0f;
        break;
    case D:
        position.x += velocity * 5.0f;
        break;
    default:
        break;
    }

    return 0;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    Engine *engine = context->engine;

    if (engine->firstMouse)
    {
        engine->lastMouseX = xpos;
        engine->lastMouseY = ypos;
        engine->firstMouse = false;
    }

    float xoffset = xpos - engine->lastMouseX;
    float yoffset = engine->lastMouseY - ypos; // reversed since y-coordinates go from bottom to top

    engine->lastMouseX = xpos;
    engine->lastMouseY = ypos;

    context->engine->children[context->engine->worldChild]->camera->ProcessMouseMovement(xoffset, yoffset);
}
