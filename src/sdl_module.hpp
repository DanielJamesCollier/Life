#ifndef SDL_MODULE_HPP
#define SDL_MODULE_HPP

// deps
#include "SDL2/SDL.h"

// std
#include <array>
#include <cstdint>

class sdl_module final {
public /* RAII */:
    sdl_module(int width, int height, int scale);
    sdl_module(sdl_module const &) = delete;
    sdl_module(sdl_module &&) = delete;
    ~sdl_module();
   
public /* functions */:
   bool event_loop();
   
   template<std::size_t WIDTH, std::size_t HEIGHT>
   void draw(std::array<std::uint32_t, WIDTH * HEIGHT> const & pixels) {
        SDL_UpdateTexture(m_renderTexture, nullptr, pixels.data(), WIDTH * sizeof(std::uint32_t)); 
        SDL_RenderCopy(m_renderer, m_renderTexture, nullptr, nullptr); 
   }

   void draw_grid() {
        SDL_SetRenderDrawColor(m_renderer, 31, 67, 124, 255);
        
        for (auto i = 0; i < width; i++) 
            SDL_RenderDrawLine(m_renderer, i * scale * 2, height * scale * 2, i * scale * 2, 0);
        
        for (auto i = 0; i < width; i++) 
            SDL_RenderDrawLine(m_renderer, 0, i * scale * 2, width * scale * 2 , i * scale * 2 );
   } 

   void swap_back_buffer() {
        SDL_RenderPresent(m_renderer);
   }
private /* data */:
    SDL_Event m_event;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_renderTexture;
    int width;
    int height;
    int scale;
};
#endif // SDL_MODULE_HPP
