#pragma once
#include "raylib.h"
#ifndef PLAYER_H
#define PLAYER_H

void playerHop(float deltaTime);
Rectangle getPlayerRect();
void setPlayerRect(Vector2 cordinate);
Texture2D getPlayer();
void loadPlayer();
Vector2 getPlayerPosition();
Rectangle getPlayerCollider();
void resetPlayer();

extern Vector2 playerPostion;
extern Rectangle playerRect;
extern Texture2D player;
extern Rectangle playerCollider;

extern Vector2 initPos;
#endif
