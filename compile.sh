#!/bin/bash
g++ main.cpp -o Build/SmokeWM -std=c++20 $(pkg-config --cflags --libs Louvre libdrm pixman-1) -I/usr/include/Louvre -I/usr/include/drm -I/usr/include/pixman-1 -lLouvre
