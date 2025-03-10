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