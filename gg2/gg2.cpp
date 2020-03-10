#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>


#define WINDOW_X_DEFAULT 800
#define WINDOW_Y_DEFAULT 600

LRESULT CALLBACK WindowProc( HWND hwnd , UINT uMsg , WPARAM wParam , LPARAM lParam );

HDC dc ;

int WINAPI wWinMain( HINSTANCE hInstance , HINSTANCE , PWSTR pCmdLine , int nCmdShow )
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.style = CS_OWNDC ;

    RegisterClass( &wc );

    

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0 ,                              // Optional window styles.
        CLASS_NAME ,                     // Window class
        L"GG" ,    // Window text
        WS_OVERLAPPEDWINDOW ,            // Window style

        // Size and position
        CW_USEDEFAULT , CW_USEDEFAULT , WINDOW_X_DEFAULT , WINDOW_Y_DEFAULT ,

        NULL ,       // Parent window    
        NULL ,       // Menu
        hInstance ,  // Instance handle
        NULL        // Additional application data
    );

    if ( hwnd == NULL )
    {
        return 0;
    }

    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof( PIXELFORMATDESCRIPTOR ),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
        PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
        32,                   // Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,                   // Number of bits for the depthbuffer
        8,                    // Number of bits for the stencilbuffer
        0,                    // Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    dc = GetDC( hwnd ) ;
    int pfn = ChoosePixelFormat( dc , &pfd ) ;
    if ( !pfn )
    {
        return 0 ;
    }
    SetPixelFormat( dc , pfn , &pfd );
    HGLRC hglrc = wglCreateContext( dc ) ;
    if ( !hglrc )
    {
        DWORD err = GetLastError() ;
        return 0 ;
    }
    wglMakeCurrent( dc , hglrc ) ;
    ShowWindow( hwnd , nCmdShow );

    // Run the message loop.

    MSG msg = { };
    while ( GetMessage( &msg , NULL , 0 , 0 ) )
    {
        TranslateMessage( &msg );
        DispatchMessage( &msg );


    }


    wglMakeCurrent( dc , NULL ) ;
    wglDeleteContext( hglrc ) ;

    return 0;
}

LRESULT CALLBACK WindowProc( HWND hwnd , UINT uMsg , WPARAM wParam , LPARAM lParam )
{

    switch ( uMsg )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;

        case WM_PAINT:
        {

            glClearColor( 0.0 , 0.0 , 1.0 , 1.0 ) ;
            glClear( GL_COLOR_BUFFER_BIT ) ;

            glColor3f( 1.0 , 1.0 , 0.0 ) ;
            
            glBegin( GL_TRIANGLES );
            {
                glVertex2f( -1.0 , -1.0 ) ;
                glVertex2f( 0.0 , 1.0 ) ;
                glVertex2f( 1.0 , -1.0 ) ;
            }
            glEnd() ;
            SwapBuffers( dc ) ;
        }
        return 0;

    }
    return DefWindowProc( hwnd , uMsg , wParam , lParam );
}