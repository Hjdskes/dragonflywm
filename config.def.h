/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

#define MODKEY Mod1Mask
#define MONKEY Mod4Mask
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} },

/* appearance */
static const char normbordercolor[] = "#444444";
static const char selbordercolor[]  = "#005577";
static const char urgbordercolor[]  = "#DC322F";
static const char chatclient[]      = "Skype";
static const unsigned int barheight = 40;       /* bar geometry */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 2;        /* Gap pixel between windows */
static const unsigned int snap      = 2;        /* snap pixel */
static const float mfact            = 0.70;     /* factor of master area size [0.05..0.95] */
static const int nmaster            = 1;        /* number of clients in master area */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = False;    /* False means bottom bar */
static const Bool resizehints       = False;    /* True means respect size hints in tiled resizals */

/* layouts */
static const Layout layouts[] = {
   /* arrange  gaps */
	{ tile,    True },
	{ chat,    True },
	{ bstack,  True },
	{ monocle, False },
	{ NULL,    False },
};

/* tagging */
static const Tag tags[] = {
	/* name	 layout       mfact	nmaster */
	{ "1",   &layouts[0], -1,	-1 },
	{ "2",   &layouts[1], 0.80, -1 },
	{ "3",   &layouts[0], -1,	-1 },
	{ "4",   &layouts[3], -1,	-1 },
};

/* rules */
static const Rule rules[] = {
    /*WM_CLASS              WM_CLASS    WM_NAME
      class                 instance    title               tags mask   isfloating  monitor */
    { "Firefox",            NULL,       NULL,               1,          False,      -1 },
    { "MPlayer",            NULL,       NULL,               1 << 3,     True,       -1 },
    { "Gimp",               NULL,       NULL,               1 << 3,     False,      -1 },
};

/* commands */
static const char *dmenu[]   = { "dmenu_run", "-f", NULL };
static const char *term[]    = { "gnome-terminal", NULL };
static const char *browser[] = { "firefox", NULL };

/* shortcuts */
static Key keys[] = {
	/* modifier                 key        function        argument */
	{ MODKEY,                   XK_r,                       spawn,          {.v = dmenu } },
	{ MODKEY,                   XK_1,                       spawn,          {.v = term } },
	{ MODKEY,                   XK_2,                       spawn,          {.v = browser } },
	{ MODKEY|ControlMask,       XK_q,                       quit,           {0} },
	{ MODKEY,                   XK_Tab,                     focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,         XK_Tab,                     focusstack,     {.i = -1 } },
	{ MODKEY,                   XK_Return,                  zoom,           {0} },
	{ MODKEY,                   XK_dead_grave,              view,           {0} },
	{ MODKEY,                   XK_q,                       killclient,     {0} },
	{ MODKEY,                   XK_bracketleft,             setmfact,       {.f = -0.05} },
	{ MODKEY,                   XK_bracketright,            setmfact,       {.f = +0.05} },
	{ MODKEY,                   XK_equal,                   incnmaster,     {.i = +1 } },
	{ MODKEY,                   XK_minus,                   incnmaster,     {.i = -1 } },
	{ MODKEY,                   XK_space,                   setlayout,      {0} },
	{ MODKEY,                   XK_Up,                      pushup,         {0} },
	{ MODKEY,                   XK_Down,                    pushdown,       {0} },
	{ MODKEY|ShiftMask,         XK_f,                       togglefloating, {0} },
	{ MODKEY,                   XK_t,                       setlayout,      {.v = &layouts[0] } },
	{ MODKEY,                   XK_c,                       setlayout,      {.v = &layouts[1] } },
	{ MODKEY,                   XK_b,                       setlayout,      {.v = &layouts[2] } },
	{ MODKEY,                   XK_m,                       setlayout,      {.v = &layouts[3] } },
	{ MODKEY,                   XK_f,                       setlayout,      {.v = &layouts[4] } },
	TAGKEYS(                    XK_F1,                      0)
	TAGKEYS(                    XK_F2,                      1)
	TAGKEYS(                    XK_F3,                      2)
	TAGKEYS(                    XK_F4,                      3)
	{ MODKEY,                   XK_a,                       view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,         XK_a,                       tag,            {.ui = ~1 } },
	{ MONKEY,                   XK_Left,                    focusmon,       {.i = -1 } },
	{ MONKEY,                   XK_Right,                   focusmon,       {.i = +1 } },
	{ MONKEY|ShiftMask,         XK_Left,                    tagmon,         {.i = -1 } },
	{ MONKEY|ShiftMask,         XK_Right,                   tagmon,         {.i = +1 } },
};

/* button definitions */
/* click can be ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};

