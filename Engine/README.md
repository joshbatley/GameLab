# Engine

## Changelog
\# v0.1.0
The initial release of the engine. Before the project restructuring, it became obvious that the library methods were too interconnected and needed to be placed into what is now called the Engine. This was always the goal, but I thought it might have been a little longer before it was needed.

This includes all the libraries and extras that were created for the Game-3-Tiler needs.
All things so far include:
-  App.cpp/h - The overarching structure of the app, allowing the game to register events, systems, and plugins to develop a game or tool.
-  AssetHandler.cpp/h - Handles the loading of assets.
-  GraphicsHandler.cpp/h - SDL2 wrapper that handles anything rendering or graphics.
-  InputManager.cpp/h - SDL2 wrapper for anything inputs.
-  WindowManager.cpp/h - SDL2 wrapper for anything window management.
-  EventHandler.h - Handles dispatching events, writers, and readers. Used for systems to talk to one another.
-  Engine.h - A thin wrapper to hide references to specific libraries so they can be replaced at later dates.
-  Vector.h - Simple Vector implementation, probably getting replaced with GLM.
-  Components/* - A folder of useful components for the ECS.
-  Systems/* - A collection of systems that are used with the app. This helps hide basic systems and pass them off to the Engine to deal with so they don't need to be replicated every time.