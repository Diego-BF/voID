#include "Customs/PlayerScript.hpp"
#include "Components/UIText.hpp"

PlayerScript::PlayerScript(GameObject *owner) : Script(owner){
    GetOwner()->GetPosition()->m_x=0;
    GetOwner()->GetPosition()->m_y=0;
};

void PlayerScript::ComponentUpdate() {
    HandleInput();
}

void PlayerScript::HandleInput() {
    m_movement.m_x = m_movement.m_y = 0;

    if (InputSystem::GetInstance()->GetKeyPressed(INPUT_D)){
        m_movement.m_x += 1;
    }
    if (InputSystem::GetInstance()->GetKeyPressed(INPUT_A)) {
        m_movement.m_x -= 1;
    }
    if (InputSystem::GetInstance()->GetKeyPressed(INPUT_S)) {
        m_movement.m_y += 1;
    }
    if (InputSystem::GetInstance()->GetKeyPressed(INPUT_W)){
        m_movement.m_y -= 1;
    }

  m_movement = m_movement.GetNormalized();

    if (InputSystem::GetInstance()->GetKeyUp(INPUT_ESCAPE)) {
        auto var = (UIText *)SceneManager::GetInstance()
                            ->GetScene("Main")
                            ->GetGameObject("Play")
                            ->GetComponent("UIText");
        var->SetText("Continue");
        SceneManager::GetInstance()->SetCurrentScene("Main");
    }
}

void PlayerScript::FixedComponentUpdate() {
    GetOwner()->GetPosition()->m_x += m_movement.m_x * m_speed;
    GetOwner()->GetPosition()->m_y += m_movement.m_y * m_speed;
}
