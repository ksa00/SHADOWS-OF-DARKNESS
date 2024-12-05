#include "Camera2D.h"
#include "Engine/Debug.h"

const XMFLOAT2 CHAR_RENDER_SIZE = { 32.0f, 32.0f }; // Example size of each tile
const XMFLOAT2 WORLD_CHIP_SIZE = { 100.0f, 100.0f }; // Example number of tiles in the world grid
const XMFLOAT2 WORLD_SIZE = {
    CHAR_RENDER_SIZE.x * WORLD_CHIP_SIZE.x,
    CHAR_RENDER_SIZE.y * WORLD_CHIP_SIZE.y
};

Camera2D::Camera2D(GameObject* parent)
    : GameObject(parent, "Camera2D"), cameraPos_(0.0f, 0.0f), cameraOrigin_(0.0f, 0.0f),
    screenSize_(800.0f, 600.0f), worldSize_(WORLD_SIZE) { // Calculate world size here
}

Camera2D::~Camera2D() {
}

void Camera2D::Initialize() {
    // Initialize camera position
    cameraPos_ = XMFLOAT2(screenSize_.x / 2, screenSize_.y / 2);
    cameraOrigin_ = XMFLOAT2(cameraPos_.x - screenSize_.x / 2, cameraPos_.y - screenSize_.y / 2);
    Debug::Log("Camera2D initialized.");
}

void Camera2D::Update() {
    // Additional logic to update the camera's view if needed
    UpdateCamera();
    Debug::Log("Camera2D updated.");
}

void Camera2D::Draw() {
    // Camera does not need to draw anything
}

void Camera2D::Release() {
    // Release any resources if needed
}

void Camera2D::SetCameraPos(const XMFLOAT2& position) {
    cameraPos_ = position;
    cameraOrigin_ = XMFLOAT2(cameraPos_.x - screenSize_.x / 2, cameraPos_.y - screenSize_.y / 2);
}

XMFLOAT2 Camera2D::GetScreenPosFromWorldPos(const XMFLOAT2& position) const {
    return XMFLOAT2(position.x - cameraOrigin_.x, position.y - cameraOrigin_.y);
}

void Camera2D::UpdateCamera() {
    // Prevent the camera from going outside the world boundaries
    if (cameraOrigin_.x < 0.0f) {
        SetCameraPos(XMFLOAT2(screenSize_.x / 2.0f, cameraPos_.y));
    }
    if (cameraOrigin_.y < 0.0f) {
        SetCameraPos(XMFLOAT2(cameraPos_.x, screenSize_.y / 2.0f));
    }
    if (cameraOrigin_.x + screenSize_.x > worldSize_.x) {
        SetCameraPos(XMFLOAT2(worldSize_.x - screenSize_.x / 2, cameraPos_.y));
    }
    if (cameraOrigin_.y + screenSize_.y > worldSize_.y) {
        SetCameraPos(XMFLOAT2(cameraPos_.x, worldSize_.y - screenSize_.y / 2.0f));
    }
}
