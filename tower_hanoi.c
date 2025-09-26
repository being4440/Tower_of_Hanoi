/*
 * tower_of_hanoi.c
 * Console visualizer for Tower of Hanoi (ANSI terminals)
 *
 * Usage:
 *   gcc -O2 -Wall -o tower_of_hanoi tower_of_hanoi.c
 *   ./tower_of_hanoi [num_disks] [delay_ms]
 *
 * Examples:
 *   ./tower_of_hanoi        # prompts for number of disks (recommended <= 8)
 *   ./tower_of_hanoi 5 150  # 5 disks, 150 ms delay between moves
 *
 * Notes:
 * - The program uses ANSI escape codes to clear and redraw the screen.
 * - On Windows you may need a terminal that supports ANSI sequences (Windows 10+),
 *   or run in an environment like Git Bash or Windows Terminal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
static void msleep(unsigned int ms) { Sleep(ms); }
#else
#include <unistd.h>
static void msleep(unsigned int ms) { usleep(ms * 1000); }
#endif

#define MAX_DISKS 12

/* Simple stack representation for three pegs. 1..n disk sizes (1 smallest)
 * pegs[peg][0] is bottom, top index tracked by heights[peg]-1 */
static int pegs[3][MAX_DISKS];
static int heights[3];
static int total_disks = 0;
static unsigned long move_count = 0;
static unsigned int delay_ms = 500;

/* ANSI helpers */
static void clear_screen() {
    /* Clear screen and move cursor home */
    printf("\x1b[2J\x1b[H");
}

/* Draw current state to terminal */
static void draw_state(void) {
    clear_screen();
    int i, p, level;
    int max_h = total_disks; /* height of tower drawing */
    int peg_spacing = (total_disks * 2) + 6; /* spacing between pegs */
    int max_width = total_disks * 2 + 1; 

    /* draw header */
    printf("Tower of Hanoi — disks=%d  moves=%lu\n\n", total_disks, move_count);

    /* draw each level from top to bottom */
    for (level = max_h - 1; level >= 0; --level) {
        for (p = 0; p < 3; ++p) {
            int disk_size = 0; /* 0 => no disk at this level */
            int h = heights[p];
            if (level < h) {
                /* disk present at this vertical level */
                disk_size = pegs[p][level];
            }

            /* center area for one peg */
            int pad = (max_width - (disk_size ? (2 * disk_size - 1) : 1)) / 2;
            /* left padding */
            for (i = 0; i < pad; ++i) putchar(' ');

            if (disk_size) {
                /* draw disk using '=' characters and disk number in middle */
                int disk_width = 2 * disk_size - 1;
                int mid = disk_width / 2;
                for (i = 0; i < disk_width; ++i) {
                    if (i == mid) {
                        /* show disk size for readability */
                        printf("%d", disk_size);
                        /* if number is multi-digit, we already printed, skip one char space */
                        if (disk_width - 1 > i) i += 0; /* no-op; just clarity */
                    } else {
                        putchar('=');
                    }
                }
            } else {
                /* draw the peg rod as '|' */
                putchar('|');
            }

            /* right padding */
            for (i = 0; i < pad; ++i) putchar(' ');

            /* spacing between pegs */
            for (i = 0; i < 4; ++i) putchar(' ');
        }
        putchar('\n');
    }

    /* draw base labels */
    for (p = 0; p < 3; ++p) {
        int label_pad = (max_width - 1) / 2;
        for (i = 0; i < label_pad; ++i) putchar(' ');
        printf("%c", 'A' + p);
        for (i = 0; i < label_pad; ++i) putchar(' ');
        for (i = 0; i < 4; ++i) putchar(' ');
    }
    putchar('\n');

    fflush(stdout);
}

/* push and pop helpers (push to top) */
static void push_disk(int peg, int disk) {
    if (heights[peg] >= MAX_DISKS) return;
    pegs[peg][heights[peg]++] = disk;
}

static int pop_disk(int peg) {
    if (heights[peg] == 0) return 0;
    return pegs[peg][--heights[peg]];
}

/* perform a single move and animate */
static void move_single(int from, int to) {
    int d = pop_disk(from);
    push_disk(to, d);
    ++move_count;
    draw_state();
    msleep(delay_ms);
}

/* recursive algorithm */
static void hanoi(int n, int from, int to, int aux) {
    if (n <= 0) return;
    if (n == 1) {
        move_single(from, to);
        return;
    }
    hanoi(n - 1, from, aux, to);
    move_single(from, to);
    hanoi(n - 1, aux, to, from);
}

int main(int argc, char **argv) {
    int i;
    int n = 0;

    if (argc >= 2) {
        n = atoi(argv[1]);
    }
    if (argc >= 3) {
        int d = atoi(argv[2]);
        if (d > 0) delay_ms = (unsigned int)d;
    }

    if (n <= 0) {
        printf("Enter number of disks (recommended 1..8): ");
        if (scanf("%d", &n) != 1) return 0;
    }

    if (n < 1) n = 1;
    if (n > MAX_DISKS) n = MAX_DISKS;
    total_disks = n;

    /* initialize pegs */
    for (i = 0; i < 3; ++i) heights[i] = 0;
    for (i = n; i >= 1; --i) push_disk(0, i); /* peg A holds all disks initially */

    draw_state();
    printf("Starting in 1 second...\n");
    msleep(1000);

    hanoi(n, 0, 2, 1);

    draw_state();
    printf("\nDone! Total moves: %lu\n", move_count);
    return 0;
}
