# KDE Connect - DBus Interface and Qt Application

*This is NOT a project from the KDE devs, it's a homebrew project for personal use*

This project provides a Qt binding wrapper library of KDE Connect's DBus interface, and provides a simple Qt GUI application which using the wrapper library.

## Should I use...

Short answer: probably not.

### the KDE Connect DBus binding Qt library provided by this project?

Not sure but probably not. Since KDE Connect project itself doesn't provide a **public** C++/Qt binding library, so I did this by simply using the Qt's XML to CPP tool for create the binding. You should consider using the code from the original [KDE Connect](https://github.com/KDE/kdeconnect-kde/) project if possible. If you can, maybe make the KDE Connect project also provide a public C++/Qt library is a better idea.

### the Qt application from this project?

No for now. It's still lack a lots of features than the official one. The original goal of the project is make a standalone application to make KDE Connect works the same as the KDE Connect plasmoid (panel for overview unread notifications, etc.) under non-KDE environment (it's [DDE](https://wiki.archlinux.org/index.php/Deepin_Desktop_Environment) and Windows for my case). I found the KDE Connect **plugin** DBus interfaces are missing under **Windows** (I'm using [KDE Craft](https://community.kde.org/Craft) for the Windows build, btw) so it probably won't work as expected if I don't fix this issue. Sadly I don't have enough time working on this project due to the overtime working and pressure...
