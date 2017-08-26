#include "Customs/FirstBossLifeBorderScript.hpp"

FirstBossLifeBorderScript::FirstBossLifeBorderScript(GameObject *owner) :
    Script(owner) {}

void FirstBossLifeBorderScript::Start() {

    CreateAnimations();

    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    position = GetOwner()->GetPosition();
    GetOwner()->SetZoomProportion(Vector(0,0));
    firstBossAttackCollider = new RectangleCollider(GetOwner(), Vector(0, 0),
                                                  GetOwner()->GetWidth(),
                                                  GetOwner()->GetHeight(), 0);

}
void FirstBossLifeBorderScript::CreateAnimations() {

    //Image Attacks
    //332 L por 9 A
    auto firstBossLifeBorderImage = new Image("assets/Barra_Life_Boss.png",0,0,
                                                                    996, 171);

    auto firstBossLifeBorderAnimation = new Animation(GetOwner(),
                                        firstBossLifeBorderImage );
    for (int column = 0; column < 19; column++) {
        for (int row = 0 ; row < 3 ; row++) {
            firstBossLifeBorderAnimation->AddFrame(new Frame(row * 332,
                                                       column * 9, 332, 9));
    }
  }


    //Animator
    auto firstBossLifeBorderAnimator = new Animator(GetOwner());
    firstBossLifeBorderAnimator->AddAnimation("firstBossLifeBorderAnimation",
                                                firstBossLifeBorderAnimation);
}


void FirstBossLifeBorderScript::ComponentUpdate() {

}

void FirstBossLifeBorderScript::FixedComponentUpdate() {
    animator->PlayAnimation("firstBossLifeBorderAnimation");
    position->m_x = 646;
    position->m_y = 10;
}
