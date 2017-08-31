// my
#include "life.hpp"
#include "sdl_module.hpp"

// std
#include <cstdint>
#include <cstdlib>
#include <array>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

int main() {
    constexpr auto grid_width {250};
    constexpr auto grid_height {250};
    constexpr auto window_scale {3}; 

    life<grid_width, grid_height> conway_grid;

    sdl_module sdl {grid_width, grid_height, window_scale};
    
    if (sdl.init() < 0) {
        std::cerr << "SDL2 init failed\n";
        SDL_Quit(); 
        return EXIT_FAILURE;
    }

    std::array<std::uint32_t, grid_width * grid_height> argb_buffer;
    
    while (sdl.event_loop()) {
        conway_grid.render_to_ARGB_buffer(argb_buffer);
        sdl.draw<grid_width, grid_height>(argb_buffer); 
        sdl.draw_grid();
        sdl.swap_back_buffer();

        conway_grid.simulate();
        std::this_thread::sleep_for(60ms);
    } 
    return EXIT_SUCCESS;
}
