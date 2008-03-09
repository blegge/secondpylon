#include <viewscene_applicationutils.h>
#include <windows.h>

extern void render_clear();

void ApplicationUtils::run_app()
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

            render_clear();
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
