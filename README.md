IDA Skins - x64dbg Edition
=========

Plugin providing advanced skinning support for the Qt version of IDA Pro utilizing [Qt stylesheets](http://qt-project.org/doc/qt-4.7/stylesheet.html), similar to CSS.

# Installation
### x64dbg
Place `IDASkins.dp32` or `IDASkins.dp64` into the 'plugins' directory of x64dbg to instal. Theme files (`skin` directory) should be placed in the same folder.

### IDA
Place `IDASkins.plX` into the `plugins` directory of your IDA installation. The theme files (the `skin` directory) needs to be copied to the root of your IDA installation.

# Theming
Theming with IDASkins works using [Qt stylesheets](http://qt-project.org/doc/qt-4.7/stylesheet.html). For information on the most important or specific UI elements, take a look in the enclosed default `stylesheet.css`.

## Screenshots

![Screenshot 1](https://cloud.githubusercontent.com/assets/4228359/7801266/f231e27a-02ef-11e5-827f-9ee551c06caf.png)
![Screenshot 2](https://raw.githubusercontent.com/athre0z/ida-skins/master/media/screenshots/screencap1.png)

Screenshot above show:
- x64dbg: The enclosed `stylesheet.css` in combination with [tr4ceflow's](http://pastebin.com/BYDKkiJX) theme.
- IDA:    The enclosed `stylesheet.css` in combination with the [idaConsonance](https://github.com/eugeneching/ida-consonance) theme.
