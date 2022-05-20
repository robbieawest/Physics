#include "functions.h"

float pythag(sf::Vector2f a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

void vCout(sf::Vector2f a, std::string str) {
	if (str.size() > 0) {
		std::cout << str << ": " << a.x << " " << a.y << std::endl;
	}
	else {
		std::cout << a.x << " " << a.y << std::endl;
	}

}

//Function to create rigid body

//Function to create solitary particle
void createParticle(sf::RenderWindow& window, std::vector<Particle> &particles, int &tCol, bool mov) {

	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	float r = rand() % 25 + 10.0f;
	float m = r * 3.0f;


	//Update colour
	//use sin waves to simulate rainbow
	float PI = 3.1415926f;

	//This particular piece of code is from krazydad.com/tutorials/makecolours.php
	//Creates rainbow colours by stacking sin waves with different phases for each colour
	int red = sin(tCol) * 127.0f + 128.0f;
	int green = sin(tCol + 2) * 127.0f + 128.0f;
	int blue = sin(tCol + 4) * 127.0f + 128.0f;
	//

	particles.push_back(Particle(mousePos, r, sf::Color(red, green, blue), m, -1));
	particles[particles.size() - 1].movable = mov;
	
	tCol++;
	if (tCol == 32)tCol = 0;
}


//Full Step
void step(std::vector<Particle>& particles, std::vector<rigidBody> &rigids, std::vector<Link> &links, sf::Vector2f g, float dt) {

	//without sub-stepping particles will collapse into eachover if there is lots of pressure
	//substepping stops this by just repeating the step an appropiate amount until kinetic energy is properly evaulated(collision works)
	//delta time has to be divided proportional to the number of sub steps

	int coef = 5.0f; //As the coefficient increases the amount at which stability to dt increases increases
	//*Have to be careful to not make coefficient too high, as the delta time will increase with the increased substeps in which the substeps keeps growing while simulation stays constant
	//^ The reason why this does not happen with small coefficient values is because the float is truncated to integer, providing a sort of cap
	int substeps = 8 * (1.0f - coef / 100.0f + dt * coef);//If dt > 0.001(fps < 100) substeps will start to increase (with truncation intended)
	std::cout << substeps << std::endl;
	//^ This suprisingly helps stability quite a lot
	dt /= substeps;
	for (int i = 0; i < substeps; i++) {

		for (auto& x : particles) {
			x.update(g, dt);
		}

		for (auto& x : particles) {
			x.collision(particles, rigids, links);
		}

		for (auto& x : rigids) {
			x.evaluateLinks();
		}

		for (auto& x : links) {
			x.pullParticles(particles);
		}
	}

	for (auto& x : rigids) {
		for (auto& y : x.links) {
			y.updateRect(x.linkedParticles);
		}
	}

	for (auto& x : links) {
		x.updateRect(particles);
	}
}

void createRigid(sf::RenderWindow &window, std::vector<rigidBody>& rigids, std::vector<Particle> &particles) {

	//This is fine for prob
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

	float width = 100.0f;
	

	if (mousePos.x - width / 2.0f >= 0 && mousePos.x + width / 2.0f <= 900 && mousePos.y - width / 2.0f >= 0 && mousePos.y + width / 2.0f <= 900) {//Boundary check with outsides
		//available to place

		float mass = 10.0f;



		for (int i = 0; i < 4; i++) {
			createRigidParticle(mousePos, width, i, particles, mass, rigids.size());
		}
		rigidBody tempBody;
		tempBody.fullMass = mass * 4.0f;

		for (int i = 4; i > 0; i--) {
			
			tempBody.linkedParticles[4 - i] = &particles[particles.size() - i];
		}

		tempBody.initialiseLinks();
		rigids.push_back(tempBody);
	}
	
}

void createRigidParticle(sf::Vector2f sp, float w, int t, std::vector<Particle> &particles, float m, int rigType) {


	switch (t)
	{
	case 0:

		particles.push_back(Particle(sp - sf::Vector2f(w / 2.0f, w / 2.0f), 5.0f, sf::Color(255, 255, 255), m, rigType));
		break;
	case 1:

		particles.push_back(Particle(sp - sf::Vector2f(-w / 2.0f, w / 2.0f), 5.0f, sf::Color(255, 255, 255), m, rigType));
		break;
	case 2:

		particles.push_back(Particle(sp - sf::Vector2f(-w / 2.0f, -w / 2.0f), 5.0f, sf::Color(255, 255, 255), m, rigType));
		break;
	case 3:

		particles.push_back(Particle(sp - sf::Vector2f(w / 2.0f, -w / 2.0f), 5.0f, sf::Color(255, 255, 255), m, rigType));
		break;
	}
	
}



