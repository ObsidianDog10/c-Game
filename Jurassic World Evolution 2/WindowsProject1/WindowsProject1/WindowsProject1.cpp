#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static int x = 200, y = 200; // Player position
    static const int playerWidth = 50, playerHeight = 50; // Player size

    switch (uMsg) {
    case WM_KEYDOWN:
        // Handle player movement with arrow keys
        switch (wParam) {
        case VK_UP:    if (y > 0) y -= 10; break; // Move up
        case VK_DOWN:  if (y < 550) y += 10; break; // Move down
        case VK_LEFT:  if (x > 0) x -= 10; break; // Move left
        case VK_RIGHT: if (x < 750) x += 10; break; // Move right
        }
        return 0;

    case WM_PAINT: {
        // Handle rendering of the player (a simple rectangle)
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Clear the window with a white background
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        // Draw the player rectangle
        RECT playerRect = { x, y, x + playerWidth, y + playerHeight };
        FillRect(hdc, &playerRect, (HBRUSH)(COLOR_WINDOW + 3)); // Player color (light blue)

        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0); // Close the window
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Define window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;  // Window procedure function
    wc.hInstance = hInstance;
    wc.lpszClassName = L"GameWindowClass";
    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0, wc.lpszClassName, L"Simple Game Window",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        nullptr, nullptr, hInstance, nullptr);

    if (!hwnd) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Game loop
    MSG msg = {};
    while (true) {
        // Process all messages in the queue
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                return 0;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Trigger a repaint every frame
        InvalidateRect(hwnd, nullptr, TRUE);
        Sleep(10); // Control the game loop speed but keep the UI responsive
    }

    return 0;
}
