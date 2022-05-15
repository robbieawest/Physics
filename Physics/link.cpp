#include "functions.h"

Link::Link() :mass(0.0f), anchorL(0.0f), ip1(-1), ip2(-1) {}

Link::Link(std::vector<Particle*> &linkedParticles, int i1, int i2, float m)
	:mass(m), ip1(i1), ip2(i2)
{
	sf::Vector2f d = linkedParticles[i2]->rep.getPosition() - linkedParticles[i1]->rep.getPosition();
	anchorL = pythag(d);

	rep.setSize(sf::Vector2f(anchorL, 3.0f));
	rep.setOrigin(1.5f, 0.0f);
	rep.setPosition(linkedParticles[i1]->rep.getPosition());
	rep.setFillColor(sf::Color(255, 255, 255, 150));
	rep.setOutlineColor(sf::Color(0, 0, 0));
	rep.setOutlineThickness(3.0f);
}

void Link::updateRect(std::vector<Particle*> &lp){
	sf::Vector2f diff = lp[ip2]->rep.getPosition() - lp[ip1]->rep.getPosition();
	diff /= pythag(diff);

	float theta = atan(diff.y / diff.x) * 180.0f / 3.1415926f;
	if (lp[ip2]->rep.getPosition().x >= lp[ip1]->rep.getPosition().x)theta += 180.0f;

	rep.setPosition(lp[ip2]->rep.getPosition());
	rep.setRotation(theta);
}


void Link::pullParticles(std::vector<Particle*>& lp) {
	//Simple math using vectors to model pulling & pushing of particles to fit link length
	sf::Vector2f d = lp[ip2]->rep.getPosition() - lp[ip1]->rep.getPosition();
	float dl = pythag(d);


	d /= dl; //normalise
	float diff = (anchorL - dl) * 0.5f;
	

	lp[ip1]->rep.move(-d * diff);
	lp[ip2]->rep.move(d * diff);
}
