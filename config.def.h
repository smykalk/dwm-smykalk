/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int gappx     = 8;       /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 2;        /* horizontal padding for statusbar */
static const char *fonts[]          = { "fontawesome:size=12", "monospace:size=11" };
static const char dmenufont[]       = "monospace:size=11";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_cyan2[]       = "#5e81ac";
static const char col_red[]         = "#bf616a";
static const char col_orange[]      = "#e0ca00";
static const char col_orange2[]     = "#a8a162";
static const char col1[]            = "#ffffff";
static const char col2[]            = "#ffffff";
static const char col3[]            = "#ffffff";
static const char col4[]            = "#ffffff";
static const char col5[]            = "#ffffff";
static const char col6[]            = "#ffffff";

enum { SchemeNorm, SchemeCol1, SchemeCol2, SchemeCol3, SchemeCol4,
       SchemeCol5, SchemeCol6, SchemeSel }; /* color schemes */

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]  = { col_gray3, col_gray1, col_gray2 },
	[SchemeCol1]  = { col1,      col_gray1, col_gray2 },
	[SchemeCol2]  = { col2,      col_gray1, col_gray2 },
	[SchemeCol3]  = { col3,      col_gray1, col_gray2 },
	[SchemeCol4]  = { col4,      col_gray1, col_gray2 },
	[SchemeCol5]  = { col5,      col_gray1, col_gray2 },
	[SchemeCol6]  = { col6,      col_gray1, col_gray2 },
	[SchemeSel]   = { col_gray4, col_cyan2,  col_red  },
};

static const char *const autostart[] = {
//	"picom", NULL,
	"nm-applet", NULL,
	"set-touchpad", NULL,
	"set-keyboard", NULL,
	"locker", NULL,
	"dualscreen", NULL,
    "sh", "-c", "hsetroot -cover ~/.local/share/wallpapers/1611701560276.jpg", NULL,
	"dwmblocks", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "8", "9" };

static const char browser[] = "firefox";
static const char terminal[] = "kitty";
static const char fileexp[] = "pcmanfm";
static const char mail[] = "thunderbird";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "firefox",  NULL,       NULL,       1,            0,           -1 },
	{ "kitty",    NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Pcmanfm",  NULL,       NULL,       1 << 2,       0,           -1 },
	{ "dolphin",  NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Code",    NULL,        NULL,       1 << 3,       0,           -1 },
	{ "Lispworks", NULL,      NULL,       1 << 3,       0,           -1 },
	{ "Spotify",  NULL,       NULL,       1 << 4,       0,           -1 },
	{ "electronplayer", NULL, NULL,       1 << 4,       0,           -1 },
	{ "Thunderbird", NULL,    NULL,       1 << 5,       0,           -1 },
    { "Microsoft Teams - Preview", NULL, NULL, 1 << 6,  0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { terminal, NULL };
static const char *browsercmd[]  = { browser, NULL };
static const char *fileexpcmd[]  = { fileexp, NULL };
static const char *spectaclecmd[] = { "spectacle", "-rbc", NULL };
static const char *lockcmd[]  = { "lock", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */

    // Update kblayout dwmblock when switching keyboard layout 
    { 0|ShiftMask,                  XK_Alt_L,  spawn,          SHCMD("sigdwmblocks 2") }, 

    // Spawning apps
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,	                    XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      spawn,          {.v = browsercmd} },
	{ MODKEY,                       XK_e,      spawn,          {.v = fileexpcmd } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = spectaclecmd } },

    // Lock screen
	{ MODKEY,                       XK_semicolon, spawn,       {.v = lockcmd} },

    // Brightness control
    { 0,                            XF86XK_MonBrightnessUp, spawn, SHCMD("brightness up && sigdwmblocks 1") }, 
    { 0,                            XF86XK_MonBrightnessDown, spawn, SHCMD("brightness down && sigdwmblocks 1") }, 

    // Volume control
    { 0,                            XF86XK_AudioRaiseVolume, spawn, SHCMD("volume up && sigdwmblocks 3") }, 
    { 0,                            XF86XK_AudioLowerVolume, spawn, SHCMD("volume down && sigdwmblocks 3") }, 
    { 0,                            XF86XK_AudioMute, spawn, SHCMD("volume toggle && sigdwmblocks 3") }, 
    { 0,                            XF86XK_AudioMicMute, spawn, SHCMD("toggle-mic") }, 

    // Window  movement
	{ MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = -1 } },
 	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = +1 } },
 	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = -1 } },

    // Increase/decrease master window count
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },

    // Resize master
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    
    // Move window to master
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
        
    // Switch between last two viewed tags
	{ MODKEY,                       XK_Tab,    view,           {0} },

    // Kill window
	{ MODKEY,                       XK_q,      killclient,     {0} },

    // Layouts
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    
    // Switch between last two used layouts
	{ MODKEY,                       XK_space,  setlayout,      {0} },

	{ MODKEY|ControlMask,           XK_space,  togglefloating, {0} },

    // View all tags
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },

    // Show window in all tags
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

    // Switch monitor focus
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },

    // Move window to left/right monitor
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

    // Exit dwm
	{ MODKEY|ControlMask,           XK_q,      quit,           {0} },

    // Restart dwm
    { MODKEY|ControlMask,           XK_r,      quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },

    // Middle mouse button on window title - move to master
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },

    // dwmblocks clicking
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },

    // Super + left click to drag a window, S + right click to resize a window
    // Super + right click to toggle floating
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },

    // Left click to view, Right click to view multiple tags
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },

    // Super + left click - move current window to selected tag
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },

    // Super + right click - display ("clone") current window in another tag
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

