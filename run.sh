#/usr/bin/env bash

pushd ./bin/*.app/Contents/MacOS/
LIBFREENECT2_PIPELINE=cl ./kinectEmotionRecognitionDebug
popd
