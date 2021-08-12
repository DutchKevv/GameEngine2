#include <iostream>
#include "./town.h"
#include "../engine/engine.h"
#include "./scenes/world.h"

void Town::init()
{
    
    RenderObject::init();
    
	townModel = new Model("game/models/castle/tower/medieval_tower_2.obj", 1);
    townModel->position = position;
    this->addChild(townModel, this->scene);

    Npc *npc = new Npc("game/models/player/vampire/vampire.dae", 100);
	npc->setAnimation("game/models/player/vampire/vampire.dae");
	npc->setTown(this);
    this->addChild(npc, this->scene);

}

void Town::renderScene(float delta, Shader *shader, bool isShadowRender)
{
	RenderObject::renderScene(delta, shader, isShadowRender);
}