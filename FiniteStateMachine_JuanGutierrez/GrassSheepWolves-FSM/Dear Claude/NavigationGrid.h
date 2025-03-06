

// MY DEAR CLAUDE: COMMENTED OUT SO THAT WE CAN IMPLEMENT THINGS STEP BY STEP! (;


/*#pragma once

#include <raylib.h>
#include <vector>
#include <unordered_map>
#include <Utility/ValueConfig.h>

// Forward declarations
class World;

// Structure to represent a tile in the grid
struct Tile {
    bool walkable;
    Color color;
};

class NavigationGrid {
public:
    NavigationGrid(int width, int height);
    ~NavigationGrid();

    // Initialize the grid with default walkable tiles
    void Initialize();

    // Get the walkable status of a tile
    bool IsTileWalkable(const Vector2& gridPosition) const;

    // Set the walkable status of a tile
    void SetTileWalkable(const Vector2& gridPosition, bool walkable);

    // Toggle the walkable status of a tile
    bool ToggleTileWalkable(const Vector2& gridPosition);

    // Draw the navigation grid
    void Draw(World* world);

    // Check if position is within grid bounds
    bool IsWithinBounds(const Vector2& gridPosition) const;

    // Get width and height
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

private:
    int width;
    int height;

    // Using a 2D vector to store grid data
    std::vector<std::vector<Tile>> grid;

    // Helper method to calculate index from position
    int GetIndex(int x, int y) const;

    // Colors for grid rendering
    const Color walkableColor = { 0, 150, 0, 50 };       // Green transparent
    const Color nonWalkableColor = { 150, 0, 0, 100 };   // Red transparent
};
*/