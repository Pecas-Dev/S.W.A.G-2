#pragma once

#include <raylib.h>
#include <vector>
#include <Utility/ValueConfig.h>


class World;


struct Tile 
{
    bool walkable;
    Color color;
};

class NavigationGrid 
{
public:
    NavigationGrid(int width, int height);
    ~NavigationGrid();


    void Initialize();


    void SetTileWalkable(const Vector2& gridPosition, bool walkable);
    void Draw(World* world);

    bool IsWithinBounds(const Vector2& gridPosition) const;
    bool IsTileWalkable(const Vector2& gridPosition) const;

private:
    int width;
    int height;

    std::vector<std::vector<Tile>> grid;

    const Color walkableColor = { 0, 150, 0, 50 };       
    const Color nonWalkableColor = { 150, 0, 0, 100 };   
};
