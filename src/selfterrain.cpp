#include <bits/stdc++.h>
using namespace std;
int abc[1026][1026];
inline static float randm(int range)
{
 return (rand() % (range * 2)) - range;
}
void alg_step(int x, int y, int size) {
    if(size <= 2){
        return;
    }
    abc[x+size/2][y+size/2] = (abc[x][y] + abc[x+2*(size/2)][y] + 
    abc[x][y+2*(size/2)] + abc[x+2*(size/2)][y+2*(size/2)])/4;

    //Diamond steps
    abc[x+size/2][y]            = (abc[x][y] + abc[x+size/2][y+size/2] + abc[x+2*(size/2)][y])/3;
    abc[x+size/2][y]            += randm(size);
    
    abc[x+2*(size/2)][y+size/2] = (abc[x][y+2*(size/2)] + abc[x+size/2][y+size/2] + abc[x+2*(size/2)][y+2*(size/2)])/3;
    abc[x+2*(size/2)][y+size/2] += randm(size);

    abc[x][y+size/2]            = (abc[x][y] + abc[x+size/2][y+size/2] + abc[x][y+2*(size/2)])/3;
    abc[x][y+size/2]            += randm(size); 
  
    abc[x+size/2][y+2*(size/2)] = (abc[x][y+2*(size/2)] + abc[x+size/2][y+size/2] + abc[x+2*(size/2)][y+2*(size/2)])/3;
    abc[x+size/2][y+2*(size/2)] += randm(size);

    //algo steps
    alg_step(x,y,size/2 + 1);
    alg_step(x+size/2,y,size/2 + 1);
    alg_step(x,y+size/2,size/2 + 1);
    alg_step(x+size/2,y+size/2,size/2 + 1);

}

// int main() {
//     int sz = 65;
//     abc[1][sz] = 10;
//     abc[1][1] = 20;
//     abc[sz][1] = 30;
//     abc[sz][sz] = 40;
//     alg_step(1,1,sz);
    
//     for(int i = 1 ; i <= sz ; ++i) {
//         for(int j = 1 ; j <= sz ; ++j) {
//             cout << abc[i][j] << " ";
//         }
//         cout << endl;
//     }
//     return 0;
// }