#include "Dependencies.h"
class Ghost
{
private:
    bool canMove(int x, int y, GameState &game_state)
    {
        return (x >= 0 && x < 40 && y >= 0 && y < 20 && game_state.map[x][y] != WALL && game_state.map[x][y] != ENEMIES);
    }
    int previous_spawn = BLANK;

public:
    bool offState = false;
    sf::Vector2i coordinates;
    void ghostHandler(GameState &game_state, float &timer, int idx)
    {
        if (timer < 0.2f)
            return;
        timer = 0;
        sf::Vector2i new_coordinates(coordinates.x + game_state.paths[idx].x, coordinates.y + game_state.paths[idx].y);

        if (canMove(new_coordinates.x, new_coordinates.y, game_state))
        {
            game_state.map[coordinates.x][coordinates.y] = previous_spawn;
            previous_spawn = game_state.map[new_coordinates.x][new_coordinates.y];
            game_state.map[new_coordinates.x][new_coordinates.y] = ENEMIES;
            coordinates = new_coordinates;
        }
    }
};
unsigned long long generateSeed()
{
    // Get current time since epoch
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    // Get process ID
    auto pid = getpid();

    // Generate random bytes
    std::random_device rd;
    unsigned char randomBytes[16];
    for (int i = 0; i < 16; ++i)
    {
        randomBytes[i] = rd();
    }

    // Combine all components to create a seed value
    unsigned long long seedValue = 0;
    seedValue |= milliseconds;
    seedValue <<= 32;
    seedValue |= pid;
    seedValue <<= 64;
    std::memcpy(&seedValue, randomBytes, sizeof(seedValue));

    return seedValue;
}
void *ghostHandlerRoutine(void *argument)
{
    GameState *game_state = (GameState *)argument;
    if (game_state->isPause)
        pthread_exit(0);
    int space = game_state->additional_storage;
    srand(generateSeed());
    int walk = rand() % 4;
    if (walk == 0)
        game_state->paths[space] = {1, 0};
    else if (walk == 1)
        game_state->paths[space] = {-1, 0};
    else if (walk == 2)
        game_state->paths[space] = {0, 1};
    else if (walk == 3)
        game_state->paths[space] = {0, -1};
    pthread_exit(0);
}