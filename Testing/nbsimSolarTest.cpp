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

TEST_CASE( "1: isApprox Test", "[PartA]" ) {
	Eigen::Vector3d v1(1,0,0), v2(0,1,0), exp(0,1,0);
	REQUIRE(v2.isApprox(exp));
}

TEST_CASE( "2: 2 pi Test", "[PartA]" ) {
	Eigen::Vector3d v1(1,0,0), v2(0,1,0), exp(0,1,0), zero(0,0,0), v1_1(1.00001, 0.00001, 0);
	nbsim::Particle parA(v1, v2);
	REQUIRE(parA.getPosition() == v1);
	REQUIRE(parA.getVelocity() == v2);

	double ts = 0.000001;
	for (double t=0; t<2*M_PI; t+=ts) {
		Eigen::Vector3d acc = -parA.getPosition();
		parA.integrateTimestep(acc, ts);
	}
		std::cout << parA.getPosition() << std::endl;
		REQUIRE(v1.isApprox(v1_1));
	REQUIRE(parA.getPosition().isApprox(v1));


}
