/*=============================================================================

  PHAS0100ASSIGNMENT2: PHAS0100 Assignment 2 Gravitational N-body Simulation

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "nbsimBasicTypes.h"

namespace nbsim {
	Particle::Particle(Eigen::Vector3d pos, Eigen::Vector3d vel) {
		_pos = pos;
		_vel = vel;
	}
	Eigen::Vector3d Particle::getPosition() {
		return _pos;
	}
	Eigen::Vector3d Particle::getVelocity() {
		return _vel;
	}
	void Particle::integrateTimestep(Eigen::Vector3d acceleration, double timestep) {
		_pos += _vel * timestep;
		_vel += acceleration * timestep;
	}

} // end namespace
