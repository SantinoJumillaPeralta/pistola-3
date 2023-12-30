#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

class Civil {
private:
    sf::Texture civilTexture;
    sf::Sprite civilSprite;
    bool visible;
    sf::Clock civilClock;
    float disappearTime;

public:
    Civil() {
        if (!civilTexture.loadFromFile("Nueva carpeta (9)/Textura/civil.jpg")) {
            std::cout << "Error al cargar la textura de Civil" << std::endl;
            // Manejar error si la carga de la textura falla
        }
        civilSprite.setTexture(civilTexture);
        civilSprite.setPosition(400, 300);
        visible = true;
        disappearTime = 15.0f;
    }

    void updateVisibility() {
        if (civilClock.getElapsedTime().asSeconds() > disappearTime) {
            if (visible) {
                visible = false;
            }
            civilClock.restart();
        }
    }

    bool isVisible() const {
        return visible;
    }

    void draw(sf::RenderWindow& window) {
        if (visible) {
            window.draw(civilSprite);
        }
    }
};

class EnemyManager {
private:
    sf::Texture enemyTexture;
    sf::Sprite enemy1;
    sf::Sprite enemy2;
    bool enemy1Visible;
    bool enemy2Visible;

public:
    EnemyManager() : enemy1Visible(true), enemy2Visible(true) {
        if (!enemyTexture.loadFromFile("Nueva carpeta(9)/Textura/enemy.jpg")) {
            std::cout << "Error al cargar la textura de Enemy" << std::endl;
            // Manejar error si la carga de la textura falla
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
};

class Player {
private:
    int lives;
    int score;
    bool enemy1Visible;
    bool enemy2Visible;
    bool civilVisible;
    sf::Clock enemyAttackClock;
    sf::Clock civilClock;
    sf::Texture enemyTexture;
    sf::Texture otherTexture;
    sf::Texture civilTexture;
    sf::Sprite enemy1;
    sf::Sprite enemy2;
    sf::Sprite other;
    sf::Sprite civil;
    sf::Font font;
    sf::Text livesText;
    sf::Text scoreText;
    sf::Clock gameOverClock;
    sf::Text gameOverText;
    float enemyAttackTime;
    float civilDisappearTime;

public:
    Player() : lives(9), score(0), enemy1Visible(true), enemy2Visible(true), civilVisible(true), enemyAttackTime(15.0f), civilDisappearTime(15.0f) {
        if (!enemyTexture.loadFromFile("Nueva carpeta (9)/Textura/enemy.jpg") || !otherTexture.loadFromFile("ruta/a/other.jpg") || !civilTexture.loadFromFile("ruta/a/civil.jpg") || !font.loadFromFile("ruta/a/arial.ttf")) {
            std::cout << "Error cargando texturas o fuente!" << std::endl;
            // Manejar error si la carga de texturas o fuente falla
        }

        enemy1.setTexture(enemyTexture);
        enemy2.setTexture(enemyTexture);
        other.setTexture(otherTexture);
        civil.setTexture(civilTexture);

        enemy1.setPosition(50, 50);
        enemy2.setPosition(300, 200);
        other.setPosition(600, 100);
        civil.setPosition(400, 300);

        livesText.setFont(font);
        livesText.setCharacterSize(20);
        livesText.setPosition(10, 10);

        scoreText.setFont(font);
        scoreText.setCharacterSize(20);
        scoreText.setPosition(600, 10);

        gameOverText.setFont(font);
        gameOverText.setCharacterSize(50);
        gameOverText.setPosition(250, 250);
        gameOverText.setString("GAME OVER");
    }

    void handleEvents(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                if (enemy1.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)) && enemy1Visible) {
                    enemy1Visible = false;
                    score += 10;
                }

                if (enemy2.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)) && enemy2Visible) {
                    enemy2Visible = false;
                    score += 10;
                }

                if (civil.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)) && civilVisible) {
                    civilVisible = false;
                    score -= 5;
                }
            }
        }
    }

    void update() {
        if (enemyAttackClock.getElapsedTime().asSeconds() > enemyAttackTime) {
            if (enemy1Visible) {
                lives--;
                enemy1Visible = false;
            }

            if (enemy2Visible) {
                lives--;
                enemy2Visible = false;
            }

            enemyAttackClock.restart();
        }

        if (civilClock.getElapsedTime().asSeconds() > civilDisappearTime) {
            if (civilVisible) {
                civilVisible = false;
            }
            civilClock.restart();
        }
    }

    void draw(sf::RenderWindow& window) {
        window.clear();

        if (enemy1Visible) {
            window.draw(enemy1);
        }

        if (enemy2Visible) {
            window.draw(enemy2);
        }

        window.draw(other);

        livesText.setString("Vidas: " + std::to_string(lives));
        scoreText.setString("Puntuacion: " + std::to_string(score));

        window.draw(livesText);
        window.draw(scoreText);

        if (civilVisible) {
            window.draw(civil);
        }

        window.display();
    }

    bool isGameOver() {
        return (lives <= 0 || enemyAttackClock.getElapsedTime().asSeconds() > enemyAttackTime);
    }