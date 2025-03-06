#include <Utility/PathFinding.h>
#include <Utility/ValueConfig.h>
#include <World/World.h>

#include <unordered_map>
#include <cmath>
#include <set>


PathFinding::PathFinding(World* world) : world(world)
{
}

PathFinding::~PathFinding()
{
}

std::vector<Vector2> PathFinding::FindPath(const Vector2& start, const Vector2& end)
{
	if (start.x == end.x && start.y == end.y)
	{
		return { start };
	}

	std::set<PathNode*, NodeComparator> openSet;

	std::unordered_map<Vector2, bool, Vector2Hash, Vector2Equal> closedSet;

	std::vector<PathNode*> allNodes;

	PathNode* startNode = new PathNode
	{
		nullptr,
		start,
		0.0f,
		CalculateHeuristic(start, end) 
	};

	allNodes.push_back(startNode);
	openSet.insert(startNode);

	while (!openSet.empty())
	{
		PathNode* current = *openSet.begin();
		openSet.erase(openSet.begin());

		closedSet[current->position] = true;

		if (current->position.x == end.x && current->position.y == end.y)
		{
			std::vector<Vector2> path = ReconstructPath(current);

			for (auto node : allNodes)
			{
				delete node;
			}

			return path;
		}

		for (const Vector2& neighborPos : GetNeighbors(current->position))
		{
			if (closedSet.find(neighborPos) != closedSet.end())
			{
				continue;
			}

			float newGCost = current->gCost + CalculateHeuristic(current->position, neighborPos);

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
			else if (newGCost < neighborNode->gCost)
			{
				openSet.erase(neighborNode);
				neighborNode->gCost = newGCost;
				neighborNode->parent = current;
				openSet.insert(neighborNode);
			}
		}
	}

	for (auto node : allNodes)
	{
		delete node;
	}

	return {};
}

bool PathFinding::HasPath(const Vector2& start, const Vector2& end)
{
	return !FindPath(start, end).empty();
}

float PathFinding::CalculateHeuristic(const Vector2& a, const Vector2& b)
{
	return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

std::vector<Vector2> PathFinding::GetNeighbors(const Vector2& position)
{
	std::vector<Vector2> neighbors;

	const int dx[] = { 0, 1, 0, -1 };
	const int dy[] = { -1, 0, 1, 0 };

	for (int i = 0; i < 4; i++)
	{
		Vector2 newPos =
		{
			position.x + dx[i],
			position.y + dy[i]
		};

		if (world->IsTileWalkable(newPos))
		{
			neighbors.push_back(newPos);
		}
	}

	const int diagDx[] = { 1, 1, -1, -1 };
	const int diagDy[] = { -1, 1, 1, -1 };

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

void PathFinding::DebugDrawPath(const std::vector<Vector2>& path, Color color)
{
	if (path.empty()) return;

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