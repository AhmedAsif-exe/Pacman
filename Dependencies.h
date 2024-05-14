#pragma once
#include <pthread.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <chrono>
#include <random>
#include <cstring>
struct GameState
{
    sf::Vector2i step;
    int **map;
    int width;
    int height;
    std::vector<sf::Vector2i> paths;
    GameState() : paths(4)
    {
    }
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