#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "particle.h"
#include "rigid.h"
#include "link.h"

void vCout(sf::Vector2f a, std::string str);

float pythag(sf::Vector2f a);
void createParticle(sf::RenderWindow & window, std::vector<Particle> & particles, int &tCol, bool mov);
void createRigidParticle(sf::Vector2f sp, float w, int t, std::vector<Particle> &particles, float m, int rigType);
void createRigid(sf::RenderWindow &window, std::vector<rigidBody>& rigids, std::vector<Particle> &particles);
void step(std::vector<Particle> & particdles, std::vector<rigidBody> &rigids, std::vector<Link> &links, sf::Vector2f g, float dt);

bool operator!=(Particle& p1, Particle& p2);



