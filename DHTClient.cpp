#include "DHTClient.h"
Hash operator^(const Hash& left, const Hash&right){
	
	Hash* a;
	Hash* b;
	Hash result;
	if (left.size >= right.size) {
		a = const_cast<Hash*>(&left);
		b = const_cast<Hash*>(&right);
	}
	else {
		a = const_cast<Hash*>(&right);
		b = const_cast<Hash*>(&left);
	}


	result.size = a->size;
	for (int i = 0; i < a->size; ++i) {
		if (i < b->size)
			result.data[a->size - 1 - i] = a->data[a->size - 1 - i] ^ b->data[b->size - 1 - i];
		else
			result.data[a->size - 1 - i] = a->data[a->size - 1 - i] ^ 0;
	}

	return result;
}
bool operator<(const Hash& left, const Hash& right) {
	if (left.size != right.size)
		return left.size < right.size;
	for (int i = 0; i < left.size; ++i) {
		if (left.data[left.size - 1 - i] != right.data[right.size - 1 - i]) {
			//std::cout << int(left.data[left.size - 1 - i] < right.data[right.size - 1 - i]);
			return left.data[left.size - 1 - i] < right.data[right.size - 1 - i];
		}
	}
	return false;
}
bool operator<=(const Hash& left, const Hash& right) {
	if (left.size != right.size)
		return left.size <= right.size;
	for (int i = 0; i < left.size; ++i) {
		if (left.data[left.size - 1 - i] != right.data[right.size - 1 - i]) {
			//std::cout << int(left.data[left.size - 1 - i] < right.data[right.size - 1 - i]);
			return left.data[left.size - 1 - i] < right.data[right.size - 1 - i];
		}
	}
	return true;
}
bool operator==(const Hash& left, const Hash& right) {
	if (left.size != right.size)
		return false;
	for (int i = 0; i < left.size; ++i) {
		if (left.data[left.size - 1 - i] != right.data[right.size - 1 - i])
			return false;
	}
	return true;
}
bool operator>(const Hash& left, const Hash& right) {
	if (right < left)
		return true;
	return false;
}
bool operator>=(const Hash& left, const Hash& right) {
	if (right >= left)
		return true;
	return false;
}

