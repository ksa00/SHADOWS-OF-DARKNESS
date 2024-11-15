#pragma once
#include <string>
#include <vector>

struct PlayerData {
    std::string name;
    int score;
    int level;
    int health;
    int attributeImageHandle;
    int activePowerUpImageHandle;

    PlayerData(const std::string& name = "", int score = 0, int level = 1, int health = 100, int attributeImageHandle = 0, int activePowerUpImageHandle = 0)
        : name(name), score(score), level(level), health(health), attributeImageHandle(attributeImageHandle), activePowerUpImageHandle(activePowerUpImageHandle) {}
};

struct Checkpoint {
    int x;
    int y;

    Checkpoint(int x = 0, int y = 0) : x(x), y(y) {}
};

struct MapData {
    std::string mapName;
    std::vector<Checkpoint> checkpoints;

    MapData(const std::string& mapName = "") : mapName(mapName) {}
};

struct GameData {
    PlayerData playerData;
    MapData mapData;

    GameData(const PlayerData& playerData = PlayerData(), const MapData& mapData = MapData())
        : playerData(playerData), mapData(mapData) {}
};
