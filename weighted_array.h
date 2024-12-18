#pragma once

#include <vector>

template<typename T, typename W = float>
class weighted_array {
public:
	struct item {
		T value;
		W weight;
		W self_weight;
	};

	weighted_array() {}

	void push_back(T const& val, W const& weight = 1) {
		m_items.push_back(item{ val, total_weight() + weight, weight});
	}

	T& operator[](W const& w) {
		if (m_items.empty()) { return m_items[0].value; }
		int begin = 0;
		int found_idx = -1;
		int end = int(m_items.size());
		while(end != begin) {
			int mid = begin + (end - begin) / 2;
			if (w <= m_items[mid].weight) {
				if (mid == 0 || w > m_items[mid - 1].weight) {
					found_idx = mid;
					break;
				} else {
					end = mid;
				}

			} else if (w > m_items[mid].weight) {
				begin = mid;
			}
		}

		return m_items[found_idx].value;
	}

	std::vector<item>& get_items() {
		return m_items;
	}

	W total_weight() const {
		return m_items.empty() ? 0 : m_items.back().weight;
	}

private:

	std::vector<item> m_items;
};