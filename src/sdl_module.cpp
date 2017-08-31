// my
#include "sdl_module.hpp"

// std
#include <cstdlib>
#include <iostream>

/*public RAII*/
//--------------------------------------
sdl_module::sdl_module(int width, int height, int scale) 
:   width{width}
,   height{height}
,   renderer_width{width}
,   renderer_height{height}
,   scale{scale} {
}

//--------------------------------------
int
sdl_module::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return -1;
    }
    
    auto position = SDL_WINDOWPOS_CENTERED;
    m_window = SDL_CreateWindow("Life", position, position, width * scale, height * scale, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    
    if (m_window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow failed - m_renderTexture: %s", SDL_GetError());
        return -1;
    }
    
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (m_renderer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRenderer failed - m_renderTexture: %s", SDL_GetError());
        return -1;
    };

    m_renderTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (m_renderTexture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRenderer failed - m_renderTexture: %s", SDL_GetError());
        return -1;
    }

    SDL_GetRendererOutputSize(m_renderer, &renderer_width, &renderer_height);

    return 0;
}

//--------------------------------------
sdl_module::~sdl_module() {
    SDL_DestroyTexture(m_renderTexture); 
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

//--------------------------------------
bool
sdl_module::event_loop() {
    while (SDL_PollEvent(&m_event)) {
        if (m_event.type == SDL_QUIT) {
            return false;
        }   
    }
    return true;
}

//--------------------------------------
void
sdl_module::draw_grid() {
    SDL_SetRenderDrawColor(m_renderer, 31, 67, 124, 255);
    
    // the renderer width may be different from the screen width 
    int step = renderer_width / (width * scale);
    
    for (auto x = 0; x < renderer_width; x+=step * step) 
        SDL_RenderDrawLine(m_renderer, x, 0, x, renderer_height);
    
    for (auto y = 0; y < renderer_width; y+=scale * step ) 
        SDL_RenderDrawLine(m_renderer, 0, y, renderer_height, y);
}

//--------------------------------------
void
sdl_module::swap_back_buffer() {
    SDL_RenderPresent(m_renderer);
}
