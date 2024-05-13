#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Fungsi untuk menampilkan menu lowongan kerja
void displayMenu() {
    // Membuka file jobList.txt untuk membaca daftar posisi lowongan
    ifstream inFile("C:\\Users\\Raihana\\RekruitmenKaryawan\\jobList.txt");
    if (!inFile.is_open()) {
        cerr << "Gagal membuka file jobList.txt" << endl;
        return;
    }

    // Menampilkan menu lowongan kerja
    cout << "Menu Lowongan Kerja:\n";
    string jobTitle;
    int positionNumber = 1;
    while (getline(inFile, jobTitle)) {
        cout << positionNumber++ << ". " << jobTitle << endl;
    }
    inFile.close();
}

// Fungsi untuk menerapkan lowongan kerja
void applyForJob(const string& jobTitle, const string& username, const string& applicantProfile) {
    // Menambahkan data pelamar ke dalam file apply.txt
    ofstream outFile("C:\\Users\\Raihana\\RekruitmenKaryawan\\apply.txt", ios::app);
    if (!outFile.is_open()) {
        cerr << "Gagal membuka file apply.txt" << endl;
        return;
    }
    outFile << applicantProfile << endl;
    outFile << "Posisi:" << jobTitle << endl;
    outFile.close();
}

// Fungsi untuk membaca data profil pelamar dari profil.txt berdasarkan username
// Fungsi untuk membaca data profil pelamar dari profil.txt berdasarkan username
string readApplicantProfile(const string& username) {
    string line;
    string applicantProfile;
    ifstream inFile("C:\\Users\\Raihana\\RekruitmenKaryawan\\profil.txt");
    if (!inFile.is_open()) {
        cerr << "Gagal membuka file profil.txt" << endl;
        return applicantProfile;
    }
    bool found = false;
    int linesRead = 0;
    while (getline(inFile, line)) {
        if (line.find("Username: " + username) != string::npos) {
            found = true;
            applicantProfile += line + "\n"; // Menyimpan baris username
        } else if (found) {
            if (!line.empty()) {
                applicantProfile += line + "\n"; // Menyimpan data profil selanjutnya
                linesRead++;
            } else {
                break; // Keluar dari loop setelah menemukan akhir profil
            }
            // Hentikan pembacaan setelah 9 baris
            if (linesRead >= 9) {
                break;
            }
        }
    }
    inFile.close();
    return applicantProfile;
}


int main() {
    int choice;
    bool exit = false;

    while (!exit) {
        displayMenu();
        cout << "Pilih nomor posisi yang ingin Anda lamar: ";
        cin >> choice;

        // Membersihkan buffer input
        cin.ignore();

        // Membuka kembali file jobList.txt untuk mencocokkan pilihan dengan nama posisi
        ifstream inFile("C:\\Users\\Raihana\\RekruitmenKaryawan\\jobList.txt");
        if (!inFile.is_open()) {
            cerr << "Gagal membuka file jobList.txt" << endl;
            return 1;
        }

        string jobTitle;
        int positionNumber = 1;
        bool jobFound = false;
        while (getline(inFile, jobTitle)) {
            if (positionNumber == choice) {
                // Meminta username pelamar
                string username;
                cout << "Masukkan username Anda: ";
                getline(cin, username);
                // Mengecek apakah pelamar telah melamar pada posisi tersebut sebelumnya
                string applicantProfile = readApplicantProfile(username);
                if (applicantProfile.find(jobTitle) != string::npos) {
                    cout << "Anda telah melamar pada posisi ini sebelumnya." << endl;
                } else {
                    applyForJob(jobTitle, username, applicantProfile);
                    cout << "Lamaran Anda untuk posisi " << jobTitle << " berhasil disimpan." << endl;
                }
                jobFound = true;
                break;
            }
            positionNumber++;
        }
        inFile.close();

        if (!jobFound) {
            cout << "Pilihan tidak valid." << endl;
            continue; // Melanjutkan ke iterasi berikutnya
        }

        cout << "Apakah Anda ingin melamar lowongan lain? (y/n): ";
        char response;
        cin >> response;
        if (response == 'n' || response == 'N') {
            exit = true;
        }
        cin.ignore(); // Membersihkan buffer input setelah membaca karakter 'n' atau 'N'
    }

    cout << "Terima kasih telah menggunakan program ini.\n";
    return 0;
}
