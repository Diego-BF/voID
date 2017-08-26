#include "Engine/SceneManager.hpp"
#include "Engine/Timer.hpp"

#include "Customs/FirstBossController.hpp"
#include "Components/UIText.hpp"
#include "Customs/PlayerScript.hpp"

FirstBossController *FirstBossController::m_instance = nullptr;

FirstBossController *FirstBossController::GetInstance() { //Singleton class
    if (!m_instance)
        m_instance = new FirstBossController();

    return m_instance;
}

FirstBossController::FirstBossController() {} //Constructor void

void FirstBossController::StartBossFight() {
  //PositAllTentacles();
  //PositBoss();
  //->boss resurge animation
  //wait time
  //set player movement free
}
void FirstBossController::EndBossFight() {
    //DeactivatePlayer();
    DeactivateTentacles();
    DeactivateBoss();
    DeactivateInsideBossFx();
}

/*Add*/
void FirstBossController::AddPlayer(GameObject *player) {
    m_player = player;
}
void FirstBossController::AddBoss(GameObject *boss) {
    m_boss = boss;
}
void FirstBossController::AddInsideBossFx(GameObject *bossInsideFx) {
    m_bossInsideFx = bossInsideFx;
}
void FirstBossController::AddTentacle(GameObject *tentacle) {
    m_tentacles.push_back(tentacle);
}
void FirstBossController::AddLifeBar(GameObject *lifeBar) {
     m_lifeBars.push_back(lifeBar);
 }
void FirstBossController::AddCreditsAnimation(GameObject *creditsAnimation) {
    m_creditsAnimation = creditsAnimation;
}
void FirstBossController::AddMap(GameObject *map) {
    m_map = map;
}

/*Posit*/
void FirstBossController::PositPlayer(Vector newPosition) {
    m_player->SetPosition(newPosition);
}
void FirstBossController::PositMap(Vector newPosition) {
    m_map->SetPosition(newPosition);
}
void FirstBossController::PositBoss() {
    m_boss->SetPosition(Vector(m_wPos, m_hPos));
}
void FirstBossController::PositAllTentacles() {
    for (auto tentacle : m_tentacles) {
        Vector *position = m_player->GetPosition();
        tentacle->SetPosition(Vector(-500, -500));
  }
}

void FirstBossController::PositTentacle(int index) {
    Vector *position = m_player->GetPosition();
    m_tentacles[index]->SetPosition(Vector(position->m_x ,position->m_y -120));
}

/*Active*/
void FirstBossController::ActivatePlayer() {
    m_player->ClearCollisions();
    m_player->active = true;
}

void FirstBossController::ActivateBoss() {
    m_boss->ClearCollisions();
    m_boss->active = true;

}

void FirstBossController::ActivateInsideBossFx() {
    //m_bossInsideFx->ClearCollisions();
    m_bossInsideFx->active = true;

}

void FirstBossController::ActivateTentacles() {
   for (auto tentacle : m_tentacles) {
      tentacle->ClearCollisions();
      tentacle->active = true;
   }
}

void FirstBossController::ActivateLifeBars() {
   for (auto lifeBar : m_lifeBars) {
       lifeBar->active = true;
   }
}

void FirstBossController::ActivateTentacle(int indexTentacle) {
    m_tentacles[indexTentacle]->active = true;
}

void FirstBossController::ActivateCreditsAnimation() {
    m_creditsAnimation->active = true;

}


/*Deactive*/
void FirstBossController::DeactivatePlayer() {
    m_player->active = false;
}

void FirstBossController::DeactivateBoss() {
    m_boss->active = false;
}

void FirstBossController::DeactivateInsideBossFx() {
    m_bossInsideFx->active = false;
}

void FirstBossController::DeactivateCreditsAnimation() {
    m_creditsAnimation->active = false;
}

void FirstBossController::DeactivateTentacles() {
    for (auto tentacle : m_tentacles) {
        tentacle->active = false;
    }
}

void FirstBossController::DeactivateLifeBars() {
    for (auto lifeBar : m_lifeBars) {
        lifeBar->active = false;
    }
}

void FirstBossController::DeactivateTentacle(int tentacleIndex) {
    m_tentacles[tentacleIndex]->active = false;
}

std::pair <int, int> FirstBossController::GetRandomPosition() {
  srand(time(NULL));

  randomPosition.first = rand();
  randomPosition.second = rand();

  return randomPosition;
}

void FirstBossController::FirstAttackSurge() {
    cout << "FirstAttack" << endl;
    if (actualTentacle == 4) {
      actualTentacle = 1;
    }

    m_tentacles[actualTentacle]->ClearCollisions();
    //m_tentacles[actualTentacle]->active = true;
    ActivateTentacle(actualTentacle);
    PositTentacle(actualTentacle);

    auto firstBossAttackScript = (FirstBossAttackScript*)
                                m_tentacles[actualTentacle]->
                                GetComponent("FirstBossAttackScript");
    //Perform attack
    firstBossAttackScript->attack = true;
    //Shake camera
    firstBossAttackScript->shake = true;
    actualTentacle++;
}

void FirstBossController::FirstAttackGone() {
    for (auto tentacle : m_tentacles) {
        auto firstBossAttackScript = (FirstBossAttackScript*)tentacle->
                                  GetComponent("FirstBossAttackScript");
        //Perform gone animation
        firstBossAttackScript->m_goneAnimation = true;
  }
}

void FirstBossController::SecondAttack() {

}

/*

GameObject *FirstBossController::GetRandomTentacle() {
  srand(time(NULL));
  int tentacleIndex = rand() % 3;
  return m_tentacles[tentacleIndex];
}

*/
