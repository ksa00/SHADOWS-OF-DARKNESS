#include "GameData.h"
#include <fstream>

void SaveGameData(const GameData& data, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&data.playerData), sizeof(PlayerData));
        size_t checkpointCount = data.mapData.checkpoints.size();
        file.write(reinterpret_cast<const char*>(&checkpointCount), sizeof(size_t));
        file.write(reinterpret_cast<const char*>(data.mapData.checkpoints.data()), checkpointCount * sizeof(Checkpoint));
        file.close();
    }
}

GameData LoadGameData(const std::string& filename) {
    GameData data;
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&data.playerData), sizeof(PlayerData));
        size_t checkpointCount;
        file.read(reinterpret_cast<char*>(&checkpointCount), sizeof(size_t));
        data.mapData.checkpoints.resize(checkpointCount);
        file.read(reinterpret_cast<char*>(data.mapData.checkpoints.data()), checkpointCount * sizeof(Checkpoint));
        file.close();
    }
    return data;
}
