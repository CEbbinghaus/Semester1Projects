#pragma once
#include"KeyHandler.h"

void KeyHandler::init() {

}

void KeyHandler::start() {
	handling = true;
	while (handling) {
		handleInput();
	}
}

void KeyHandler::handleInput() {
	char character = getch();
	if (keys.find(character) != keys.end()) {
		keys[character]();
	}
	if (keys.find(7) != keys.end()) {
		keys[7]();
	}
}
void KeyHandler::stop() {
	handling = false;
}

void KeyHandler::on(char character, function<void()> handler) {
	keys[character] = handler;
}
char KeyHandler::subscribeToEvent() {
	return getch();
}