#include "Square.h"
#include "Line.h"


Square::Square()
{
}


Square::~Square()
{
}

void Square::addLine(Line *line) {
	lines.push_back(line);
}

bool Square::lineBelongsTo(Line *line) {
	for (Line *currentLines : lines) {
		if (currentLines == line) {
			return true;
		}
	}

	return false;
}

std::pair<Square*, Square*> Square::splitByLine(Line *line) {
	Square *sq1 = new Square();
	Square *sq2 = new Square();

	return std::make_pair(sq1, sq2);
}