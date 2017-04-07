#pragma once

#include <vector>
class Line;

class Square
{
private:
	std::vector<Line *> lines;
public:
	Square();
	~Square();

	void addLine(Line *line);
	bool lineBelongsTo(Line *line);
	std::pair<Square*, Square*> splitByLine(Line *line);
};

