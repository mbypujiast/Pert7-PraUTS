#include <iostream>
#include <vector>
#include <algorithm> // Untuk next_permutation
#include <climits>   // Untuk INT_MAX

using namespace std;

const int MAX_CITIES = 5;
string cityNames[MAX_CITIES] = {
    "Jakarta", "Bandung", "Solo", "Ponorogo", "Surabaya"
};


int distMatrix[MAX_CITIES][MAX_CITIES] = {
    // JKT  BDG   SOLO   PNG   SBY
    {0,     150,  530,  720,  800},   // JKT
    {150,   0,    640,  860,  750},   // BDG
    {530,   640,  0,    110,  350},   // SOLO
    {720,   860,  110,  0,    240},   // PNG
    {800,   750,  350,  240,  0}      // SBY
};

void showHeader() {
    cout << "==============================================" << endl;
    cout << "IMPLEMENTASI ALGORITMA BRUTE FORCE PADA TSP" << endl;
    cout << "THIS IS FOR TWICE WORLD TOUR IN INDONESIA" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Nama  : Puji Astuti Suryaningtyas" << endl;
    cout << "NIM   : 24533867" << endl;
    cout << "Kelas : 4D Teknik Informatika" << endl;
    cout << "==============================================" << endl << endl;
}

void showFooter() {
    cout << "\n==============================================" << endl;
    cout << "PROGRAM SELESAI DIIJALANKAN" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Program ini disusun oleh:" << endl;
    cout << "Nama  : Puji Astuti Suryaningtyas" << endl;
    cout << "NIM   : 24533867" << endl;
    cout << "Kelas : 4D Teknik Informatika" << endl;
    cout << "Universitas Muhammadiyah Ponorogo" << endl;
    cout << "===============================================" << endl;
}

int main() {
    char choice;
    
    do {
        showHeader();

        cout << "Daftar Kota Tersedia:" << endl;
        for(int i=0; i<MAX_CITIES; i++) {
            cout << (i+1) << ". " << cityNames[i] << endl;
        }

        int n;
        cout << "\nMasukkan jumlah kota yang akan dikunjungi (Maks 5): ";
        cin >> n;

        if(n < 2 || n > MAX_CITIES) {
            cout << "\n[ERROR] Jumlah kota harus antara 2 sampai 5!" << endl;
            cout << "Silakan coba lagi dengan jumlah yang benar.\n" << endl;
            continue; 
        }

        vector<int> cities;
        cout << endl;
        for(int i=0; i<n; i++) {
            int choiceCity;
            bool valid = false;
            while(!valid) {
                cout << "Pilih kota ke-" << (i+1) << " (1-" << MAX_CITIES << "): ";
                cin >> choiceCity;
                
                if(choiceCity >= 1 && choiceCity <= MAX_CITIES) {
                    bool exists = false;
                    for(int c : cities) {
                        if(c == choiceCity-1) exists = true;
                    }
                    
                    if(!exists) {
                        cities.push_back(choiceCity-1);
                        valid = true;
                    } else {
                        cout << "  -> Kota sudah dipilih! Pilih kota lain.\n";
                    }
                } else {
                    cout << "  -> Input salah! Masukkan angka 1-" << MAX_CITIES << "\n";
                }
            }
        }

        cout << "\nMenghitung semua kemungkinan rute (" << n << " kota)..." << endl;
        cout << "Mohon tunggu sebentar..." << endl;
        
        int startNode = cities[0];
        vector<int> others;
        for(size_t i=1; i<cities.size(); i++) {
            others.push_back(cities[i]);
        }

        sort(others.begin(), others.end());

        int minDist = INT_MAX;
        vector<int> bestRoute;

        do {
            vector<int> currentRoute;
            currentRoute.push_back(startNode);
            for(int node : others) currentRoute.push_back(node);

            int currentDist = 0;
            for(size_t i=0; i<currentRoute.size()-1; i++) {
                currentDist += distMatrix[currentRoute[i]][currentRoute[i+1]];
            }
            currentDist += distMatrix[currentRoute.back()][startNode];

            if(currentDist < minDist) {
                minDist = currentDist;
                bestRoute = currentRoute;
            }

        } while(next_permutation(others.begin(), others.end()));

        cout << "\n--------------------------------------------" << endl;
        cout << "HASIL OPTIMASI RUTE TERPENDEK:" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Rute Terbaik: ";
        for(size_t i=0; i<bestRoute.size(); i++) {
            cout << cityNames[bestRoute[i]];
            if(i < bestRoute.size()-1) cout << " -> ";
        }
        cout << " -> " << cityNames[startNode] << " (Kembali)" << endl;
        
        cout << "Total Jarak Tempuh: " << minDist << " km" << endl;
        cout << "--------------------------------------------" << endl;

        cout << "\nApakah Anda ingin menghitung rute lain? (Y/N): ";
        cin >> choice;
        cout << endl;

    } while (choice == 'Y' || choice == 'y');

    showFooter();

    return 0;
}