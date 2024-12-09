#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "Components.h"

class PositionComponent : public Component {
public:

	PositionComponent() {
		xpos = ypos = 0;
	}

	PositionComponent(int x, int y) {
		xpos = x;
		ypos = y;
	}

	int x() { return xpos; }
	int y() { return ypos; }

	void init() override {
		xpos = 0;
		ypos = 0;
	}

	void update() override {
		xpos++;
		ypos++;
	}

	void setPos(int x, int y) {
		xpos = x;
		ypos = y;
	}
private:
	int xpos, ypos;
};

#endif /* POSITION_COMPONENT_H */