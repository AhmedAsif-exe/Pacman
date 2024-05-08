#include "Dependencies.h"
#define COIN = 68;
#define POINTS = 236;
#define ENEMIES = 85;
#define WALL = 0;
#define SPAWN = 105;
int **map;
int width;
int height;
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
    }
}
void render_map(sf::RenderWindow &window)
{
    sf::RectangleShape rectangle(sf::Vector2f(20.0f, 20.0f));

    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y)
            if (!map[x][y])
            {
                rectangle.setPosition(x * 20, y * 20 + 50);
                rectangle.setFillColor(sf::Color(255, 255, 255, 200));
                window.draw(rectangle);
            }
}
void *game(void *argument)
{
    sf::RenderWindow window(sf::VideoMode(800, 500), "Pac Man");
    sf::Texture wallpaper;
    wallpaper.loadFromFile("Resources/Wallpaper.jpg");
    sf::Sprite img(wallpaper);
    img.setScale(0.75f, 0.83f);

    generate_map();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear();
        window.draw(img);
        render_map(window);
        window.display();
    }
    for (unsigned int i = 0; i < width; ++i)
        delete[] ::map[i];
    delete[] ::map;
    pthread_exit(0);
}