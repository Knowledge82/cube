#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

// NO BONUS MAIN
int     main(int ac, char **av)
{
        int             fd;
        char    *line;
        int             count_lines;

        count_lines = 0;
        if (ac == 1)
        {
                fd = 0;
                printf("Reading from stdin (press Ctrl + D to stop):\n");
        }
        else
        {
                fd = open(av[1], O_RDONLY);
                if (fd == -1)
                {
                        printf("Cannot read file.\n");
                        return (1);
                }
        }
        while (1)
        {
                line = get_next_line(fd);
                if (line == NULL)
                        break;
                count_lines++;
                printf("LINE [%d] =%s\n", count_lines, line);
                free(line);
        }
        if (ac > 1)
                close(fd);

        return (0);
}

