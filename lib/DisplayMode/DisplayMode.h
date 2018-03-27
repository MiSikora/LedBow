#ifndef __INC_LEDBOW_DISPLAYMODE_H
#define __INC_LEDBOW_DISPLAYMODE_H

enum DisplayMode {
  NONE,
  RED,
  GREEN,
  BLUE,
  VIOLET,
  YELLOW,
  CYAN,
  WHITE,
  RAINBOW,
  FOUNTAIN,
  NEON,
  FINAL_DISPLAY_MODE_ENTRY
};

inline DisplayMode& operator++(DisplayMode& mode) {
  mode = static_cast<DisplayMode>(mode + 1);
  if (mode == FINAL_DISPLAY_MODE_ENTRY) {
    mode = NONE;
  }
  return mode;
}

inline DisplayMode operator++(DisplayMode& mode, int) {
  DisplayMode rVal = mode;
  ++mode;
  return rVal;
}

#endif
