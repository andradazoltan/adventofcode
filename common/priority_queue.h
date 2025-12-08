/**
 * Priority queue data structure using min heap property.
 */
#pragma once

#include <vector>
#include <tuple>
#include <algorithm>

template <class T> class PriorityQueue {
    public:
        PriorityQueue() {}
        ~PriorityQueue() {}
        
        /**
        * Insert a new element val with priority prio.
        */
        void insert(int prio, T val) {
            pq.push_back(std::tuple<int, T>{prio, val});
            shift_up(pq.size() - 1);
        }

        /**
         * Pop the element with minimum priority.
         */
        T pop(void) {
            if (pq.size() == 0) return T();

            T result = std::get<1>(pq[0]);
            pq[0] = pq[pq.size() - 1];
            pq.pop_back();
            shift_down(0);

            return result;
        }

    private:
        std::vector<std::tuple<int, T>> pq;

        inline int parent(int i) {
            return (i - 1) / 2;
        }

        inline int left_child(int i) {
            return (2 * i) + 1;
        }

        inline int right_child(int i) {
            return (2 * i) + 2;
        }

        /**
         * Shift elements up starting at index i to maintain the
         * min heap property.
         */
        void shift_up(int i) {
            while ((i > 0) && (std::get<0>(pq[parent(i)]) > std::get<0>(pq[i]))) {
                std::swap(pq[parent(i)], pq[i]);
                i = parent(i);
            }
        }

        /**
         * Shift elements down starting at index i to maintain the
         * min heap property.
         */
        void shift_down(int i) {
            int min_i = i;

            int l = left_child(i);
            if ((l < pq.size()) && (std::get<0>(pq[l]) < std::get<0>(pq[min_i]))) {
                min_i = l;
            }
            int r = right_child(i);
            if ((r < pq.size()) && (std::get<0>(pq[r]) < std::get<0>(pq[min_i]))) {
                min_i = r;
            }

            if (i != min_i) {
                std::swap(pq[i], pq[min_i]);
                shift_down(min_i);
            }
        }
};
