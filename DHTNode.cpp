
#include "DHTNode.h"

DHTNode::DHTNode(const Hash& clientHash) {
	hashes_count = 0;
	buckets_count = 1;
	this->clientHash = clientHash;
	Bucket* firstBucket = new Bucket(&clientHash);
	firstBucket->end.size = firstBucket->end.capacity;
	for (int i = 0; i < firstBucket->end.size; ++i)
		firstBucket->end.data[i] = 0xFF;
	Buckets.insert(firstBucket);
}

void DHTNode::divideBucket(std::set<Bucket*, pBucketComparator>::iterator iterBucket) {
	auto iterMiddleClient((*iterBucket)->clients.begin());
	int lenMoveIterator = int((*iterBucket)->clients.size() / 2);
	std::advance(iterMiddleClient, lenMoveIterator);
	
	
	Bucket* newBucket = new Bucket(&clientHash);
	newBucket->pClientHash = (*iterBucket)->pClientHash;
	Client* pMiddleClient = *iterMiddleClient;
	newBucket->start = pMiddleClient->hash ^ clientHash;
	newBucket->end = (*iterBucket)->end;

	auto iterNewBucket(iterMiddleClient);
	while (iterNewBucket != (*iterBucket)->clients.end()) {
		newBucket->clients.push_back(*iterNewBucket);
		++iterNewBucket;
	}
	(*iterBucket)->clients.erase(iterMiddleClient, (*iterBucket)->clients.end());
	(*iterBucket)->end = newBucket->start;
	Buckets.insert(newBucket);
	++buckets_count;
		
}

iterPair DHTNode::findElement(const Hash* hashFind) const{
	auto iterBucket(Buckets.find(hashFind));
	if (iterBucket != Buckets.end()) {
		for (std::vector<Client*>::iterator iterClient = (*iterBucket)->clients.begin(); iterClient < (*iterBucket)->clients.end();++iterClient) {
			if ((*iterClient)->hash == *hashFind) {
				return { iterBucket, iterClient };
			}
		}
	}
	return {Buckets.end()};
}

int DHTNode::removeElement(iterPair link) {
	(*link.iterBucket)->clients.erase(link.iterHash);
	return 0;
}
	
int DHTNode::removeElement(const Hash* hashRemove) {
	
	iterPair link(findElement(hashRemove));
	if (link.iterBucket != Buckets.end()) {
		removeElement(link);
		return 0;
	}
	return -1;
}

int DHTNode::addElement(const Client* clientAdd) {
	Hash hash_used_to_find_bucket(clientAdd->hash ^ clientHash);
	auto iterBucket(Buckets.find(&hash_used_to_find_bucket));
	(*iterBucket)->clients.push_back(const_cast<Client *>(clientAdd));
	++hashes_count;
	(*iterBucket)->sortBucket();
	if ((*iterBucket)->clients.size() > current_max_bucket_size) {
		divideBucket(iterBucket);
		return 1;
	}
	return 0;
}

Client* DHTNode::SeekNode(const Hash* seekNodeHash) const{
	Client* closeClient = nullptr;
	bool isfirsttime = true;
	for (auto pBucket : Buckets) {
		for (auto pClient : pBucket->clients) {
			if (isfirsttime) {
				closeClient = pClient;
				isfirsttime = false;
			}
			if ((pClient->hash ^ *seekNodeHash) < (closeClient->hash ^ *seekNodeHash)) {
				closeClient = pClient;
			}
		}
	}
	return closeClient;
}