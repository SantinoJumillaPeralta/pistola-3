#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

class Civil {
private:
    sf::Texture civilTexture;
    sf::Sprite civilSprite;
    bool isVisible;
    sf::Clock civilClock;
    float disappearTime;

public:
    Civil() {
        if (!civilTexture.loadFromFile("civil.jpg")) {
            // Handle error if texture loading fails
        }
        civilSprite.setTexture(civilTexture);
        civilSprite.setPosition(400, 300);
        isVisible = true;
        disappearTime = 15.0f;
    }

    void updateVisibility() {
        if (civilClock.getElapsedTime().asSeconds() > disappearTime) {
            if (isVisible) {
                isVisible = false;
            }
            civilClock.restart();
        }
    }

    bool isVisible() const {
        return isVisible;
    }

    void draw(sf::RenderWindow& window) {
        if (isVisible) {
            window.draw(civilSprite);
        }
    }
};
        return EXIT_SUCCESS;
    }