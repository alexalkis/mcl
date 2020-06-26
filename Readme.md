# MCL

A preservation attempt, to make it compile on modern systems.

Switched to cmake (Clion) since "configure" stopped working.

#### Plugins
In the plugins/ folder, CMakeLists.txt has some hardcoded paths.  If you get no plugins look there first.



#### Build
```
git clone https://github.com/alexalkis/mcl
cd mcl
mkdir build
cd build
cmake ..
make
```

If you are missing libperl-dev or python2.7-dev or liblua5.X-dev the corresponding plugin won't be build.
Build will fail on missing ncurses. (install libncurses-dev or something similar)

The lua plugin is not operational.  It just builds, more like proof of concept thing...
