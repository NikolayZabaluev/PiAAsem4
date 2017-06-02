#ifndef SORT_H
#define SORT_H
#include <vector>
#include <algorithm>

template<typename T>
void merge(std::vector<T> &left, std::vector<T> &right, std::vector<T> &arr) {
	arr.clear();
	while ((left.size()!=0)&&(right.size()!=0)) {
		if (left.front()<=right.front()) {
			arr.push_back(left.front());
			left.erase(left.begin());
		}
		else {
			arr.push_back(right.front());
			right.erase(right.begin());
		}
	}
	arr.insert(arr.end(), left.begin(), left.end());
	arr.insert(arr.end(), right.begin(), right.end());
}

template<typename T>
void sort(std::vector<T> &arr) {
    if (arr.size()>1) {
        std::vector<T> left( arr.begin(), arr.begin()+(arr.size()>>1) );
        sort(left);
        std::vector<T> right( arr.begin()+(arr.size()>>1), arr.end() );
        sort(right);

        merge(left, right, arr);
	}

}
#endif // SORT_H