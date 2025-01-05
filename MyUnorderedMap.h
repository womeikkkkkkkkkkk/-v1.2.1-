#ifndef MYUNORDEREDMAP_H
#define MYUNORDEREDMAP_H
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <functional>
#include <stdexcept>

// MyUnorderedMap 类实现
template <typename T>
class MyUnorderedMap {
private:
	static const int TABLE_SIZE = 10;  // 哈希表的桶数

	// 哈希函数：使用对象的id进行哈希
	int hash(int key) {
		key = key ^ (key >> 16);   // 异或操作
		key = key * 0x45d9f3b;     // 常数乘法
		key = key ^ (key >> 16);   // 再次异或
		return key % TABLE_SIZE;
	}
	// 快速排序的分区函数
	int partition(std::vector<T>& elements, int low, int high, bool ascending) {
		T pivot = elements[high];  // 选择最后一个元素作为基准
		int i = low - 1;  // 小于基准的元素的索引

		// 根据排序方式选择小于基准还是大于基准
		for (int j = low; j < high; ++j) {
			if ((ascending && elements[j].getId() <= pivot.getId()) ||
				(!ascending && elements[j].getId() >= pivot.getId())) {
				i++;
				std::swap(elements[i], elements[j]);
			}
		}
		std::swap(elements[i + 1], elements[high]);  // 将基准元素放到正确位置
		return i + 1;
	}

	// 快速排序的递归实现
	void quickSortHelper(std::vector<T>& elements, int low, int high, bool ascending) {
		if (low < high) {
			int pi = partition(elements, low, high, ascending);  // 获取分区位置
			quickSortHelper(elements, low, pi - 1, ascending);  // 对左子区间排序
			quickSortHelper(elements, pi + 1, high, ascending);  // 对右子区间排序
		}
	}
public:
	std::vector<std::list<T>> table;  // 用链表实现每个桶
	MyUnorderedMap() {
		table.resize(TABLE_SIZE);
	}

	// 插入一个用户
	void insert(const T& user) {
		int index = hash(user.getId());
		table[index].push_back(user);
	}

	// 查找用户，返回一个指向用户的指针
	T* find(int id) {
		int index = hash(id);
		for (auto& user : table[index]) {
			if (user.getId() == id) {
				return &user;  // 找到用户，返回指针
			}
		}
		return nullptr;  // 如果没有找到，返回nullptr
	}

	// 删除用户
	void remove(int id) {
		int index = hash(id);
		auto& bucket = table[index];
		for (auto it = bucket.begin(); it != bucket.end(); ++it) {
			if (it->getId() == id) {
				bucket.erase(it);
				break;
			}
		}
	}

	// 获取哈希表中的用户数量
	size_t size() const {
		size_t count = 0;
		for (const auto& bucket : table) {
			count += bucket.size();
		}
		return count;
	}

	// 判断哈希表是否为空
	bool empty() const {
		return size() == 0;
	}

	// 清空哈希表
	void clear() {
		for (auto& bucket : table) {
			bucket.clear();
		}
	}

	// 交换当前哈希表与另一个哈希表
	void swap(MyUnorderedMap<T>& other) {
		std::swap(table, other.table);
	}

	// 获取桶的数量
	size_t bucket_count() const {
		return TABLE_SIZE;
	}

	// 获取特定桶的索引
	size_t bucket(int id) const {
		return hash(id);
	}

	// 获取指定桶的元素数量
	size_t bucket_size(int index) const {
		return table[index].size();
	}

	// 获取 begin 和 end 迭代器
	auto begin() {
		for (auto bucket_it = table.begin(); bucket_it != table.end(); ++bucket_it) {
			if (!bucket->empty()) {
				return bucket.begin();  // 返回第一个非空桶的迭代器
			}
		}
		return table.end();  // 如果没有元素，返回 end
	}

	auto end() {
		return table.end();
	}
	//升序
	// 提取所有元素并使用快速排序排序，返回排序后的结果
	std::vector<T> getAllElements_asc(bool ascending = true) {
		std::vector<T> allElements;

		// 提取所有桶中的元素
		for (const auto& bucket : table) {
			for (const auto& user : bucket) {
				if (std::find(allElements.begin(), allElements.end(), user) == allElements.end()) {
					allElements.push_back(user);
				}
			}
		}

		// 使用快速排序对所有元素进行排序
		quickSortHelper(allElements, 0, allElements.size() - 1, ascending);

		return allElements;
	}
	//降序
	std::vector<T> getAllElements_des(bool ascending = false) {
		std::vector<T> allElements;

		// 提取所有桶中的元素
		for (const auto& bucket : table) {
			for (const auto& user : bucket) {
				if (std::find(allElements.begin(), allElements.end(), user) == allElements.end()) {
					allElements.push_back(user);
				}
			}
		}

		// 使用快速排序对所有元素进行排序
		quickSortHelper(allElements, 0, allElements.size() - 1, ascending);

		return allElements;
	}
};
#endif