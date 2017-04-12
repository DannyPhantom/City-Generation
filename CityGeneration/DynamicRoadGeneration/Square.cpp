#include "Square.h"
#include "Line.h"


Square::Square()
{
}


Square::~Square()
{
}

bool Square::lineBelongsTo(Line *line) {
	if (line == top || line == left || line == right || line == bottom) {
		return true;
	}
	else {
		return false;
	}
}

std::pair<Square*, Square*> Square::splitByLine(Line *line) {
	Square *sq1 = new Square();
	Square *sq2 = new Square();

	if (line->isHorizontal()) {
		sq1->top = top;
		sq1->bottom = line;
		sq1->left = new Line(); sq1->left->start = *sq1->top->getLeft(); sq1->left->end = *line->getLeft();
		sq1->right = new Line(); sq1->right->start = *sq1->top->getRight(); sq1->right->end = *line->getRight();

		sq2->top = line;
		sq2->bottom = bottom;
		sq2->left = new Line(); sq2->left->start = *line->getLeft(); sq2->left->end = *sq2->bottom->getLeft();
		sq2->right = new Line(); sq2->right->start = *line->getRight(); sq2->right->end = *sq2->bottom->getRight();

		//delete left;
		//delete right;
	}
	else {
		sq1->left = left;
		sq1->right = line;
		sq1->top = new Line(); sq1->top->start = *sq1->left->getTop(); sq1->top->end = *line->getTop();
		sq1->bottom = new Line(); sq1->bottom->start = *sq1->left->getBot(); sq1->bottom->end = *line->getBot();

		sq2->left = line;
		sq2->right = right;
		sq2->top = new Line(); sq2->top->start = *line->getTop(); sq2->top->end = *sq2->right->getTop();
		sq2->bottom = new Line(); sq2->bottom->start = *line->getBot(); sq2->bottom->end = *sq2->right->getBot();

		//delete top;
		//delete bottom;
	}

	return std::make_pair(sq1, sq2);
}

std::vector<Line *> Square::getLines() {
	std::vector<Line *> lines;
	lines.push_back(top);
	lines.push_back(right);
	lines.push_back(left);
	lines.push_back(bottom);
	return lines;
}

bool Square::pointBelongsTo(glm::vec2 point) {
	return top->pointBelongsTo(point) || right->pointBelongsTo(point) || bottom->pointBelongsTo(point) || left->pointBelongsTo(point);
}