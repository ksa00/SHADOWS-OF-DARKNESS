#ifndef STAGE_H
#define STAGE_H

#include "Engine/GameObject.h"
#include <vector>
#include <string>

class Stage : public GameObject {
public:
    Stage(GameObject* parent);
    ~Stage();

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

private:
    std::vector<std::vector<int>> mapData_;
    void LoadStageData(const std::string& fileName);
};

#endif // STAGE_H
