#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
    // The 1000-digit number as a string
    string number = "7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055112540698747158523863050715693290963295227443043557668966489504452445231617318564030987111217223831136222989342338030813533627661428280644448664523874930358907296290491560440772390713810515859307960866701724271218839987979087922749219016997208880937765727330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450";

    int n = number.length();
    int max_product = 0;

    // Iterate over every possible 13-digit sequence
    for (int i = 0; i <= n - 13; ++i) {
        int product = 1;

        // Compute the product of the 13 digits in the current window
        for (int j = 0; j < 13; ++j) {
            product *= (number[i + j] - '0');  // Convert char to int and multiply
        }

        // Update the max_product if the current product is greater
        max_product = max(max_product, product);
    }

    cout << "The greatest product of thirteen adjacent digits is: " << max_product << endl;

    return 0;
}