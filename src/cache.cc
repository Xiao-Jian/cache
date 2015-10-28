#include "cache.h"
#include "string.h"
#include "math.h"

void cache::setData(int _a,int _b,int _c,int _d,int _f) {
	blocksize = _a;
	size = _b;
	assoc = _c;
	replacement_policy = _d;
	write_policy = _f;
	
	a = b = c = d = f = g = 0;
	e = 0;
	
	memset(tag, 0, sizeof(tag));
	memset(flagD, 0, sizeof(flagD));
	memset(flagV, 0, sizeof(flagV));
	
	cache_blocks = _b / _a;
	set = _b / ( _a * _c );
    index_bits = log(set) / log(2);
    block_offset_bits = log(blocksize) / log(2);
    tag_bits = 32 - index_bits - block_offset_bits;

    for(int i = 0; i < MAX_S; i ++)
    	for(int j = 0; j < MAX_A; j ++ )
    		counter[i][j] = j;
}

int cache::hit(unsigned int add) {
	unsigned int tmp = add;
    int flag = 1;
    unsigned int block_offset = tmp % blocksize;
    tmp >>= block_offset_bits;
  	unsigned int index = tmp % set;
    tmp >>= index_bits;
    unsigned int tag1 = tmp;

    for(int i = 0; i < assoc; i ++) {
    	if(tag1 == tag[index][i] && flagV[index][i])
    		return i;
    }
    return -1;
}

int cache::invalid(unsigned int index) {
    for(int i = 0; i < assoc; i ++) {
    	if(!flagV[index][i])
    		return i;
    }
    return -1;
}

int cache::replaceLRU(unsigned int index, unsigned int tag1) {
	int m = -1, pos;
	for(int i = 0; i < assoc; i ++)
		if(m < counter[index][i]) {
			m = counter[index][i];
			pos = i;
		}
	counter[index][pos] = 0;
	for(int i = 0; i < assoc; i ++) {
		if(i == pos) continue;
		counter[index][i] ++;
	}

	tag[index][pos] = tag1;
	flagV[index][pos] = 1;
	return pos;
}

/*void cache::replaceLFU(unsigned int index) {


}*/