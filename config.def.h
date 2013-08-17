/* see LICENSE for copyright and license */

#include <X11/XF86keysym.h>

#ifndef CONFIG_H
#define CONFIG_H

#define MOD1            Mod1Mask
#define MOD4            Mod4Mask
#define CONTROL         ControlMask
#define SHIFT           ShiftMask

/** generic settings **/
#define MASTER_SIZE     0.70      /* size of the master area */
#define USELESSGAP      4         /* the size of the useless gap in pixels */ 
#define SHOW_PANEL      True      /* show panel by default on exec */
#define PANEL_HORIZ     True      /* True means panel is horizontal */
#define TOP_PANEL       False     /* False means panel is on bottom */
#define PANEL_HEIGHT    40        /* 0 for no space for panel, thus no panel */
#define ATTACH_ASIDE    True      /* False means new window is master */
#define FOLLOW_WINDOW   False     /* follow the window when moved to a different desktop */
#define FOLLOW_MOUSE    True      /* focus the window the mouse just entered */
#define CLICK_TO_FOCUS  False     /* focus an unfocused window when clicked  */
#define FOCUS_BUTTON    Button3   /* mouse button to be used along with CLICK_TO_FOCUS */
#define BORDER_WIDTH    1         /* window border width */
#define FOCUS           "#FF950E" /* focused window border color    */
#define UNFOCUS         "#3F3F3F" /* unfocused window border color  */
#define MINWSZ          50        /* minimum window size in pixels  */
#define DEFAULT_DESKTOP 0         /* the desktop to focus initially */
#define DESKTOPS        4         /* number of desktops - edit DESKTOPCHANGE keys to suit */

/**
 * layouts and names for each desktop
 */
static const int initlayouts[] = { TILE, TILE, TILE, MONOCLE };
static const char *desknames[] = { "Web", "Chat", "Term", "Work", NULL };

/**
 * open applications to specified desktop with specified mode.
 * if desktop is negative, then current is assumed
 */
static const AppRule rules[] = { \
    /*  class     instance  title  desktop  follow  float */
    { "Firefox",    NULL,   NULL,     0,    False,  False },
    { "MPlayer",    NULL,   NULL,     3,    True,   True  },
    { "Gimp",       NULL,   NULL,     3,    False,  False },
};

/* helper for spawning shell commands */
#define SHCMD(cmd) {.com = (const char*[]){"/bin/sh", "-c", cmd, NULL}}

/**
 * custom commands
 */
static const char *menu[]    = { "dmenu_run", "-f", "-p", "Run:", NULL };
static const char *term[]    = { "xterm", NULL };
static const char *browser[] = { "firefox", NULL };

#define DESKTOPCHANGE(K,N) \
    {  MOD1,             K,              change_desktop, {.i = N}}, \
    {  MOD1|ShiftMask,   K,              client_to_desktop, {.i = N}},

/**
 * keyboard shortcuts
 */
static Key keys[] = {
    /* modifier          key               function        argument */
    {  MOD1|CONTROL,     XK_r,             quit,           {.i = 0}}, /* quit with exit value 0 */
    {  MOD1|CONTROL,     XK_q,             quit,           {.i = 1}}, /* quit with exit value 1 */
    {  MOD1|CONTROL,     XK_b,             togglepanel,    {NULL}},
    {  MOD1,             XK_space,         togglefloat,    {NULL}},
    {  MOD1,             XK_u,             focusurgent,    {NULL}},
    {  MOD1,             XK_q,             killclient,     {NULL}},
    {  MOD1,             XK_Return,        swap_master,    {NULL}},
    {  MOD1,             XK_j,             next_win,       {NULL}},
    {  MOD1,             XK_k,             prev_win,       {NULL}},
    {  MOD1,             XK_Down,          move_down,      {NULL}},
    {  MOD1,             XK_Up,            move_up,        {NULL}},
    {  MOD1,             XK_bracketleft,   resize_master,  {.i = -10}}, /* decrease size in px */
    {  MOD1,             XK_bracketright,  resize_master,  {.i = +10}}, /* increase size in px */
    {  MOD1|SHIFT,       XK_bracketleft,   resize_stack,   {.i = -10}}, /* shrink   size in px */
    {  MOD1|SHIFT,       XK_bracketright,  resize_stack,   {.i = +10}}, /* grow     size in px */
    {  MOD1,             XK_Left,          rotate,         {.i = -1}},
    {  MOD1,             XK_Right,         rotate,         {.i = +1}},
    {  MOD1|SHIFT,       XK_Left,          rotate_filled,  {.i = -1}},
    {  MOD1|SHIFT,       XK_Right,         rotate_filled,  {.i = +1}},
    {  MOD1,             XK_Tab,           last_desktop,   {NULL}},
    {  MOD1,             XK_t,             switch_mode,    {.i = TILE}},
    {  MOD1,             XK_m,             switch_mode,    {.i = MONOCLE}},
    {  MOD1,             XK_b,             switch_mode,    {.i = BSTACK}},
    {  MOD1,             XK_g,             switch_mode,    {.i = GRID}},
    {  MOD1,             XK_f,             switch_mode,    {.i = FLOAT}},
    {  MOD4,             XK_j,             moveresize,     {.v = (int []){   0,  25,   0,   0 }}}, /* move down  */
    {  MOD4,             XK_k,             moveresize,     {.v = (int []){   0, -25,   0,   0 }}}, /* move up    */
    {  MOD4,             XK_l,             moveresize,     {.v = (int []){  25,   0,   0,   0 }}}, /* move right */
    {  MOD4,             XK_h,             moveresize,     {.v = (int []){ -25,   0,   0,   0 }}}, /* move left  */
    {  MOD4|SHIFT,       XK_j,             moveresize,     {.v = (int []){   0,   0,   0,  25 }}}, /* height grow   */
    {  MOD4|SHIFT,       XK_k,             moveresize,     {.v = (int []){   0,   0,   0, -25 }}}, /* height shrink */
    {  MOD4|SHIFT,       XK_l,             moveresize,     {.v = (int []){   0,   0,  25,   0 }}}, /* width grow    */
    {  MOD4|SHIFT,       XK_h,             moveresize,     {.v = (int []){   0,   0, -25,   0 }}}, /* width shrink  */
    {  MOD1,             XK_r,             spawn,          {.com = menu}},
    {  MOD1,             XK_1,             spawn,          {.com = term}},
    {  MOD1,             XK_2,             spawn,          {.com = browser}},
       DESKTOPCHANGE(    XK_F1,                             0)
       DESKTOPCHANGE(    XK_F2,                             1)
       DESKTOPCHANGE(    XK_F3,                             2)
       DESKTOPCHANGE(    XK_F4,                             3)
};

/**
 * mouse shortcuts
 */
static Button buttons[] = {
    {  MOD1,    Button1,     mousemotion,   {.i = MOVE}},
    {  MOD1,    Button2,     togglefloat,   {0}},
    {  MOD1,    Button3,     mousemotion,   {.i = RESIZE}},
};
#endif

/* vim: set expandtab ts=4 sts=4 sw=4 : */
