/*=============================================================================

PHAS0100ASSIGNMENT2: PHAS0100 Assignment 2 Gravitational N-body Simulation

Copyright (c) University College London (UCL). All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include <CLI11.hpp>
#include <nbsimBasicTypes.h>
#include <nbsimMyFunctions.h>
#include <nbsimExceptionMacro.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "nbsimSolarSystemData.ipp"

// Example, header-only library, included in project for simplicity's sake.
#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>

#define YEAR2SEC 365*24*60*60
/**
 * \brief Demo file to check that includes and library linkage is correct.
 */
int main(int argc, char** argv)
{

	int returnStatus = EXIT_FAILURE;
	int ibody = 0;
	Eigen::Vector3d pos, vel;
	int mass;
	std::shared_ptr<nbsim::MassiveParticle> planet[9];
	double ts = 0.000274 * YEAR2SEC, dur = 1* YEAR2SEC;


	std::string names[9];
	CLI::App app{"Solar system simulator"};
	//app.require_subcommand(1);


	CLI11_PARSE(app, argc, argv);

	/* Init planets */
	for (int ibody=0; ibody <9; ibody++) {
		//std::cout << nbsim::solarSystemData[ibody].name << std::endl;
		names[ibody] = nbsim::solarSystemData[ibody].name;
		mass = nbsim::solarSystemData[ibody].mu / GRAV;
		pos = nbsim::solarSystemData[ibody].position;
		vel = nbsim::solarSystemData[ibody].velocity;
		planet[ibody] = std::make_shared<nbsim::MassiveParticle>(pos, vel, mass);
	}
	/* Add mutual attraction */
	for (int i=0; i <9; i++) {
		for (int j=0; j<9; j++) {

			//printf("Adding %d to %d\n", j, i);
			if (i != j) planet[i]->addAttractor(planet[j]);
		}
	}

	/* simulate */
	for (double t=0; t<dur; t+=ts) {
		for (int i=0; i<9; i++) {
			planet[i]->calculateAcceleration();
		}
		for (int i=0; i<9; i++) {
			planet[i]->integrateTimestep(ts);
		}
	}
	/* output res */
	for (int i=0; i<9; i++) {
		std::cout << names[i] << std::endl;
		std::cout << planet[i]->getPosition() << std::endl;
	}

	return 0;
}
