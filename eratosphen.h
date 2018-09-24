#ifndef ERATOSPHEN_H
#define ERATOSPHEN_H
////////////////////////////////////////////////////////////////////////////////
///                                                                          ///
///                                                                          ///
///                                                                          ///
///                                                                          ///
///                Решето Эратосфена с модификацией , не использующей        ///
///                                                                          ///
///                             в прогонке чётные числа.                     ///
///                                                                          ///
///                                                                          ///
///                                                                          ///
////////////////////////////////////////////////////////////////////////////////



#include <iostream>
#include <vector>
using namespace std;


int main()
{


    long int n;
      cout << "n= ";
      cin >> n;
     vector <long int> a (n+1);

      for (int i = 1; i < n + 1; i+=2)
        a[i] = i;
      for (int p = 2; p < n + 1; p++)
      {
        if (a[p] != 0)
        {
          cout << a[p] << endl;
          for (int j = p*p; j < n + 1; j += p)
            {
              a.push_back(0);

          }
        }
      }
      for (int n:a)
      {

          cout<<n;
      }





}
#endif // ERATOSPHEN_H
