#include "main.h"
#include "restaurant.cpp"

// void print(table* r, int num){
//     if(num == 0) return;
//     print(r->next, num-1);
//     cout << r->ID << " ";
// }

int main(int argc, char* argv[]) {

    restaurant* r = new restaurant();
    string fileName = "test.txt";

    //initialize table with ID, name and age
    for (int i = 1; i <= MAXSIZE; i++)
    {
        r->recentTable = r->insert(r->recentTable,i,"",0);
    }
    // r->recentTable = r->recentTable->next;
    // print(r->recentTable, 3);


    simulate(fileName,r);
    delete r;

    return 0;
}

