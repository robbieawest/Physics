#pragma once
#include "functions.h"

class Link;

class rigidBody {
public:

	std::vector<Particle*> linkedParticles;

	std::vector<Link> links;//six links for rectangular hatching shape

	float fullMass;
	
	rigidBody();

	void evaluateLinks();
	void initialiseLinks();
	void particleCollision(Particle* p);
};
