
// MY DEAR CLAUDE: COMMENTED OUT SO THAT WE CAN IMPLEMENT THINGS STEP BY STEP! (;

/*#include <Simulation/EditMode.h>
#include <World/World.h>
#include <World/NavigationGrid.h>
#include <Utility/ValueConfig.h>
#include <imgui.h>
#include <raylib.h>

EditMode::EditMode(World* world)
    : world(world),
    isActive(false),
    cursorGridPosition({ 0, 0 }),
    currentTool(Tool::AddWall),
    onNavigationChanged(nullptr)
{
}

EditMode::~EditMode()
{
}

void EditMode::Update()
{
    if (!isActive) return;

    HandleInput();
}

void EditMode::Draw()
{
    if (!isActive) return;

    // Draw the UI for tool selection
    DrawToolUI();

    // Draw cursor
    DrawCursor();
}

void EditMode::Toggle()
{
    isActive = !isActive;

    // When entering edit mode, make sure we update the cursor position
    if (isActive) {
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
    // Update cursor grid position based on mouse
    Vector2 mousePos = GetMousePosition();
    cursorGridPosition = ScreenToGrid(mousePos);

    // Change tools with keyboard
    if (IsKeyPressed(KEY_ONE)) {
        currentTool = Tool::AddWall;
    }
    else if (IsKeyPressed(KEY_TWO)) {
        currentTool = Tool::RemoveWall;
    }

    // Apply changes when mouse is clicked
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        // Check if cursor is within bounds
        if (world->GetNavigationGrid()->IsWithinBounds(cursorGridPosition)) {
            bool changed = false;

            // Apply the current tool
            switch (currentTool) {
            case Tool::AddWall:
                world->GetNavigationGrid()->SetTileWalkable(cursorGridPosition, false);
                changed = true;
                break;

            case Tool::RemoveWall:
                world->GetNavigationGrid()->SetTileWalkable(cursorGridPosition, true);
                changed = true;
                break;
            }

            // If changes were made, notify
            if (changed && onNavigationChanged) {
                onNavigationChanged();
            }
        }
    }
}

void EditMode::DrawToolUI()
{
    // Create ImGui window for tool selection
    ImGui::Begin("Edit Mode Tools");

    // Tool selection
    int toolIndex = static_cast<int>(currentTool);

    if (ImGui::RadioButton("Add Wall (1)", &toolIndex, 0)) {
        currentTool = Tool::AddWall;
    }

    if (ImGui::RadioButton("Remove Wall (2)", &toolIndex, 1)) {
        currentTool = Tool::RemoveWall;
    }

    ImGui::Separator();

    ImGui::Text("Left-click to apply the selected tool");
    ImGui::Text("Press ESC to exit Edit Mode");

    ImGui::End();
}

void EditMode::DrawCursor()
{
    float scaleFactor = world->GetScaleFactor();
    float cellSize = ValueConfig::World::CellSize * scaleFactor;
    float minY = world->GetMinY();

    // Draw cursor rectangle
    Rectangle cursorRect = {
        cursorGridPosition.x * cellSize,
        cursorGridPosition.y * cellSize + minY,
        cellSize,
        cellSize
    };

    Color cursorColor;

    // Change cursor color based on tool
    switch (currentTool) {
    case Tool::AddWall:
        cursorColor = { 255, 0, 0, 100 }; // Red for adding walls
        break;

    case Tool::RemoveWall:
        cursorColor = { 0, 255, 0, 100 }; // Green for removing walls
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

    int gridX = static_cast<int>(screenPos.x / cellSize);
    int gridY = static_cast<int>((screenPos.y - minY) / cellSize);

    return { static_cast<float>(gridX), static_cast<float>(gridY) };
}
*/