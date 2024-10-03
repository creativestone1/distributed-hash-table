#pragma once
#include "DHTClient.h"
struct Bucket {
	Bucket(const Hash* pointerClientHash):pClientHash(pointerClientHash) { std::cout << "Bucket Inited\n"; }
	~Bucket() { std::cout << "Bucket Closed\n"; }
	const Hash* pClientHash;
	Hash start;
	Hash end;
	std::vector<Client*> clients;
	int sortBucket() {
		int n = clients.size();
		if (n == 0 || n == 1)
			return 0;
		for (int i = 0; i < n - 1; ++i) {
			for (int j = i + 1; j < n;j++) {
				if ((clients[i]->hash^*pClientHash) > (clients[j]->hash^*pClientHash)) {
					Client* a = clients[i];
					clients[i] = clients[j];
					clients[j] = a;
				}
			}
		}
		return 1;
	}
	bool isInBucket(const Client* client) {
		for (auto it : clients) {
			if (it->hash == client->hash) {
				return true;
			}
		}
		return false;
	}
	bool isInBucket(const Hash* hash) {
		for (auto it : clients) {
			if (it->hash == *hash) {
				return true;
			}
		}
		return false;
	}
};
struct pBucketComparator {
	using is_transparent = void;

	bool operator()(const Bucket* bucket1, const Bucket* bucket2) const{
		return (bucket1->start < bucket2->start);
	}
	bool operator()(const Bucket* bucket, const Hash* hashComp) const{
		return (bucket->end < (*hashComp));
	}
	bool operator()(const Hash* hashComp, const Bucket* bucket) const{
		return ((*hashComp) < bucket->start);
	}

};
