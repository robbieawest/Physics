#include "functions.h"

float pythag(sf::Vector2f a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

//Function to create rigid body

//Function to create solitary particle
void createParticle(sf::RenderWindow& window, std::vector<Particle> &particles) {

	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Color col(rand() % 255, rand() % 255, rand() % 255);
	float r = rand() % 25 + 10.0f;
	float m = r / 2.0f;

	particles.push_back(Particle(mousePos, r, col, m));
}


//Full Step
void step(std::vector<Particle>& particles, sf::Vector2f g, float dt) {
	
	for (auto& x : particles) {
		x.update(g, dt);
	}

	for (auto& x : particles) {
		x.collision(particles);
	}
}

