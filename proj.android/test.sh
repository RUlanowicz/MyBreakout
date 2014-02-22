cd ~/GitHub/MyBreakout/proj.android
./build_native.py
ant debug -Dsdk.dir="/usr/local/Cellar/android-sdk/22.3"
cd bin/
adb shell pm uninstall edu.pitt.cs1635.rru3.prog3
adb install MyBreakout-debug.apk