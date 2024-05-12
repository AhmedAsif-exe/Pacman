#include "Dependencies.h"
enum spawns
{
    COIN = 113,
    POINTS = 140,
    ENEMIES = 85,
    WALL = 0,
    PLAYER = 165,
    BLANK = 255
};
class PacPlayer
{
private:
    sf::Vector2i coordinates;
    bool canMove(int x, int y)
    {
        return (map[x][y] != WALL && x >= 0 && x < 40 && y >= 0 && y < 20);
    }
    float timer = 0.1f;

public:
    float frame_time = 0;
    PacPlayer() : coordinates(sf::Vector2i(19, 14)) {}

    void handleInput()
    {
        if (frame_time < timer)
            return;

        frame_time -= timer;

        if (canMove(coordinates.x - 1, coordinates.y) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            map[coordinates.x - 1][coordinates.y] = PLAYER;
            map[coordinates.x][coordinates.y] = BLANK;
            --coordinates.x;
        }
        else if (canMove(coordinates.x + 1, coordinates.y) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            map[coordinates.x + 1][coordinates.y] = PLAYER;
            map[coordinates.x][coordinates.y] = BLANK;
            ++coordinates.x;
        }
        else if (canMove(coordinates.x, coordinates.y - 1) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            map[coordinates.x][coordinates.y - 1] = PLAYER;
            map[coordinates.x][coordinates.y] = BLANK;
            --coordinates.y;
        }
        else if (canMove(coordinates.x, coordinates.y + 1) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            map[coordinates.x][coordinates.y + 1] = PLAYER;
            map[coordinates.x][coordinates.y] = BLANK;
            ++coordinates.y;
        }
    }
};