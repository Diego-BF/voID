#include "Customs/ControleLogoScript.hpp"
#include "Globals/EngineGlobals.hpp"

#include <stdio.h>

ControleLogoScript::ControleLogoScript(GameObject *owner) : Script(owner) {}
void ControleLogoScript::Start() {

    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    GetOwner()->SetZoomProportion(Vector(0,0));

}
void ControleLogoScript::CreateAnimations(){

    auto controle_LogoSprite = new Image("assets/introcontrole.png", 0, 0, 5115, 512);
    auto controleAnimation = new Animation(GetOwner(), controle_LogoSprite);
    for (int i = 0; i < 15; i++) {
        controleAnimation->AddFrame(new Frame(i * 341, 0, 341, 256));
    }
    for (int i = 0; i < 15; i++) {
        controleAnimation->AddFrame(new Frame(i * 341, 256, 341, 256));
    }

    auto controleAnimator = new Animator(GetOwner());
    controleAnimation->SetFramesPerSecond(9);
    controleAnimator->AddAnimation("CONTROLE ANIMATION", controleAnimation);

}


void ControleLogoScript::ComponentUpdate() {


}

void ControleLogoScript::FixedComponentUpdate() {

    time.Update(1);
    if (time.GetTime()>=390) {
        animator->PlayAnimation("CONTROLE ANIMATION");
    }
    if (time.GetTime()>=490) {
        animator->StopAllAnimations();
    }

    if (time.GetTime()>=530) {
        SceneManager::GetInstance()->SetCurrentScene("Main");
    }


}
