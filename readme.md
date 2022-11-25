# Overview
First try at an application using [GStreamer](https://gstreamer.freedesktop.org/documentation/index.html?gi-language=c)

I followed the [Basic tutorial 1: Hello World!](https://gstreamer.freedesktop.org/documentation/tutorials/basic/hello-world.html?gi-language=c)

# Setup 
## Linux
Simplified notes from [Installing on Linux](https://gstreamer.freedesktop.org/documentation/installing/on-linux.html?gi-language=c)

```shell
apt-get install \
libgstreamer1.0-dev \
libgstreamer-plugins-base1.0-dev \
libgstreamer-plugins-bad1.0-dev \
gstreamer1.0-plugins-base \
gstreamer1.0-plugins-good \
gstreamer1.0-plugins-bad \
gstreamer1.0-plugins-ugly \
gstreamer1.0-libav \
gstreamer1.0-tools \
gstreamer1.0-x \
gstreamer1.0-alsa \
gstreamer1.0-gl \
gstreamer1.0-gtk3 \
gstreamer1.0-qt5 \
gstreamer1.0-pulseaudio
```

### Issues
#### Doc package
`gstreamer1.0-doc` didn't seem to be an available package. I just skipped it.

#### udev conflict
```shell
The following packages have unmet dependencies:
 udev : Breaks: systemd (< 249.11-0ubuntu3.6)
        Breaks: systemd:i386 (< 249.11-0ubuntu3.6)
        Recommends: systemd-hwe-hwdb but it is not going to be installed
E: Error, pkgProblemResolver::Resolve generated breaks, this may be caused by held packages.
```

--> Just needed to update `apt dist-upgrade`


# Code
Mostly a copy/paste, but needed to add a static cast to the options for `gst_bus_timed_pop_filtered`  
```c
msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
```

# Building
## Localhost with Dependencies installed

### Script
From the project directory:
```shell
./scripts/run-build-linux.bash
```

#### CMake / IDE
No special CMake flags are needed. Pick your build time (release / debug), configure your build directory,
and all should work.

## Docker
A docker environment is defined to abstract the build. It can be used as a remote host containing the dependencies
or as a fully automated build.

### Automated build
This will handle building the image; mounting the source into the container; and the artifacts will be in the 
`<project-root>/build/linux-release`.
```shell
./scripts/run-build-docker.bash
```
