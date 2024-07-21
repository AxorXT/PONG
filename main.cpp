#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "STAR PONG!");

    //Creamos la imagen o textura de  Darth Vader
    sf::Texture DarthTexture;
    if (!DarthTexture.loadFromFile("../Darth_vader.png")) {
        std::cerr << "Failed to load image" << std::endl;
        std::cerr << "Error de carga" << std::endl;
    }

    //creamos el sprite
    sf::Sprite Darth(DarthTexture);
    Darth.setScale(0.19f, 0.19f);
    Darth.setPosition(410, 230);

    //Creamos la imagen o textura de  Luke Skywalker
    sf::Texture LukeTexture;
    if (!LukeTexture.loadFromFile("../luke.png")) {
        std::cerr << "Failed to load image" << std::endl;
        std::cerr << "Error de carga" << std::endl;
    }

    //creamos el sprite
    sf::Sprite Luke(LukeTexture);
    Luke.setScale(0.5f, 0.5f);
    Luke.setPosition(300, 230);

    //Creamos la imagen o textura de la estrella de la meurte
    sf::Texture EstrellasTexture;
    if (!EstrellasTexture.loadFromFile("../estrella_muerte.jpg")) {
        std::cerr << "Failed to load image" << std::endl;
        std::cerr << "Error de carga" << std::endl;
    }

    //creamos el sprite
    sf::Sprite Star(EstrellasTexture);
    Star.setScale(1.2f, 1.2f);
    Star.setPosition(90, 0);

    //Creamos la imagen o textura de  baby yoda
    sf::Texture BebeYodaTexture;
    if (!BebeYodaTexture.loadFromFile("../baby-yoda.png")) {
        std::cerr << "Failed to load image" << std::endl;
        std::cerr << "Error de carga" << std::endl;
    }

    //creamos el sprite
    sf::Sprite BebeYoda(BebeYodaTexture);
    BebeYoda.setScale(0.02f, 0.02f);
    BebeYoda.setPosition(400, 230);

    //Division de juego
    sf::RectangleShape division;
    division.setSize(sf::Vector2f(7, 600));
    division.setPosition(400, 0);

    //Creamos la primera barra
    sf::RectangleShape barra1;
    barra1.setSize(sf::Vector2f(15, 130));
    barra1.setPosition(30, 20);
    barra1.setFillColor(sf::Color::Blue);

    //Creamos la segunda barra
    sf::RectangleShape barra2;
    barra2.setSize(sf::Vector2f(15, 130));
    barra2.setPosition(750, 20);
    barra2.setFillColor(sf::Color::Red);

    //Le damos velocidad al sprite
    sf::Vector2f bolaVelocity(0.10f, 0.10f);
    float BarraAumento = 0.3f;
    float BolaAumento = 0.007f;

    //Agregamos la puntuacion con los textos
    int Puntuacion1 = 0;
    int Puntuacion2 = 0;

    sf::Font font;
    if (!font.loadFromFile("../arial.ttf")) {}

    //Texto del Jugador 1
    sf::Text Player1;
    Player1.setFont(font);
    Player1.setCharacterSize(30);
    Player1.setPosition(200, 10);

    //Texto del Jugador 2
    sf::Text Player2;
    Player2.setFont(font);
    Player2.setCharacterSize(30);
    Player2.setPosition(550, 10);

    while (window.isOpen()) {
        sf::Event event;

        //Movimiento de Barras W S
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && barra1.getPosition().y > 0) {
            barra1.move(0.f, -BarraAumento);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && barra1.getPosition().y < 480) {
            barra1.move(0.f, BarraAumento);
        }

        //Movimiento de Barras UP DOWN
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && barra2.getPosition().y > 0){
            barra2.move(0.f, -BarraAumento);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && barra2.getPosition().y < 480){
            barra2.move(0.f, BarraAumento);
        }

        //agregamos la velocidad de la bola
        BebeYoda.move(bolaVelocity);

        //agregamos la coalision con los bordes de arriba y abajo
        if (BebeYoda.getPosition().y < 0 || BebeYoda.getPosition().y > 560){
            bolaVelocity.y = -bolaVelocity.y;
        }

        // Colisión con la primera barra
        if (BebeYoda.getGlobalBounds().intersects(barra1.getGlobalBounds())) {
            bolaVelocity.x = -bolaVelocity.x;
        }

        // Colisión con la segunda barra
        if (BebeYoda.getGlobalBounds().intersects(barra2.getGlobalBounds())) {
            bolaVelocity.x = -bolaVelocity.x;
        }

        //Con esto detectamos cuando la pelota sale por los lados
        if (BebeYoda.getPosition().x < 0) {
            Puntuacion2++;
            BebeYoda.setPosition(395, 295);
            bolaVelocity.x = bolaVelocity.x > 0 ? bolaVelocity.x + BolaAumento : bolaVelocity.x - BolaAumento;
            bolaVelocity.y = bolaVelocity.y > 0 ? bolaVelocity.y + BolaAumento : bolaVelocity.y - BolaAumento;
        }
        if (BebeYoda.getPosition().x > 790) {
            Puntuacion1++;
            BebeYoda.setPosition(395, 295);
            bolaVelocity.x = bolaVelocity.x > 0 ? bolaVelocity.x + BolaAumento : bolaVelocity.x - BolaAumento;
            bolaVelocity.y = bolaVelocity.y > 0 ? bolaVelocity.y + BolaAumento : bolaVelocity.y - BolaAumento;
        }

        //Actualizamos los puntajes
        std::stringstream Puntaje1;
        Puntaje1 << Puntuacion1;
        Player1.setString(Puntaje1.str());

        std::stringstream Puntaje2;
        Puntaje2 << Puntuacion2;
        Player2.setString(Puntaje2.str());


        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(Star);
        window.draw(Luke);
        window.draw(Darth);
        window.draw(BebeYoda);
        window.draw(division);
        window.draw(barra1);
        window.draw(barra2);
        window.draw(Player1);
        window.draw(Player2);
        window.display();
    }

    return 0;
}