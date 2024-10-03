#include <iostream>
#include <cstdlib>
#include <ctime>
#include "DHTNode.h"
#include <random>
Hash ClientHash;
Hash generateRandomHash() {
	Hash newHash;
	newHash.size = Hash::STANDART_HASH_CAPACITY - int(((double)std::rand() / RAND_MAX) * 2 );
	for (int i = 0; i < newHash.size; ++i) {
		newHash.data[i] = uint8_t(((double)std::rand() / RAND_MAX) * 255.);
	}
	return newHash;
}
void printHash(const Hash& hash) {
	std::cout << '[';
	for (int i = 0; i < hash.size; ++i) {
		std::cout << int(hash.data[hash.size - 1 - i]);
		if (i != hash.size - 1)
			std::cout << '|';
	}
	std::cout << ']';
}
void printClient(const Client& client) {
	std::cout << '[';
	for (int i = 0; i < client.hash.size; ++i) {
		std::cout << int(client.hash.data[client.hash.size - 1 - i]);
		if (i != client.hash.size - 1)
			std::cout << '|';
	}
	std::cout << "]\txor:\t";
	printHash(client.hash ^ ClientHash);
	std::cout << "\t| ip: " << client.ip << "\tport\t" << client.port << "|\n";
}
void printBucket(const Bucket& bucket, int bucketNum) {
	std::cout << "\nBUCKET" << bucketNum << '\n';
	std::cout << "from:\t"; 
	printHash(bucket.start);
	std::cout << '\n';
	std::cout << "to:\t";
	printHash(bucket.end);
	std::cout << '\n';
	std::cout << "INSIDE:\n";
	for (auto i : bucket.clients) {
		printClient(*i);
		std::cout << " ";
	}
	std::cout << '\n'<<'\n';
}
int main(){
	std::random_device rd;
	unsigned int seed = rd() ^ static_cast<unsigned int>(time(0));
	srand(seed);
	
	
	ClientHash = generateRandomHash();
	std::cout << "Generated: ";
	printHash(ClientHash);
	std::cout << '\n';


	DHTNode dht(ClientHash);
	
	{
		int j = 1;
		for (auto i : dht.Buckets) {
			printBucket(*i, j);
			++j;
		}
	}

	
	for (int k = 0; k < 10; k++) {
		std::cout << "//////////////////////////////////////////////////////////////////////\n";
		std::cout << "k = " << k << '\n';
		Client* newClient = new Client({ generateRandomHash(), 32647, 1080 });
		std::cout << "Generated: ";
		printClient(*newClient);
		std::cout << '\n'<<'\n';
		dht.addElement(newClient);
		int j = 1;
		for (auto i : dht.Buckets) {
			printBucket(*i, j);
			++j;
		}
		if (k == 4) {
			dht.removeElement(&(newClient->hash));
		}
		std::cout << "//////////////////////////////////////////////////////////////////////\n";
	}
	
}