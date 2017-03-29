/*
  Enki - a fast 2D robot simulator
  Copyright © 2017 Jimmy Gouraud <jimmy.gouraud@etu.u-bordeaux.fr>
  Copyright © 2017 Mathieu Lirzin <mathieu.lirzin@etu.u-bordeaux.fr>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Serialize.h"

namespace Enki
{
	using namespace std;
	
	std::vector<std::string> split(const string& str, const char separator)
	{
		std::vector<std::string> tab;
		int pos = -1;
		do
		{
			int begin = pos + 1;
			pos = str.find_first_of(separator, begin);
			tab.push_back(str.substr(begin, pos - begin));
		} while (pos != std::string::npos);
		// delete blank end
		tab.pop_back();
		return tab;
	}
	
}
