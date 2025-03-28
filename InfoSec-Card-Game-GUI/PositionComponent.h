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

	}

	void update() override {
		
	}

	void setPos(int x, int y) {
		xpos = x;
		ypos = y;
	}
private:
	int xpos, ypos;
};

#endif /* POSITION_COMPONENT_H */