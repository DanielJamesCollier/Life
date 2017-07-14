// my
#include "life.hpp"
#include "sdl_module.hpp"

// std
#include <cstdint>
#include <array>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

int main() {
    constexpr auto grid_width {700};
    constexpr auto grid_height {1000};
    constexpr auto window_scale {1}; 

    life<grid_width, grid_height> conway_grid;
    sdl_module sdl {grid_width, grid_height, window_scale};

    std::array<std::uint32_t, grid_width * grid_height> argb_buffer;
    
    while (sdl.event_loop()) {
        conway_grid.render_to_ARGB_buffer(argb_buffer);
        sdl.draw<grid_width, grid_height>(argb_buffer); 
        conway_grid.simulate();
        std::this_thread::sleep_for(50ms);
    } 
    return 0;
}
