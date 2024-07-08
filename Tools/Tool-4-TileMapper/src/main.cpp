#include "Engine.h"

int main()
{
    App app(Window::Config {
      .title = "Tool TileMapper",
      .showCursor = false,
      .relativeMouse = false,
    });

    app
      .Run();
}
