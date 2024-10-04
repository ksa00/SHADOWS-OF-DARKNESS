#include "Background.h"

Background::Background(GameObject* parent)
	:screenWidth(800)
{

}

Background::~Background()
{
	for (auto& layer : layers) {
		if (layer.hBackGround) {
			delete[] layer.hBackGround;
		}
	}
}

void Background::Initialize()
{
}

void Background::Update()
{
	float playerMovementX = 0.0f;

	if (GetAsyncKeyState(VK_LEFT)) {
		playerMovementX = -1.0f; // Move left
	}
	else if (GetAsyncKeyState(VK_RIGHT)) {
		playerMovementX = 1.0f; // Move right
	}
	for (auto& layer : layers) {
		layer.position += playerMovementX*layer.scrollSpeed;

		// Reset position if it goes off-screen
		if (layer.position > screenWidth) {
			layer.position -= screenWidth;
		}
		else if (layer.position < -screenWidth) {
			layer.position += screenWidth;
		}
	}
}

void Background::Draw()
{
}

void Background::Release()
{
}

void Background::AddLayer(int* hImg, float scrollspeed)
{
	layers.push_back({ hImg,scrollspeed,0.0f });
}
