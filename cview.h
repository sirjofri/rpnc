#ifndef CVIEW_H
#define CVIEW_H
#define TYPE int

#include <xcb/xcb.h>
#include <string>

class mycalc;

#include "mycalc.h"

class cview
{
public:
	cview(mycalc *mc);
	~cview();
private:
	mycalc *m;
	const char *display;
	xcb_connection_t *c;
	xcb_screen_t *screen;
	xcb_drawable_t win;
	xcb_gcontext_t gc;
	TYPE bufnum;
	void setup();
	static void text_draw(xcb_connection_t *c, xcb_screen_t *screen, xcb_window_t window, int16_t x1, int16_t y1, const char* label);
	static xcb_gcontext_t gc_font_get(xcb_connection_t *c, xcb_screen_t *screen, xcb_window_t window, const char *font_name);
};

#endif
