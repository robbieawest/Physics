#include "functions.h"

int main() {

	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(900, 900), "Physics Engine", sf::Style::Default);
	window.setFramerateLimit(144);

	std::vector<Particle> particles;

	sf::Vector2f gravity(0.0f, 100.0f);

	int addingType = 0;

	//delta time
	sf::Clock dtClock;
	float dt;


	//texts
	sf::Font calibri;
	calibri.loadFromFile("calibri.ttf");

	sf::Text fps;
	fps.setFillColor(sf::Color::Red);
	fps.setCharacterSize(35.0f);
	fps.setFont(calibri);

	sf::Text timeStep;
	timeStep.setFillColor(sf::Color::Red);
	timeStep.setPosition(0.0f, 35.0f);
	timeStep.setFont(calibri);


	while (window.isOpen()) {
		sf::Event evnt;

		while (window.pollEvent(evnt)) {

			switch (evnt.type) {

			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:

				if (addingType == 0) {
					createParticle(window, particles);
				}
			}
		}

		//Update delta time
		dt = dtClock.getElapsedTime().asSeconds();
		dtClock.restart();

		//Text updates
		timeStep.setString("TimeStep: " + std::to_string(dt));
		fps.setString("FPS: " + std::to_string(1.0f / dt));

		step(particles, gravity, dt);

		window.clear();

		for (auto& x : particles) {
			window.draw(x.rep);
		}

		window.draw(fps);
		window.draw(timeStep);

		window.display();
	}

	return 0;
}