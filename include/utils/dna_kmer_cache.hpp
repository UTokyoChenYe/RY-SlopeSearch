#pragma once
#include <unordered_map>
#include <mutex>
#include <string>
#include <vector>
#include <functional>

struct DnaKmerCache {
    size_t seq_hash;
    int k;
    std::string method;

    bool operator==(const DnaKmerCache& other) const noexcept {
        return seq_hash == other.seq_hash && k == other.k && method == other.method;
    }
};

struct DnaKmerCacheHash {
    size_t operator()(const DnaKmerCache& key) const noexcept {
        size_t h1 = key.seq_hash;
        size_t h2 = std::hash<int>()(key.k);
        size_t h3 = std::hash<std::string>()(key.method);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

class ThreadSafeDnaKmerCache {
public:
    bool contains(const DnaKmerCache& key) {
        std::lock_guard<std::mutex> lock(mtx_);
        return cache_.find(key) != cache_.end();
    }

    // safe return by value; if not exists, return empty vector
    std::vector<size_t> get(const DnaKmerCache& key) {
        std::lock_guard<std::mutex> lock(mtx_);
        auto it = cache_.find(key);
        return (it != cache_.end()) ? it->second : std::vector<size_t>{};
    }

    // out version: avoid copying (recommended to use internally)
    bool try_get(const DnaKmerCache& key, std::vector<size_t>& out) {
        std::lock_guard<std::mutex> lock(mtx_);
        auto it = cache_.find(key);
        if (it == cache_.end()) return false;
        out = it->second; // if zero-copy is needed, copying is still needed here; can store shared pointers, but more complex
        return true;
    }

    void set(const DnaKmerCache& key, const std::vector<size_t>& value) {
        std::lock_guard<std::mutex> lock(mtx_);
        cache_[key] = value;
    }

    void set(DnaKmerCache key, std::vector<size_t>&& value) {
        std::lock_guard<std::mutex> lock(mtx_);
        cache_[std::move(key)] = std::move(value);
    }

private:
    std::unordered_map<DnaKmerCache, std::vector<size_t>, DnaKmerCacheHash> cache_;
    std::mutex mtx_;
};

// global cache object declaration (only declaration! do not define in multiple translation units)
extern ThreadSafeDnaKmerCache g_dna_kmer_cache;
