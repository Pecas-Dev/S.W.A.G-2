
// MY DEAR CLAUDE: COMMENTED OUT SO THAT WE CAN IMPLEMENT THINGS STEP BY STEP! (;

/*#include <Entities/Sheep/States/SheepStates.h>
#include <Entities/Grass/GrassStateMachine.h>
#include <Entities/Sheep/SheepStateMachine.h>
#include <Entities/Wolf/WolfStateMachine.h>
#include <Utility/SimulationConfig.h>
#include <Utility/ValueConfig.h>
#include <World/World.h>
#include <World/NavigationGrid.h>
#include <Utility/PathFinding.h>
#include <algorithm>


// Creates a new world with specified dimensions and cell size.
World::World(int width, int height, float cellSize, float viewportYOffset, float scaleFactor, Simulation* simulation)
    : width(width),
    height(height),
    cellSize(cellSize* scaleFactor),
    minY(viewportYOffset),
    scaleFactor(scaleFactor),
    simulation(simulation)
{
    // Create navigation grid
    navigationGrid = std::make_unique<NavigationGrid>(width, height);

    // Create pathfinding system
    pathFinding = std::make_unique<PathFinding>(this);
}

World::~World()
{
    // Clean up resources
}

// Initializes the world with a specified number entities.
void World::Initialize(int grassCount, int sheepCount, int wolfCount)
{
	float minimumY = GetMinY();

	// Initialize navigation grid
	navigationGrid->Initialize();

	// Initialize grass
	for (int i = 0; i < grassCount; i++)
	{
		Vector2 position;

		do
		{
			position.x = static_cast<float>(GetRandomValue(0, width - 1));
			position.y = static_cast<float>(GetRandomValue(0, height - 1));

			if (position.y * cellSize * scaleFactor + minY < minimumY)
			{
				position.y = minimumY / (cellSize * scaleFactor);
			}

		} while (IsCellOccupied(position));

		CreateGrass(position);
	}

	// Create wolf at its den.
	Vector2 wolfPosition;
	wolfPosition.x = static_cast<float>(GetScreenWidth() * 3.0f / 4.0f - ValueConfig::World::CellSize * scaleFactor * 2);
	wolfPosition.y = static_cast<float>(GetScreenHeight() * 2.0f / 3.0f) / 2;

	float maxX = static_cast<float>(GetScreenWidth()) * 3.0f / 4.0f - ValueConfig::World::CellSize * scaleFactor;
	float maxY = static_cast<float>(GetScreenHeight()) * 2.0f / 3.0f - ValueConfig::World::CellSize * scaleFactor;

	wolfPosition.x = std::max(0.0f, std::min(wolfPosition.x, maxX));
	wolfPosition.y = std::max(minimumY, std::min(wolfPosition.y, maxY));


	for (int i = 0; i < wolfCount; i++)
	{
		CreateWolf(wolfPosition);
	}

	// Create initial sheep at random positions.
	for (int i = 0; i < sheepCount; i++)
	{
		Vector2 sheepPosition;

		do
		{
			sheepPosition.x = static_cast<float>(GetRandomValue(0, width - 1)) * cellSize * scaleFactor;
			sheepPosition.y = static_cast<float>(GetRandomValue(0, height - 1)) * cellSize * scaleFactor;

		} while (IsCellOccupied(sheepPosition));

		CreateSheep(sheepPosition);
	}

	// Create some obstacles in the navigation grid (optional)
	for (int i = 0; i < width * height / 50; i++) {
		Vector2 obstaclePos = {
			static_cast<float>(GetRandomValue(0, width - 1)),
			static_cast<float>(GetRandomValue(0, height - 1))
		};

		// Don't create obstacles where entities are
		if (!IsCellOccupied(obstaclePos)) {
			navigationGrid->SetTileWalkable(obstaclePos, false);
		}
	}
}

// Updates all grass entities and processes pending grass creation.
void World::Update(float deltaTime)
{
	// Update sheep poop instances.
	UpdateSheepPoop(deltaTime);

	// Update blood splatter instances.
	UpdateBloodSplatters(deltaTime);

	// Update debug paths
	UpdateDebugPaths(deltaTime);

	// Update and remove dead grass.
	for (auto it = grasses.begin(); it != grasses.end();)
	{
		if (!(*it)->IsAlive())
		{
			it = grasses.erase(it);
		}
		else
		{
			(*it)->Entity::Update(deltaTime);
			++it;
		}
	}

	// Update wolves
	for (auto it = wolves.begin(); it != wolves.end();)
	{
		if (!(*it)->IsAlive())
		{
			it = wolves.erase(it);
		}
		else
		{
			(*it)->Entity::Update(deltaTime);
			++it;
		}
	}

	std::vector<Vector2> newSheepPositions;

	// Update sheep
	for (auto it = sheeps.begin(); it != sheeps.end();)
	{
		if (!(*it)->IsAlive())
		{
			it = sheeps.erase(it);
		}
		else
		{
			(*it)->SetNewSheepPositions(&newSheepPositions);
			(*it)->Entity::Update(deltaTime);
			(*it)->SetNewSheepPositions(nullptr);

			++it;
		}
	}

	for (const auto& position : newSheepPositions)
	{
		CreateSheep(position);
	}

	// Create new grass from pending positions.
	for (const auto& positions : pendingGrassPositions)
	{
		CreateGrass(positions);
	}

	pendingGrassPositions.clear();
}

// Renders all grass entities in the world.
void World::Draw()
{
	// Draw navigation grid (walls/obstacles)
	navigationGrid->Draw(this);

	// Draw debug paths if enabled
	if (showDebugPaths) {
		for (const auto& debugPath : debugPaths) {
			pathFinding->DebugDrawPath(debugPath.points, debugPath.color);
		}
	}

	for (const auto& grass : grasses)
	{
		grass->Draw();
	}

	for (const auto& poop : sheepPoopInstances)
	{
		float alpha = 1.0f - (poop.lifetime / SheepPoopInstance::maxLifetime);
		Color poopColor = { 139, 69, 19, static_cast<unsigned char>(255 * alpha) };

		DrawCircle(static_cast<int>(poop.position.x + ValueConfig::World::CellSize * scaleFactor / 2), static_cast<int>(poop.position.y + ValueConfig::World::CellSize * scaleFactor / 2), 5.0f * scaleFactor, poopColor);
	}

	for (const auto& splatter : bloodSplatters)
	{
		float alpha = 1.0f - (splatter.lifetime / BloodSplatterInstance::maxLifetime);

		Color bloodColor;

		if (splatter.size > 6.0f)
		{
			bloodColor = { 139, 0, 0, static_cast<unsigned char>(255 * alpha) };
		}
		else
		{
			bloodColor = { 220, 20, 20, static_cast<unsigned char>(255 * alpha) };
		}

		DrawCircle(static_cast<int>(splatter.position.x), static_cast<int>(splatter.position.y), splatter.size * scaleFactor, bloodColor);
	}

	for (const auto& wolf : wolves)
	{
		wolf->Draw();
	}

	for (const auto& sheep : sheeps)
	{
		sheep->Draw();
	}
}

// Check if a tile is walkable
bool World::IsTileWalkable(const Vector2& gridPosition) const
{
	return navigationGrid->IsTileWalkable(gridPosition);
}

// Find a path using the pathfinding system
std::vector<Vector2> World::FindPath(const Vector2& start, const Vector2& end)
{
	return pathFinding->FindPath(start, end);
}

// Convert world position to grid position
Vector2 World::WorldToGrid(const Vector2& worldPos) const
{
	float adjustedY = worldPos.y - minY;
	int gridX = static_cast<int>(worldPos.x / (ValueConfig::World::CellSize * scaleFactor));
	int gridY = static_cast<int>(adjustedY / (ValueConfig::World::CellSize * scaleFactor));

	return { static_cast<float>(gridX), static_cast<float>(gridY) };
}

// Convert grid position to world position
Vector2 World::GridToWorld(const Vector2& gridPos) const
{
	float worldX = gridPos.x * ValueConfig::World::CellSize * scaleFactor;
	float worldY = gridPos.y * ValueConfig::World::CellSize * scaleFactor + minY;

	return { worldX, worldY };
}

// Recalculate paths for all entities
void World::RecalculateAllPaths()
{
	for (auto& sheep : sheeps) {
		if (sheep->IsAlive() && sheep->GetCurrentPath().has_value()) {
			Vector2 target = sheep->GetPathTarget();
			Vector2 start = WorldToGrid(sheep->GetPosition());
			std::vector<Vector2> path = FindPath(start, target);
			sheep->SetCurrentPath(path, target);
		}
	}

	for (auto& wolf : wolves) {
		if (wolf->IsAlive() && wolf->GetCurrentPath().has_value()) {
			Vector2 target = wolf->GetPathTarget();
			Vector2 start = WorldToGrid(wolf->GetPosition());
			std::vector<Vector2> path = FindPath(start, target);
			wolf->SetCurrentPath(path, target);
		}
	}
}

// Debug path visualization methods
void World::AddDebugPath(const std::vector<Vector2>& path, Color color)
{
	if (path.empty()) return;

	DebugPath debugPath;
	debugPath.points = path;
	debugPath.color = color;
	debugPath.timeToLive = DebugPath::defaultTimeToLive;

	debugPaths.push_back(debugPath);
}

void World::UpdateDebugPaths(float deltaTime)
{
	for (auto it = debugPaths.begin(); it != debugPaths.end();) {
		it->timeToLive -= deltaTime;

		if (it->timeToLive <= 0) {
			it = debugPaths.erase(it);
		}
		else {
			++it;
		}
	}
}

void World::ClearDebugPaths()
{
	debugPaths.clear();
}*/

