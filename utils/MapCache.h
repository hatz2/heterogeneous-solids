//
// Created by Alberto Elorza Rubio on 05/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_MAPCACHE_H
#define HETEROGENEOUS_SOLIDS_MAPCACHE_H

#include <map>
#include <string>
#include <functional>

namespace hs {

    template <typename T, typename K = std::string>
    class MapCache {
    private:
        std::map<K, T> storage;
    public:
        MapCache() = default;

        const T& load_or(const K& name, std::function<T()> get);
    };

    template<typename T, typename K>
    const T& MapCache<T, K>::load_or(const K& name, std::function<T()> get) {
        if (storage.count(name)) return storage[name];
        storage[name] = get();
        return storage[name];
    }

} // hs

#endif //HETEROGENEOUS_SOLIDS_MAPCACHE_H
