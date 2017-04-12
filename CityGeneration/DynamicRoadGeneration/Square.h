#pragma once

#include <vector>
#include "../Libraries/glm/glm.hpp"
class Line;

class Square
{
public:
	Square();
	~Square();

	bool lineBelongsTo(Line *line);
	std::pair<Square*, Square*> splitByLine(Line *line);
	std::vector<Line *> getLines();
	bool pointBelongsTo(glm::vec2 point);

	Line *top;
	Line *left;
	Line *right;
	Line *bottom;
};

