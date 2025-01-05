#ifndef MYUNORDEREDMAP_H
#define MYUNORDEREDMAP_H
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <functional>
#include <stdexcept>

// MyUnorderedMap ��ʵ��
template <typename T>
class MyUnorderedMap {
private:
	static const int TABLE_SIZE = 10;  // ��ϣ���Ͱ��

	// ��ϣ������ʹ�ö����id���й�ϣ
	int hash(int key) {
		key = key ^ (key >> 16);   // ������
		key = key * 0x45d9f3b;     // �����˷�
		key = key ^ (key >> 16);   // �ٴ����
		return key % TABLE_SIZE;
	}
	// ��������ķ�������
	int partition(std::vector<T>& elements, int low, int high, bool ascending) {
		T pivot = elements[high];  // ѡ�����һ��Ԫ����Ϊ��׼
		int i = low - 1;  // С�ڻ�׼��Ԫ�ص�����

		// ��������ʽѡ��С�ڻ�׼���Ǵ��ڻ�׼
		for (int j = low; j < high; ++j) {
			if ((ascending && elements[j].getId() <= pivot.getId()) ||
				(!ascending && elements[j].getId() >= pivot.getId())) {
				i++;
				std::swap(elements[i], elements[j]);
			}
		}
		std::swap(elements[i + 1], elements[high]);  // ����׼Ԫ�طŵ���ȷλ��
		return i + 1;
	}

	// ��������ĵݹ�ʵ��
	void quickSortHelper(std::vector<T>& elements, int low, int high, bool ascending) {
		if (low < high) {
			int pi = partition(elements, low, high, ascending);  // ��ȡ����λ��
			quickSortHelper(elements, low, pi - 1, ascending);  // ��������������
			quickSortHelper(elements, pi + 1, high, ascending);  // ��������������
		}
	}
public:
	std::vector<std::list<T>> table;  // ������ʵ��ÿ��Ͱ
	MyUnorderedMap() {
		table.resize(TABLE_SIZE);
	}

	// ����һ���û�
	void insert(const T& user) {
		int index = hash(user.getId());
		table[index].push_back(user);
	}

	// �����û�������һ��ָ���û���ָ��
	T* find(int id) {
		int index = hash(id);
		for (auto& user : table[index]) {
			if (user.getId() == id) {
				return &user;  // �ҵ��û�������ָ��
			}
		}
		return nullptr;  // ���û���ҵ�������nullptr
	}

	// ɾ���û�
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

	// ��ȡ��ϣ���е��û�����
	size_t size() const {
		size_t count = 0;
		for (const auto& bucket : table) {
			count += bucket.size();
		}
		return count;
	}

	// �жϹ�ϣ���Ƿ�Ϊ��
	bool empty() const {
		return size() == 0;
	}

	// ��չ�ϣ��
	void clear() {
		for (auto& bucket : table) {
			bucket.clear();
		}
	}

	// ������ǰ��ϣ������һ����ϣ��
	void swap(MyUnorderedMap<T>& other) {
		std::swap(table, other.table);
	}

	// ��ȡͰ������
	size_t bucket_count() const {
		return TABLE_SIZE;
	}

	// ��ȡ�ض�Ͱ������
	size_t bucket(int id) const {
		return hash(id);
	}

	// ��ȡָ��Ͱ��Ԫ������
	size_t bucket_size(int index) const {
		return table[index].size();
	}

	// ��ȡ begin �� end ������
	auto begin() {
		for (auto bucket_it = table.begin(); bucket_it != table.end(); ++bucket_it) {
			if (!bucket->empty()) {
				return bucket.begin();  // ���ص�һ���ǿ�Ͱ�ĵ�����
			}
		}
		return table.end();  // ���û��Ԫ�أ����� end
	}

	auto end() {
		return table.end();
	}
	//����
	// ��ȡ����Ԫ�ز�ʹ�ÿ����������򣬷��������Ľ��
	std::vector<T> getAllElements_asc(bool ascending = true) {
		std::vector<T> allElements;

		// ��ȡ����Ͱ�е�Ԫ��
		for (const auto& bucket : table) {
			for (const auto& user : bucket) {
				if (std::find(allElements.begin(), allElements.end(), user) == allElements.end()) {
					allElements.push_back(user);
				}
			}
		}

		// ʹ�ÿ������������Ԫ�ؽ�������
		quickSortHelper(allElements, 0, allElements.size() - 1, ascending);

		return allElements;
	}
	//����
	std::vector<T> getAllElements_des(bool ascending = false) {
		std::vector<T> allElements;

		// ��ȡ����Ͱ�е�Ԫ��
		for (const auto& bucket : table) {
			for (const auto& user : bucket) {
				if (std::find(allElements.begin(), allElements.end(), user) == allElements.end()) {
					allElements.push_back(user);
				}
			}
		}

		// ʹ�ÿ������������Ԫ�ؽ�������
		quickSortHelper(allElements, 0, allElements.size() - 1, ascending);

		return allElements;
	}
};
#endif