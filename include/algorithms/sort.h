#ifndef _ALGORITHMS_SORT_HEADER_
#define _ALGORITHMS_SORT_HEADER_

#include <algorithm>

namespace algorithms { namespace sorting
{
    template< class RandomIt >
    void insertion_sort(RandomIt first, RandomIt last)
    {
        if (first == last)
            return;

        auto begin = first;
        while (begin != (last - 1))
        {
            auto comp = begin;
            auto key = *(begin + 1);
            while ( (comp >= first) && (*comp > key) )
            {
                std::iter_swap(comp + 1, comp);
                if (comp == first)
                    break;
                --comp;
            }
            ++begin;
        }
    }

    template< class RandomIt >
    void merge_sort(RandomIt first, RandomIt last)
    {
        if (first < last - 1)
        {
            auto mid = std::next(first, std::distance(first, last) / 2);
            merge_sort(first, mid);
            merge_sort(mid, last);
            std::inplace_merge(first, mid, last);
        }
    }

    template< class RandomIt >
    void bubble_sort(RandomIt first, RandomIt last)
    {
        for (auto up = first; up <= last - 2; ++up)
        {
            for (auto down = last - 1; down >= up + 1 ; --down)
            {
                if (*down < *(down -1))
                {
                    std::iter_swap(down, down - 1);
                }
            }
        }
    }

    template< class RandomIt >
    void heap_sort(RandomIt first, RandomIt last)
    {
        std::make_heap(first, last);
        for (auto end = last - 1; end > first; --end)
        {
            std::iter_swap(first, end);
            std::make_heap(first, end);
        }
    }

    template< class ForwardIt >
    void quick_sort(ForwardIt first, ForwardIt last)
    {
        if (first == last) return;
        auto pivot = *(last-1);
        ForwardIt middle1 = std::partition(first, last,	[pivot](const auto& em) { return em < pivot; });
        ForwardIt middle2 = std::partition(middle1, last, [pivot](const auto& em) { return !(pivot < em); });
        quick_sort(first, middle1);
        quick_sort(middle2, last);
    }
}} // namespace algorithms::sorting
#endif
