#include "Screen.h"

#include <iostream>

Screen* Screen::screen;

Screen::~Screen() {
  delete screen;
}

Screen* Screen::getScreen() {
  if(screen == nullptr) {
    screen = new Screen();
  }
  return screen;
}

void Screen::createImage(const int m, const int n) {
  this->m = m;
  this->n = n;
  clearImage();
}

void Screen::clearImage() {
  pixels = std::vector<char>(m*n, 'O');
}

void Screen::print() {
  for(int y = 0; y < n; y++) {
    for(int x = 0; x < m; x++) {
      std::cout << getPixelColour(x, y);
    }
    std::cout << '\n';
  }
}

void Screen::colourPixel(const int x, const int y, const char c) {
  pixels[y*m+x] = c;
}

void Screen::drawVertical(const int x, const int y1, const int y2, const char c) {
  for(int y = y1; y <= y2; y++) {
    screen->colourPixel(x, y, c);
  }
}

void Screen::drawHorizontal(const int x1, const int x2, const int y, const char c) {
  for(int x = x1; x <= x2; x++) {
    screen->colourPixel(x, y, c);
  }
}

void Screen::fillRegion(const int x, const int y, const char c) {
  const char fillColour = getPixelColour(x, y);
  colourPixel(x, y, c);
  auto fill = [&](const int nextX, const int nextY){
    if(checkIfInBounds(nextX, nextY) && hasColour(nextX, nextY, fillColour)) {
      fillRegion(nextX, nextY, c);
    }
  };

  fill(x, y-1);
  fill(x, y+1);
  fill(x-1, y);
  fill(x+1, y);
}

const bool Screen::hasColour(const int x1, const int y1, const char c) {
  return getPixelColour(x1, y1) == c;
}

const char Screen::getPixelColour(const int x, const int y) {
  return pixels[y*m+x];
}

const bool Screen::checkIfInBounds(const int x, const int y) {
  return x >= 0 && x < m && y >= 0 && y < n;
}
