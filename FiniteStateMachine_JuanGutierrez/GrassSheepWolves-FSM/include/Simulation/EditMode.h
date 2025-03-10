// MY DEAR CLAUDE: THIS IS THE CURRENT IMPLEMENTATION , THE ONE BELOW IS THE FULL ON IMPLEMENTATION YOU GAVE ME WHEN I FIRST ASKED YOU TO HELP ME WITH THIS, SO YOU CAN USE THAT AS REFERENCE, BUT PERHAPS THE CODE WILL CHANGE WITH TIME SO WE MIGHT NEED TO ADAPT IT, SO YEAH, IT'S REFERENCE, BUT NOT SET IN STONE.

#pragma once

#include <raylib.h>

#include <functional>


class World;
class NavigationGrid;


class EditMode
{
public:
    EditMode(World* world);
    ~EditMode();

    void Update();
    void Draw();
    void Toggle();


    bool IsActive() const { return isActive; }

    void SetOnNavigationChangedCallback(std::function<void()> callback);

private:
    enum class Tool
    {
        AddWall,
        RemoveWall
    };

    Tool currentTool;


    World* world;


    Vector2 cursorGridPosition;


    bool isActive;



    void HandleInput();
    void DrawToolUI();
    void DrawCursor();


    std::function<void()> onNavigationChanged;


    Vector2 ScreenToGrid(const Vector2& screenPos) const;
};








































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