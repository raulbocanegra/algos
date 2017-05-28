#define CATCH_CONFIG_MAIN
#include <external/catch/catch.hpp>
#include <algorithms/sort.h>
#include <chrono>

using namespace std;
using namespace introduction::algorithms;

TEST_CASE("Insertion sort", "[insertion_sort]")
{
    std::vector<int> vec{ 6, 3, 9, 7 ,24, 1, 23, 98, 65, 4 };
    auto vec_std_sort = vec;
	cout << "Sequence to order:" << endl;
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	cout << endl;
    auto before_std_sort = std::chrono::system_clock::now();
    std::sort(vec_std_sort.begin(), vec_std_sort.end());
    auto after_std_sort = std::chrono::system_clock::now();
    auto t_std_sort = std::chrono::duration_cast<std::chrono::duration<double>>(after_std_sort - before_std_sort);

	SECTION("insertion sort")
	{
		cout << "Insertion sort:" << endl;

		auto before = std::chrono::system_clock::now();
		sorting::insertion_sort(vec.begin(), vec.end());
		auto after = std::chrono::system_clock::now();

		std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
		cout << endl;

		auto t = std::chrono::duration_cast<std::chrono::duration<double>>(after - before);
		cout << "Time: " << std::fixed << t.count() << " seconds" << endl;
		cout << "Time std::sort: " << std::fixed << t_std_sort.count() << " seconds" << endl;
        auto faster_percent = (t_std_sort.count() == 0) ? 0.0 : (100*t.count() / t_std_sort.count());
        cout << "std::sort is " << faster_percent << "% faster" << endl;
        CHECK(vec == vec_std_sort);
	}

	SECTION("merge sort")
	{
		cout << "Merge sort:" << endl;
		
		auto before = std::chrono::system_clock::now();
		sorting::merge_sort(vec.begin(), vec.end());
		auto after = std::chrono::system_clock::now();
		
		std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
		cout << endl;
		
		auto t = std::chrono::duration_cast<std::chrono::duration<double>>(after - before);
		cout << "Time: " << std::fixed << t.count() << " seconds" << endl;
		cout << "Time std::sort: " << std::fixed << t_std_sort.count() << " seconds" << endl;
        auto faster_percent = (t_std_sort.count() == 0) ? 0.0 : (100*t.count() / t_std_sort.count());
        cout << "std::sort is " << faster_percent << "% faster" << endl;
        CHECK(vec == vec_std_sort);
	}

	SECTION("bubble sort")
	{
		cout << "Bubble sort:" << endl;

		auto before = std::chrono::system_clock::now();
		sorting::bubble_sort(vec.begin(), vec.end());
		auto after = std::chrono::system_clock::now();

		std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
		cout << endl;

		auto t = std::chrono::duration_cast<std::chrono::duration<double>>(after - before);
		cout << "Time: " << std::fixed << t.count() << " seconds" << endl;
		cout << "Time std::sort: " << std::fixed << t_std_sort.count() << " seconds" << endl;
        auto faster_percent = (t_std_sort.count() == 0) ? 0.0 : (100*t.count() / t_std_sort.count());
        cout << "std::sort is " << faster_percent << "% faster" << endl;
        CHECK(vec == vec_std_sort);
	}

	SECTION("heap sort")
	{
		cout << "Heap sort:" << endl;

		auto before = std::chrono::system_clock::now();
		sorting::heap_sort(vec.begin(), vec.end());
		auto after = std::chrono::system_clock::now();

		std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
		cout << endl;

		auto t = std::chrono::duration_cast<std::chrono::duration<double>>(after - before);
		cout << "Time: " << std::fixed << t.count() << " seconds" << endl;
		cout << "Time std::sort: " << std::fixed << t_std_sort.count() << " seconds" << endl;
        auto faster_percent = (t_std_sort.count() == 0) ? 0.0 : (100*t.count() / t_std_sort.count());
        cout << "std::sort is " << faster_percent << "% faster" << endl;
        CHECK(vec == vec_std_sort);
	}

}
