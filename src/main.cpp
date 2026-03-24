#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

const int TILE_SIZE = 80;
const int BOARD_SIZE = 8;

std::string getPieceKey(Piece p)
{
    std::string key = "";

    if (p.color == PieceColor::White)
        key += "w";
    else
        key += "b";

    if (p.type == PieceType::King)
        key += "K";
    else if (p.type == PieceType::Queen)
        key += "Q";
    else if (p.type == PieceType::Rook)
        key += "R";
    else if (p.type == PieceType::Bishop)
        key += "B";
    else if (p.type == PieceType::Knight)
        key += "N";
    else if (p.type == PieceType::Pawn)
        key += "P";

    return key;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 640), "Chess");

    // load textures
    std::map<std::string, sf::Texture> textures;
    std::string colors = "wb";
    std::string pieces = "KQRBNP";
    for (char c : colors)
        for (char p : pieces)
        {
            std::string key = "";
            key += c;
            key += p;
            textures[key].loadFromFile("Assets/" + key + ".png");
        }

    for (auto &t : textures)
    {
        if (t.second.getSize().x == 0)
            std::cout << "Failed to load: " << t.first << std::endl;
        else
            std::cout << "Loaded: " << t.first << std::endl;
    }

    Game game;
    sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    sf::RectangleShape highlight(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    highlight.setFillColor(sf::Color(0, 255, 0, 100));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                int col = event.mouseButton.x / TILE_SIZE;
                int row = event.mouseButton.y / TILE_SIZE;

                if (row >= 0 && row < 8 && col >= 0 && col < 8)
                    game.handleClick(row, col);
            }
        }

        window.clear();

        // draw board
        for (int row = 0; row < BOARD_SIZE; row++)
        {
            for (int col = 0; col < BOARD_SIZE; col++)
            {
                if ((row + col) % 2 == 0)
                    tile.setFillColor(sf::Color(240, 217, 181));
                else
                    tile.setFillColor(sf::Color(181, 136, 99));

                tile.setPosition(col * TILE_SIZE, row * TILE_SIZE);
                window.draw(tile);

                // draw piece
                Piece p = game.getBoard().getPiece(row, col);
                if (p.type != PieceType::empty)
                {
                    std::string key = getPieceKey(p);
                    sf::Sprite sprite;
                    sprite.setTexture(textures[key]);

                    float scaleX = (float)TILE_SIZE / textures[key].getSize().x;
                    float scaleY = (float)TILE_SIZE / textures[key].getSize().y;
                    sprite.setScale(scaleX, scaleY);

                    sprite.setPosition(col * TILE_SIZE, row * TILE_SIZE);
                    window.draw(sprite);
                }
            }
        }

        window.display();
    }

    return 0;
}