// hanoi.c
// Combined: DSA Hanoi algorithm + native moves.json generator.
// - Exports run_hanoi, get_move_from, get_move_to (for WASM via emcc)
// - main(argc,argv) writes moves.json when compiled natively and run.

#include <stdio.h>
#include <stdlib.h>
// hanoi.c
// Combined: DSA Hanoi algorithm + native moves.json generator.
// - Exports run_hanoi, get_move_from, get_move_to (for WASM via emcc)
// - main(argc,argv) writes moves.json when compiled natively and run.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct { int from; int to; } Move;

// Dynamic array of moves
static Move *moves = NULL;
static size_t moves_cap = 0;
static size_t moves_len = 0;

static void ensure_cap(size_t need) {
    if (moves_cap >= need) return;
    size_t nc = moves_cap ? moves_cap * 2 : 1024;
    while (nc < need) nc *= 2;
    Move *p = realloc(moves, nc * sizeof(Move));
    if (!p) { perror("realloc"); exit(1); }
    moves = p;
    moves_cap = nc;
}

static void record_move(int from, int to) {
    ensure_cap(moves_len + 1);
    moves[moves_len].from = from;
    moves[moves_len].to = to;
    moves_len++;
}

static void hanoi_rec(int n, int a, int b, int c) {
    if (n == 0) return;
    hanoi_rec(n-1, a, c, b);
    record_move(a, b);
    hanoi_rec(n-1, c, b, a);
}

// API used from JS (WASM): compute moves into internal buffer and return count
int run_hanoi(int n) {
    moves_len = 0;
    hanoi_rec(n, 0, 2, 1);
    return (int)moves_len;
}

int get_move_from(int i) { if ((size_t)i < moves_len) return moves[i].from; return -1; }
int get_move_to(int i)   { if ((size_t)i < moves_len) return moves[i].to;   return -1; }

// Native helper: write moves.json to stdout or file
static int write_moves_json(const char *path, int n) {
    FILE *f = fopen(path, "w");
    if (!f) { perror("fopen"); return 1; }
    fprintf(f, "{\n  \"n\": %d,\n  \"moves\": [\n", n);
    for (size_t i = 0; i < moves_len; ++i) {
        fprintf(f, "    [%d,%d]", moves[i].from, moves[i].to);
        if (i + 1 < moves_len) fprintf(f, ",\n"); else fprintf(f, "\n");
    }
    fprintf(f, "  ]\n}\n");
    fclose(f);
    return 0;
}

#ifdef __EMSCRIPTEN__
// When compiled for WASM, there's no main; exports are controlled at link time.
#else
// Native main: generate moves.json (default n=4) or to stdout if '-' given
int main(int argc, char **argv) {
    int n = 4;
    if (argc > 1) n = atoi(argv[1]);
    if (n < 0) n = 0;
    run_hanoi(n);
    const char *out = "moves.json";
    if (argc > 2) out = argv[2];
    int rc = write_moves_json(out, n);
    fprintf(stderr, "Wrote %s with %zu moves (n=%d)\n", out, moves_len, n);
    return rc;
}
#endif
