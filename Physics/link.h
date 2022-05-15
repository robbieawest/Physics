#pragma once
#include "functions.h"

class Link {
public:
	sf::RectangleShape rep;
	float mass;
	float anchorL;
	int ip1, ip2;

	Link();
	Link(std::vector<Particle*> &linkedParticles, int i1, int i2, float m);

	void pullParticles(std::vector<Particle*>& lp);
	void updateRect(std::vector<Particle*> &lp);
};
