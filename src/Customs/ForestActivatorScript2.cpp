#include "Customs/ForestActivatorScript2.hpp"
#include "Globals/EngineGlobals.hpp"
#include "Customs/CentralLightScript1.hpp"
ForestActivatorScript2::ForestActivatorScript2(GameObject *owner) : Script(owner) {}
void ForestActivatorScript2::Start() {

    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    gamecontroller = input->GetGameController(0);
    GetOwner()->SetZoomProportion(Vector(0,0));
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
    if (map) {
        GetOwner()->SetZoomProportion(Vector(map->originalWidth/GetOwner()->originalWidth,map->originalHeight/GetOwner()->originalHeight));
    }
}
void ForestActivatorScript2::CreateAnimations(){

    auto forestactivatorSprite = new Image("assets/forestactivator.png", 0, 0,832, 64);
    auto forestactivatorAnimation = new Animation(GetOwner(), forestactivatorSprite);
    for (int i = 0; i < 13; i++) {
        forestactivatorAnimation->AddFrame(new Frame(i * 64, 0, 64, 64));
    }

    auto forestactivatorAnimation2 = new Animation(GetOwner(), forestactivatorSprite);
    forestactivatorAnimation2->AddFrame(new Frame(12 * 64, 0, 64, 64));

    auto forestactivatorAnimator = new Animator(GetOwner());
    forestactivatorAnimation->SetFramesPerSecond(9);
    //forestactivatorAnimation2->SetFramesPerSecond(1);
    forestactivatorAnimator->AddAnimation("FOREST ACTIVATOR ANIMATION", forestactivatorAnimation);
    forestactivatorAnimator->AddAnimation("FOREST ACTIVATOR ANIMATION2", forestactivatorAnimation2);


}


void ForestActivatorScript2::ComponentUpdate() {

    if (!animator->IsPlaying("FOREST ACTIVATOR ANIMATION") && activate==0 && runned==false) {
        animator->PlayAnimation("FOREST ACTIVATOR ANIMATION");
        activate=1;
        runned=true;
    }

    if (runned && !animator->IsPlaying("FOREST ACTIVATOR ANIMATION")) {
        animator->PlayAnimation("FOREST ACTIVATOR ANIMATION2");
    }

    if (runned) {
        auto script = (CentralLightScript1*)SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("CENTRAL LIGHT 1")->GetComponent("CentralLightScript1");
        script->Activate();
    }
}
void ForestActivatorScript2::FixedComponentUpdate() {

}
