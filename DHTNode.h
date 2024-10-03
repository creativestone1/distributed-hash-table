#pragma once
#include <set>
#include <stdint.h>
#include <string>

#include "DHTBucket.h"

struct iterPair {
	std::set<Bucket*, pBucketComparator>::iterator iterBucket;
	std::vector<Client*>::iterator iterHash;
};

class DHTNode {
public:
	Hash clientHash;
	std::size_t hashes_count;
	std::size_t buckets_count;
	std::size_t current_max_bucket_size = 3;
	std::set<Bucket*, pBucketComparator> Buckets;
	
	DHTNode(const Hash& clientHash);

	void divideBucket(std::set<Bucket*, pBucketComparator>::iterator iterBucket);

	iterPair findElement(const Hash* hashFind) const;

	int removeElement(iterPair link);

	int removeElement(const Hash* hashRemove);

	int addElement(const Client* clientAdd);

	Client* SeekNode(const Hash* seekNodeHash) const;
};