#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/GiveCoin.ico

convert ../../src/qt/res/icons/GiveCoin-16.png ../../src/qt/res/icons/GiveCoin-32.png ../../src/qt/res/icons/GiveCoin-48.png ${ICON_DST}
