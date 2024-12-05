#include "Stage.h"
#include "Engine/CsvReader.h"
#include "Engine/Image.h"
#include "Engine/Debug.h"

Stage::Stage(GameObject* parent) : GameObject(parent, "Stage")
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
    // Load stage data
    LoadStageData("stage1.csv");
}

void Stage::Update()
{
    // Update logic for the stage
}

void Stage::Draw()
{
    // Dimensions for each tile
    const int tileWidth = 32;
    const int tileHeight = 32;

    // Iterate through mapData_ to render each tile
    for (int y = 0; y < mapData_.size(); ++y) {
        for (int x = 0; x < mapData_[y].size(); ++x) {
            int tileId = mapData_[y][x];
            if (tileId != 255) {
                // Calculate tile position
                float posX = static_cast<float>(x * tileWidth);
                float posY = static_cast<float>(y * tileHeight);

                // Convert position to NDC
                float ndcX, ndcY;
                Transform transform;
                transform.position_ = { posX, posY, 0.0f };
                Image::ConvertToNDC(transform, ndcX, ndcY);

                // Load tile image based on tileId using switch case
                int tileImageHandle = -1;
                switch (tileId) {
                case 18:
                    tileImageHandle = Image::Load("path/to/tile_18.png");
                    break;
                case 19:
                    tileImageHandle = Image::Load("path/to/tile_19.png");
                    break;
                case 34:
                    tileImageHandle = Image::Load("path/to/tile_34.png");
                    break;
                case 35:
                    tileImageHandle = Image::Load("path/to/tile_35.png");
                    break;
                    // Add more cases as needed
                default:
                    Debug::Log("Unknown tile ID: " + std::to_string(tileId));
                    break;
                }

                // Draw the tile if a valid image handle was loaded
                if (tileImageHandle != -1) {
                    transform.position_ = { ndcX, ndcY, 0.0f }; // Update transform to NDC
                    Image::SetTransform(tileImageHandle, transform);
                    Image::Draw(tileImageHandle);
                    Image::Release(tileImageHandle); // Release image handle after drawing
                }
            }
        }
    }
}

void Stage::Release()
{
    // Release stage resources
}

void Stage::LoadStageData(const std::string& fileName)
{
    CsvReader csvReader;
    if (csvReader.Load(fileName)) {
        int width = csvReader.GetWidth();
        int height = csvReader.GetHeight();

        mapData_.resize(height);
        for (int y = 0; y < height; ++y) {
            mapData_[y].resize(width);
            for (int x = 0; x < width; ++x) {
                mapData_[y][x] = csvReader.GetValue(x, y);
            }
        }
        Debug::Log("Stage data loaded successfully from " + fileName);
    }
    else {
        Debug::Log("Failed to load stage data from " + fileName);
    }
}
