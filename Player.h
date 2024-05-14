#include "Dependencies.h"

class PacPlayer
{
private:
    sf::Vector2i coordinates;
    bool canMove(int x, int y, int **map)
    {
        return (x >= 0 && x < 40 && y >= 0 && y < 20 && map[x][y] != WALL);
    }
    float timer = 0.1f;
    int points = 0;

    void setScore(int x, int y, int **map)
    {
        if (map[x][y] == POINTS)
            points += 5;
        else if (map[x][y] == COIN)
            points += 10;
    }

public:
    PacPlayer() : coordinates(sf::Vector2i(19, 14)) {}
    void handleMovement(GameState &game_state, float &frame_time)
    {
        std::cout << "Frame time : " << frame_time << std::endl;
        if (frame_time < 0.2f)
            return;
        frame_time = 0;
        sf::Vector2i new_position = {coordinates.x + game_state.step.x,
                                     coordinates.y + game_state.step.y};
        if (canMove(new_position.x, new_position.y, game_state.map))
        {
            setScore(new_position.x, new_position.y, game_state.map);
            game_state.map[coordinates.x][coordinates.y] = BLANK;
            game_state.map[new_position.x][new_position.y] = PLAYER;
            coordinates = new_position;
            game_state.step = {0, 0};
        }
    }
};