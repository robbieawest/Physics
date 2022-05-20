#pragma once
#include "functions.h"

class rigidBody;
class Link;

class Particle {
public:

	sf::Vector2f pastPos;
	sf::Vector2f acceleration;

	sf::CircleShape rep;

	float mass;
	bool movable;

	int rigidType;
	int linking;

	Particle();
	Particle(sf::Vector2f spawnPos, float r, sf::Color col, float m, int rig);
	
	void update(sf::Vector2f g, float dt);
	void collision(std::vector<Particle>& particles, std::vector<rigidBody> &rigids, std::vector<Link> &links);
};
