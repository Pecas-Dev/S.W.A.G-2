#include <World/NavigationGrid.h>
#include <Utility/ValueConfig.h>
#include <Simulation/EditMode.h>
#include <World/World.h>

#include <imgui.h>
#include <raylib.h>


EditMode::EditMode(World* world) : world(world), isActive(false), cursorGridPosition({ 0, 0 }), currentTool(Tool::AddWall), onNavigationChanged(nullptr)
{
}

EditMode::~EditMode()
{
}

void EditMode::Update()
{
	if (!isActive)
	{
		return;
	}

	HandleInput();
}

void EditMode::Draw()
{
	if (!isActive)
	{
		return;
	}

	DrawToolUI();
	DrawCursor();
}

void EditMode::Toggle()
{
	isActive = !isActive;

	if (isActive && world)
	{
		Vector2 mousePos = GetMousePosition();
		cursorGridPosition = ScreenToGrid(mousePos);
	}
}

void EditMode::SetOnNavigationChangedCallback(std::function<void()> callback)
{
	onNavigationChanged = callback;
}

void EditMode::HandleInput()
{
	Vector2 mousePos = GetMousePosition();

	cursorGridPosition = ScreenToGrid(mousePos);

	if (IsKeyPressed(KEY_ONE))
	{
		currentTool = Tool::AddWall;
	}
	else if (IsKeyPressed(KEY_TWO))
	{
		currentTool = Tool::RemoveWall;
	}

	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		if (world->GetNavigationGrid()->IsWithinBounds(cursorGridPosition))
		{
			bool changed = false;

			switch (currentTool)
			{
			case Tool::AddWall:
				world->GetNavigationGrid()->SetTileWalkable(cursorGridPosition, false);
				changed = true;
				break;

			case Tool::RemoveWall:
				world->GetNavigationGrid()->SetTileWalkable(cursorGridPosition, true);
				changed = true;
				break;
			}

			if (changed && onNavigationChanged)
			{
				onNavigationChanged();
			}
		}
	}
}

void EditMode::DrawToolUI()
{
	int screenWidth = GetScreenWidth();

	float windowWidth = 280.0f;
	float windowHeight = 120.0f;

	float posX = screenWidth - windowWidth - 1555.0f;
	float posY = 70.0f;

	ImGui::SetNextWindowPos(ImVec2(posX, posY));
	ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));

	ImGui::Begin("Edit Mode Tools", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	int toolIndex = static_cast<int>(currentTool);

	if (ImGui::RadioButton("Add Wall (1)", &toolIndex, 0))
	{
		currentTool = Tool::AddWall;
	}

	if (ImGui::RadioButton("Remove Wall (2)", &toolIndex, 1))
	{
		currentTool = Tool::RemoveWall;
	}

	ImGui::Separator();

	ImGui::Text("Left-click to apply the selected tool");
	ImGui::Text("Press Q to exit Edit Mode");

	ImGui::End();
}

void EditMode::DrawCursor()
{
	float scaleFactor = world->GetScaleFactor();
	float cellSize = ValueConfig::World::CellSize * scaleFactor;
	float minY = world->GetMinY();

	Rectangle cursorRect =
	{
		cursorGridPosition.x * cellSize,
		cursorGridPosition.y * cellSize + minY,
		cellSize,
		cellSize
	};

	Color cursorColor = { 255, 255, 255, 100 };

	switch (currentTool)
	{
	case Tool::AddWall:
		cursorColor = { 255, 0, 0, 100 };
		break;

	case Tool::RemoveWall:
		cursorColor = { 0, 255, 0, 100 };
		break;
	}

	DrawRectangleRec(cursorRect, cursorColor);
	DrawRectangleLinesEx(cursorRect, 2.0f, WHITE);
}

Vector2 EditMode::ScreenToGrid(const Vector2& screenPos) const
{
	float scaleFactor = world->GetScaleFactor();
	float cellSize = ValueConfig::World::CellSize * scaleFactor;
	float minY = world->GetMinY();

	Simulation* simulation = dynamic_cast<Simulation*>(world->GetSimulation());

	float viewportWidth = 0;
	float viewportHeight = 0;
	float viewportX = 0;
	float viewportY = minY;

	if (simulation)
	{
		viewportWidth = simulation->GetViewportWidth();
		viewportHeight = simulation->GetViewportHeight();
		viewportX = 0;
		viewportY = simulation->GetViewportYOffset();
	}

	bool isInViewport = screenPos.x >= viewportX && screenPos.x < viewportX + viewportWidth && screenPos.y >= viewportY && screenPos.y < viewportY + viewportHeight;

	int gridX = static_cast<int>(screenPos.x / cellSize);
	int gridY = static_cast<int>((screenPos.y - minY) / cellSize);

	int maxGridX = static_cast<int>(viewportWidth / cellSize) - 1;
	int maxGridY = static_cast<int>(viewportHeight / cellSize) - 1;

	gridX = isInViewport ? std::max(0, std::min(gridX, maxGridX)) : -1;
	gridY = isInViewport ? std::max(0, std::min(gridY, maxGridY)) : -1;

	return { static_cast<float>(gridX), static_cast<float>(gridY) };
}