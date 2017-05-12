#include "Customs/NakedManScript.h"

NakedManScript::NakedManScript(GameObject *owner) : Script(owner) {}

void NakedManScript::Start() {
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");
  input = InputSystem::GetInstance();
}

void NakedManScript::ComponentUpdate() {
  // movement animation and input detection
  movements = movements & 0x00;
  if (input->GetKeyPressed(INPUT_W)) {
    movements = movements | 0x08;
    animator->PlayAnimation("Walk Up");
  } else if (input->GetKeyPressed(INPUT_S)) {
    movements = movements | 0x04;
    animator->PlayAnimation("Walk Down");
  } else if (input->GetKeyPressed(INPUT_A)) {
    movements = movements | 0x02;
    animator->GetAnimation("Walk Side")->SetFlip(true, false);
    animator->PlayAnimation("Walk Side");
  } else if (input->GetKeyPressed(INPUT_D)) {
    movements = movements | 0x01;
    animator->GetAnimation("Walk Side")->SetFlip(false, false);
    animator->PlayAnimation("Walk Side");
  } else {
    animator->StopAllAnimations();
  }

  if (InputSystem::GetInstance()->GetKeyUp(INPUT_ESCAPE)) {
    auto var = (UIText *)SceneManager::GetInstance()
                   ->GetScene("Main")
                   ->GetGameObject("Play")
                   ->GetComponent("UIText");
    var->SetText("Continue");
    SceneManager::GetInstance()->SetCurrentScene("Main");
  }
}

void NakedManScript::FixedComponentUpdate() {
  if (0x08 & movements)
    position->m_y -= walkSpeed;
  else if (0x04 & movements)
    position->m_y += walkSpeed;
  else if (0x02 & movements)
    position->m_x -= walkSpeed;
  else if (0x01 & movements)
    position->m_x += walkSpeed;

  if (position->m_x + 64 >= deadzone_x)
    position->m_x = deadzone_x - 64;
  if (position->m_x <= deadzone_x - 200)
    position->m_x = deadzone_x - 200;
  if (position->m_y + 64 >= deadzone_y)
    position->m_y = deadzone_y - 64;
  if (position->m_y <= deadzone_y - 200)
    position->m_y = deadzone_y - 200;
}
