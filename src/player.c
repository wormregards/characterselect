#include "../header/player.h"
#include "../header/playerSprite.h"
#include "../header/controls.h"

Texture2D player;
Rectangle playerRect;
Vector2 playerPosition;
Rectangle playerCollider;
Vector2 initPos;

void loadPlayer() {
	Image image = {
		.data = PLAYERSPRITE_DATA,
		.width = PLAYERSPRITE_WIDTH,
		.height = PLAYERSPRITE_HEIGHT,
		.format = PLAYERSPRITE_FORMAT,
		.mipmaps = 1
	};

	playerRect.width = 32;
	playerRect.height = 32;
    
	player = LoadTextureFromImage(image);

    playerCollider.width = 32;
    playerCollider.height = 32;
}

Texture2D getPlayer() {
	return player;
}

Rectangle getPlayerRect() {
	return playerRect;
}

Vector2 getPlayerPosition() {
	return playerPosition;
}

Rectangle getPlayerCollider() {
    return playerCollider;
}

void resetPlayer() {
    playerPosition.x = 0;
    playerPosition.y = 0;
}

void playerHop(float deltaTime) {
    const float jumpHeight = 15.0f;
    static bool isJumping = false;
    static float startY = 0.0f;
    float targetY = startY - jumpHeight;
    float deltaY = targetY - playerPosition.y;

    playerPosition.x += 80 * deltaTime;
    // Check if the space bar is pressed and the player is not already jumping
    if (getControls().space) {
        isJumping = true;
        startY = playerPosition.y;
    }

    // If the player is jumping
    if (isJumping) {
        targetY = startY - jumpHeight;
        deltaY = targetY - playerPosition.y;
        if ((playerPosition.y - 1) <= targetY) {
            isJumping = false;
            startY = playerPosition.y;
        }
       
        playerPosition.y += deltaY * deltaTime * 18.0f;
    }
    else {
        // player falls
        playerPosition.y += 50.f * deltaTime;
    }

    playerCollider.x = playerPosition.x + 2;
    playerCollider.y = playerPosition.y + 1;
}

void setPlayerRect(Vector2 cordinate) {
    playerRect.x = 32 * cordinate.x;
    playerRect.y = 32 * cordinate.y;
}