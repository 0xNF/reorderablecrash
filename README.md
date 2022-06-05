This project is used to demonstrate how projects built using Flutter, running on Windows, will crash when the project imports the [reorderablelistview](https://api.flutter.dev/flutter/material/ReorderableListView-class.html) widget.


The crash takes a few forms:

1. If running in release mode, the application will hard crash to desktop, leaving no traces whatsoever
1. If running in Debug mode, an "Abort?" dialog box will be called. 

The reasons for this crash are documented on the Flutter Engine repo in [this thread](https://github.com/flutter/flutter/issues/103808#issuecomment-1144347869)