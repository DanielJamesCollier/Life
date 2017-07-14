#include <random> 
#include <chrono>

/* RAII */
//-------------------------------
template<std::size_t WIDTH, std::size_t HEIGHT> 
life<WIDTH, HEIGHT>::life()
:   grid_a{}
,   grid_b{}
,   current_gen{grid_a}
,   next_gen{grid_b}
{
    reset_to_random_grid();
}

/*
 * simulation rules
 
 - Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
 - Any live cell with two or three live neighbours lives on to the next generation.
 - Any live cell with more than three live neighbours dies, as if by overpopulation.
 - Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction. 
 */

/* size = 5
  0 0 0 0 0 
  0 0 0 0 0 
  0 0 0 0 0
  0 0 0 0 0
  0 0 0 0 0
 */

/* public functions */
//-------------------------------
template<std::size_t WIDTH, std::size_t HEIGHT> 
void 
life<WIDTH, HEIGHT>::simulate() {

    for (auto y = 1; y < HEIGHT - 1; y++) {
        for (auto x = 1; x < WIDTH - 1; x++) {
            
            std::size_t index {(y * WIDTH) + x};
            
            // how many neighbours are alive
            int neighbours {};
            
            // side neighbours
            neighbours += current_gen[index - 1]; // left 
            neighbours += current_gen[index + 1]; // right;
            
            // bottom neighbours
            neighbours += current_gen[index + WIDTH];
            neighbours += current_gen[index + (WIDTH - 1)];
            neighbours += current_gen[index + (WIDTH + 1)];     
            
            // top neighbours 
            neighbours += current_gen[index - WIDTH]; // top
            neighbours += current_gen[index - (WIDTH + 1)]; // top left
            neighbours += current_gen[index - (WIDTH - 1)]; // top right
            
            bool is_alive = current_gen[index] == 1 ? true : false;

            if (is_alive) {
                if (neighbours < 2) { // dies from underpopulation
                    next_gen[index] = 0; 
                } else if (neighbours == 2 || neighbours == 3) {
                    next_gen[index] = 1;
                } else if (neighbours > 3) { // dies from overpopulation
                    next_gen[index] = 0;
                }
            } else {
                if (neighbours == 3) { // dead cell comes alive by repoduction
                    next_gen[index] = 1;
                }
            }           
        }
    }   
    std::swap(next_gen, current_gen); 
    next_gen.fill(0);
}


//-------------------------------
template<std::size_t WIDTH, std::size_t HEIGHT> 
void
life<WIDTH, HEIGHT>::reset_to_random_grid() {
    unsigned seed {static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count())};
    std::mt19937_64 generator {seed};
    std::uniform_int_distribution<std::uint8_t> distribution {0, 1}; // 0 is dead // 1 is alive
    
    for (auto & grid_element : current_gen) {
        grid_element = distribution(generator);
    }
}

//-------------------------------
template<std::size_t WIDTH, std::size_t HEIGHT>
void
life<WIDTH, HEIGHT>::render_to_ARGB_buffer(std::array<std::uint32_t, WIDTH * HEIGHT> &buffer) {
    for (auto i = 0; i < WIDTH * HEIGHT; i++) {
        auto const pixel = current_gen[i];
        buffer[i] = (0x00FFFFFF * pixel) | 0xFF000000; 
    }
}
