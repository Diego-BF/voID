#include "Customs/ThunderScript.hpp"
#include "Globals/EngineGlobals.hpp"

ThunderScript::ThunderScript(GameObject *owner) : Script(owner) {}
void ThunderScript::Start() {

    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    GetOwner()->SetZoomProportion(Vector(0,0));

}

void ThunderScript::CreateAnimations(){

    auto thunderImage = new Image("assets/Sprites/dashes.png",0,0,2952, 815);

    auto thunderBlueAnimation= new Animation(GetOwner(),thunderImage );
    for (int i = 0; i < 6; i++) {
        thunderBlueAnimation->AddFrame(new Frame(i * 100,135, 100, 267));
    }

    auto thunderYellowAnimation= new Animation(GetOwner(),thunderImage );
    for (int i = 0; i < 5; i++) {
        thunderYellowAnimation->AddFrame(new Frame(555 + (i * 59),135, 59, 267));
    }

    // animator
    auto thunderAnimator = new Animator(GetOwner());

    thunderAnimator->AddAnimation("thunderBlueAnimation", thunderBlueAnimation);
    thunderAnimator->AddAnimation("thunderYellowAnimation", thunderYellowAnimation);

}

void ThunderScript::ComponentUpdate() {

    if (input->GetKeyDown(INPUT_1)) {
        animator->PlayAnimation("thunderBlueAnimation");
    }

    if (input->GetKeyDown(INPUT_2)) {
        animator->PlayAnimation("thunderYellowAnimation");
    } else {
        //animator->StopAllAnimations();
    }

}

void ThunderScript::FixedComponentUpdate() {


    //position->m_x=0;
    //position->m_y=0;


}
