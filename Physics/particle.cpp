#include "functions.h"

Particle::Particle(sf::Vector2f spawnPos, float r, sf::Color col, float m)
	: mass(m), pastPos(spawnPos), acceleration(0.0f, 0.0f)
{
	rep.setRadius(r);
	rep.setOrigin(r, r);
	rep.setPosition(spawnPos);
	rep.setFillColor(col);

}

void Particle::update(sf::Vector2f g, float dt) {
	//This only concerns gravity as a force, not collisions
	//Collisions impact past and current position
	
	acceleration = g;

	sf::Vector2f newPos = 2.0f * rep.getPosition() - pastPos + acceleration * dt * dt;
	pastPos = rep.getPosition();
	rep.setPosition(newPos);
}

void Particle::collision(std::vector<Particle> &particles) { //To add objects in
	
	//First, check collisions with outer boundaries

	if (rep.getPosition().y + rep.getRadius() > 900) {

		float diff = 900.0f - (rep.getPosition().y + rep.getRadius());
		rep.move(sf::Vector2f(0.0f, diff));
		pastPos.y = rep.getPosition().y + (rep.getPosition().y - pastPos.y);
		pastPos.y -= diff * 0.5f;
	}
	else if (rep.getPosition().y - rep.getRadius() < 0) {

		float diff = 0.0f - (rep.getPosition().y - rep.getRadius());
		rep.move(sf::Vector2f(0.0f, diff));
		pastPos.y = rep.getPosition().y + (rep.getPosition().y - pastPos.y);
		pastPos.y -= diff * 0.5f;

	}
	if (rep.getPosition().x + rep.getRadius() > 900) {

		float diff = 900.0f - (rep.getPosition().x + rep.getRadius());
		rep.move(sf::Vector2f(diff, 0.0f));
		pastPos.x = rep.getPosition().x + (rep.getPosition().x - pastPos.x);
		pastPos.x -= diff * 0.5f;
	}
	else if (rep.getPosition().x - rep.getRadius() < 0) {

		float diff = 0.0f - (rep.getPosition().x - rep.getRadius());
		rep.move(sf::Vector2f(diff, 0.0f));
		pastPos.x = rep.getPosition().x + (rep.getPosition().x - pastPos.x);
		pastPos.x -= diff * 0.5f;

	}

	

	//Next, check collisions with other particles
	
	for (auto& x : particles) {
		sf::Vector2f d = rep.getPosition() - x.rep.getPosition();
		float distance = pythag(d);
		if (distance != 0.0f && distance <= rep.getRadius() + x.rep.getRadius()) {//If distance = 0.0f then it is the same particle, we definitely do not want to collide a particle with itself, the simulation would blow up
			//Collision

			//Move each particle along collision axis(d) until they are not touching
			//Particles should move relative to the mass ratio between them both

			
			
			float totalMass = mass + x.mass;
			float movingDistance = rep.getRadius() + x.rep.getRadius() - distance;

			d /= pythag(d); //Turn into unit vector
			
			rep.move(d * movingDistance * (x.mass / totalMass));
			x.rep.move(-d * movingDistance * (mass / totalMass));		

			// I dont think there needs to be any consideration of momentum direction and such in collisions
			// It seems like verlet handles that implicitly

		
		}
	}
	
	

}
