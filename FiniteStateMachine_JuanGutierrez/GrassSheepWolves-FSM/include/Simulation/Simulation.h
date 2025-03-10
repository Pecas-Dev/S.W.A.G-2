#pragma once

#include <Utility/SimulationConfig.h>
#include <Simulation/EditMode.h>
#include <Utility/ValueConfig.h>
#include <World/World.h>

#include <string>
#include <vector>


class SimulationConfig;


class Simulation
{
public:
	struct Viewport
	{
		float x;
		float y;
		float width;
		float height;
	};


	enum class SimulationState
	{
		Setup,
		Running,
		EditMode
	};


	Simulation();
	~Simulation();

	void Run();


	Vector2 GetViewportMaxCoordinates() const { return Vector2{ simulationViewport.width - ValueConfig::World::CellSize * screenScaleFactor, simulationViewport.height - ValueConfig::World::CellSize * screenScaleFactor }; }

	float GetViewportHeight() const { return simulationViewport.height; }
	float GetViewportWidth() const { return simulationViewport.width; }
	float GetViewportYOffset() const { return simulationViewport.y; }


	void AddConsoleMessage(const std::string& message) { consoleMessages.push_back(message); }

	void TogglePathVisualization();
	void OnNavigationChanged();
	void ToggleEditMode();


	bool IsInEditMode() const { return currentState == SimulationState::EditMode; }

	bool ShouldShowDetectionRadii() const { return showDetectionRadii; }

private:
	void Initialize();
	void Update();
	void Draw();

	void InitializeImGui();
	void StartSimulation();
	void ShutdownImGui();
	void DrawSetupUI();

	void RenderGrassSettings();
	void RenderSheepSettings();
	void RenderWolfSettings();

	void CenterWindow(int width, int height);
	void RenderSimulationInViewport();
	void UpdateValidScalingOptions();
	void DrawEntityStatusWindow();
	void DrawSimulationLayout();
	void DrawConsoleWindow();
	void DrawLegendPanel();
	void DrawEditModeUI();
	void DrawTabBar();


	void CalculateWindowDimensions(float scaleFactor, int& outWidth, int& outHeight) const;


	float GetHighestValidScaleFactor() const;


	bool IsScaleOptionValid(int scaleIndex) const;


	static void ConsoleOutputCallback(const char* text, void* userData);


	SimulationState currentState;
	Viewport simulationViewport;
	SimulationConfig config;


	int screenHeight;
	int screenWidth;


	int initialGrassCount;
	int initialSheepCount;
	int initialWolfCount;


	int currentScaleIndex = 2;
	int _monitorWidth;
	int _monitorHeight;

	float screenScaleFactor = 1.0f;
	float cellSize;

	bool showDetectionRadii = false;
	bool showEntityStatus = true;
	bool pendingResize = false;
	bool scaleOptionEnabled[5];
	bool showPaths = false;

	const char* scaleOptions[5] = { "0.5x", "0.75x", "1x", "1.25x", "1.5x" };


	static constexpr int BaseWindowWidth = 1850;
	static constexpr int BaseWindowHeight = 900;


	std::unique_ptr<World> world;

	std::unique_ptr<EditMode> editMode;    

	std::vector<std::string> consoleMessages;
};
