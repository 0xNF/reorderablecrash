# Reorderable List View Crash

This project is used to demonstrate how projects built using Flutter, running on Windows, will crash when the project imports the [reorderablelistview](https://api.flutter.dev/flutter/material/ReorderableListView-class.html) widget.


The crash takes a few forms:

1. If running in release mode, the application will hard crash to desktop, leaving no traces whatsoever
1. If running in Debug mode, an "Abort?" dialog box will be called. 

The reasons for this crash are documented on the Flutter Engine repo in [this thread](https://github.com/flutter/flutter/issues/103808#issuecomment-1144347869), but the tl;dr is that a list being iterated over in [flutter/engine/src/flutter/shell/platform/common/accessibility_bridge.cc](https://github.com/flutter/engine/blob/main/shell/platform/common/accessibility_bridge.cc#L411) has an incorrect number of elements. I don't know why. 

# Reproducing the Crash
Run the project on Windows. This crash is Windows only. Some people report never being able to reproduce this crash, but this particular repository will crash 100% for me, on my own windows machine (Surface Laptop Studio, Windows 11, 10.0.22000 N/A Build 22000).

