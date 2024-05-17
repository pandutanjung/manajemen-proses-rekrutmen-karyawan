#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Struktur data untuk menyimpan informasi CV
struct CV {
    string pendidikan;
    string pengalaman;
    string keahlian;
    double ipk;
};

// Fungsi untuk melakukan seleksi dan penilaian terhadap CV
void seleksiCV(const vector<CV>& cvs, ofstream& outFile) {
    for (const auto& cv : cvs) {
        // Analisis kualifikasi
        int nilai = 0;
        if (cv.pendidikan == "S2" || cv.pendidikan == "S3") {
            nilai += 30;
        } else if (cv.pendidikan == "S1") {
            nilai += 20;
        }

        if (cv.pengalaman == "Ya") {
            nilai += 20;
        }

        if (!cv.keahlian.empty()) {
            nilai += 20;
        }

        if (cv.ipk >= 3.5) {
            nilai += 30;
        } else if (cv.ipk >= 3.0) {
            nilai += 20;
        }

        // Menilai hasil
        if (nilai >= 70) {
            outFile << "Pelamar " << cv.pendidikan << " lolos seleksi dengan nilai " << nilai << endl;
            outFile << "Jadwal wawancara akan diinformasikan secara otomatis" << endl;
        } else {
            outFile << "Pelamar " << cv.pendidikan << " tidak lolos seleksi dengan nilai " << nilai << endl;
        }
    }
}

int main() {
    vector<CV> cvs;
    ifstream file("input_cv.txt");
    ofstream outFile("output.txt");

    if (file.is_open() && outFile.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            CV cv;
            getline(ss, cv.pendidikan, ',');
            getline(ss, cv.pengalaman, ',');
            getline(ss, cv.keahlian, ',');
            ss >> cv.ipk;
            cvs.push_back(cv);
        }

        file.close();

        seleksiCV(cvs, outFile); // Kirim ofstream ke fungsi seleksi

        outFile.close(); // Tutup file output
    } else {
        cerr << "Gagal membuka file input_cv.txt atau output.txt" << endl;
        return 1;
    }

    return 0;
}
