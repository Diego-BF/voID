#ifndef __NAKED_MAN_SCRIPT__
#define __NAKED_MAN_SCRIPT__

#include "Engine/InputSystem.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/Timer.hpp"
#include "Engine/CameraSystem.hpp"
#include "Engine/GameController.hpp"

#include "Components/Animator.hpp"
#include "Components/Script.hpp"
#include "Components/UIText.hpp"
#include "Components/RectangleCollider.hpp"
#include "Customs/PlayerAttackScript.hpp"
#include "Customs/HitScript.hpp"

class NakedManScript : public Script {
public:

    NakedManScript(GameObject *owner);
    std::string GetComponentName() override {
        return "NakedManScript";
    };
    void FixedComponentUpdate() override;
    void Start() override;
    char GetMovement() {
        return movements;
    };

    bool lockplayerMovements = false;
    int bulletNumber = 10;
    bool gameControllerActivated = false;
    float gameControllerAngle = 0;
    bool activated = true;
    int life = 100;

protected:

    void ComponentUpdate() override;

private:

    void SetDirection();
    void KeyBoardUpdate();
    void GameControllerUpdate();
    void CreateAnimations();
    void WallCollisionResolution();
    void GameCollisionCheck();
    void StartFirstBoss();

    //Player Movements
    void Movements();

    void Animations();

    void Shoot();
    void ReloadGun();
    void PlayerLife();

    void MovementsSounds();

    bool zoom = true;

    bool bossFight = false;
    bool walking = false;

    int bulletController = 0;
    int dashController = 0;

    InputSystem *input = nullptr;
    GameController *game_controller = nullptr;
    Animator *animator = nullptr;
    Vector *position = nullptr;
    float walkSpeed = 15;
    float fixedWalkSpeed = 15;
    int movements = 0; // 1=UP, 2=DOWN,3=LEFT,4=RIGHT,5=UP LEFT.6=UP RIGHT,7=DOWN LEFT,8=DOWN RIGHT
    int deadzoneX = EngineGlobals::screen_width / 2;
    int deadzoneY = EngineGlobals::screen_height / 2;
    int lastDirection = 1;
    RectangleCollider *nakedManCollider = nullptr;

    int m_hitFrames = 0;
    bool m_hit = false;

    Timer timerReload;
    Timer lifeRecover;
    Timer timerHit;

    bool cameraLock = true;
    bool isMovingLooking = true;

    bool endBossFight = false;
    static bool isZooming;
    std::pair<int, int> mousePosition;
};

#endif
