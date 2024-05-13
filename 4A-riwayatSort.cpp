#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <algorithm>
#include <iomanip>
#include <string>

using namespace std;

// Struktur data untuk pelamar
struct Pelamar {
    string username;
    string nama;
    string posisi;
    int nilaiBerkas;
    string jadwalWawancara;
    int nilaiWawancara;
    int totalNilai;
    string keterangan;
};

// Fungsi untuk mencetak baris tabel dengan border di setiap sisi sel
void cetakBarisTabel(const array<string, 8>& data, const array<int, 8>& widths) {
    cout << "|";
    for (size_t i = 0; i < data.size(); i++) {
        cout << setw(widths[i]) << left << data[i] << "|";
    }
    cout << endl;
}

// Fungsi untuk mencetak garis horizontal tabel
void cetakGaris(const array<int, 8>& widths) {
    cout << "+";
    for (const int& width : widths) {
        cout << string(width, '-') << "+";
    }
    cout << endl;
}

// Fungsi untuk menampilkan tabel list seluruh pelamar
void tampilkanSeluruhPelamar(const vector<Pelamar>& pelamar, const string& posisi) {
    cout << "Daftar Pelamar untuk Posisi " << posisi << " (Diurutkan):\n";
    
    // Daftar lebar kolom
    array<int, 8> widths = {11, 17, 18, 12, 20, 15, 12, 13}; // Sesuaikan lebar kolomnya
    
    // Mencetak header tabel
    cetakGaris(widths);
    cetakBarisTabel({"Username", "Nama", "Posisi", "Nilai Berkas", "Jadwal Wawancara", "Nilai Wawancara", "Nilai Total", "Keterangan"}, widths);
    cetakGaris(widths);
    
    // Mencetak data pelamar
    for (const auto& p : pelamar) {
        array<string, 8> data = {
            p.username,
            p.nama,
            p.posisi,
            to_string(p.nilaiBerkas),
            p.jadwalWawancara,
            to_string(p.nilaiWawancara),
            to_string(p.totalNilai),
            p.keterangan
        };
        cetakBarisTabel(data, widths);
        cetakGaris(widths);
    }
    cout << endl;
}

// Fungsi untuk membaca data pelamar dari file
vector<Pelamar> bacaDataPelamar(const string& namaFile) {
    vector<Pelamar> pelamar;
    ifstream file(namaFile);
    if (!file.is_open()) {
        cerr << "Gagal membuka file " << namaFile << endl;
        exit(1);
    }
    string line;
    while (getline(file, line)) {
        Pelamar p;
        stringstream ss(line);
        getline(ss, p.username, ',');
        getline(ss, p.nama, ',');
        getline(ss, p.posisi, ',');
        string nilaiBerkasStr;
        getline(ss, nilaiBerkasStr, ',');
        p.nilaiBerkas = stoi(nilaiBerkasStr);
        getline(ss, p.jadwalWawancara, ',');
        string nilaiWawancaraStr;
        getline(ss, nilaiWawancaraStr, ',');
        p.nilaiWawancara = stoi(nilaiWawancaraStr);
        p.totalNilai = p.nilaiBerkas + p.nilaiWawancara;
        getline(ss, p.keterangan);
        pelamar.push_back(p);
    }
    file.close();
    return pelamar;
}

// Fungsi pembanding untuk mengurutkan pelamar berdasarkan total nilai
bool compareByTotalNilai(const Pelamar& a, const Pelamar& b) {
    return a.totalNilai > b.totalNilai;
}

// Fungsi pembanding untuk mengurutkan pelamar berdasarkan nama
bool compareByNama(const Pelamar& a, const Pelamar& b) {
    return a.nama < b.nama;
}

// Fungsi pembanding untuk mengurutkan pelamar berdasarkan posisi
bool compareByPosisi(const Pelamar& a, const Pelamar& b) {
    return a.posisi < b.posisi;
}

// Fungsi pembanding untuk mengurutkan pelamar berdasarkan keterangan diterima/ditolak
bool compareByKeterangan(const Pelamar& a, const Pelamar& b) {
    return a.keterangan < b.keterangan;
}

int main() {
    // Membaca data pelamar dari file posisilowongan.txt
    vector<Pelamar> pelamarSoftwareEngineer = bacaDataPelamar("softwareEngineer.txt");
    vector<Pelamar> pelamarDesainer = bacaDataPelamar("desainer.txt");
    vector<Pelamar> pelamarContentWriter = bacaDataPelamar("contentWriter.txt");

    int choice;
    cout << "Pilih cara sorting (1. Berdasarkan Nama, 2. Berdasarkan Posisi, 3. Berdasarkan Keterangan Diterima/Ditolak): ";
    cin >> choice;

    switch (choice) {
        case 1:
            sort(pelamarSoftwareEngineer.begin(), pelamarSoftwareEngineer.end(), compareByNama);
            sort(pelamarDesainer.begin(), pelamarDesainer.end(), compareByNama);
            sort(pelamarContentWriter.begin(), pelamarContentWriter.end(), compareByNama);
            break;
        case 2:
            sort(pelamarSoftwareEngineer.begin(), pelamarSoftwareEngineer.end(), compareByPosisi);
            sort(pelamarDesainer.begin(), pelamarDesainer.end(), compareByPosisi);
            sort(pelamarContentWriter.begin(), pelamarContentWriter.end(), compareByPosisi);
            break;
        case 3:
            sort(pelamarSoftwareEngineer.begin(), pelamarSoftwareEngineer.end(), compareByKeterangan);
            sort(pelamarDesainer.begin(), pelamarDesainer.end(), compareByKeterangan);
            sort(pelamarContentWriter.begin(), pelamarContentWriter.end(), compareByKeterangan);
            break;
        default:
            cout << "Pilihan tidak valid.\n";
            return 1;
    }

    tampilkanSeluruhPelamar(pelamarSoftwareEngineer, "Software Engineer");
    tampilkanSeluruhPelamar(pelamarDesainer, "Desainer");
    tampilkanSeluruhPelamar(pelamarContentWriter, "Content Writer");

    return 0;
}
