#!/bin/bash

# build project
make -j8

# check if build failed
if [ $? -ne 0 ]; then
    echo "Build failed. Not launching VisualBoyAdvance."
    exit 1
fi

# run rom in emulator
/usr/bin/flatpak run --branch=stable --arch=aarch64 --command=visualboyadvance-m --file-forwarding com.vba_m.visualboyadvance-m bouncy-bird.gba