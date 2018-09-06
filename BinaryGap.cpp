// Codility binary gap problem
#include <iostream>
#include <algorithm>

using namespace std;

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;
int recurGap(int N, int mask1, int mask2, int gap, int remove1, int remove2) {
    if( gap <= 0 || mask1 >= mask2)
        return 0;
    int sign = 1;
    sign <<= 31;
    
    while(mask1) {
        if(mask1 == 0) break;
        if((N & mask1) == 0) {
            gap--;
            mask1 <<= 1;
            if(remove1 == 0) remove1 = 1;
            else {
                remove1 <<= 1;
                remove1 |= 1;
            }
        }
        else break;
    }
    while(mask2) {
        if(mask2 == 0) break;
        if((N & mask2) == 0) {
            gap--;
            mask2 >>= 1;
            remove2 >>= 1;
            remove2 |= sign;
        }
        else break;
    }
    if( gap <= 0 || mask1 >= mask2)
        return 0;
    int gapMask = ~(mask1 | mask2) ^ (remove1 | remove2);
    if(gapMask == 0)
        return 0;
    if ((gapMask & N) == 0)
    {
        return gap;
    }
    return max(recurGap(N, mask1 << 1, mask2, gap - 1, (remove1 << 1) | 1, remove2),
        recurGap(N, mask1, mask2 >> 1, gap - 1, remove1, (remove2 >> 1) | sign) );
}

int solution(int N) {
    // write your code in C++14 (g++ 6.2.0)
    int mask1 = 1;
    int mask2 = 1;
    mask2 <<= 30;
    int gap = 29;
    int remove1 = 0;
    int remove2 = 1;
    remove2 <<= 31;
    return recurGap(N, mask1, mask2, gap, remove1, remove2);
}

int main()
{
    return 0;
}