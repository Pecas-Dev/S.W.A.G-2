#pragma once

#include <Utility/SimulationConfig.h>
#include <Utility/StateMachine.h>
#include <Utility/ValueConfig.h>
#include <Entities/Entity.h>

#include <raylib.h>

#include <optional>


class World;
class SheepStateMachine;


class WolfStateMachine : public Entity, public StateMachine
{
public:
	enum class WolfState
	{
		Sleeping,
		Roaming,
		Hunting,
		Eating,
		ReturnToDen,

		Following
	};

	WolfStateMachine(World* world, Vector2 position, float scaleFactor = 1.0f);
	~WolfStateMachine();

	void Initialize();

	void Sense(float deltaTime) override;
	void Decide(float deltaTime) override;
	void Act(float deltaTime) override;
	void Draw() override;


	void DrawStatusBars(Vector2 barPosition, float staminaValue);
	void SetPosition(Vector2 newPosition);
	void DrawHuntingLine();
	void FindNewTarget();



	// MY DEAR CLAUDE: COMMENTED OUT SO THAT WE CAN IMPLEMENT THINGS STEP BY STEP! (;
	/*
	void NavigateTo(Vector2 targetGridPosition);
	void FollowPath(float deltaTime);
	void ClearPath();
	bool HasReachedPathEnd() const;
	bool IsFollowingPath() const { return !currentPath.empty() && currentWolfState == WolfState::Following; }
	const std::optional<std::vector<Vector2>>& GetCurrentPath() const { return currentPath; }
	Vector2 GetPathTarget() const { return pathTarget; }
	void SetCurrentPath(const std::vector<Vector2>& path, Vector2 target);*/





	void SetTargetSheep(SheepStateMachine* sheep) { targetSheep = sheep; }
	void SetCurrentState(WolfState state) { currentWolfState = state; }
	void SetStamina(float value) { stamina = value; }
	void SetHunger(float value) { hunger = value; }

	float GetHungerThreshold() const { return hungerThreshold; }
	float GetStamina() const { return stamina; }
	float GetHunger() const { return hunger; }

	Vector2 GetPosition() const { return position; }

	SheepStateMachine* GetTargetSheep() const { return targetSheep; }
	WolfState GetCurrentState() const { return currentWolfState; }
	World* GetWorld() const { return world; }


	bool IsTired() const { return stamina < tiredThreshold; }
	bool IsAlive() const { return isAlive; }

	void Die() { isAlive = false; }

private:
	SheepStateMachine* targetSheep;
	WolfState currentWolfState;
	World* world;


	Vector2 position;


	Texture2D wolfTexture;


	bool isAlive;

	float hunger;
	float stamina;
	float scaleFactor;
	float targetingTimer;



	// MY DEAR CLAUDE: COMMENTED OUT SO THAT WE CAN IMPLEMENT THINGS STEP BY STEP! (;

	/*
	std::optional<std::vector<Vector2>> currentPath;
	Vector2 pathTarget;
	size_t currentPathIndex = 0;
	float pathFollowTimer = 0.0f;
	static constexpr float pathUpdateInterval = 0.5f; // Time between path recalculations */



	const float tiredThreshold = RuntimeConfig::WolfStaminaMax() * 0.2f;
	const float hungerThreshold = RuntimeConfig::WolfHungerThreshold();

	static constexpr float targetAcquisitionDelay = 0.5f;
	static constexpr float cellSize = ValueConfig::World::CellSize;
	static constexpr float staminaRecoveryRate = ValueConfig::Wolf::StaminaRecoveryRate;
};