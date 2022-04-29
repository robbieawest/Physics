#include "functions.h"

float pythag(sf::Vector2f a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

//Function to create rigid body

//Function to create solitary particle
void createParticle(sf::RenderWindow& window, std::vector<Particle> &particles, int &tCol) {

	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	float r = rand() % 25 + 10.0f;
	float m = r * 3.0f;


	//Update colour
	//use sin waves to simulate rainbow
	float PI = 3.1415926f;

	//This particular piece of code is from krazydad.com/tutorials/makecolours.php
	//Creates rainbow colours by stacking sin waves with different phases for each colour
	int red = sin(tCol) * 127.0f + 128.0f;
	int green = sin(tCol + 2) * 127.0f + 128.0f;
	int blue = sin(tCol + 4) * 127.0f + 128.0f;
	//

	particles.push_back(Particle(mousePos, r, sf::Color(red, green, blue), m));
	
	tCol++;
	if (tCol == 32)tCol = 0;
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

