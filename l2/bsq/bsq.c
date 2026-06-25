#include "bsq.h" 

typedef struct {int y, x, size;} square;

int min3(int a, int b, int c)
{
    if (a <= b && a <= c) return a;
    if (b <= a && b <= c) return b;
    return c;
}

int _strlen(char *str)
{
    int i = 0;
    while (str[i]) i++;
    return i;
}

int main(int ac, char **av)
{
    FILE *f = ac > 1 ? fopen(av[1], "r") : stdin;
    if (!f) return (fprintf(stderr, "file error\n"), 1);

    int height = 0;
    char empty = 0, obs = 0, full = 0;

    if (fscanf(f, "%d %c %c %c\n", &height, &empty, &obs, &full) != 4)
        return (fprintf(stderr, "map error\n"), 1);

    if (empty == obs || empty == full || obs == full)
        return (fprintf(stderr, "map error\n"), 1);

    char **map = calloc(height, sizeof(char *));
    if (!map) return (fprintf(stderr, "malloc error\n"), 1);

    int width = 0;

    for (int i = 0; i < height; i++) {
        char *line = NULL;
        size_t len = 0;
        if (getline(&line, &len, f) < 0)
            return (fprintf(stderr, "map error\n"), 1);

        int l = _strlen(line);
        if (l > 0 && line[l - 1] == '\n')
            line[--l] = '\0';

        if (!width) width = l;
        else if (l != width)
            return (fprintf(stderr, "map error\n"), 1);

        map[i] = line;
    }

    if (f != stdin) fclose(f);

    int **db = calloc(height + 1, sizeof(int *));
    for (int i = 0; i <= height; i++)
        db[i] = calloc(width + 1, sizeof(int));

    square sq = {0,0,0};

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] == empty) {
                db[i+1][j+1] = 1 + min3(db[i][j+1], db[i+1][j], db[i][j]);
                if (sq.size < db[i+1][j+1])
                    sq = (square){i, j, db[i+1][j+1]};
            } else if (map[i][j] != obs) {
                return (fprintf(stderr, "map error\n"), 1);
            }
        }
    }

    for (int i = sq.y - sq.size + 1; i <= sq.y; i++) {
        for (int j = sq.x - sq.size + 1; j <= sq.x; j++)
            map[i][j] = full;
    }

    for (int i = 0; i < height; i++) {
        fprintf(stdout, "%s\n", map[i]);
        free(map[i]);
    }
    free(map);

    for (int i = 0; i <= height; i++)
        free(db[i]);
    free(db);

    return 0;
}













#include "stdio.h"
#include "stdlib.h"

int slen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return i;
}
int min(int a, int b, int c)
{
	return a < b ? (a < c ? a : c) : (b < c ? b : c);
}
int bsq(FILE *file)
{
	char empty = 0, obstacle = 0, full = 0;
	int height = 0;
	if (fscanf(file, "%d%c%c%c\n", &height, &empty, &obstacle, &full) != 4)
		return 1;
	if (height <= 0 || empty == obstacle || empty == full || obstacle == full)
		return 1;
	char** map = calloc(height, sizeof(char*));
	int i = 0, w;
	char *line = NULL;
	size_t len = 0;
	for (; getline(&line, &len, file) != -1; i++)
	{
		if (i == height)
			return 1;
		map[i] = line;
		line = NULL;
		len = 0;
		if (i == 0)
		{
			w = slen(map[0]);
			if (w == 0 || map[0][w-1] != '\n')
				return 1;
		}
		else if (w != slen(map[i]) || map[i][w-1] != '\n')
			return 1;
	}
	if (i < height)
		return 1;
	////////////////////////////////////////////////////////////
	int **dp = calloc(height + 1, sizeof(int*));
	int y = 0, x = 0, size = 0;
	for (int i = 0; i <= height; i++)
		dp[i] = calloc(w + 1, sizeof(int));
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < w - 1; j++)
		{
			if (map[i][j] == empty)
			{
				dp[i+1][j+1] = 1 + min(dp[i][j], dp[i+1][j], dp[i][j+1]);
				if (size < dp[i+1][j+1])
					y = i, x = j, size = dp[i+1][j+1]; 
			}
			else if (map[i][j] != obstacle)
				return 1;
		}
	}
	for (int i = y - size + 1; i <= y; i++)
	{
		for (int j = x - size + 1; j <= x; j++)
			map[i][j] = full;
	}
	for (int i = 0; i < height; i++)
		fprintf(stdout, "%s", map[i]);
	return 0;
}

int main(int ac, char **av)
{
	if (ac == 1)
		bsq(stdin);
	else if (ac == 2)
	{
		FILE *file = fopen(av[1], "r");
		if (!file || bsq(file))
			fprintf(stderr, "Error: invalid map\n");
		if (file)
			fclose(file);
	}
	else
		fprintf(stderr, "Error: invalid map\n");

	return 0;
}
































