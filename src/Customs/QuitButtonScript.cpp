#include "Customs/QuitButtonScript.hpp"

QuitButtonScript::QuitButtonScript(GameObject *owner) : Script(owner) {}

void QuitButtonScript::Start() {
    m_uiButton = (UIButton *)GetOwner()->GetComponent("UIButton");
}

void QuitButtonScript::ComponentUpdate() {
    auto textButton = (UIText *)GetOwner()->GetComponent("UIText");
    auto soundButton = (UISound *)GetOwner()->GetComponent("UISound");
  
  if (m_uiButton->IsClicked()) {
    soundButton->Play(0, -1);
    SDLSystem::GetInstance()->SetRunning(false);
  }

  if (m_uiButton->IsOver()) {
    textButton->SetColor(160,160,160, 255);
  } else {
  	textButton->SetColor(255,255,255, 255);
  }
}
