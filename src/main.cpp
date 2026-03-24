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

    // load font
    sf::Font font;
    if (!font.loadFromFile("Assets/Inter_24pt-SemiBold.ttf"))
        std::cout << "Failed to load font!" << std::endl;

    Game game;
    sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));

    while (window.isOpen())
    {
        // 1. handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && !game.isGameOver())
            {
                int col = event.mouseButton.x / TILE_SIZE;
                int row = event.mouseButton.y / TILE_SIZE;
                if (row >= 0 && row < 8 && col >= 0 && col < 8)
                    game.handleClick(row, col);
            }
        }

        window.clear();

        // 2. draw board and pieces
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

        // 3. draw winning screen
        if (game.isGameOver())
        {
            // dark overlay
            sf::RectangleShape overlay(sf::Vector2f(640, 640));
            overlay.setFillColor(sf::Color(0, 0, 0, 150));
            window.draw(overlay);

            // white box
            sf::RectangleShape box(sf::Vector2f(400, 120));
            box.setFillColor(sf::Color(255, 255, 255, 220));
            box.setPosition(120, 260);
            window.draw(box);

            // text
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(42);
            text.setFillColor(sf::Color::Black);

            if (game.getWinner() == PieceColor::White)
                text.setString("White Wins!");
            else if (game.getWinner() == PieceColor::Black)
                text.setString("Black Wins!");
            else
                text.setString("Stalemate!");

            sf::FloatRect textBounds = text.getLocalBounds();
            text.setPosition(320 - textBounds.width / 2, 290);
            window.draw(text);
        }

        window.display();
    }

    return 0;
}