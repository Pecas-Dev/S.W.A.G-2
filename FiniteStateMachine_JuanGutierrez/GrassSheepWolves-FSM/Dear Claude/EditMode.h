

// MY DEAR CLAUDE: COMMENTED OUT SO THAT WE CAN IMPLEMENT THINGS STEP BY STEP! (;

/*#pragma once

#include <raylib.h>
#include <functional>

// Forward declarations
class World;
class NavigationGrid;

class EditMode {
public:
    EditMode(World* world);
    ~EditMode();

    // Update and handle input for edit mode
    void Update();

    // Draw edit mode UI and helpers
    void Draw();

    // Toggle edit mode on/off
    void Toggle();

    // Check if edit mode is active
    bool IsActive() const { return isActive; }

    // Set the callback function for when navigation is modified
    void SetOnNavigationChangedCallback(std::function<void()> callback);

private:
    World* world;
    bool isActive;

    // Position of the cursor in grid coordinates
    Vector2 cursorGridPosition;

    // Tool selection (e.g., add wall, remove wall)
    enum class Tool {
        AddWall,
        RemoveWall
    };

    Tool currentTool;

    // Callback for when navigation is changed
    std::function<void()> onNavigationChanged;

    // Helper functions
    void HandleInput();
    void DrawToolUI();
    void DrawCursor();

    // Convert screen coordinates to grid coordinates
    Vector2 ScreenToGrid(const Vector2& screenPos) const;
};
*/