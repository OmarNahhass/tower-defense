#pragma once

/*

	Class that generates the map for the Tower Defense game

*/

class Map
{
	private:	

	public:
		// Constructors, Destructors
		Map();
		virtual ~Map();

		// Functions
		void update();
		void render();
};

