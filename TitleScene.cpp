#include "TitleScene.h"
#include"Player.h"
#include"Camera2D.h"
#include"Stage.h"
#include"Enemy.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

TitleScene::TitleScene(GameObject* parent)
    : GameObject(parent, "TitleScene"), isAttributeSelectionNeeded_(false) // Set to true initially to show attribute selection
{
}

void TitleScene::Initialize() {
    // Initialize other game objects if needed
   // Instantiate<Camera2D>(this);
    Instantiate<Player>(this);
	Instantiate<Enemy>(this);
	//Instantiate<Stage>(this);
}

void TitleScene::Update() {
    if (isAttributeSelectionNeeded_) {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_ATTRIBUTE_SELECT);
        isAttributeSelectionNeeded_ = false;
    }

    // Update other game objects if needed
}

void TitleScene::Draw() {
    // Draw other game objects if needed
}

void TitleScene::Release() {
    // Release resources if needed
}
