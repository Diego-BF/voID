#include "Customs/SnowActivatorScript.hpp"
#include "Globals/EngineGlobals.hpp"
#include "Customs/CentralLightScript2.hpp"
#include "Customs/MapScript.hpp"

SnowActivatorScript::SnowActivatorScript(GameObject *owner) : Script(owner) {}
void SnowActivatorScript::Start() {

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

void SnowActivatorScript::CreateAnimations(){

    auto snowactivatorSprite = new Image("assets/snowactivator.png", 0, 0,832, 64);
    auto snowactivatorAnimation = new Animation(GetOwner(), snowactivatorSprite);
    for (int i = 0; i < 13; i++) {
        snowactivatorAnimation->AddFrame(new Frame(i * 64, 0, 64, 64));
    }

    auto snowactivatorAnimation2 = new Animation(GetOwner(), snowactivatorSprite);
    snowactivatorAnimation2->AddFrame(new Frame(12 * 64, 0, 64, 64));

    auto snowactivatorAnimator = new Animator(GetOwner());
    snowactivatorAnimation->SetFramesPerSecond(9);
    snowactivatorAnimator->AddAnimation("SNOW ACTIVATOR ANIMATION", snowactivatorAnimation);
    snowactivatorAnimator->AddAnimation("SNOW ACTIVATOR ANIMATION2", snowactivatorAnimation2);

}

void SnowActivatorScript::ComponentUpdate() {

    if (!animator->IsPlaying("SNOW ACTIVATOR ANIMATION") && activate==0 && runned==false) {
        animator->PlayAnimation("SNOW ACTIVATOR ANIMATION");
        activate=1;
        runned=true;
    }

    if (runned && !animator->IsPlaying("SNOW ACTIVATOR ANIMATION")) {
        animator->PlayAnimation("SNOW ACTIVATOR ANIMATION2");
    }
    if (runned) {
        auto script = (CentralLightScript2*)SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("CENTRAL LIGHT 2")->GetComponent("CentralLightScript2");
        script->Activate();
        auto map = (MapScript*)SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("Map")->GetComponent("MapScript");
        map->rightWalls[49].m_x=0;
        map->rightWalls[49].m_y=0;
        map->rightWalls[49].m_w=0;
        map->rightWalls[49].m_h=0;
        //map->rightWallsAmmount-=1;
        map->rightWallsOriginal[49].m_x=0;
        map->rightWallsOriginal[49].m_y=0;
        map->rightWallsOriginal[49].m_w=0;
        map->rightWallsOriginal[49].m_h=0;
    }

}

void SnowActivatorScript::FixedComponentUpdate() {

}
