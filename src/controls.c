#include "../header/controls.h"

struct Controls controls;
struct Controls getControls() {
	if (IsKeyPressed(KEY_SPACE)) {
		controls.space = true;
	}

	else {
		controls.space = false;
	}

	if (IsKeyReleased(KEY_SPACE)) {
		controls.space = false;
	}

	return controls;
};

void resetControls() {
	controls.up = 0;
	controls.down = 0;
	controls.left = 0;
	controls.right = 0;
}