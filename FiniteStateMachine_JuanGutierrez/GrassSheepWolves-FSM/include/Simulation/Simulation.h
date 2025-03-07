#pragma once

#include <Utility/SimulationConfig.h>


// MY DEAR CLAUDE: COMMENTED OUT SO THAT WE CAN IMPLEMENT THINGS STEP BY STEP! (;

/*#include <Simulation/EditMode.h>*/


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

	bool ShouldShowDetectionRadii() const { return showDetectionRadii; }



	// MY DEAR CLAUDE: COMMENTED OUT SO THAT WE CAN IMPLEMENT THINGS STEP BY STEP! (;

	/*bool ShouldShowPaths() const { return showPaths; }

	// Edit mode methods
	void ToggleEditMode();
	void TogglePathVisualization();
	bool IsInEditMode() const { return currentState == SimulationState::EditMode; }

	// Path recalculation callback
	void OnNavigationChanged();*/



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

	void RenderSimulationInViewport();
	void UpdateValidScalingOptions();
	void DrawEntityStatusWindow();
	void DrawSimulationLayout();
	void DrawConsoleWindow();
	void DrawLegendPanel();
	void DrawTabBar();


	// MY DEAR CLAUDE: COMMENTED OUT SO THAT WE CAN IMPLEMENT THINGS STEP BY STEP! (;

	/*void DrawEditModeUI();*/



	void CalculateWindowDimensions(float scaleFactor, int& outWidth, int& outHeight) const;
	void CenterWindow(int width, int height);


	float GetHighestValidScaleFactor() const;


	bool IsScaleOptionValid(int scaleIndex) const;


	static void ConsoleOutputCallback(const char* text, void* userData);


	SimulationState currentState;
	Viewport simulationViewport;
	SimulationConfig config;


	int screenWidth;
	int screenHeight;

	int initialGrassCount;
	int initialSheepCount;
	int initialWolfCount;


	int currentScaleIndex = 2;
	int _monitorWidth;
	int _monitorHeight;

	float cellSize;
	float screenScaleFactor = 1.0f;

	bool showEntityStatus = true;
	bool showDetectionRadii = false;
	bool pendingResize = false;
	bool scaleOptionEnabled[5];

	const char* scaleOptions[5] = { "0.5x", "0.75x", "1x", "1.25x", "1.5x" };


	static constexpr int BaseWindowWidth = 1850;
	static constexpr int BaseWindowHeight = 900;


	std::unique_ptr<World> world;


	// MY DEAR CLAUDE: COMMENTED OUT SO THAT WE CAN IMPLEMENT THINGS STEP BY STEP! (;

	/*bool showPaths = false;           // New flag for path visualization
	std::unique_ptr<EditMode> editMode;    // New edit mode object*/




	std::vector<std::string> consoleMessages;
};
