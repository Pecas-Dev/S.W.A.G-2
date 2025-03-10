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