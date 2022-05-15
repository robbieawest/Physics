#include "functions.h"


void rigidBody::evaluateLinks() {

	//Update particle positions based off of links

	for (auto& x : links) {
		x.pullParticles(linkedParticles);
	}

}


void rigidBody::initialiseLinks() {
	//make links

	links.push_back(Link(linkedParticles, 0, 1, 2.0f)); //Horizontals
	links.push_back(Link(linkedParticles, 1, 2, 2.0f));
	links.push_back(Link(linkedParticles, 2, 3, 2.0f));
	links.push_back(Link(linkedParticles, 3, 0, 2.0f));
	links.push_back(Link(linkedParticles, 0, 2, 2.0f)); //Diags
	links.push_back(Link(linkedParticles, 1, 3, 2.0f));

}
void rigidBody::particleCollision(Particle* p) {

	//Find closest side using closest point checker

	int closestSide = -1;
	sf::Vector2f closestD(9999.0f, 9999.0f);

	for (int i = 0; i < linkedParticles.size(); i++) {

		if (linkedParticles[i] != p && pythag(linkedParticles[i]->rep.getPosition() - p->rep.getPosition()) < pythag(closestD)) {
			closestSide = i;
			closestD = linkedParticles[i]->rep.getPosition() - p->rep.getPosition();
		}
	}

	int i1 = closestSide - 1, i2 = closestSide + 1, int nClosest = -1;//Get points indexes opposite of the sides connected
	i1 = i1 < 0 ? 3 : i1;
	i2 = i2 > 3 ? 0 : i2; //Confine into boundaries

	//Closest of the two new points will be the other point of the line which is closest
	closestD = linkedParticles[i2]->rep.getPosition() - p->rep.getPosition();
	if (linkedParticles[i1] != p && pythag(linkedParticles[i1]->rep.getPosition() - p->rep.getPosition()) < pythag(closestD)) {
		nClosest = i1;
	}
	else {
		nClosest = i2;
	}

	//Now that we have the closest and the next closest, we can now check for a collision between the points of a rectangle
	//where W = point diameter and L = position diff


}


rigidBody::rigidBody() 
: linkedParticles(4, nullptr)
{}

