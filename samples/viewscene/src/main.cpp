// This is a simple application demonstrating the use of secondpylon to build a basic little renderering. Note that this
// is meant for a simple, one-off application window. Subwindows within another application and full screen window
// support is more complex.

#include <windows.h>
#include <secondpylon\plat\plat_types.h>
#include <secondpylon\error\error_assert.h>

using namespace secondpylon::plat;

struct window
{
    window() :
	    m_window(0)
    {
    }

	HWND m_window;
};

LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    switch( uMsg )
    {
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

static char* g_window_class_name = "secondpylon_example_viewscene_window";

static void register_classes(HINSTANCE instance)
{
    WNDCLASS wc = { 0, WndProc, 0, 0, instance, LoadIcon(0, IDI_APPLICATION), LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(BLACK_BRUSH), 0, g_window_class_name };
    ATOM result = RegisterClass(&wc);
    SPERROR_ASSERT(result != 0);
    SPERROR_UNREFERENCED(result);
}

static void unregister_classes(HINSTANCE instance)
{
    BOOL result = UnregisterClass(g_window_class_name, instance);
    SPERROR_ASSERT(result != 0);
    SPERROR_UNREFERENCED(result);
}

static void create_window(window& window_result, HINSTANCE instance, const char* window_name, uint16 width, uint16 height)
{
    SPERROR_ASSERT(window_result.m_window == 0);

    DWORD window_style = 
        (WS_POPUP 
        | WS_CLIPSIBLINGS 
        | WS_CLIPCHILDREN 
        | WS_CAPTION 
        | WS_SYSMENU 
        | WS_MINIMIZEBOX);
	
	HWND new_window = CreateWindowEx(
		0,                         // Extended Window Style
		g_window_class_name, // Registered Class Name
		window_name,		// Window Name
		window_style,		// Window Style
		0,                         // Horiz. Position of Window
		0,					        // Vert. Position of Window
		width,				    // Window Width
		height,				    // Window Height
		NULL,                  // Parent Window
		NULL,                  // Menu
		instance,			    // App Instance
		NULL);                 // Window Creation Data
    SPERROR_ASSERT(new_window != 0);

	ShowWindow(new_window, SW_SHOWNORMAL);

    // Store the results now that everything completed successfully.
    window_result.m_window  = new_window;
}

static void destroy_window(window& destroy)
{
    DestroyWindow(destroy.m_window);
    destroy.m_window = 0;
}

static void run_app()
{
    bool quit_posted = false;
	while (!quit_posted)
	{
        MSG msg;
		while (PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ))
		{
			if (msg.message == WM_QUIT)
            {
                quit_posted = true;
            }

            TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	// clean up any pending messages posted after WM_QUIT
    {
        MSG msg;
	    while (PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ))
	    {
		    TranslateMessage(&msg);
		    DispatchMessage(&msg);
        }
    }
}

int main(int /*args*/, char* /*argv*/)
{
    // Normal entrypoint would use WinMain, which wouldn't require this.
    HMODULE instance = GetModuleHandle(NULL);

    // Show the scene

    // Create Window and run the application
    register_classes(instance);

    window app_window;
    create_window(app_window, instance, "viewscene", 128, 128);
	run_app();
    destroy_window(app_window);

    unregister_classes(instance);
}
