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


#### Debugging Curses applications in CLion
Install on your linux distro 'daemonize'  (e.g. sudo apt install daemonize)

Add new configuration `GDB Remote Debug`
On `target remote args` type in `127.0.0.1:2159`

On the `before launch` section, click the `+` button and add `run external tool`

##### Configure External Tool
###### Program
`/usr/bin/daemonize` (or wherever your distro put it)

###### Arguments
-c $ProjectFileDir$ /usr/bin/konsole -e gdbserver 127.0.0.1:2159 $ProjectFileDir$/cmake-build-debug/mcl
###### Working Directory
$ProjectFileDir$

<br><br>
You might need to install gdbserver as well (sudo apt install gdbserver)