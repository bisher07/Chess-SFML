#include <SFML/Graphics.hpp>

const int TILE_SIZE = 80; // each square is 80x80 pixels
const int BOARD_SIZE = 8; // 8x8 board

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 640), "Chess");

    // create a square shape we'll reuse for every tile
    sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // draw the board
        for (int row = 0; row < BOARD_SIZE; row++)
        {
            for (int col = 0; col < BOARD_SIZE; col++)
            {

                // if row+col is even = light square, odd = dark square
                if ((row + col) % 2 == 0)
                    tile.setFillColor(sf::Color(240, 217, 181)); // light
                else
                    tile.setFillColor(sf::Color(181, 136, 99)); // dark

                // position the tile
                tile.setPosition(col * TILE_SIZE, row * TILE_SIZE);
                window.draw(tile);
            }
        }

        window.display();
    }

    return 0;
}