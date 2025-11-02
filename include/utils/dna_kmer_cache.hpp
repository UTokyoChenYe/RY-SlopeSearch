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
        if (it == cache_.end()) {
            ++misses_;
            return false;
        }
        out = it->second; // if zero-copy is needed, copying is still needed here; can store shared pointers, but more complex
        ++hits_;
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

    // get basic cache statistics (thread-safe)
    void get_basic_stats(size_t& entries, double& hit_rate) const {
        std::lock_guard<std::mutex> lock(mtx_);
        entries = cache_.size();
        size_t total = hits_ + misses_;
        hit_rate = (total > 0) ? (100.0 * hits_ / total) : 0.0;
    }

    // get all vector sizes in the cache (thread-safe)
    std::vector<size_t> get_all_vector_sizes() const {
        std::lock_guard<std::mutex> lock(mtx_);
        std::vector<size_t> sizes;
        sizes.reserve(cache_.size());
        for (const auto& [key, vec] : cache_) {
            sizes.push_back(vec.size());
        }
        return sizes;
    }

private:
    std::unordered_map<DnaKmerCache, std::vector<size_t>, DnaKmerCacheHash> cache_;
    mutable std::mutex mtx_;
    size_t hits_ = 0;
    size_t misses_ = 0;
};

// global cache object declaration (only declaration! do not define in multiple translation units)
extern ThreadSafeDnaKmerCache g_dna_kmer_cache;
