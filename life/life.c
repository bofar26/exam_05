#include "life.h"

/* 画图：笔从 (0, 0) 开始，最初抬起。 */
static void draw(char *board, int width, int height)
{
    int x = 0;
    int y = 0;
    int pen = 0;
    char c;

    while (read(0, &c, 1) == 1)
    {
        if (c == 'w')
            y--;
        else if (c == 's')
            y++;
        else if (c == 'a')
            x--;
        else if (c == 'd')
            x++;
        else if (c == 'x')
            pen = !pen;
        if (pen && x >= 0 && x < width && y >= 0 && y < height)
            board[y * width + x] = 1;
    }
}

/* 数周围八格；越界的格子不计入。 */
static int neighbors(char *board, int width, int height, int x, int y)
{
    int count = 0;

    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            int nx = x + dx;
            int ny = y + dy;

            if (dx == 0 && dy == 0)
                continue;
            if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                count += board[ny * width + nx];
        }
    }
    return count;
}

/* 只读 board，只写 next，所有格子同时进入下一轮。 */
static void step(char *board, char *next, int width, int height)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int i = y * width + x;
            int n = neighbors(board, width, height, x, y);

            next[i] = (n == 3 || (board[i] && n == 2));
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 4)
        return 1;
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int iterations = atoi(argv[3]);

    if (width <= 0 || height <= 0 || iterations < 0)
        return 1;
    if (width > INT_MAX / height)
        return 1;
    char *board = calloc(width * height, sizeof(char));
    char *next = calloc(width * height, sizeof(char));

    if (!board || !next)
    {
        free(board);
        free(next);
        return 1;
    }
    draw(board, width, height);
    for (int i = 0; i < iterations; i++)
    {
        step(board, next, width, height);
        char *tmp = board;
        board = next;
        next = tmp;
    }
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
            putchar(board[y * width + x] ? 'O' : ' ');
        putchar('\n');
    }
    free(board);
    free(next);
    return 0;
}
