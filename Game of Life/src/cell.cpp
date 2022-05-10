#include "cell.hpp"


Cell::Cell() {
    // By default, all cells are dead
    alive = false;
    cell.setFillColor(sf::Color::Red);
    cell.setSize(sf::Vector2f(1 / (float)X_CELLS, 1 / (float)Y_CELLS));
}

Cell::Cell(int number, const sf::Vector2u window_size) {
    cell.setSize(sf::Vector2f(1 / (float)X_CELLS, 1 / (float)Y_CELLS));

    cell.setPosition((number % X_CELLS) / (float)X_CELLS,
                     (number / X_CELLS) / (float)Y_CELLS);
}

bool Cell::is_alive() {
    return alive;
}

void Cell::make_alive() {
    alive = true;
    cell.setFillColor(sf::Color::Green);
}

void Cell::make_dead() {
    alive = false;
    cell.setFillColor(sf::Color::Red);
}

void Cell::toggle_life() {
    alive = !alive;
    if (alive)
        cell.setFillColor(sf::Color::Green);
    else
        cell.setFillColor(sf::Color::Red);
}

bool Cell::is_active() {
    return active;
}

void Cell::make_active() {
    active = true;
}

void Cell::make_inactive() {
    active = false;
}

int count_alive_neighbors(bool *cell_states, int cell_number) {
    int alive_neighbors = 0;

    // Four corner cells
    switch(cell_number) {
        // Left upper
        case 0:
            return cell_states[cell_number + 1] +
                   cell_states[cell_number + X_CELLS] +
                   cell_states[cell_number + X_CELLS + 1];
        // Right upper
        case X_CELLS - 1:
            return cell_states[cell_number - 1] +
                   cell_states[cell_number + X_CELLS] +
                   cell_states[cell_number + X_CELLS - 1];
        // Left bottom
        case X_CELLS * (Y_CELLS - 1):
            return cell_states[cell_number + 1] +
                   cell_states[cell_number - X_CELLS] +
                   cell_states[cell_number - X_CELLS + 1];
        // Right bottom
        case X_CELLS * Y_CELLS - 1:
            return cell_states[cell_number - 1] +
                   cell_states[cell_number - X_CELLS] +
                   cell_states[cell_number - X_CELLS - 1];
        default:
            break;
    }

    // Other upper-horizontal cells
    if (cell_number < X_CELLS)
            alive_neighbors = cell_states[cell_number - 1] +
                              cell_states[cell_number + X_CELLS - 1] +
                              cell_states[cell_number + X_CELLS] +
                              cell_states[cell_number + X_CELLS + 1] +
                              cell_states[cell_number + 1];
    // Other bottom-horizontal cells
    else if (cell_number / X_CELLS == Y_CELLS - 1)
            alive_neighbors = cell_states[cell_number - 1] +
                              cell_states[cell_number - X_CELLS - 1] +
                              cell_states[cell_number - X_CELLS] +
                              cell_states[cell_number - X_CELLS + 1] +
                              cell_states[cell_number + 1];
    // Other left-vertical cells
    else if (cell_number % X_CELLS == 0)
            alive_neighbors = cell_states[cell_number - X_CELLS] +
                              cell_states[cell_number - X_CELLS + 1] +
                              cell_states[cell_number + 1] +
                              cell_states[cell_number + X_CELLS + 1] +
                              cell_states[cell_number + X_CELLS];
    // Other right-vertical cells
    else if (cell_number % X_CELLS == X_CELLS - 1)
            alive_neighbors = cell_states[cell_number - X_CELLS] +
                              cell_states[cell_number - X_CELLS - 1] +
                              cell_states[cell_number - 1] +
                              cell_states[cell_number + X_CELLS - 1] +
                              cell_states[cell_number + X_CELLS];
    // Non-contiguous cells
    else
            alive_neighbors = cell_states[cell_number - X_CELLS - 1] +
                              cell_states[cell_number - X_CELLS] +
                              cell_states[cell_number - X_CELLS + 1] +
                              cell_states[cell_number + 1] +
                              cell_states[cell_number + X_CELLS + 1] +
                              cell_states[cell_number + X_CELLS] +
                              cell_states[cell_number + X_CELLS - 1] +
                              cell_states[cell_number - 1];

    return alive_neighbors;
}
