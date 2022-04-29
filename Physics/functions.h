#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "particle.h"
#include "rigid.h"
#include "link.h"

float pythag(sf::Vector2f a);
void createParticle(sf::RenderWindow & window, std::vector<Particle> & particles, int &tCol);
void step(std::vector<Particle> & particles, sf::Vector2f g, float dt);


