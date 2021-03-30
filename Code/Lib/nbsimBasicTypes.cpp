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
	Eigen::Vector3d Particle::getPosition() const {
		return _pos;
	}
	Eigen::Vector3d Particle::getVelocity() const {
		return _vel;
	}
	void Particle::integrateTimestep(const Eigen::Vector3d acceleration, const double& timestep) {
		_pos += _vel * timestep;
		_vel += acceleration * timestep;
	}

	/* MassiveParticle */
	MassiveParticle::MassiveParticle(Eigen::Vector3d pos, 
									Eigen::Vector3d vel,
									const double& m):Particle(pos, vel), _mass(m) {}
	double MassiveParticle::getMu() const {
		return _mass * GRAV;
	}
	void MassiveParticle::addAttractor(std::shared_ptr<MassiveParticle> attractor) {
		_attractorSet.insert(attractor);
	}
	void MassiveParticle::removeAttractor(std::shared_ptr<MassiveParticle> attractor) {
		_attractorSet.erase(attractor);
	}
	void MassiveParticle::calculateAcceleration() {
		_acc << 0, 0, 0;
		for (auto attractor : _attractorSet) {
			Eigen::Vector3d r = this->getPosition() - attractor->getPosition();
			_acc += -attractor->getMu() 
				/ (r.transpose()*r)
				* r.normalized();
		}
	}

	void MassiveParticle::integrateTimestep(const double& timestep) {
		_pos += _vel * timestep;
		_vel += _acc * timestep;
	}

} // end namespace
