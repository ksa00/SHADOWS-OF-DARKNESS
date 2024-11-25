#include "AttributeSelectionScreen.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"

AttributeSelectionScreen::AttributeSelectionScreen(GameObject* parent)
    : GameObject(parent, "AttributeSelectionScreen")
{
}

void AttributeSelectionScreen::Initialize() {
    availableAttributes_.push_back(AttributeFactory::CreateAttribute(Attribute::FIRE));
    availableAttributes_.push_back(AttributeFactory::CreateAttribute(Attribute::WATER));
    availableAttributes_.push_back(AttributeFactory::CreateAttribute(Attribute::WIND));
    availableAttributes_.push_back(AttributeFactory::CreateAttribute(Attribute::EARTH));
    availableAttributes_.push_back(AttributeFactory::CreateAttribute(Attribute::ELECTRIC));
    availableAttributes_.push_back(AttributeFactory::CreateAttribute(Attribute::ICE));
    availableAttributes_.push_back(AttributeFactory::CreateAttribute(Attribute::DARK));

    ShowAttributeSelection();
}

void AttributeSelectionScreen::Update() {
    if (Input::IsMouseButtonDown(0)) { // Assuming 0 is the left mouse button
        int mouseX = static_cast<int>(Input::GetMousePosition().x);
        int mouseY = static_cast<int>(Input::GetMousePosition().y);
        HandleAttributeClick(mouseX, mouseY);
    }
}

void AttributeSelectionScreen::Draw() {
    const float startX = 100.0f;
    const float startY = 100.0f;
    const float gapX = 150.0f;

    for (size_t i = 0; i < availableAttributes_.size(); ++i) {
        float x = startX + i * gapX;
        float y = startY;
        Transform transform;
        transform.position_.x = x;
        transform.position_.y = y;
        Image::SetTransform(availableAttributes_[i]->GetImageHandle(), transform);
        Image::Draw(availableAttributes_[i]->GetImageHandle());
    }
}

void AttributeSelectionScreen::Release() {
    for (auto attr : availableAttributes_) {
        delete attr;
    }
}

void AttributeSelectionScreen::ShowAttributeSelection() {
    // The actual drawing is handled in the Draw method
}

void AttributeSelectionScreen::HandleAttributeClick(int x, int y) {
    const float startX = 100.0f;
    const float startY = 100.0f;
    const float gapX = 150.0f;
    const float imageSize = 64.0f; // Assuming each attribute image is 64x64 pixels

    for (size_t i = 0; i < availableAttributes_.size(); ++i) {
        float imgX = startX + i * gapX;
        float imgY = startY;

        if (x >= imgX && x <= imgX + imageSize && y >= imgY && y <= imgY + imageSize) {
            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
            pSceneManager->OnAttributeChosen(static_cast<Attribute::Type>(i));
            pSceneManager->ChangeScene(SCENE_ID_PLAY);
            break;
        }
    }
}
