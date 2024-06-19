# Window Manager V1.0
A simple file to handle most the SDL stuff, it hides away SDL logic to prevent that coming up in the main file.

When including the next projects extend this so instead of passing just a texture you can pass other class that then
rendered. This is just the basic set up for it.

### Changelog

\#1.0
---
Initial release

\#1.1
---
Split windowing and rendering out so the renderers has all the texture/font maps and window deals with all thing windows.
> After testing in Game2 Refactored it was not fit for purpose this fixes more of the bug bares.