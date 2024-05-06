#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    int frames, pages, pageFaults = 0, pageHits = 0;
    vector<int> referenceString;

    cout << "Enter the number of frames: ";
    cin >> frames;
 
    cout << "Enter the number of pages: ";
    cin >> pages;

    cout << "Enter the reference string: ";
    for (int i = 0; i < pages; ++i) {
        int page;
        cin >> page;
        referenceString.push_back(page);
    }

    vector<int> frame(frames, -1); // Initialize all frames to -1 (empty)
    unordered_set<int> frameSet;

    cout << "\nPage reference string: ";
    for (int i = 0; i < pages; ++i)
        cout << referenceString[i] << " ";
    cout << endl;

    for (int i = 0; i < pages; ++i) {
        if (frameSet.find(referenceString[i]) != frameSet.end()) {
            ++pageHits;
        } else {
            ++pageFaults;
            if (frameSet.size() < frames) {
                frameSet.insert(referenceString[i]);
            } else {
                int victim = frame[0];
                frameSet.erase(victim);
                frameSet.insert(referenceString[i]);
            }
        }
    }

    cout << "\nNumber of page faults: " << pageFaults << endl;
    cout << "Number of page hits: " << pageHits << endl;
    cout << "Total number of page references: " << pages << endl;
    cout << "Page hit ratio: " << static_cast<float>(pageHits) / pages << endl;
    cout << "Page fault ratio: " << static_cast<float>(pageFaults) / pages << endl;

    return 0;
}
