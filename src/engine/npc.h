#pragma once

#include <string>
#include "./model.h"
#include "./shader.h"
#include "../game/town.h"


class Npc : public Model
{
public:
    Town *town;
    
    Npc(std::string const &path, unsigned int amount = 1, bool gamma = false);

    void init();
    void update(float update);
    void setTown(Town *town);

    void renderScene(float delta, Shader *shader, bool isShadowRender);
};
