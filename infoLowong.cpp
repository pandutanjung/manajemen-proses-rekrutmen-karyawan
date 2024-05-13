#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

// Kelas yang mewakili kualifikasi pelamar
class JobQualification {
public:
    string education;  // Minimal pendidikan
    string major;      // Jurusan
    string ipk;        // IPK
    string age;        // Usia

    // Konstruktor
    JobQualification(string education, string major, string ipk, string age)
        : education(education), major(major), ipk(ipk), age(age) {}

    // Fungsi untuk menampilkan kualifikasi pelamar
    void display() const {
        cout << "Minimal Pendidikan: " << education << ", Jurusan: " << major
             << ", Syarat IPK: " << ipk
             << ", Syarat Usia: " << age;
    }
};

// Kelas yang mewakili posisi lowongan kerja
class JobPosition {
public:
    string title;             // Judul posisi
    JobQualification qualification; // Kualifikasi pelamar

    // Konstruktor
    JobPosition(string title, JobQualification qualification)
        : title(title), qualification(qualification) {}
};

// Fungsi untuk menambahkan posisi lowongan kerja
void addJobPosition(vector<JobPosition>& jobPositions) {
    string title;
    string education;
    string major;
    string ipk;
    string age;

    // Input judul posisi lowongan kerja
    cout << "Masukkan judul posisi lowongan kerja: ";
    getline(cin, title);

    // Input kualifikasi pelamar
    cout << "Masukkan minimal pendidikan: ";
    getline(cin, education);
    cout << "Masukkan jurusan kuliah: ";
    getline(cin, major);
    cout << "Masukkan syarat IPK: ";
    getline(cin, ipk);
    cout << "Masukkan syarat Usia: ";
    getline(cin, age);

    // Membuat objek JobQualification
    JobQualification qualification(education, major, ipk, age);

    // Membuat objek JobPosition dan menambahkannya ke dalam vektor
    JobPosition newPosition(title, qualification);
    jobPositions.push_back(newPosition);

    cout << "Posisi lowongan kerja berhasil ditambahkan.\n";
}

// Fungsi untuk menghapus posisi lowongan kerja berdasarkan nomor
void deleteJobPosition(vector<JobPosition>& jobPositions) {
    size_t positionNumber;
    
    // Meminta pengguna memasukkan nomor posisi yang ingin dihapus
    cout << "Masukkan nomor posisi lowongan kerja yang ingin dihapus: ";
    cin >> positionNumber;
    
    // Memeriksa apakah nomor posisi valid
    if (positionNumber < 1 || positionNumber > jobPositions.size()) {
        cout << "Nomor posisi tidak valid.\n";
        return;
    }
    
    // Menghapus posisi lowongan kerja sesuai nomor yang diberikan
    jobPositions.erase(jobPositions.begin() + positionNumber - 1);
    
    cout << "Posisi lowongan kerja nomor " << positionNumber << " telah dihapus.\n";
}

// Fungsi untuk menampilkan posisi dan informasi lowongan kerja dalam bentuk tabel
// Fungsi untuk menampilkan posisi dan informasi lowongan kerja dalam bentuk tabel
void displayJobPositions(const vector<JobPosition>& jobPositions) {
    // Mengatur lebar kolom
    int colWidth = 30; // Mengurangi lebar kolom untuk mengakomodasi kolom nomor
    int numWidth = 5; // Lebar kolom nomor

    // Menampilkan header tabel dengan batas tepi dan pembatas kolom
    cout << "+" << string(numWidth, '-') << "+" << string(colWidth, '-') << "+" << string(colWidth, '-') << "+\n";
    cout << "| " << left << setw(numWidth - 1) << "No"
         << "| " << left << setw(colWidth - 1) << "Posisi Lowongan"
         << "| " << left << setw(colWidth - 1) << "Kualifikasi Pelamar" << "|\n";
    cout << "+" << string(numWidth, '-') << "+" << string(colWidth, '-') << "+" << string(colWidth, '-') << "+\n";

    // Nomor posisi
    int positionNumber = 1;

    // Membuka file jobList.txt untuk penulisan
    ofstream outFile("C:\\Users\\Raihana\\RekruitmenKaryawan\\jobList.txt");
    if (!outFile.is_open()) {
        cerr << "Gagal membuka file jobList.txt" << endl;
        return;
    }

    // Menampilkan data posisi lowongan kerja dengan batas tepi dan pembatas kolom
    for (const auto& position : jobPositions) {
        // Menampilkan nomor posisi lowongan kerja
        cout << "| " << left << setw(numWidth - 1) << positionNumber;
        // Menampilkan judul posisi lowongan kerja
        cout << "| " << left << setw(colWidth - 1) << position.title;
        // Menampilkan kualifikasi pelamar dengan baris baru untuk setiap atribut
        cout << "| " << left << setw(colWidth - 1) << ("Minimal Pendidikan: " + position.qualification.education) << "|\n";
        cout << "| " << string(numWidth - 1, ' ') << "| " << left << string(colWidth - 1, ' ') << "| " << left << setw(colWidth - 1) << ("Jurusan: " + position.qualification.major) << "|\n";
        cout << "| " << string(numWidth - 1, ' ') << "| " << left << string(colWidth - 1, ' ') << "| " << left << setw(colWidth - 1) << ("Syarat IPK: " + position.qualification.ipk) << "|\n";
        cout << "| " << string(numWidth - 1, ' ') << "| " << left << string(colWidth - 1, ' ') << "| " << left << setw(colWidth - 1) << ("Syarat Usia: " + position.qualification.age) << "|\n";

        // Menulis judul posisi lowongan ke dalam file jobList.txt
        outFile << position.title << endl;
        
        // Garis pemisah antara lowongan kerja
        cout << "+" << string(numWidth, '-') << "+" << string(colWidth, '-') << "+" << string(colWidth, '-') << "+\n";

        positionNumber++;
    }

    // Menutup file jobList.txt setelah selesai
    outFile.close();
}


int main() {
    vector<JobPosition> jobPositions;
    int choice;

    do {
    // Menampilkan menu opsi
    cout << "\nMenu:\n";
    cout << "1. Tambah Posisi Lowongan Kerja\n";
    cout << "2. Tampilkan Posisi Lowongan Kerja\n";
    cout << "3. Hapus Posisi Lowongan Kerja\n"; // Opsi baru untuk menghapus lowongan kerja
    cout << "0. Keluar\n";
    cout << "Pilih opsi: ";
    cin >> choice;
    cin.ignore(); // Membersihkan buffer input

    // Menjalankan opsi berdasarkan pilihan pengguna
    switch (choice) {
        case 1:
            addJobPosition(jobPositions);
            break;
        case 2:
            displayJobPositions(jobPositions);
            break;
        case 3: // Kasus baru untuk menghapus lowongan kerja
            deleteJobPosition(jobPositions);
            break;
        case 0:
            cout << "Program berhenti.\n";
            break;
        default:
            cout << "Opsi tidak valid.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}
