#pragma once
#include "functions.h"

class rigidBody;

class Particle {
public:

	sf::Vector2f pastPos;
	sf::Vector2f acceleration;

	sf::CircleShape rep;

	float mass;

	Particle();
	Particle(sf::Vector2f spawnPos, float r, sf::Color col, float m);
	
	void update(sf::Vector2f g, float dt);
	void collision(std::vector<Particle>& particles, std::vector<rigidBody> &rigids);
};
