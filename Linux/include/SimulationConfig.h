/**
 * @file SimulationConfig.h
 * Configuration file with common parameters of the simulation.
 */

#pragma once

/* Simulation configuration */
namespace sim_config		
{
	inline constexpr float sim_freq = 100.0f;			/* Simulation frequency [Hz] */
	inline constexpr float sim_dt = 1.0f / sim_freq;	/* Simulation delta time [s] */

} // namespace sim_config

