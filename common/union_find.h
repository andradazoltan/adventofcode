#pragma once

#include <vector>

class UnionFind {
public:
    UnionFind(int n) {      
        // Initialize each node to have itself be the representative
        graph.resize(n);
        for (int i = 0; i < n; i++) {
            graph[i] = i;
        }

        // Initialize size array with 1s
        size.resize(n, 1);
    }

    /**
     * Find the representative for the set that includes i.
     */
    int find(int i) {
        int root = graph[i];
      
        if (graph[root] != root) {
            return graph[i] = find(root);
        }
      
        return root;
    }

    /**
     * Unite the set that includes i and the set that includes j;
     */
    void unite(int i, int j) {
        int irep = find(i);
        int jrep = find(j);

        // They are in the same set, no action needed
        if (irep == jrep)
            return;

        int isize = size[irep];
        int jsize = size[jrep];

        // If i’s size is less than j’s size then move i under j
        if (isize < jsize) {
            graph[irep] = jrep;
            size[jrep] += size[irep];
        }
        // Otherwise move j under i
        else {
            graph[jrep] = irep;
            size[irep] += size[jrep];
        }
    }

    /**
     * Get the size of all the sets in a sorted list.
     */
    std::vector<int> get_sorted_size_of_sets(void) {
        std::vector<int> result;

        for (int i = 0; i < graph.size(); i++) {
            if (graph[i] == i)
                result.push_back(size[i]);
        }    

        std::sort(result.begin(), result.end(), [](int a, int b){ return a > b;});

        return result;
    }

private:
    std::vector<int> graph;
    std::vector<int> size; 
};
