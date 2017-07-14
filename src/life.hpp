#ifndef LIFE_HPP
#define LIFE_HPP

// std
#include <cstddef> // std::size_t
#include <cstdint> // std::uint8_t
#include <array>

template<std::size_t WIDTH, std::size_t HEIGHT>
class life final {
public /*RAII*/:
    life(); 
    life(life const &) = delete;
    life(life &&) = delete;
    ~life() = default;

public /*functions*/:
    void simulate();
    void reset_to_random_grid();
    void render_to_ARGB_buffer(std::array<std::uint32_t, WIDTH * HEIGHT> &buffer);
    std::size_t get_generation_counter() const;

private /*functions*/:
    bool is_evolving();

private /*data*/:
    std::array<std::uint8_t, WIDTH * HEIGHT> grid_a;
    std::array<std::uint8_t, WIDTH * HEIGHT> grid_b;
    std::array<std::uint8_t, WIDTH * HEIGHT> &current_gen;
    std::array<std::uint8_t, WIDTH * HEIGHT> &next_gen;
    std::size_t generation_counter;
};
#include "life.inl"
#endif // LIFE_HPP
