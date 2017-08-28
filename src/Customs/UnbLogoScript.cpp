#include "Customs/UnbLogoScript.hpp"
#include "Globals/EngineGlobals.hpp"

UnbLogoScript::UnbLogoScript(GameObject *owner) : Script(owner) {}
void UnbLogoScript::Start() {

    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    gamecontroller = input->GetGameController(0);
    GetOwner()->SetZoomProportion(Vector(0,0));

}

void UnbLogoScript::CreateAnimations(){

    auto unb_LogoSprite = new Image("assets/introunb.png", 0, 0, 5115, 512);
    auto unbAnimation = new Animation(GetOwner(), unb_LogoSprite);
    for (int i = 0; i < 15; i++) {
        unbAnimation->AddFrame(new Frame(i * 341, 0, 341, 256));
    }
    for (int i = 0; i < 15; i++) {
        unbAnimation->AddFrame(new Frame(i * 341, 256, 341, 256));
    }

    auto unbAnimator = new Animator(GetOwner());
    unbAnimation->SetFramesPerSecond(9);
    unbAnimator->AddAnimation("UNB ANIMATION", unbAnimation);
}

void UnbLogoScript::ComponentUpdate() {
    if (gamecontroller) {
        if (gamecontroller->GetButtonDown(GC_INPUT_X)) {
            SceneManager::GetInstance()->SetCurrentScene("Main");
        }
    }
    if (input->GetKeyPressed(INPUT_RETURN)) {
        SceneManager::GetInstance()->SetCurrentScene("Main");
    }

}

void UnbLogoScript::FixedComponentUpdate() {

    time.Update(1);

    animator->PlayAnimation("UNB ANIMATION");

    if (time.GetTime()>=100) {
        animator->StopAllAnimations();
    }

/*
if(!animator->IsPlaying("UNB ANIMATION")){
printf("%f\n",time.GetTime());
time.Restart();
animator->PlayAnimation("UNB ANIMATION");
}time.Update(1);


if(time.GetTime()>=90){
animator->PlayAnimation("SDL ANIMATION");
}
if(time.GetTime()>=160){
animator->StopAllAnimations();
}

if(animator->IsPlaying("UNB ANIMATION"))
time.Update(1);
*/
}
