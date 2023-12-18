#include "cache_timing.h"

#include <stdio.h>
#include <stdlib.h>

#include "util.h"

const size_t REPEATS = 100000;

int main() {
    uint64_t sum_miss = 0;
    uint64_t sum_hit = 0;

    for (size_t i = 0; i < REPEATS; i++) {
        page_t *page = malloc(sizeof(page_t));
        flush_cache_line((void *) page);
        uint64_t miss = time_read((void *) page);
        uint64_t hit = time_read((void *) page);
        if (hit <= miss) {
            sum_miss += miss;
            sum_hit += hit;
        }
    }

    printf("average miss = %" PRIu64 "\n", sum_miss / REPEATS);
    printf("average hit  = %" PRIu64 "\n", sum_hit / REPEATS);
    // average miss around 263 cycles, average hit around 58
}
