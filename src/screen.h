#ifndef _SCREEN_H_
#define _SCREEN_H_

extern char _cursor_x;
extern char _cursor_y;

void setCursorPosition(char x, char y);
void backupCursor();
void advanceCursor();
void blankScreen();

#endif /* _SCREEN_H_ */
