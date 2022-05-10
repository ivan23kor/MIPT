#include "pattern.hpp"

void add_pentadecathlon(Cell *cells, bool *cell_states, int center) {
    char cell_count = 22;
    int pentadecathlon[cell_count];

    if ((center % X_CELLS > 5) && (center % X_CELLS <= X_CELLS - 5) &&
        (center / X_CELLS > 8) && (center / X_CELLS <= Y_CELLS - 9)) {
            int counter = 0;
            pentadecathlon[counter++] = center + X_CELLS*4;
            pentadecathlon[counter++] = center + X_CELLS*2;
            pentadecathlon[counter++] = center + X_CELLS*1;
            pentadecathlon[counter++] = center;
            pentadecathlon[counter++] = center - X_CELLS*1;
            pentadecathlon[counter++] = center - X_CELLS*3;

            pentadecathlon[counter++] = center - X_CELLS*3 - 1;
            pentadecathlon[counter++] = center - X_CELLS*2 - 1;
            pentadecathlon[counter++] = center - X_CELLS*1 - 1;
            pentadecathlon[counter++] = center - X_CELLS*0 - 1;
            pentadecathlon[counter++] = center + X_CELLS*1 - 1;
            pentadecathlon[counter++] = center + X_CELLS*2 - 1;
            pentadecathlon[counter++] = center + X_CELLS*3 - 1;
            pentadecathlon[counter++] = center + X_CELLS*4 - 1;

            pentadecathlon[counter++] = center - X_CELLS*3 + 1;
            pentadecathlon[counter++] = center - X_CELLS*2 + 1;
            pentadecathlon[counter++] = center - X_CELLS*1 + 1;
            pentadecathlon[counter++] = center - X_CELLS*0 + 1;
            pentadecathlon[counter++] = center + X_CELLS*1 + 1;
            pentadecathlon[counter++] = center + X_CELLS*2 + 1;
            pentadecathlon[counter++] = center + X_CELLS*3 + 1;
            pentadecathlon[counter++] = center + X_CELLS*4 + 1;
            for (int i = 0; i < cell_count; ++i)
                {
                    cell_states[pentadecathlon[i]] = true;
                    cells[pentadecathlon[i]].make_alive();
                    cells[pentadecathlon[i]].make_active();
                }
    }

    return;
}

void add_pulsar(Cell *cells, bool *cell_states, int center) {
    int pulsar[48];
    if ((center % X_CELLS > 7) && (center % X_CELLS < X_CELLS - 8) &&
        (center / X_CELLS > 7) && (center / X_CELLS < Y_CELLS - 8)) {
            int counter = 0;
            pulsar[counter++] = center - X_CELLS - 2;
            pulsar[counter++] = center - X_CELLS - 3;
            pulsar[counter++] = center - X_CELLS - 4;
            pulsar[counter++] = center - X_CELLS + 2;
            pulsar[counter++] = center - X_CELLS + 3;
            pulsar[counter++] = center - X_CELLS + 4;
            pulsar[counter++] = center + X_CELLS - 2;
            pulsar[counter++] = center + X_CELLS - 3;
            pulsar[counter++] = center + X_CELLS - 4;
            pulsar[counter++] = center + X_CELLS + 2;
            pulsar[counter++] = center + X_CELLS + 3;
            pulsar[counter++] = center + X_CELLS + 4;

            pulsar[counter++] = center - X_CELLS * 2 - 1;
            pulsar[counter++] = center - X_CELLS * 3 - 1;
            pulsar[counter++] = center - X_CELLS * 4 - 1;
            pulsar[counter++] = center - X_CELLS * 2 + 1;
            pulsar[counter++] = center - X_CELLS * 3 + 1;
            pulsar[counter++] = center - X_CELLS * 4 + 1;
            pulsar[counter++] = center + X_CELLS * 2 - 1;
            pulsar[counter++] = center + X_CELLS * 3 - 1;
            pulsar[counter++] = center + X_CELLS * 4 - 1;
            pulsar[counter++] = center + X_CELLS * 2 + 1;
            pulsar[counter++] = center + X_CELLS * 3 + 1;
            pulsar[counter++] = center + X_CELLS * 4 + 1;
            
            pulsar[counter++] = center - X_CELLS * 6 - 2;
            pulsar[counter++] = center - X_CELLS * 6 - 3;
            pulsar[counter++] = center - X_CELLS * 6 - 4;
            pulsar[counter++] = center - X_CELLS * 6 + 2;
            pulsar[counter++] = center - X_CELLS * 6 + 3;
            pulsar[counter++] = center - X_CELLS * 6 + 4;
            pulsar[counter++] = center + X_CELLS * 6 - 2;
            pulsar[counter++] = center + X_CELLS * 6 - 3;
            pulsar[counter++] = center + X_CELLS * 6 - 4;
            pulsar[counter++] = center + X_CELLS * 6 + 2;
            pulsar[counter++] = center + X_CELLS * 6 + 3;
            pulsar[counter++] = center + X_CELLS * 6 + 4;

            pulsar[counter++] = center - X_CELLS * 2 - 6;
            pulsar[counter++] = center - X_CELLS * 3 - 6;
            pulsar[counter++] = center - X_CELLS * 4 - 6;
            pulsar[counter++] = center - X_CELLS * 2 + 6;
            pulsar[counter++] = center - X_CELLS * 3 + 6;
            pulsar[counter++] = center - X_CELLS * 4 + 6;
            pulsar[counter++] = center + X_CELLS * 2 - 6;
            pulsar[counter++] = center + X_CELLS * 3 - 6;
            pulsar[counter++] = center + X_CELLS * 4 - 6;
            pulsar[counter++] = center + X_CELLS * 2 + 6;
            pulsar[counter++] = center + X_CELLS * 3 + 6;
            pulsar[counter++] = center + X_CELLS * 4 + 6;
            for (int i = 0; i < 48; ++i)
            {
                cell_states[pulsar[i]] = true;
                cells[pulsar[i]].make_alive();
                cells[pulsar[i]].make_active();
            }
    }
    return;
}