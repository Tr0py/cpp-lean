/*=============================================================================

  PHAS0100ASSIGNMENT2: PHAS0100 Assignment 2 Gravitational N-body Simulation

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef nbsimBasicTypes_h
#define nbsimBasicTypes_h

#include "nbsimWin32ExportHeader.h"
#include <Eigen/Dense>
#include <memory>
#include <iostream>
#include <stdlib.h>
#include <set>

#define GRAV 6.674e-11

/**
* \defgroup internal internal
* \brief Internal stuff, not for end-users.
*/

/**
* \defgroup types types
* \brief Package-wide data types.
*/

/**
* \defgroup utilities utilities
* \brief Groups of c-style functions.
*/

/**
* \defgroup applications applications
* \brief Small, end-user applications, most likely command line.
*/

/**
* \file nbsimBasicTypes.h
* \brief Defines types and typedefs used in this library.
* \ingroup types
*/

//! Single namespace for all code in this package
namespace nbsim
{
	/* PartA */
	class Particle
	{
		protected:
			Eigen::Vector3d _pos;
			Eigen::Vector3d _vel;
		public:
			Particle(Eigen::Vector3d, Eigen::Vector3d);
			~Particle() {};
			Eigen::Vector3d getPosition() const;
			Eigen::Vector3d getVelocity() const;
			void integrateTimestep(const Eigen::Vector3d acceleration, const double& timestep);
	};

	/* PartB */
	class MassiveParticle : public Particle
	{
		protected:
			Eigen::Vector3d _acc;
			const double _mass;
			std::set<std::shared_ptr<MassiveParticle>> _attractorSet;
		public:
			MassiveParticle(Eigen::Vector3d pos, Eigen::Vector3d vel, const double& m);
			~MassiveParticle() {};
			void calculateAcceleration();
			double getMu() const;
			void addAttractor(std::shared_ptr<MassiveParticle> attractor);
			void removeAttractor(std::shared_ptr<MassiveParticle> attractor);
			void integrateTimestep(const double& timestep);
	};


} // end namespace

#endif
