#pragma once

#include <vector>
#include "json-develop/single_include/nlohmann/json.hpp"
using nlohmann::json;

template<typename T, typename W = float>
class weighted_array {
public:
	struct item {
		T value;
		W self_weight;
		W weight;
	};

	weighted_array() {}

	void push_back(T const& val, W const& weight = 1) {
		m_items.push_back(item{ val, weight, total_weight() + weight});
	}

	// Performs a binary search on weights (since they are always ascending)
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

	W total_weight() const {
		return m_items.empty() ? 0 : m_items.back().weight;
	}

	void normalize(W const& new_total_weight) {
		if (m_items.empty()) { return; }
		const W div = new_total_weight / m_items.back().weight;
		W curr_weight = 0;
		for (item& i : m_items) {
			i.self_weight /= div;
			curr_weight += i.self_weight;
			i.weight = curr_weight;
		}
	}

	template<typename T, typename W>
	friend void from_json(json const& js, weighted_array<T, W>& arr) {
		W curr_weight = 0;
		for (json const& object : js) {
			W w = object["weight"];
			curr_weight += w;
			arr.m_items.push_back(weighted_array<T, W>::item{object["value"], w, curr_weight});
		}
	}

	template<typename T, typename W>
	friend void to_json(json& js, weighted_array<T, W> const& arr) {
		for (item const& i : arr) {
			js.push_back(json{ {"value", i.value}, {"weight", i.self_weight} });
		}
	}

private:

	std::vector<item> m_items;
};