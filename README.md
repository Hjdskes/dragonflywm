DragonflyWM
============================
DragonflyWM is a nimble, fast and modern tiling window manager for X, based on DWM.

It has some EWMH compliancy: third party panels such as tint2 are supported (albeit rudimentary), as are simple window switchers.
Pager support (virtual desktops) is partly there; the tag system of DWM is at fault here. See [this patch][url] for an explanation.

More EWMH support, such as real desktops (with names), minimizing of clients and struts are on the TODO list. Feel free to help out!

DragonflyWM is, as said, based on DWM. Everything draw and font related has been removed. Some patches are included:

*pertag2;
*useless gaps;
*bottom stack layout;
*chat layout;
*xkeycodetokeysim fix;
*attachaside;
*urgentborder;
*push;
*netwmdemandsattention.

All credit for these go to their original authors. For more licensing, see LICENSE.

Installation
------------
In order to build DragonflyWM you need the Xlib header files.

DragonflyWM is configured through config.h, so edit this first.
Afterwards enter the following command to build and install:

    # make clean install
    
Bugs
----

For any bug or request [fill an issue][bug] on [GitHub][ghp].

  [bug]: https://github.com/Unia/dragonfly/issues
  [ghp]: https://github.com/Unia/dragonfly

License
-------
See LICENSE for licensing information.
