#pragma once
#include "Engine/GameObject.h"
#include "Attributes.h"
#include "AttributeFactory.h"
#include <vector>

// AttributeSelectionScreen class
class AttributeSelectionScreen : public GameObject {
public:
    AttributeSelectionScreen(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

private:
    std::vector<Attribute*> availableAttributes_;

    void ShowAttributeSelection();
    void HandleAttributeClick(int x, int y);
};
