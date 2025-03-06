
// MY DEAR CLAUDE: COMMENTED OUT SO THAT WE CAN IMPLEMENT THINGS STEP BY STEP! (;

/*#include <World/NavigationGrid.h>
#include <World/World.h>
#include <raylib.h>

NavigationGrid::NavigationGrid(int width, int height) : width(width), height(height)
{
    // Initialize grid with dimensions
    grid.resize(height, std::vector<Tile>(width, { true, walkableColor }));
}

NavigationGrid::~NavigationGrid()
{
}

void NavigationGrid::Initialize()
{
    // Set all tiles as walkable by default
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid[y][x] = { true, walkableColor };
        }
    }
}

bool NavigationGrid::IsTileWalkable(const Vector2& gridPosition) const
{
    int x = static_cast<int>(gridPosition.x);
    int y = static_cast<int>(gridPosition.y);

    // Check if position is within bounds
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false; // Out of bounds tiles are not walkable
    }

    return grid[y][x].walkable;
}

void NavigationGrid::SetTileWalkable(const Vector2& gridPosition, bool walkable)
{
    int x = static_cast<int>(gridPosition.x);
    int y = static_cast<int>(gridPosition.y);

    // Check if position is within bounds
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return; // Out of bounds, do nothing
    }

    grid[y][x].walkable = walkable;
    grid[y][x].color = walkable ? walkableColor : nonWalkableColor;
}

bool NavigationGrid::ToggleTileWalkable(const Vector2& gridPosition)
{
    int x = static_cast<int>(gridPosition.x);
    int y = static_cast<int>(gridPosition.y);

    // Check if position is within bounds
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false; // Out of bounds, don't toggle
    }

    // Toggle walkable status
    grid[y][x].walkable = !grid[y][x].walkable;
    grid[y][x].color = grid[y][x].walkable ? walkableColor : nonWalkableColor;

    return grid[y][x].walkable;
}

void NavigationGrid::Draw(World* world)
{
    float scaleFactor = world->GetScaleFactor();
    float cellSize = ValueConfig::World::CellSize * scaleFactor;
    float minY = world->GetMinY();

    // Draw grid
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Tile& tile = grid[y][x];

            // Draw tile
            Rectangle rec = {
                x * cellSize,
                y * cellSize + minY,
                cellSize,
                cellSize
            };

            DrawRectangleRec(rec, tile.color);

            // Draw grid lines
            DrawRectangleLinesEx(rec, 1.0f, { 100, 100, 100, 50 });
        }
    }
}

bool NavigationGrid::IsWithinBounds(const Vector2& gridPosition) const
{
    int x = static_cast<int>(gridPosition.x);
    int y = static_cast<int>(gridPosition.y);

    return (x >= 0 && x < width && y >= 0 && y < height);
}

int NavigationGrid::GetIndex(int x, int y) const
{
    return y * width + x;
}

*/