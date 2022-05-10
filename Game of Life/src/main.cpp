#include <iostream>
#include <omp.h>
#include <sys/time.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include "src/pattern.hpp"
#include "src/window.hpp"


#define SLEEP_TIME 100

int get_cell_number_by_position(const sf::RenderWindow &window);


int main(int argc, char const *argv[])
{
    int i = 0;
    int current_cell_neighbors = 0;
    int current_cell_number = 0;
    int cycle_count = 0;
    int cycle_count_pure = 0;

    // Time measurement variables
    struct timeval start, start_pure, end, end_pure;
    double delta = 0.0;
    double delta_pure = 0.0;

    bool is_initialasing = true;
    bool cell_states[X_CELLS * Y_CELLS];
    Cell cells[X_CELLS * Y_CELLS];

    sf::RectangleShape white_background;

    sf::Vertex grid[X_CELLS + Y_CELLS][2];

    sf::VideoMode my_mode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(1, 1), "Game of Life");

    //=========================================================================

    // Window dimensions
    const sf::Vector2f screen_size(my_mode.width, my_mode.height);
    const sf::Vector2i window_position(screen_size *
                                       (float)WINDOW_POSITION_SCALE);
    const sf::Vector2u window_size(screen_size * (float)WINDOW_SIZE_SCALE);

    // Apply the dimensions
    window.setPosition(window_position);
    window.setSize(window_size);

    // Cell
    for (int i = 0; i < X_CELLS * Y_CELLS; ++i)
        cell_states[i] = false;    // By default, all the cells are dead
    for (int i = 0; i < X_CELLS * Y_CELLS; ++i)
        cells[i] = Cell(i, window.getSize());

    // White background
    white_background.setFillColor(sf::Color::White);
    white_background.setSize(sf::Vector2f(window_size));

    // Vertical lines
    for (int i = 0; i < X_CELLS; ++i)
    {
        grid[i][0] = sf::Vertex(sf::Vector2f(i * 1 / (float)X_CELLS, 0));
        grid[i][0].color = sf::Color::Black;
        grid[i][1] = sf::Vertex(sf::Vector2f(i * 1 / (float)X_CELLS, 1));
        grid[i][1].color = sf::Color::Black;
    }
    // Horizontal lines
    for (int i = 0; i < Y_CELLS; ++i)
    {
        grid[X_CELLS + i][0] = sf::Vertex(sf::Vector2f(
            0, i * 1 / (float)Y_CELLS));
        grid[X_CELLS + i][0].color = sf::Color::Black;

        grid[X_CELLS + i][1] = sf::Vertex(sf::Vector2f(
            1, i * 1 / (float)Y_CELLS));
        grid[X_CELLS + i][1].color = sf::Color::Black;
    }


    // Output FPS not more often than once per second
    gettimeofday(&start, NULL);

    // Start the game loop
    while (window.isOpen())
    {
        // Init mode
        {
            // Exit init mode
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
                    ((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) ||
                    (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)))) {
                is_initialasing = false;
            }

            // Initializing the field
            if (is_initialasing) {
                // Add one cell
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    current_cell_number = get_cell_number_by_position(window);
                    if (current_cell_number != -1) {
                        cells[current_cell_number].make_active();
                        cells[current_cell_number].toggle_life();
                        cell_states[current_cell_number] =
                            !cell_states[current_cell_number];
                        // Sleep for staggering effect elimination
                        sf::sleep(sf::milliseconds(100));
                    }
                }
                // Add pulsar
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) &&
                        sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                    current_cell_number = get_cell_number_by_position(window);
                    if (current_cell_number != -1)
                        add_pentadecathlon(cells, cell_states, current_cell_number);
                }
                // Add pulsar
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) &&
                        sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                    current_cell_number = get_cell_number_by_position(window);
                    if (current_cell_number != -1)
                        add_pulsar(cells, cell_states, current_cell_number);
                }
            }
        }

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }


        // Cell logic calculation
        {
            gettimeofday(&start_pure, NULL);
            if (!is_initialasing) {
                #pragma omp parallel for private(i)
                for (i = 0; i < X_CELLS * Y_CELLS; ++i) {
                    #pragma omp critical
                    {
                        current_cell_neighbors = count_alive_neighbors(cell_states, i);
                        if (!(cells[i].is_alive()) && (current_cell_neighbors == 3)) {
                            cells[i].make_active();
                            cells[i].make_alive();
                        }

                        if ((cells[i].is_alive()) && (current_cell_neighbors < 2) ||
                                (current_cell_neighbors > 3))
                            cells[i].make_dead();
                    }
                }
                #pragma omp barrier
            }
            gettimeofday(&end_pure, NULL);
            delta_pure = ((end_pure.tv_sec  - start_pure.tv_sec) * 1000000u +
                            end_pure.tv_usec - start_pure.tv_usec) / 1.e6;
            std::cout << "Pure FPS: " << (double)1 / delta_pure << std::endl;
        }

        // Draw and store cells' states
        {
            window.clear();

            window.draw(white_background);
            for (int i = 0; i < X_CELLS + Y_CELLS; ++i)
                window.draw(grid[i], 2, sf::Lines);

            // #pragma omp parallel for
            for (int i = 0; i < X_CELLS * Y_CELLS; ++i) {
                cell_states[i] = cells[i].is_alive();
                if (cells[i].is_active())
                    window.draw(cells[i].cell);
            }
            if (!is_initialasing) sf::sleep(sf::milliseconds(SLEEP_TIME));
            
            window.display();
        }

        // // Time punch-out
        // {
        //     cycle_count++;
        //     gettimeofday(&end, NULL);
        //     delta = ((end.tv_sec  - start.tv_sec) * 1000000u +
        //                      end.tv_usec - start.tv_usec) / 1.e6;
        //     if (delta >= 1.0) {
        //         std::cout << "FPS: " << (float)cycle_count / delta << std::endl;
        //         cycle_count = 0;
        //         gettimeofday(&start, NULL);
        //     }
        // }
    }

    return 0;
}

int get_cell_number_by_position(const sf::RenderWindow &window) {
    // Tag the position where had tapped
    sf::Vector2f mouse_position(sf::Mouse::getPosition(window));
    sf::Vector2f window_size(window.getSize());

    // Determine the pertinent cell
    if ((mouse_position.x < window_size.x) &&
        (mouse_position.x > 0) &&
        (mouse_position.y < window_size.y) &&
        (mouse_position.y > 0))
                return (float)(mouse_position.x / window_size.x) *
                       X_CELLS + (int)((float)(mouse_position.y /
                       window_size.y) * Y_CELLS) * X_CELLS;
    else
        return -1;
}
