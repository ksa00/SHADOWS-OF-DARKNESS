
#include "Engine/GameObject.h"
#include <DirectXMath.h>

using namespace DirectX;

class Camera2D : public GameObject {
public:
    Camera2D(GameObject* parent);
    ~Camera2D();

    void SetCameraPos(const XMFLOAT2& position);
    XMFLOAT2 GetScreenPosFromWorldPos(const XMFLOAT2& position) const;
    void UpdateCamera();

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

private:
    XMFLOAT2 cameraPos_;       // Center position of the camera in world coordinates
    XMFLOAT2 cameraOrigin_;    // Origin position of the camera in world coordinates
    XMFLOAT2 screenSize_;      // Size of the screen
    XMFLOAT2 worldSize_;       // Size of the world
};
