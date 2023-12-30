#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

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
        if (!enemyTexture.loadFromFile("Nueva carpeta(9)\\Textura\\enemy.jpg") || !otherTexture.loadFromFile("C:\\Users\\santino\\Desktop\\Nueva carpeta (9)\\Textura\\other.jpg") || !civilTexture.loadFromFile("C:\\Users\\santino\\Desktop\\Nueva carpeta (9)\\Textura\\civil.jpg") || !font.loadFromFile("C:\\Users\\santino\\Desktop\\Nueva carpeta (9)\\Textura\\arial.ttf")) {
            std::cout << "Error cargando texturas o fuente!" << std::endl;
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

    // Cargar la textura del cursor personalizado
    sf::Texture cursorTexture;
    if (!cursorTexture.loadFromFile("ruta/a/mira.jpg")) {
        std::cout << "Error cargando el archivo del cursor!" << std::endl;
    }

    // Crear un sprite para el cursor personalizado
    sf::Sprite cursorSprite(cursorTexture);

    // Establecer el cursor para la ventana del juego
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
    window.setMouseCursorVisible(false); // Ocultar el cursor predeterminado
    window.setMouseCursorGrabbed(true); // Capturar el cursor del sistema

    // Bucle principal del juego
    while (window.isOpen()) {
        handleEvents(window);
        update();
        draw(window);

        if (isGameOver()) {
            displayGameOver(window);
        }
    }
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
    return (lives <= 0 || enemyAttackClock.getElapsedTime().asSeconds() > 420);
}

void displayGameOver(sf::RenderWindow& window) {
    if (!gameOverClock.isRunning()) {
        gameOverClock.restart();
    }

    if (gameOverClock.getElapsedTime().asSeconds() < 10) {
        window.clear();
        window.draw(gameOverText);
        window.display();
    }
    else {
        std::cout << "Juego terminado. Puntuacion final: " << score << std::endl;
        // Reset values and return to menu
        lives = 9;
        score = 0;
        enemy1Visible = true;
        enemy2Visible = true;
        civilVisible = true;
        enemyAttackClock.restart();
        gameOverClock.restart();
        // Return to menu or perform any other necessary action
    }
}
return EXIT_SUCCESS;
}