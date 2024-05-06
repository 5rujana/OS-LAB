//memory management using segmentation
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cout << "Enter the number of segments: ";
    cin >> n;
    cout << "Enter the number of memory blocks: ";
    cin >> m;
    int segment[n], memory[m];
    cout << "Enter the size of each segment: ";
    for (int i = 0; i < n; i++)
    {
        cin >> segment[i];
    }
    cout << "Enter the size of each memory block: ";
    for (int i = 0; i < m; i++)
    {
        cin >> memory[i];
    }
    cout << "Segment\tMemory\tAllocated\n";
    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << "\t";
        for (int j = 0; j < m; j++)
        {
            cout << j + 1 << "\t";
            if (segment[i] <= memory[j])
            {
                cout << "Yes\n";
                memory[j] -= segment[i];
                break;
            }
            else
            {
                cout << "No\n";
            }
        }
    }
    return 0;
}
