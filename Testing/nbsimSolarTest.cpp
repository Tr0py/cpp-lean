/*=============================================================================

  PHAS0100ASSIGNMENT2: PHAS0100 Assignment 2 Gravitational N-body Simulation

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "catch.hpp"
#include "nbsimCatchMain.h"
#include "nbsimBasicTypes.h"
#include "nbsimMyFunctions.h"
#include <iostream>
#include <Eigen/Dense>
#include <cmath>

/* precision for isApprox() */
#define PREC 0.01

TEST_CASE( "1: isApprox Test", "[PartA]" ) {
	Eigen::Vector3d v1(1,0,0), v2(0,1,0), exp(0,1.0001,0.0001);
	REQUIRE(v2.isApprox(exp, PREC));
}

TEST_CASE( "2: particle move test", "[PartA]" ) {
	Eigen::Vector3d v1(1,0,0), v2(0,1,0), exp(0,1,0), zero(0,0,0), v1_1(1.00001, 0.00001, 0);
	nbsim::Particle parA(v1, v2), parB(v1, v2), parC(v1, v2);
	/* Check if correctly initialized. */
	REQUIRE(parA.getPosition() == v1);
	REQUIRE(parA.getVelocity() == v2);
	double ts = 0.0001;
	/* a. no acceleration. */
	for (double t=0; t<2*M_PI; t+=ts) {
		parA.integrateTimestep(zero, ts);
	}
	/* xt should be x + v * t . */
	std::cout << parA.getPosition() << std::endl;
	REQUIRE(parA.getPosition().isApprox(v1 + v2 * 2*M_PI, PREC));

	/* b. constant acc. */
	for (double t=0; t<2*M_PI; t+=ts) {
		parB.integrateTimestep(v2, ts);
	}
	/* xt should be x + v*t + 0.5*a*t^2 */
	std::cout << parB.getPosition() << std::endl;
	std::cout << v1 + v2*2*M_PI + 0.5*v2*2*M_PI*2*M_PI << std::endl;
	REQUIRE(parB.getPosition().isApprox(v1 + v2*2*M_PI + 0.5*v2*2*M_PI*2*M_PI, PREC));

	/* c.  centripetal a=-x. */
	for (double t=0; t<2*M_PI; t+=ts) {
		Eigen::Vector3d acc = -parC.getPosition();
		parC.integrateTimestep(acc, ts);
	}
	std::cout << parC.getPosition() << std::endl;
	REQUIRE(parC.getPosition().isApprox(v1, PREC));

}

TEST_CASE("MassiveParticle test", "[PartA]") {
	Eigen::Vector3d x1(1,0,0), v1(0,0.5,0), x2(-1,0,0), v2(0,-0.5,0);
	std::shared_ptr<nbsim::MassiveParticle> mp0(new nbsim::MassiveParticle(x1, v1, 10)), 
											mp1(new nbsim::MassiveParticle(x1, v1, 1/GRAV)), 
											mp2(new nbsim::MassiveParticle(x2, v2, 1/GRAV));
	double ts = 0.0001, dur = 2*M_PI;
	/* check init */
	REQUIRE(mp0->getPosition().isApprox(x1));
	REQUIRE(mp0->getVelocity().isApprox(v1));
	/* a. no attractor test. */
	for (double t=0; t<dur; t+=ts) {
		mp0->integrateTimestep(ts);
	}
	/* xt should be x + v * t . */
	std::cout << mp0->getPosition() << std::endl;
	std::cout << x1 + v1 * dur << std::endl;
	REQUIRE(mp0->getPosition().isApprox(x1 + v1 * dur, PREC));

	/* b. gravitationally attract */
	mp1->addAttractor(mp2);
	mp2->addAttractor(mp1);
	std::cout << "mu" << mp1->getMu() << std::endl;
	for (double t=0; t<dur; t+=ts) {
		mp1->calculateAcceleration();
		mp1->integrateTimestep(ts);
		mp2->calculateAcceleration();
		mp2->integrateTimestep(ts);
	}
	/* distance should be the same */
	Eigen::Vector3d ro = (x1 - x2);
	Eigen::Vector3d r = (mp1->getPosition() - mp2->getPosition());
	std::cout << ro.norm() << std::endl;
	std::cout << r.norm() << std::endl;
	REQUIRE(abs(ro.norm() - r.norm()) < PREC);

}
