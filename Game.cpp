#include "Dependencies.h"
#include "Player.h"
void *Player(void *);
void generate_map()
{
    sf::Image image;
    image.loadFromFile("Resources/map.png");
    width = image.getSize().x;
    height = image.getSize().y;
    std::cout << width << " " << height << std::endl;
    ::map = new int *[width];
    for (unsigned int i = 0; i < width; ++i)
        ::map[i] = new int[height];

    for (unsigned int x = 0; x < width; ++x)
    {
        for (unsigned int y = 0; y < height; ++y)
        {
            sf::Color color = image.getPixel(x, y);

            int grayscale = (color.r + color.g + color.b) / 3;
            ::map[x][y] = grayscale;
        }
        std::cout << std::endl;
    }
}
void render_map(sf::RenderWindow &window)
{
    sf::RectangleShape rectangle(sf::Vector2f(20.0f, 20.0f));
    sf::CircleShape circle;

    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y)
            if (::map[x][y] == WALL)
            {
                rectangle.setPosition(x * 20 + 50, y * 20 + 50);
                rectangle.setFillColor(sf::Color(255, 255, 255, 240));
                window.draw(rectangle);
            }
            else if (::map[x][y] == POINTS)
            {
                circle.setRadius(2.5f);
                circle.setPosition(x * 20 + 57.5f, y * 20 + 57.5f);
                circle.setFillColor(sf::Color(255, 255, 255, 200));
                window.draw(circle);
            }
            else if (::map[x][y] == COIN)
            {
                circle.setRadius(5.0f);
                circle.setPosition(x * 20 + 55.0f, y * 20 + 55.0f);
                circle.setFillColor(sf::Color::Yellow);
                window.draw(circle);
            }
            else if (::map[x][y] == PLAYER)
            {
                sf::Texture pacman;
                pacman.loadFromFile("Resources/player.png");
                sf::Sprite character;
                character.setTexture(pacman);
                character.setTextureRect(sf::IntRect(0, 0, 16, 16));
                character.setPosition(x * 20 + 52.0f, y * 20 + 52.0f);
                window.draw(character);
            }
}
void *game(void *argument)
{
    sf::RenderWindow window(sf::VideoMode(900, 500), "Pac Man");
    sf::Texture wallpaper;
    wallpaper.loadFromFile("Resources/Wallpaper.jpg");
    sf::Sprite img(wallpaper);
    img.setScale(0.75f, 0.83f);
    generate_map();
    sf::Clock clock;
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Resources/player.png");
    PacPlayer player;

    pthread_t playerThread;
    while (window.isOpen())
    {
        player.frame_time += clock.getElapsedTime().asSeconds();
        clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear();
        window.draw(img);

        pthread_create(&playerThread, NULL, Player, (void *)&player);
        pthread_join(playerThread, NULL); // Handle player input
        render_map(window);

        window.display();
    }

    for (unsigned int i = 0; i < width; ++i)
        delete[] ::map[i];
    delete[] ::map;

    pthread_exit(0);
}

void *Player(void *argument)
{
    PacPlayer *player = (PacPlayer *)argument;
    player->handleInput();
    pthread_exit(0);
}