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
    unsigned int index = (add>>block_offset_bits) & (set-1);
    unsigned int tag1 = (add>>(block_offset_bits+index_bits));

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

void cache::replace() {

}

void cache::read(unsigned int add) {
    unsigned int index = (add>>block_offset_bits) & (set-1);
    unsigned int tag1 = (add>>(block_offset_bits+index_bits));
	a ++;
    if(hit(add)==-1) {//miss
        b ++;
        int i = invalid(index);
        if(i>-1) {//If have a invalid block
            if(replacement_policy) {//LFU
                //L1.replaceLFU(index, tag1);
            }
            else {//LRU
                flagV[index][i] = 1;
                tag[index][i] = tag1;
                for(int j = 0; j < assoc; j ++) {
                    if(counter[index][j] < counter[index][i])
                        counter[index][j] ++;
                }
                counter[index][i] = 0;
            }
        }
        else {//replace_policy
            if(replacement_policy) {//LFU
                //L1.replaceLFU(index, tag1);
            }
            else {//LRU
                int LRU = replaceLRU(index, tag1);
                if(!write_policy) {
                	if(flagD[index][LRU]) {
                    	f ++;
                    	flagD[index][LRU] = 0;
      	        	}
                }
            }
        }
    }
    else {//hit
        if(replacement_policy) {//LFU
                    
        }
        else {
                    
        }
    }
}

void cache::write(unsigned int add) {
    unsigned int index = (add>>block_offset_bits) & (set-1);
    unsigned int tag1 = (add>>(block_offset_bits+index_bits));
	c ++;
    if(hit(add)==-1) {//miss
        d ++;
        int i = invalid(index);
        if(write_policy) {//WTNA
            //Nothing
        }
        else {//WBWA
            if(i > -1) {//If have a invalid block
                if(replacement_policy) {//LFU
                    //replaceLFU(index, tag1);
                }
                else {//LRU
                    /*if(flagD[index][i])
                        f ++;*/
                    flagV[index][i] = 1;
                    flagD[index][i] = 1;
                    tag[index][i] = tag1;
                    for(int j = 0; j < assoc; j ++) {
                        if(counter[index][j] < counter[index][i])
                            counter[index][j] ++;
                    }
                 	counter[index][i] = 0;
                }
            }
            else {
                if(replacement_policy) {//LFU
                    //replaceLFU(index, tag1);
                }
                else {//LRU
                    int LRU = replaceLRU(index, tag1);
                    if(flagD[index][LRU])
                        f ++;
                    flagD[index][LRU] = 1;
                }
            }
        }
    }
    else {//hit
        int i = hit(add);
        if(write_policy) {//WTNA
            //
        }
        else {//WBWA
            //if(flagD[index][i])
            //    f ++;
            flagD[index][i] = 1;
            tag[index][i] = tag1;
            for(int j = 0; j < assoc; j ++) {
                if(counter[index][j] < counter[index][i])
                    counter[index][j] ++;
            }
            counter[index][i] = 0;
        }
    }
}