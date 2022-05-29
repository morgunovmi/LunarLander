# LunarLander
A little game demo where you have to land a rocket on the surface of the moon avoiding rough terrain.

![sc](https://user-images.githubusercontent.com/48750724/170862969-42539b7a-0ef7-499a-b604-8e66bad546e7.png)

## Playing

To play the game you can download the binary from the Releases page.
Then you install it with
```
sudo dpkg -i ./LunarLander_version_num_architecture.deb
LunarLander
```
If you run into errors with GLIBCXX version, upgrade the libstdc++6
How to do on Ubuntu
```
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt update
sudo apt-get install --only-upgrade libstdc++6
```

## Build
You need to have a compiler that supports the C++17 standard. For gcc it's version 8 or higher.
You also need to have X11 development libraries installed.

These build instructions are for linux and assume you have CMake installed.

```
git clone https://github.com/morgunovmi/LunarLander.git
cd LunarLander
mkdir build-release
cd build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
./LunarLander
```
