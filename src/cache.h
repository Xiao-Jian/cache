#ifndef CACHE_H
#define CACHE_H

#define MAX_S 2223
#define MAX_A 101

class cache {

public:
	int blocksize;
	int size;
	int assoc;
	int replacement_policy;
	int write_policy;
	
	int cache_blocks;
	int set;
	int index_bits;
	int block_offset_bits;
	int tag_bits;
	
	unsigned int tag[MAX_S][MAX_A];
	bool flagD[MAX_S][MAX_A];
	bool flagV[MAX_S][MAX_A];
	int counter[MAX_S][MAX_A];
	int a,b,c,d,f,g;
	double e, aat;

	cache *nextLevel;

public:
	void setData(int a, int b, int c, int d, int f);
	int getBlocksize();
	int getSize();
	int getAssoc();
	int getRp();
	int getWp();
	int hit(unsigned int add);
	int invalid(unsigned int index);
	int replaceLRU(unsigned int index, unsigned int tag1);
	void replaceLFU(unsigned int index, unsigned int tag1);
	void replace();
	void read(unsigned int add);
	void write(unsigned int add);

};

#endif //CACHE_H