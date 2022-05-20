#include "functions.h"

int main() {

	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(900, 900), "Physics Engine", sf::Style::Default);
	window.setFramerateLimit(144);

	std::vector<Particle> particles;
	particles.reserve(1000); //Reserving memory stops pointers to particles from invalidating due to resizing vector on push_back(moving particles to different memory locations)
	//This stops it by just allocating space, so no reallocation is needed
	std::vector<rigidBody> rigids;
	std::vector<Link> links;//links outside of rigid bodies

	sf::Vector2f gravity(0.0f, 300.0f);

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

	//Colour alternation for rainbow pattern
	int tCol = 0.0f;


	while (window.isOpen()) {
		sf::Event evnt;

		while (window.pollEvent(evnt)) {

			switch (evnt.type) {

			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:

				if (addingType == 0) {
					createParticle(window, particles, tCol, true);
				}
				else if (addingType == 1) {
					createRigid(window, rigids, particles);
				}
				else if (addingType == 2) {
					createParticle(window, particles, tCol, false);
				}
				else if (addingType == 3) {
					createParticle(window, particles, tCol, true);
					links.push_back(Link(particles, particles.size() - 1, particles.size() - 2, 1.0f));
				}
				else if (addingType == 4) {
					createParticle(window, particles, tCol, false);
					links.push_back(Link(particles, particles.size() - 1, particles.size() - 2, 1.0f));
				}

				break;
			case sf::Event::TextEntered:
				if (evnt.text.unicode == 't') {
					addingType++;
					addingType = addingType == 5 ? 0 : addingType;
				}
			}
			
		}

		//Update delta time
		dt = dtClock.getElapsedTime().asSeconds();
		dtClock.restart();
		tCol += dt;

		//Text updates
		timeStep.setString("TimeStep: " + std::to_string(dt));
		fps.setString("FPS: " + std::to_string(1.0f / dt));

		step(particles, rigids, links, gravity, dt);

		window.clear();
		
		for (auto& x : links) {
			window.draw(x.rep);
		}

		for (auto& x : particles) {
			window.draw(x.rep);
		}

		for (auto& x : rigids) {
			for (auto& y : x.links) {
				window.draw(y.rep);
			}
		}

		
		window.draw(fps);
		window.draw(timeStep);

		window.display();
	}

	return 0;
}