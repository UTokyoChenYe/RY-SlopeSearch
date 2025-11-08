#pragma once
#include <cstddef>

struct KmerCount {
    size_t kmer;
    int count;
};

// struct KmerCount {
//     uint64_t kmer;
//     uint32_t count;
// } __attribute__((packed));