#include "tileManager.h"
#include "../dataSource/dataSource.h"
#include "../mapTile/mapTile.h"

#include <iostream>
#include <thread>

bool TileManager::CheckNewTileStatus() {
    //Todo: Contact the view module to get new tile needed?
    // if True, call updateVisibleTiles()
    // else, nothing
    if (true) {
        //CalculateVisibleTileIDs();
        UpdateTiles();
    }
    return true;
}

void curlWorkerThread() {

}

void TileManager::UpdateTiles() {
    DataSource *dataSource = m_DataSources.at(0).get();

    //Naive Implementation to set tile Coordinates explicitly
    m_VisibleTileIDs.push_back(glm::ivec3(0,0,0));
    m_VisibleTileIDs.push_back(glm::ivec3(19293,24641,16));
    m_VisibleTileIDs.push_back(glm::ivec3(19293,24641,14));
    bool success = dataSource->LoadTile(m_VisibleTileIDs);
    //TODO: error handling of LoadTile return bool

    // Create MapTiles from the tileCoordinates after these are loaded.
    for(auto &tileID : m_VisibleTileIDs) {
        MapTile *mapTile = new MapTile(tileID);
        m_VisibleTiles.push_back(mapTile);
    }
}

TileManager::TileManager() {
}


// Should be used when adding new data sources.... FUTURE
void TileManager::AddDataSource(std::unique_ptr<DataSource> _dataSource) {
    m_DataSources.push_back(std::move(_dataSource));
}

std::vector<MapTile*> TileManager::GetVisibleTiles() {
    return m_VisibleTiles;
}

std::vector<std::unique_ptr<DataSource>>&& TileManager::GetDataSources() {
    return std::move(m_DataSources);
}
