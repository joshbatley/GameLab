#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION

#include <SDL2/SDL.h>
#include <QuartzCore/CAMetalLayer.hpp>
#include <Metal/Metal.hpp>
#include <iostream>

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create an SDL window
    SDL_Window *window = SDL_CreateWindow("SDL2 Metal Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_METAL);
    if (!window) {
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Get the Metal layer from the SDL window
    SDL_MetalView metalView = SDL_Metal_CreateView(window);
    CA::MetalLayer *metalLayer = (CA::MetalLayer *)SDL_Metal_GetLayer(metalView);

    // Get the Metal device
    MTL::Device *device = MTL::CreateSystemDefaultDevice();

    metalLayer->setDevice(device);
    // Create a command queue
    MTL::CommandQueue *commandQueue = device->newCommandQueue();

    // Main loop
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Create a drawable
        CA::MetalDrawable *drawable = metalLayer->nextDrawable();
        if (!drawable) continue;

        // Create a render pass descriptor
        MTL::RenderPassDescriptor *passDescriptor = MTL::RenderPassDescriptor::alloc()->init();
        passDescriptor->colorAttachments()->object(0)->setClearColor(MTL::ClearColor::Make(1.0, 0.0, 0.0, 1.0)); // Red color
        passDescriptor->colorAttachments()->object(0)->setLoadAction(MTL::LoadActionClear);
        passDescriptor->colorAttachments()->object(0)->setStoreAction(MTL::StoreActionStore);
        passDescriptor->colorAttachments()->object(0)->setTexture(drawable->texture());

        // Create a command buffer
        auto *commandBuffer = commandQueue->commandBuffer();

        // Create a render command encoder
        MTL::RenderCommandEncoder *encoder = commandBuffer->renderCommandEncoder(passDescriptor);
        encoder->endEncoding();

        // Present the drawable
        commandBuffer->presentDrawable(drawable);
        commandBuffer->commit();

        // Release the pass descriptor
        passDescriptor->release();
    }

    // Cleanup
    commandQueue->release();
    device->release();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
