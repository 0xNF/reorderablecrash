#include <flutter/dart_project.h>
#include <flutter/flutter_view_controller.h>
#include <windows.h>

#include "flutter_window.h"
#include "utils.h"
#include <iostream>

void DebugOut(wchar_t* fmt, ...)
{
    va_list argp;
    va_start(argp, fmt);
    wchar_t dbg_out[4096];
    vswprintf_s(dbg_out, fmt, argp);
    va_end(argp);
    OutputDebugString(dbg_out);
    std::wcout << dbg_out << std::endl;
    std::wcout.flush();
}
void nop(bool b) {

}

int APIENTRY wWinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prev,
    _In_ wchar_t* command_line, _In_ int show_command) {
    // Attach to console when present (e.g., 'flutter run') or create a
    // new console when running with a debugger.
    if (!::AttachConsole(ATTACH_PARENT_PROCESS) && ::IsDebuggerPresent()) {
        CreateAndAttachConsole();
    }

    // Initialize COM, so that it is available for use in the library and/or
    // plugins.
    ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

    flutter::DartProject project(L"data");

    std::vector<std::string> command_line_arguments =
        GetCommandLineArguments();

    project.set_dart_entrypoint_arguments(std::move(command_line_arguments));

    FlutterWindow window(project);
    Win32Window::Point origin(10, 10);
    Win32Window::Size size(1280, 720);
    if (!window.CreateAndShow(L"reorderablecrash", origin, size)) {
        return EXIT_FAILURE;
    }
    window.SetQuitOnClose(true);

    std::exception_ptr windowProcException = nullptr;
    ::MSG msg;
    bool m = ::GetMessage(&msg, nullptr, 0, 0);
    while (m) {
        DebugOut(L"message=%x, hwnd=%x, wp=%x, lp=%x, pt=(%d, %d)\n", msg.message, msg.hwnd, (UINT)msg.wParam, (UINT)msg.lParam, msg.pt.x, msg.pt.y);

        try {
            bool tm = ::TranslateMessage(&msg);
            bool dm = ::DispatchMessage(&msg);
            nop(tm);
            nop(dm);
        }
        catch (...) {
            windowProcException = std::current_exception();
        }
        m = ::GetMessage(&msg, nullptr, 0, 0);
    }
    //while (::GetMessage(&msg, nullptr, 0, 0)) {
    //  ::TranslateMessage(&msg);
    //  ::DispatchMessage(&msg);
    //}

    ::CoUninitialize();
    return EXIT_SUCCESS;
}


