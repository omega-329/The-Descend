#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "The Descent");

    sf::CircleShape player(20.f);  // radius = 20
    player.setFillColor(sf::Color::White);
    player.setPosition({400, 300});  // start center-ish

    float speed = 200.f;

    sf::Clock clock;

    while (window.isOpen()) {

        while (std::optional event=window.pollEvent()) {

            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float dt = clock.restart().asSeconds();

        sf::Vector2f pos = player.getPosition();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            pos.y -= speed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            pos.y += speed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            pos.x -= speed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            pos.x += speed * dt;

        // keep inside window bounds
        float radius = player.getRadius();
        if (pos.x < 0) pos.x = 0;
        if (pos.y < 0) pos.y = 0;
        if (pos.x + radius * 2 > window.getSize().x)
            pos.x = window.getSize().x - radius * 2;
        if (pos.y + radius * 2 > window.getSize().y)
            pos.y = window.getSize().y - radius * 2;

        player.setPosition(pos);

        window.clear(sf::Color::Black);
        window.draw(player);
        window.display();
    }
}