#include "Customs/LightScript.hpp"
#include "Globals/EngineGlobals.hpp"

LightScript::LightScript(GameObject *owner) : Script(owner) {}
void LightScript::Start() {

    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    //Not affected by zoom
    GetOwner()->SetZoomProportion(Vector(0,0));

}
void LightScript::CreateAnimations(){

    auto lightImage = new Image("assets/luz.png",0,0,682, 512);

    auto  lightAnimation= new Animation(GetOwner(),lightImage );
    lightAnimation->AddFrame(new Frame(0,0, 682, 512));

     // animator
    auto lightAnimator = new Animator(GetOwner());
    lightAnimator->AddAnimation("lightAnimation", lightAnimation);



}


void LightScript::ComponentUpdate() {
    player = SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("NakedMan");
    if (player) {
        if (play==1) {
            animator->PlayAnimation("lightAnimation");
        }

        if (input->GetKeyDown(INPUT_Y) && play==0) {
            play=1;
        }

        else if (input->GetKeyDown(INPUT_Y) && play==1) {
            play=0;
        }

    }
}

void LightScript::FixedComponentUpdate() {
    if (player) {
        position->m_x  =  player->GetPosition()->m_x -  GetOwner()->GetWidth()/2 + 40;
        position->m_y  =  player->GetPosition()->m_y -  GetOwner()->GetHeight()/2 + 40;
    }
}
