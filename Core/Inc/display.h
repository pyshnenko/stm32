#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdbool.h>

	bool checkPhoto (void);
void draw(int xs, int ys, int line);
void startTable (void);
void scrollBar(int total, int position);
void nrfState(bool status);
void startPage (void);
void rightButtonName (char *buf);
void leftButtonName (char *buf);
void clearCentralBox(void);
void centralBoxText(char *buf, int startLine, int len);
void focusButtonIcon (bool press);
void shootButtonIcon (bool press);
void photoCounter (int count);
void ssd1306_WriteIntOnCentralBox(int count, int xpos, int ypos);

#endif /* DISPLAY_H_ */