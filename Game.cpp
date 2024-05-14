#include "Dependencies.h"
#include "Player.h"
#include "Enemy.h"

void *Player(void *);
void generate_map(GameState &game_state)
{
    sf::Image image;
    image.loadFromFile("Resources/map.png");
    game_state.width = image.getSize().x;
    game_state.height = image.getSize().y;
    std::cout << game_state.width << " " << game_state.height << std::endl;
    game_state.map = new int *[game_state.width];
    for (unsigned int i = 0; i < game_state.width; ++i)
        game_state.map[i] = new int[game_state.height];

    for (unsigned int x = 0; x < game_state.width; ++x)
    {
        for (unsigned int y = 0; y < game_state.height; ++y)
        {
            sf::Color color = image.getPixel(x, y);

            int grayscale = (color.r + color.g + color.b) / 3;
            game_state.map[x][y] = grayscale;
            if (grayscale >= 100)
                std::cout << grayscale << " ";
            else if (grayscale < 100 && grayscale >= 10)
                std::cout << grayscale << "  ";
            else if (grayscale < 10)
                std::cout << grayscale << "   ";
        }
        std::cout << std::endl;
    }
}
void render_map(sf::RenderWindow &window, GameState &game_state)
{
    sf::RectangleShape rectangle(sf::Vector2f(20.0f, 20.0f));
    sf::CircleShape circle;

    for (int x = 0; x < game_state.width; ++x)
        for (int y = 0; y < game_state.height; ++y)
            if (game_state.map[x][y] == WALL)
            {
                rectangle.setPosition(x * 20 + 50, y * 20 + 50);
                rectangle.setFillColor(sf::Color(255, 255, 255, 240));
                window.draw(rectangle);
            }
            else if (game_state.map[x][y] == POINTS)
            {

                circle.setRadius(2.5f);
                circle.setPosition(x * 20 + 57.5f, y * 20 + 57.5f);
                circle.setFillColor(sf::Color(255, 255, 255, 200));
                window.draw(circle);
            }
            else if (game_state.map[x][y] == COIN)
            {
                circle.setRadius(5.0f);
                circle.setPosition(x * 20 + 55.0f, y * 20 + 55.0f);
                circle.setFillColor(sf::Color::Yellow);
                window.draw(circle);
            }
            else if (game_state.map[x][y] == PLAYER)
            {
                sf::Texture pacman;
                pacman.loadFromFile("Resources/player.png");
                sf::Sprite character;
                character.setTexture(pacman);
                character.setTextureRect(sf::IntRect(0, 0, 16, 16));
                character.setPosition(x * 20 + 52.0f, y * 20 + 52.0f);
                window.draw(character);
            }
            else if (game_state.map[x][y] == ENEMIES)
            {
                sf::Texture enemyText;
                enemyText.loadFromFile("Resources/clyde.png");
                sf::Sprite enemy;
                enemy.setTexture(enemyText);
                enemy.setTextureRect(sf::IntRect(112, 0, 16, 16));
                enemy.setPosition(x * 20 + 52.0f, y * 20 + 52.0f);
                window.draw(enemy);
            }
}
void *game(void *argument)
{
    GameState game_state;

    sf::RenderWindow window(sf::VideoMode(900, 500), "Pac Man");
    sf::Texture wallpaper;
    wallpaper.loadFromFile("Resources/Wallpaper.jpg");
    sf::Sprite img(wallpaper);
    img.setScale(0.75f, 0.83f);
    generate_map(game_state);
    sf::Clock clock;
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Resources/player.png");
    PacPlayer player;
    float frame_time = 0;
    float enemy_frame_timer[4] = {0};
    pthread_t playerThread, GhostThread[4];
    Ghost enemy[4];
    enemy[0].coordinates = {18, 8};
    enemy[1].coordinates = {21, 8};
    enemy[2].coordinates = {18, 10};
    enemy[3].coordinates = {21, 10};
    sf::Texture pauseIcon;
    pauseIcon.loadFromFile("Resources/pause.png");
    sf::Sprite pause(pauseIcon);
    pause.setScale(0.75f, 0.83f);
    pause.setPosition(375, 150);
    while (window.isOpen())
    {
        game_state.eternal_frame += clock.getElapsedTime().asSeconds();
        frame_time += clock.getElapsedTime().asSeconds();
        for (int i = 0; i < 4; ++i)
            enemy_frame_timer[i] += clock.getElapsedTime().asSeconds();
        clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear();
        window.draw(img);

        pthread_create(&playerThread, NULL, Player, &game_state);
        pthread_join(playerThread, NULL); // Handle player input

        for (int i = 0; i < 4; i++)
        {
            game_state.additional_storage = i;
            pthread_create(&GhostThread[i], NULL, ghostHandlerRoutine, &game_state);
        }

        for (int i = 0; i < 4; i++)
            pthread_join(GhostThread[i], NULL);

        if (!game_state.isPause)
        {
            player.handleMovement(game_state, frame_time);

            for (int i = 0; i < 4; i++)
                enemy[i].ghostHandler(game_state, enemy_frame_timer[i], i);
        }
        render_map(window, game_state);
        if (game_state.isPause)
            window.draw(pause);

        window.display();
    }

    for (unsigned int i = 0; i < game_state.width; ++i)
        delete[] game_state.map[i];
    delete[] game_state.map;

    pthread_exit(0);
}
