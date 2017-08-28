#include "Customs/PlayerAttackScript.hpp"
#include "Globals/EngineGlobals.hpp"
#include "Customs/NakedManScript.hpp"

PlayerAttackScript::PlayerAttackScript(GameObject *owner) : Script(owner) {}
void PlayerAttackScript::Start() {

    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
    if (map) {
        GetOwner()->SetZoomProportion(Vector(map->originalWidth/GetOwner()->originalWidth,map->originalHeight/GetOwner()->originalHeight));
    }
    player =  SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("NakedMan");

    playerCollider = new RectangleCollider(GetOwner(), Vector(0, 0), GetOwner()->GetWidth(), GetOwner()->GetHeight(), 0);




}
void PlayerAttackScript::CreateAnimations(){

    // Renderer
    auto bulletImage = new Image("assets/Sprites/green_bullet.png",0,0,124, 124);
    auto bulletRenderer = new Renderer(GetOwner(), bulletImage);

}


void PlayerAttackScript::ComponentUpdate() {


    player =  SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("NakedMan");
    auto playerScript = (NakedManScript*)player->GetComponent("NakedManScript");




    if (player && playerScript) {

        //Get player Position
        playerPosition.m_x  =  player->GetPosition()->m_x +  player->GetWidth()/2;
        playerPosition.m_y  =  player->GetPosition()->m_y +  player->GetHeight()/2;

        //Get Mouse Position
        mousePosition.m_x = input->GetMousePosition().first;
        mousePosition.m_y = input->GetMousePosition().second;


        if (shoot && !playerScript->gameControllerActivated) {
            GetOwner()->active = true;
            angle = playerPosition.GetAngleRadians(mousePosition);
            bulletVelocity.m_x = bulletSpeed * cos(angle);
            bulletVelocity.m_y = bulletSpeed * sin(angle);
            position->m_x = playerPosition.m_x;
            position->m_y = playerPosition.m_y;
            auto soundButton = (UISound *)GetOwner()->GetComponent("UISound");
            soundButton->Play(0, -1);
            shoot = false;
        }
        if (shoot && playerScript->gameControllerActivated) {
            GetOwner()->active = true;
            angle = playerScript->gameControllerAngle*3.14/180;
            bulletVelocity.m_x = bulletSpeed * cos(angle);
            bulletVelocity.m_y = bulletSpeed * sin(angle);
            position->m_x = playerPosition.m_x;
            position->m_y = playerPosition.m_y;
            shoot = false;
        }
    }
}

void PlayerAttackScript::FixedComponentUpdate() {
    GameCollisionCheck();

    bulletSpeed = bulletSpeed;
    position->m_y += bulletVelocity.m_y;
    position->m_x += bulletVelocity.m_x;

}

void PlayerAttackScript::GameCollisionCheck() {
    for (auto obj : GetOwner()->GetCollisions()) {
        if (obj->GetTag() == "Bullet") {
            //cout << "Bullet Colider" << endl;
            GetOwner()->ClearCollisions();
        } else if (obj->GetTag() == "FirstBoss") {
            cout << "Boss Colider" << endl;
            auto firstBossLifeScript = (FirstBossLifeScript*)SceneManager::GetInstance()
               ->GetCurrentScene()
               ->GetGameObject("FirstBossLife")
               ->GetComponent("FirstBossLifeScript");
            //cout << "flag" << endl;
            firstBossLifeScript->hit = true;
            GetOwner()->active = false;
            GetOwner()->ClearCollisions();

        } else if(obj->GetTag() == "FirstBossAtack") {
            cout << "Boss Atack Colider" << endl;
            GetOwner()->ClearCollisions();
        }
    }
}

void PlayerAttackScript::SetShoot(bool shoot){
    this->shoot = shoot;
}
