#ifndef CORE_HPP
#define CORE_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

constexpr int SCALE{ 1 };
constexpr int WINDOW_WIDTH{ 800 * SCALE }, WINDOW_HEIGHT{ 600 * SCALE };
constexpr float TILE_SIZE{ 32 };
constexpr float TILE_EDITING_WINDOW_WIDTH{ TILE_SIZE * 6.7f };
constexpr float DEFAULT_BACKGROUND_COLOUR[3] = { 0.2f, 0.2f, 0.2f };

constexpr ImGuiWindowFlags TILE_EDIT_WINDOW_FLAGS{ ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse };

constexpr ImGuiWindowFlags SELECTED_TEXTURE_WINDOW_FLAGS{ ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
ImGuiWindowFlags_NoTitleBar };

#endif /* CORE_HPP */

