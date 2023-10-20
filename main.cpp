#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <vector>

using namespace std;

void GetFilesNames(char* dirrectory, vector<string> &fileNames) {
    DIR *d;
    struct dirent *dir;

    d = opendir(dirrectory);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            fileNames.push_back(dir->d_name);
        }

        closedir(d);
    }
}

string ReadFile(string fileName) {
    string line;
 
    ifstream in(fileName);
    if (in.is_open())
    {
        while (getline(in, line)) {
        }
    }

    in.close();

    return line;
}

void GetFilesContent(vector<string> &fileNames, vector<string> &filesContent) {
    int count = fileNames.size();
    for (int i = 0; i < count; ++i) {
        filesContent.push_back(ReadFile(fileNames[i]));
    }
}

int LevenshteinDistance(string line1, int m, string line2, int n)
{
    if (m == 0) {
        return n;
    }
    if (n == 0) {
        return m;
    }
 
    int cost = 0;

    if (line1[m - 1] == line2[n - 1]) {
        cost = 0;
    } else {
        cost = 1;
    }
 
    return min (min(LevenshteinDistance(line1, m - 1, line2, n) + 1,
            LevenshteinDistance(line1, m, line2, n - 1) + 1),
            LevenshteinDistance(line1, m - 1, line2, n - 1) + cost);
}

int main(int argc, char *argv[]) {
    char* dir1 = argv[0];
    char* dir2 = argv[1];

    vector<string> fileNames1;
    vector<string> fileNames2;

    GetFilesNames(dir1, fileNames1);
    GetFilesNames(dir2, fileNames2);

    vector<string> fileContent1;
    vector<string> fileContent2;

    GetFilesContent(fileNames1, fileContent1);
    GetFilesContent(fileNames2, fileContent2);

    int coefficient = 0;
    cin >> coefficient;

    vector<bool> firstDirFiles(fileNames1.size(), false);
    vector<bool> secondDirFiles(fileNames2.size(), false);

    for (int i = 0; i < fileNames1.size(); ++i) {
        for (int j = 0; j < fileNames2.size(); ++j){
            int dist = LevenshteinDistance(fileContent1[i], fileContent1[i].size(), fileContent2[j], fileContent2[j].size());

            if (dist == 0) {
                cout << dir1 << "/" << fileNames1[i] << "-" << dir2 << "/" << fileNames2[j] << "\n";

                firstDirFiles[i] = true;
                secondDirFiles[j] = true;
            } else {
                int k = 1 - dist / max(fileContent1[i].size(), fileContent2[j].size());

                if (k == coefficient) {
                    cout << dir1 << "/" << fileNames1[i] << " - " << dir2 << "/" << fileNames2[j] << " - " << k * 100 << "\n";
                }
            }
        }
    }

    for (int i = 0; i < firstDirFiles.size(); ++i) {
        if (firstDirFiles[i] == false) {
            cout << fileNames1[i] << " ";
        }

        cout << "\n";
    }

    for (int i = 0; i < secondDirFiles.size(); ++i) {
        if (secondDirFiles[i] == false) {
            cout << fileNames2[i] << " ";
        }

        cout << "\n";
    }
    
    return 0;
}