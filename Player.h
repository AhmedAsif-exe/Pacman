#include "Dependencies.h"

class PacPlayer
{
private:
    sf::Vector2i coordinates;
    bool canMove(int x, int y)
    {
        return (::map[x][y] != WALL && x >= 0 && x < 40 && y >= 0 && y < 20);
    }
    float timer = 0.1f;
    int points = 0;

    void setScore(int x, int y)
    {
        if (map[x][y] == POINTS)
            points += 5;
        else if (map[x][y] == COIN)
            points += 10;
    }

public:
    float frame_time = 0;
    PacPlayer() : coordinates(sf::Vector2i(19, 14)) {}
    void handleMovement()
    {
        if (frame_time < timer)
            return;

        frame_time -= timer;

        if (canMove(coordinates.x - 1, coordinates.y) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            setScore(coordinates.x - 1, coordinates.y);
            ::map[coordinates.x - 1][coordinates.y] = PLAYER;
            ::map[coordinates.x][coordinates.y] = BLANK;
            --coordinates.x;
        }
        else if (canMove(coordinates.x + 1, coordinates.y) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            setScore(coordinates.x + 1, coordinates.y);
            ::map[coordinates.x + 1][coordinates.y] = PLAYER;
            ::map[coordinates.x][coordinates.y] = BLANK;
            ++coordinates.x;
        }
        else if (canMove(coordinates.x, coordinates.y - 1) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            setScore(coordinates.x, coordinates.y - 1);
            ::map[coordinates.x][coordinates.y - 1] = PLAYER;
            ::map[coordinates.x][coordinates.y] = BLANK;
            --coordinates.y;
        }
        else if (canMove(coordinates.x, coordinates.y + 1) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            setScore(coordinates.x, coordinates.y + 1);
            ::map[coordinates.x][coordinates.y + 1] = PLAYER;
            ::map[coordinates.x][coordinates.y] = BLANK;
            ++coordinates.y;
        }
    }
};