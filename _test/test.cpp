//g++ -framework sfml-window -framework sfml-graphics -framework sfml-system -framework sfml-audio main.cpp -o main

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(480, 800), "Fighter");
    sf::Texture background;
    // Load background
    if (!background.loadFromFile("resources/images/background.png")){
        return EXIT_FAILURE;
    }
    sf::Sprite bg(background);
    // Load the plane image
    sf::Texture texture;
    if (!texture.loadFromFile("resources/images/plane.png")){
        return EXIT_FAILURE;
    }
    // Create a sprite with the texture of the plane
    sf::Sprite plane(texture);
    // Move the sprite to the bottom
    plane.setPosition(sf::Vector2f(200, 670));
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("resources/fonts/arial.ttf")){
        return EXIT_FAILURE;
    }
    sf::Text text("PHP is the best language in the world", font, 24);
    text.setPosition(sf::Vector2f(10, 400));
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("resources/audios/bgm.ogg")){
        return EXIT_FAILURE;
    }
    // Play the music
    music.setLoop(true);
    music.play();
    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();
        // Draw the background
        window.draw(bg);
        // Draw the sprite
        window.draw(plane);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}