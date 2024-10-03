#pragma once
#include <set>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include <iostream>


struct Hash {
	Hash() : size(1), capacity(STANDART_HASH_CAPACITY) {
		data[0] = uint8_t(0x00); //std::cout << "Hash Inited\n";// std::cout << (int)data[0];
	}
	static const std::size_t STANDART_HASH_CAPACITY = 3;
	uint8_t data[STANDART_HASH_CAPACITY];
	std::size_t size;
	std::size_t capacity;
};

Hash operator^(const Hash& left, const Hash& right);
bool operator<(const Hash& left, const Hash& right);
bool operator<=(const Hash& left, const Hash& right);
bool operator==(const Hash& left, const Hash& right);
bool operator>(const Hash& left, const Hash& right);
bool operator>=(const Hash& left, const Hash& right);



struct Client {
	Hash hash;
	uint32_t ip;
	uint16_t port;
};

struct pClientComparator {
	const Hash* pCompareHash;
	pClientComparator(const Hash* hash_to_compare_with) : pCompareHash(hash_to_compare_with) {}

	bool operator()(const Client* client1,const Client* client2) const{
		//std::cout << "hash compataror\n";
		return (client1->hash ^ (*pCompareHash)) < (client2->hash ^ (*pCompareHash));
	}
};







