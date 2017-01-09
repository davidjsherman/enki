/*
   Enki - a fast 2D robot simulator
   Copyright © 2017 Nicolas Palard <nicolas.palard@etu.u-bordeaux.fr>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef RANDOM_WORLD_H
#define RANDOM_WORLD_H

#include <enki/PhysicalEngine.h>
#include <enki/robots/thymio2/Thymio2.h>
#include <enki/robots/e-puck/EPuck.h>
#include <enki/robots/s-bot/Sbot.h>
#include <enki/robots/marxbot/Marxbot.h>
#include <enki/robots/khepera/Khepera.h>

/*!	\file Randomizer.h
	\brief Header of 'random' module.
*/

namespace Enki
{
	const int MAX_ROBOTS = 30;
	const bool ONLY_THYMIOS = true;
	const int MAX_DYNAMIC_OBJECTS = 50;
	const bool ONLY_SIMPLE_SHAPES = true;
	const int MAX_HEIGHT = 800;
	const int MIN_HEIGHT = 200;
	const int MAX_WIDTH = 800;
	const int MIN_WIDTH = 200;
	const int MIN_RADIUS = 300;
	const int MAX_RADIUS = 500;

	const int NUMBER_OF_ROBOTS_TYPES = 5;
	enum ROBOT_TYPES { THYMIO2, EPUCK, SBOT, MARXBOT, KHEPERA };

	/*!
	  \brief Return a random Integer between min and max.
	  \param min the minimum
	  \param max the maximum
	  \pre min should be not equals to max
	  \return The generated Integer
	*/
	int randomNumber(int min, int max);

	/*!
	  \brief Generate randomly a Color.
	  \post The returned color should be compound with 4 float values between 0 a 1.
	  \return The generated PhysicalObject
	*/
	Color randomColor();

	/*!
	  \brief Generate randomly a PhysicalObject
	  \param w the world in which the object will spawn.
	  \pre w must have been initialized
	  \post The PhysicalObject should have his x,y in the given World.
	  \return The generated PhysicalObject
	*/
	PhysicalObject* randomObject(World* w);

	/*!
	  \brief Generic function used to create randomly any kind of robots
	  \param w the world in which the robots will spawn
	  \pre w must have been initialized
	  \return The generated robot
	*/
	Robot* randomRobot(World* w);

	/*!
	  \brief Generate randomly a Thymio2
	  \param w the world in which the thymio will spawn.
	  \pre w must have been initialized
	  \post The Thymio2 should have his x,y in the given World.
	*/
	Thymio2* randomThymio(World* w);

	/*!
	  \brief Generate randomly a EPuck
	  \param w the world in which the thymio will spawn.
	  \pre w must have been initialized
	  \post The EPuck should have his x,y in the given World.
	  \return The generated EPuck
	*/
	EPuck* randomEPuck(World* w);

	/*!
	  \brief Generate randomly a Sbot
	  \param w the world in which the thymio will spawn.
	  \pre w must have been initialized
	  \post The Sbot should have his x,y in the given World.
	  \return The generated Sbot
	*/
	Sbot* randomSbot(World* w);

	/*!
	  \brief Generate randomly a Marxbot
	  \param w the world in which the thymio will spawn.
	  \pre w must have been initialized
	  \post The Marxbot should have his x,y in the given World.
	  \return The generated Marxbot
	*/
	Marxbot* randomMarxbot(World* w);

	/*!
	  \brief Generate randomly a Khepera
	  \param w the world in which the thymio will spawn.
	  \pre w must have been initialized
	  \post The Khepera should have his x,y in the given World.
	  \return The generated Khepera
	*/
	Khepera* randomKhepera(World* w);

	/*!
	  \brief Generate randomly a World with some object inside it
	  \return The generated World
	*/
	World* randomWorld();
}

#endif
