#include <iostream>
#include <array>
#include <algorithm>
#include <iomanip>
#include <string>

using namespace std;

// Struktur data untuk pelamar
struct Pelamar {
    int id;
    string nama;
    string posisiLowongan;
    int nilaiBerkas;
    int nilaiWawancara;
    int nilaiRerata;
    string jadwalWawancara;
    string keterangan; // "Diterima" atau "Ditolak"
};

// Fungsi untuk menghitung nilai rerata dari nilai berkas dan nilai wawancara
int hitungNilaiRerata(int nilaiBerkas, int nilaiWawancara) {
    return (nilaiBerkas + nilaiWawancara) / 2;
}

// Fungsi untuk mencetak baris tabel dengan border di setiap sisi sel
void cetakBarisTabel(const array<string, 7>& data, const array<int, 7>& widths) {
    cout << "|";
    for (size_t i = 0; i < data.size(); i++) {
        cout << setw(widths[i]) << left << data[i] << "|";
    }
    cout << endl;
}

// Fungsi untuk mencetak garis horizontal tabel
void cetakGaris(const array<int, 7>& widths) {
    cout << "+";
    for (const int& width : widths) {
        cout << string(width, '-') << "+";
    }
    cout << endl;
}

// Fungsi untuk menampilkan tabel list seluruh pelamar
void tampilkanSeluruhPelamar(const array<Pelamar, 4>& pelamar) {
    cout << "Daftar Seluruh Pelamar:\n";
    
    // Daftar lebar kolom
    array<int, 7> widths = {4, 10, 10, 7, 10, 7, 10};
    
    // Mencetak header tabel
    cetakGaris(widths);
    cetakBarisTabel({"ID", "Nama", "Posisi", "Berkas", "Wawancara", "Rerata", "Jadwal WWC"}, widths);
    cetakGaris(widths);
    
    // Mencetak data pelamar
    for (const auto& p : pelamar) {
        array<string, 7> data = {
            to_string(p.id),
            p.nama,
            p.posisiLowongan,
            to_string(p.nilaiBerkas),
            to_string(p.nilaiWawancara),
            to_string(p.nilaiRerata),
            p.jadwalWawancara
        };
        cetakBarisTabel(data, widths);
        cetakGaris(widths);
    }
    cout << endl;
}

// Fungsi untuk menampilkan tabel list seluruh pelamar yang diterima
void tampilkanPelamarDiterima(const array<Pelamar, 4>& pelamar) {
    cout << "Daftar Pelamar Diterima:\n";
    
    // Daftar lebar kolom
    array<int, 7> widths = {4, 10, 10, 7, 10, 7, 10};
    
    // Mencetak header tabel
    cetakGaris(widths);
    cetakBarisTabel({"ID", "Nama", "Posisi", "Berkas", "Wawancara", "Rerata", "Jadwal WWC"}, widths);
    cetakGaris(widths);
    
    // Mencetak data pelamar yang diterima
    for (const auto& p : pelamar) {
        if (p.keterangan == "Diterima") {
            array<string, 7> data = {
                to_string(p.id),
                p.nama,
                p.posisiLowongan,
                to_string(p.nilaiBerkas),
                to_string(p.nilaiWawancara),
                to_string(p.nilaiRerata),
                p.jadwalWawancara
            };
            cetakBarisTabel(data, widths);
            cetakGaris(widths);
        }
    }
    cout << endl;
}

// Fungsi untuk menampilkan tabel list pelamar yang diterima per posisi lowongan
void tampilkanPelamarDiterimaPerPosisi(const array<Pelamar, 4>& pelamar, const string& posisiLowongan) {
    cout << "Daftar Pelamar Diterima untuk Posisi " << posisiLowongan << ":\n";
    
    // Daftar lebar kolom
    array<int, 7> widths = {4, 10, 10, 7, 10, 7, 10};
    
    // Mencetak header tabel
    cetakGaris(widths);
    cetakBarisTabel({"ID", "Nama", "Posisi", "Berkas", "Wawancara", "Rerata", "Jadwal WWC"}, widths);
    cetakGaris(widths);
    
    // Mencetak data pelamar yang diterima per posisi lowongan
    for (const auto& p : pelamar) {
        if (p.posisiLowongan == posisiLowongan && p.keterangan == "Diterima") {
            array<string, 7> data = {
                to_string(p.id),
                p.nama,
                p.posisiLowongan,
                to_string(p.nilaiBerkas),
                to_string(p.nilaiWawancara),
                to_string(p.nilaiRerata),
                p.jadwalWawancara
            };
            cetakBarisTabel(data, widths);
            cetakGaris(widths);
        }
    }
    cout << endl;
}

// Fungsi pembanding untuk mengurutkan pelamar berdasarkan id
bool compareById(const Pelamar& a, const Pelamar& b) {
    return a.id < b.id;
}

int main() {
    // Contoh data pelamar
    array<Pelamar, 4> pelamar = {
        Pelamar{1, "Budi", "Programmer", 85, 90, hitungNilaiRerata(85, 90), "2024-05-02", "Diterima"},
        Pelamar{2, "Andi", "Programmer", 75, 70, hitungNilaiRerata(75, 70), "2024-05-03", "Ditolak"},
        Pelamar{3, "Cici", "Desainer", 90, 95, hitungNilaiRerata(90, 95), "2024-05-04", "Diterima"},
        Pelamar{4, "Doni", "Desainer", 60, 65, hitungNilaiRerata(60, 65), "2024-05-05", "Ditolak"}
    };

    // Mengurutkan pelamar berdasarkan id
    sort(pelamar.begin(), pelamar.end(), compareById);

    // Tampilkan tabel list seluruh pelamar
    tampilkanSeluruhPelamar(pelamar);

    // Tampilkan tabel list seluruh pelamar yang diterima
    tampilkanPelamarDiterima(pelamar);

    // Tampilkan tabel list pelamar yang diterima per posisi lowongan
    tampilkanPelamarDiterimaPerPosisi(pelamar, "Programmer");

    return 0;
}
