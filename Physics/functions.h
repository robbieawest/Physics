#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "particle.h"
#include "rigid.h"
#include "link.h"

void vCout(sf::Vector2f a, std::string str);

float pythag(sf::Vector2f a);
void createParticle(sf::RenderWindow & window, std::vector<Particle> & particles, int &tCol);
void createRigidParticle(sf::Vector2f sp, float w, int t, std::vector<Particle> &particles, float m);
void createRigid(sf::RenderWindow &window, std::vector<rigidBody>& rigids, std::vector<Particle> &particles);
void step(std::vector<Particle> & particles, std::vector<rigidBody> &rigids, sf::Vector2f g, float dt);


