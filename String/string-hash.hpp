#pragma once

#include "../Template/template.hpp"

template <typename T>
struct StringHash {
    vector<T> hash, mod_pow;
    T mod;
    size_t base;
    size_t _size;

    StringHash(const string &s = "", T _mod = 998244353, size_t _base = 31)
        : hash(s.length() + 1, 0),
          mod_pow(s.length() + 1, 0),
          mod(_mod),
          base(_base),
          _size(s.length()) {
        build(s);
    }

    void build(const string &s) {
        mod_pow[0] = 1;
        for (int i = 1; i <= (int)_size; i++) {
            mod_pow[i] = mod_pow[i - 1] * base % mod;
            hash[i] = (hash[i - 1] * base % mod + (int)s[i - 1]) % mod;
        }
    }

    // hash[l...r] = \sum_{i=l}^{r} {s[i] * base ^ {r-i}}
    //             = hash[r] - hash[l - 1] * base ^ {r-l+1}
    T get_hash(int l, int r) const {
        if (l > r) return 0;
        assert(1 <= l && r <= _size);
        return (hash[r] - hash[l - 1] * mod_pow[r - l + 1] % mod + mod) % mod;
    }

    inline void add(const char &c) {
        int i = ++_size;
        mod_pow.emplace_back(mod_pow[i - 1] * base % mod);
        hash.emplace_back((hash[i - 1] * base % mod + (int)c) % mod);
    }
    void add(const string &t) {
        for (auto &c : t) {
            add(c);
        }
    }

    size_t size() const { return _size; }
};

template <typename T, size_t _size = 2>
struct MultiModStringHash {
   private:
    array<StringHash<T>, _size> hashes;

   public:
    MultiModStringHash(const string &s = "",
                       const array<T, _size> mods = {998244353, (T)(1e9 + 7)},
                       const array<size_t, _size> basis = {31, 233}) {
        for (size_t i = 0; i < _size; i++) {
            hashes[i] = StringHash<T>(s, mods[i], basis[i]);
        }
    }

    void add(const char &c) {
        for (size_t i = 0; i < _size; i++) {
            hashes[i].add(c);
        }
    }
    void add(const string &t) {
        for (size_t i = 0; i < _size; i++) {
            hashes[i].add(t);
        }
    }

    vector<T> get_hash(int l, int r) const {
        vector<T> res(_size, 0);
        for (size_t i = 0; i < _size; i++) {
            res[i] = hashes[i].get_hash(l, r);
        }
        return res;
    }

    const StringHash<T> &operator[](int k) const { return hashes[k]; }
    size_t size() const {
        assert(_size > 0);
        return hashes[0].size();
    }
};