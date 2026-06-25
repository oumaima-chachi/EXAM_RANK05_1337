#include "life.h"
#include <unistd.h>
int count_neighbors(int *grid, int w, int h, int x, int y)
{
    int neighbors = 0;

    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            if (dx == 0 && dy == 0)
                continue;

            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < w && ny >= 0 && ny < h)
                neighbors += grid[ny * w + nx];
        }
    }
    return neighbors;
}

int main(int ac, char **av)
{
    if (ac != 4)
        return (1);

    int w = atoi(av[1]);
    int h = atoi(av[2]);
    int iterations = atoi(av[3]);

    int *grid = calloc(w * h, sizeof(int));
    int *next = calloc(w * h, sizeof(int));

    int x = 0;
    int y = 0;
    int draw = 0;
    char c;

    /* Lecture des commandes */
    while (read(0, &c, 1) > 0)
    {
        if (c == 'x')
            draw = !draw;

        if (c == 'w' && y > 0)          // haut
            y--;

        if (c == 's' && y < h - 1)      // bas
            y++;

        if (c == 'a' && x > 0)          // gauche
            x--;

        if (c == 'd' && x < w - 1)      // droite
            x++;

        if (draw)
            grid[y * w + x] = 1;
    }

    /* Simulations */
    while (iterations--)
    {
        for (int i = 0; i < w * h; i++)
        {
            int x = i % w;
            int y = i / w;

            int n = count_neighbors(grid, w, h, x, y);

            if (grid[i]) // cellule vivante
                next[i] = (n == 2 || n == 3);
            else         // cellule morte
                next[i] = (n == 3);
        }

        int *tmp = grid;
        grid = next;
        next = tmp;
    }

    /* Affichage */
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            if (grid[y * w + x])
                putchar('O');
            else
                putchar(' ');
        }
        putchar('\n');
    }

    free(grid);
    free(next);
    return (0);
}
