#pragma once

#include <raylib.h>

#include <functional>
#include <vector>
#include <map>
#include <set>


class World;


struct PathNode
{
	PathNode* parent;
	Vector2 position;
	float gCost;
	float hCost;


	float fCost() const { return gCost + hCost; }

	bool operator<(const PathNode& other) const { if (fCost() != other.fCost()) { return fCost() < other.fCost(); }return hCost < other.hCost; }
	bool operator==(const PathNode& other) const { return position.x == other.position.x && position.y == other.position.y; }
};

struct NodeComparator
{
	bool operator()(const PathNode* a, const PathNode* b) const { if (a->fCost() != b->fCost()) { return a->fCost() < b->fCost(); }return a->hCost < b->hCost; }
};

struct Vector2Hash
{
	std::size_t operator()(const Vector2& v) const { return std::hash<float>()(v.x) ^ (std::hash<float>()(v.y) << 1); }
};

struct Vector2Equal
{
	bool operator()(const Vector2& lhs, const Vector2& rhs) const { return lhs.x == rhs.x && lhs.y == rhs.y; }
};

class PathFinding 
{
public:
	PathFinding(World* world);
	~PathFinding();


	void DebugDrawPath(const std::vector<Vector2>& path, Color color);

	bool HasPath(const Vector2& start, const Vector2& end);


	std::vector<Vector2> FindPath(const Vector2& start, const Vector2& end);

private:
	World* world;

	float CalculateHeuristic(const Vector2& a, const Vector2& b);


	std::vector<Vector2> GetNeighbors(const Vector2& position);
	std::vector<Vector2> ReconstructPath(PathNode* endNode);
};