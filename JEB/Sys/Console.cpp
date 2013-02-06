#include "Console.hpp"

#if defined(__APPLE__)

#include <sys/ioctl.h>
#include <unistd.h>

static bool sizeImpl(unsigned* height, unsigned* width)
{
    struct winsize ws;
    if ((ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 &&
         ioctl(STDERR_FILENO, TIOCGWINSZ, &ws) == -1 &&
         ioctl(STDIN_FILENO,  TIOCGWINSZ, &ws) == -1) ||
        ws.ws_col == 0)
        return false;

    *height = ws.ws_row;
    *width = ws.ws_col;
    return true;
}

#elif defined(WIN32)

#include <Windows.h>

static bool sizeImpl(unsigned* height, unsigned* width)
{
  HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hCon == INVALID_HANDLE_VALUE)
    return false;

  CONSOLE_SCREEN_BUFFER_INFO conInfo;
  if (!GetConsoleScreenBufferInfo(hCon, &conInfo))
    return false;

  *width = (unsigned)(conInfo.srWindow.Right - conInfo.srWindow.Left + 1);
  *height = (unsigned)(conInfo.srWindow.Bottom - conInfo.srWindow.Top + 1);
  return true;
}

#endif

namespace JEB
{
namespace Console
{

bool size(unsigned* height, unsigned* width)
{
    return sizeImpl(height, width);
}

}
}
