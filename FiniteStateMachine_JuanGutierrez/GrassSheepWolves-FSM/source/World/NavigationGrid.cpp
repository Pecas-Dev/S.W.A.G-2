// MY DEAR CLAUDE: THIS IS THE CURRENT IMPLEMENTATION , THE ONE BELOW IS THE FULL ON IMPLEMENTATION YOU GAVE ME WHEN I FIRST ASKED YOU TO HELP ME WITH THIS, SO YOU CAN USE THAT AS REFERENCE, BUT PERHAPS THE CODE WILL CHANGE WITH TIME SO WE MIGHT NEED TO ADAPT IT, SO YEAH, IT'S REFERENCE, BUT NOT SET IN STONE.


#include <World/NavigationGrid.h>
#include <World/World.h>
#include <raylib.h>


// Initializes a new navigation grid with the specified dimensions.
NavigationGrid::NavigationGrid(int width, int height) : width(width), height(height)
{
	grid.resize(height, std::vector<Tile>(width, { true, walkableColor }));
}


NavigationGrid::~NavigationGrid()
{
}

// Sets up the initial state of the navigation grid with walkable tiles and random obstacles.
void NavigationGrid::Initialize()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			grid[y][x] = { true, walkableColor };
		}
	}

	int numObstacles = width * height / 50;

	for (int i = 0; i < numObstacles; i++)
	{
		int x = GetRandomValue(0, width - 1);
		int y = GetRandomValue(0, height - 1);

		grid[y][x] = { false, nonWalkableColor };
	}
}

// Checks if a tile at the specified grid position is walkable.
bool NavigationGrid::IsTileWalkable(const Vector2& gridPosition) const
{
	int x = static_cast<int>(gridPosition.x);
	int y = static_cast<int>(gridPosition.y);

	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return false;
	}

	return grid[y][x].walkable;
}

// Sets the walkable status of a tile at the specified grid position.
void NavigationGrid::SetTileWalkable(const Vector2& gridPosition, bool walkable)
{
	int x = static_cast<int>(gridPosition.x);
	int y = static_cast<int>(gridPosition.y);

	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return;
	}

	grid[y][x].walkable = walkable;
	grid[y][x].color = walkable ? walkableColor : nonWalkableColor;
}

// Checks if a grid position is within the bounds of the navigation grid.
bool NavigationGrid::IsWithinBounds(const Vector2& gridPosition) const
{
	int x = static_cast<int>(gridPosition.x);
	int y = static_cast<int>(gridPosition.y);

	return (x >= 0 && x < width && y >= 0 && y < height);
}

// Renders the navigation grid, highlighting non-walkable tiles with color.
void NavigationGrid::Draw(World* world)
{
	float scaleFactor = world->GetScaleFactor();
	float cellSize = ValueConfig::World::CellSize * scaleFactor;
	float minY = world->GetMinY();

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Tile& tile = grid[y][x];

			if (!tile.walkable)
			{
				Rectangle rec =
				{
					x * cellSize,
					y * cellSize + minY,
					cellSize,
					cellSize
				};

				DrawRectangleRec(rec, tile.color);
				DrawRectangleLinesEx(rec, 1.0f, { 100, 100, 100, 50 });
			}
		}
	}
}
































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