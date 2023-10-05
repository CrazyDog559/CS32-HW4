//
//  badvector.cpp
//  HW4
//
//  Created by Drew Wan on 5/12/23.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

vector<int> destroyedOnes;

class Restaurant
{
  public:
    Restaurant(int s) : m_stars(s) {}
    ~Restaurant() { destroyedOnes.push_back(m_stars); }
    int stars() const { return m_stars; }
  private:
    int m_stars;
};

  // Remove the restaurants in v with 2 or fewer stars and destroy them.
  // It is acceptable if the order of the remaining restaurants is not
  // the same as in the original vector.
void removeBad(vector<Restaurant*>& v) {
    vector<Restaurant*> temp;
   for (vector<Restaurant*>::iterator it = v.begin(); it != v.end(); ++it) {
       if ((*it)->stars() > 2) {
           temp.push_back(*it);
       }
       else {
           delete *it;
       }
   }
   v = temp;
}

void test()
{
    int a[8] = { 4, 3, 2, 4, 1, 1, 5, 2 };
    vector<Restaurant*> x;
    for (int k = 0; k < 8; k++)
        x.push_back(new Restaurant(a[k]));
    assert(x.size() == 8 && x.front()->stars() == 4 && x.back()->stars() == 2);
    removeBad(x);
    assert(x.size() == 4 && destroyedOnes.size() == 4);
    vector<int> v;
    for (int k = 0; k < 4; k++)
        v.push_back(x[k]->stars());
    sort(v.begin(), v.end());
    int expect[4] = { 3, 4, 4, 5 };
    for (int k = 0; k < 4; k++)
        assert(v[k] == expect[k]);
    sort(destroyedOnes.begin(), destroyedOnes.end());
    int expectGone[4] = { 1, 1, 2, 2 };
    for (int k = 0; k < 4; k++)
        assert(destroyedOnes[k] == expectGone[k]);
    for (vector<Restaurant*>::iterator p = x.begin(); p != x.end(); p++)
        delete *p;
}

int main()
{
    test();
    cout << "Passed" << endl;
}




