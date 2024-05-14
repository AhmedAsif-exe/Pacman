#pragma once
#include <pthread.h>
#include <SFML/Graphics.hpp>
#include <iostream>

struct GameState
{
    sf::Vector2i step;
    int **map;
    int width;
    int height;
};
enum spawns
{
    COIN = 113,
    POINTS = 140,
    WALL = 0,
    PLAYER = 165,
    BLANK = 255,
    ENEMIES = 133

};