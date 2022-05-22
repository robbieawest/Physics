#include "functions.h"

Particle::Particle()
	: mass(0.0f), pastPos(0.0f, 0.0f), acceleration(0.0f, 0.0f), rigidType(-1), movable(true), linking(0)
{}

Particle::Particle(sf::Vector2f spawnPos, float r, sf::Color col, float m, int rig)
	: mass(m), pastPos(spawnPos), acceleration(0.0f, 0.0f), rigidType(rig), movable(true), linking(0)
{
	rep.setRadius(r);
	rep.setOrigin(r, r);
	rep.setPosition(spawnPos);
	rep.setFillColor(col);

}

void Particle::update(sf::Vector2f g, float dt) {
	//This only concerns gravity as a force, not collisions
	//Collisions impact past and current position
	if (movable) {

		acceleration = g;

		sf::Vector2f newPos = 2.0f * rep.getPosition() - pastPos + acceleration * dt * dt; //Verlet integration
		pastPos = rep.getPosition();
		rep.setPosition(newPos);
	}
}

void Particle::collision(std::vector<Particle> &particles, std::vector<rigidBody> &rigids, std::vector<Link> &links, sf::Vector2f g, float dt) { //To add objects in
	
	//First, check collisions with outer boundaries

	if (rep.getPosition().y + rep.getRadius() > 900) {

		float diff = 900.0f - (rep.getPosition().y + rep.getRadius());
		rep.move(sf::Vector2f(0.0f, diff));
		pastPos.y = rep.getPosition().y + (rep.getPosition().y - pastPos.y);
		pastPos.y -= diff * 0.8f;//0.4f is for loss of kinetic energy on collision which reflects the physics of a realistic, inelastic ball

		//Implement friction on x
		float xDiff = rep.getPosition().x - pastPos.x;

		float Fr = pythag(g) / mass * 0.01f * dt; //Friction force where 0.01 is the coefficient of friction
		if (xDiff < 0.0f) Fr *= -1.0f;
		
		bool t = xDiff < 0.0f;
		if (xDiff != 0.0f) 	xDiff -= Fr;
		if ((xDiff < 0.0f) != t) xDiff = 0.0f;
				
		pastPos.x = rep.getPosition().x - xDiff;//Rearrange for pastPos.x
	}
	else if (rep.getPosition().y - rep.getRadius() < 0) {//Rest just uses theory from above^

		float diff = 0.0f - (rep.getPosition().y - rep.getRadius());
		rep.move(sf::Vector2f(0.0f, diff));
		pastPos.y = rep.getPosition().y + (rep.getPosition().y - pastPos.y);
		pastPos.y -= diff * 0.2f;
	}
	if (rep.getPosition().x + rep.getRadius() > 900) {

		float diff = 900.0f - (rep.getPosition().x + rep.getRadius());
		rep.move(sf::Vector2f(diff, 0.0f));
		pastPos.x = rep.getPosition().x + (rep.getPosition().x - pastPos.x);
		pastPos.x -= diff * 0.2f;
	}
	else if (rep.getPosition().x - rep.getRadius() < 0) {

		float diff = 0.0f - (rep.getPosition().x - rep.getRadius());
		rep.move(sf::Vector2f(diff, 0.0f));
		pastPos.x = rep.getPosition().x + (rep.getPosition().x - pastPos.x);
		pastPos.x -= diff * 0.2f;

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
			
			if(movable)
				rep.move(d * movingDistance * (x.mass / totalMass));
			if(x.movable)
				x.rep.move(-d * movingDistance * (mass / totalMass));		

			// I dont think there needs to be any consideration of momentum direction and such in collisions
			// It seems like verlet handles that implicitly

		
		}
	}	

	//Check collision with rigid bodies
	for (auto& x : rigids) {
		x.particleCollision(this);
	}
	

	//Now check collision with links...

	for (auto& x : links) {
		x.particleCollision(particles, *this);
	}
}
