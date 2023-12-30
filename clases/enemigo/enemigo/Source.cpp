#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

class EnemyManager {
private:
    sf::Texture enemyTexture;
    sf::Sprite enemy1;
    sf::Sprite enemy2;
    bool enemy1Visible;
    bool enemy2Visible;

public:
    EnemyManager() : enemy1Visible(true), enemy2Visible(true) {
        if (!enemyTexture.loadFromFile("enemy.jpg")) {
            // Handle error
        }

        enemy1.setTexture(enemyTexture);
        enemy2.setTexture(enemyTexture);

        enemy1.setPosition(50, 50);
        enemy2.setPosition(300, 200);
    }

    void handleMouseClick(sf::RenderWindow& window, int& playerScore) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        if (enemy1.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)) && enemy1Visible) {
            enemy1Visible = false;
            playerScore += 10;
        }

        if (enemy2.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)) && enemy2Visible) {
            enemy2Visible = false;
            playerScore += 10;
        }
    }

    void drawEnemies(sf::RenderWindow& window) {
        if (enemy1Visible) {
            window.draw(enemy1);
        }

        if (enemy2Visible) {
            window.draw(enemy2);
        }
    }

    void resetEnemies() {
        enemy1Visible = true;
        enemy2Visible = true;
    }

    return EXIT_SUCCESS;
}
