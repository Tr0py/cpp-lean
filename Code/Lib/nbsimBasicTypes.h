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
	class Particle
	{
		private:
			Eigen::Vector3d _pos;
			Eigen::Vector3d _vel;
		public:
			Particle(Eigen::Vector3d, Eigen::Vector3d);
			~Particle() {};
			Eigen::Vector3d getPosition();
			Eigen::Vector3d getVelocity();
			void integrateTimestep(Eigen::Vector3d acceleration, double timestep);
	};

} // end namespace

#endif
