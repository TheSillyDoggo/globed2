# Globed

Globed is an open-source, highly customizable multiplayer mod for Geometry Dash.

This repository contains the complete rewrite of Globed, for Geometry Dash 2.2 and all future versions. If you want the 2.1 version, the [old repository](https://github.com/dankmeme01/globed) is still up, however it is no longer maintained.

## Installation

Globed is a [Geode](https://github.com/geode-sdk/geode) mod, so it requires you to install Geode first. Once that's done, simply open the mods page in-game and download it from the index.

## Hosting a server

todo

## Roadmap

Planned features:

* wait for 2.2

Known issues:

* i am silly
* voice chat is a bit silly

## Contributing

If you want to contribute, please read the [Contributor guide](./contribution.md).

## Building

For building the server, you need nothing more than a Rust toolchain. Past that, it's essentially the same as any other Rust project. Building the client is, however, a bit more complex.

If you encounter any problems when building the client, please don't hesitate to reach out to me on discord (@dank_meme01). I know this is a bit confusing and there's probably a way to make it simpler but oh well.

### Windows

If you are on Linux, I recommend dualbooting to windows right now or using a VM. Otherwise good luck and have fun :)

The steps below have to be done only once. After you get all the libraries you can modify and rebuild the mod as much as you want without going through the agony again.

For libsodium, open the [latest release](https://github.com/jedisct1/libsodium), download the asset called `libsodium-1.x.y-msvc.zip` and unzip it into `libs/`. The `libs/libsodium` folder should now contain folders `include`, `Win32` and `x64`.

For libsamplerate, clone the [repo](https://github.com/libsndfile/libsamplerate), and build it with Visual Studio. Make sure to set the configuration to x86-Release. Once the build is done, copy the library from `out/build/x86-Release/src/samplerate.lib` into `libs/libsamplerate/Win32` in the mod directory. Create the path if it doesn't already exist.

For opus, clone the [opus repo](https://github.com/xiph/opus), and open the file `win32/VS2015/opus.sln`. If it asks you to upgrade the solution, do it. Select the configuration Release Win32 and build the project "opus". Once that is done, copy the library from `win32/VS2015/Win32/Release/opus.lib` into `libs/opus/Win32` in the mod directory. Create the path if it doesn't already exist.

Now, also if you are on Linux there's one extra step - open your splat directory and inside navigate to `crt/lib/x86`. Either make a symlink or simply copy the file `vcomp.lib` to `VCOMP.lib` in the same directory. Make sure the name is capitalized exactly like that.

If everything is successful, simply proceed with the CMake build, like you would in any other mod. Should work hopefully :)

### Mac

gotta figure it out somehow

### Android

alrighty, let's have some fun shall we? if you are not on linux then use WSL. make sure to have android NDK installed.

for the first build, you need to build all the libraries yourself.

```sh
# change ndk home to whatever folder you have it installed in
ANDROID_NDK_HOME=/opt/android-ndk ./build-sodium-android.sh
ANDROID_NDK_HOME=/opt/android-ndk ./build-opus-android.sh
ANDROID_NDK_HOME=/opt/android-ndk ./build-samplerate-android.sh
```

this will pull the repos and build them from source. if you don't see any errors then you're epic! the built libraries should be automatically copied into the correct directory.

now simply use your epic build script and build the mod with cmake like you would build any other mod!

NOTE: when configuring the mod you must set `-DANDROID_PLATFORM=android-28` or higher. versions below do not have the `getrandom()` syscall so libsodium will fail to link. this means the mod is **incompatible** with versions of Android below 9.

## Credit

ca7x3, Firee, Croozington, Coloride, Cvolton, mat, alk, maki, xTymon - thank you for being awesome, whether it's because you helped me, suggested ideas, or if I just found you awesome in general :D

camila314 - thank you for [UIBuilder](https://github.com/camila314/uibuilder)

RobTop - thank you for releasing this awesome game :)

## Open source acknowledgments

* [Geode](https://github.com/geode-sdk/geode) - the one thing that made all of this possible :)
* [Opus](https://github.com/xiph/opus) - audio codec used for audio compression
* [libsamplerate](https://github.com/libsndfile/libsamplerate) - library used for resampling audio
* [Sodium](https://github.com/jedisct1/libsodium) - crypto library used for data encryption