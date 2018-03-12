#ifndef __INC_DISPLAYMODE_H
#define __INC_DISPLAYMODE_H

enum DisplayMode {
  NONE,
  RED,
  GREEN,
  BLUE
};

DisplayMode& operator++(DisplayMode& mode) {
  if (mode == BLUE) {
    mode = NONE;
  } else {
    mode = static_cast<DisplayMode>(mode + 1);
  }
  return mode;
}

DisplayMode operator++(DisplayMode& mode, int) {
  DisplayMode rVal = mode;
  ++mode;
  return rVal;
}

#endif
