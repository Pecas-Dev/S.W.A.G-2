#include <Utility/PathFinding.h>
#include <Utility/ValueConfig.h>
#include <World/World.h>

#include <unordered_map>
#include <cmath>
#include <set>


// Initializes a new PathFinding instance with a reference to the world
PathFinding::PathFinding(World* world) : world(world)
{
}

PathFinding::~PathFinding()
{
}

// Implements the A* algorithm to find the shortest path between two positions.
std::vector<Vector2> PathFinding::FindPath(const Vector2& start, const Vector2& end)
{
	// If the start and the end are the same, it will return a single point.
	if (start.x == end.x && start.y == end.y)
	{
		return { start };
	}

	// Nodes that need to be evaluated.
	std::set<PathNode*, NodeComparator> openSet;

	// Nodes that have already been evaluated.
	std::unordered_map<Vector2, bool, Vector2Hash, Vector2Equal> closedSet;

	// Tracks all nodes we create. It is also used for cleanup.
	std::vector<PathNode*> allNodes;

	// Creation of the Start Node.
	PathNode* startNode = new PathNode
	{
		nullptr,
		start,
		0.0f,
		CalculateHeuristic(start, end)
	};

	allNodes.push_back(startNode);
	openSet.insert(startNode);

	// Main loop of the A* Pathfinding Algorithm.
	while (!openSet.empty())
	{
		// Gets the node with the lowest fCost.
		PathNode* current = *openSet.begin();
		openSet.erase(openSet.begin());

		closedSet[current->position] = true;

		// If the current node is the end node, it will reconstruct the path and return it.
		if (current->position.x == end.x && current->position.y == end.y)
		{
			std::vector<Vector2> path = ReconstructPath(current);

			for (auto node : allNodes)
			{
				delete node;
			}

			return path;
		}

		// Iterates and check through all the neighbors of the current node.
		for (const Vector2& neighborPos : GetNeighbors(current->position))
		{
			if (closedSet.find(neighborPos) != closedSet.end())
			{
				continue;
			}

			// Calculates the new movement cost (gCost) for the neighbor node.
			float newGCost = current->gCost + CalculateHeuristic(current->position, neighborPos);

			// Checks if the neighbor node is already in the open set.
			bool inOpenSet = false;

			PathNode* neighborNode = nullptr;

			for (auto node : openSet)
			{
				if (node->position.x == neighborPos.x && node->position.y == neighborPos.y)
				{
					neighborNode = node;
					inOpenSet = true;
					break;
				}
			}

			// If the neighbor node is not in the open set, it will create a new node and add it to the open set.
			if (!inOpenSet)
			{
				neighborNode = new PathNode
				{
					current,
					neighborPos,
					newGCost,
					CalculateHeuristic(neighborPos, end)
				};

				allNodes.push_back(neighborNode);
				openSet.insert(neighborNode);
			}
			else if (newGCost < neighborNode->gCost) // If the new gCost is lower, it will update the neighbor node.
			{
				openSet.erase(neighborNode);
				neighborNode->gCost = newGCost;
				neighborNode->parent = current;
				openSet.insert(neighborNode);
			}
		}
	}

	// No path found, clean up and return empty path 
	for (auto node : allNodes)
	{
		delete node;
	}

	return {};
}

// Checks if there is a valid path between two points.
bool PathFinding::HasPath(const Vector2& start, const Vector2& end)
{
	return !FindPath(start, end).empty();
}

// Computes the Manhattan Distance heuristic between points.
float PathFinding::CalculateHeuristic(const Vector2& a, const Vector2& b)
{
	return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

// Finds all walkable adjacent grid positions.
std::vector<Vector2> PathFinding::GetNeighbors(const Vector2& position)
{
	std::vector<Vector2> neighbors;

	// Checks for walkable tiles in the 4 directions (up, right, down, left).
	const int dx[] = { 0, 1, 0, -1 };
	const int dy[] = { -1, 0, 1, 0 };

	for (int i = 0; i < 4; i++)
	{
		Vector2 newPos =
		{
			position.x + dx[i],
			position.y + dy[i]
		};

		// If the tile is walkable, it will add it to the neighbors list.
		if (world->IsTileWalkable(newPos))
		{
			neighbors.push_back(newPos);
		}
	}

	// Checks for walkable tiles in the 4 diagonal directions.
	const int diagDx[] = { 1, 1, -1, -1 };
	const int diagDy[] = { -1, 1, 1, -1 };

	// Adds the diagonal movements if the horizontal and vertical neighbors are walkable.
	for (int i = 0; i < 4; i++)
	{
		Vector2 newPos =
		{
			position.x + diagDx[i],
			position.y + diagDy[i]
		};

		Vector2 horizontal = { position.x + diagDx[i], position.y };
		Vector2 vertical = { position.x, position.y + diagDy[i] };


		if (world->IsTileWalkable(newPos) && world->IsTileWalkable(horizontal) && world->IsTileWalkable(vertical))
		{
			neighbors.push_back(newPos);
		}
	}

	return neighbors;
}

// Builds the complete path by tracing parent nodes.
std::vector<Vector2> PathFinding::ReconstructPath(PathNode* endNode)
{
	PathNode* current = endNode;

	std::vector<Vector2> path;

	while (current != nullptr)
	{
		path.push_back(current->position);
		current = current->parent;
	}

	std::reverse(path.begin(), path.end());

	return path;
}

// Visualizes a path for debugging purposes.
void PathFinding::DebugDrawPath(const std::vector<Vector2>& path, Color color)
{
	if (path.empty()) 
	{
		return;
	}

	float scaleFactor = world->GetScaleFactor();
	float cellSize = ValueConfig::World::CellSize * scaleFactor;
	float minY = world->GetMinY();

	for (size_t i = 0; i < path.size() - 1; i++)
	{
		Vector2 start =
		{
			path[i].x * cellSize + cellSize / 2,
			path[i].y * cellSize + cellSize / 2 + minY
		};

		Vector2 end =
		{
			path[i + 1].x * cellSize + cellSize / 2,
			path[i + 1].y * cellSize + cellSize / 2 + minY
		};

		DrawLineEx(start, end, 2.0f * scaleFactor, color);
	}

	for (const auto& node : path)
	{
		Vector2 pos =
		{
			node.x * cellSize + cellSize / 2,
			node.y * cellSize + cellSize / 2 + minY
		};

		DrawCircleV(pos, 3.0f * scaleFactor, color);
	}
}