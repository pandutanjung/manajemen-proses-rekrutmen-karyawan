#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits> // library untuk clear buffer

using namespace std;

// Struktur untuk menyimpan informasi pengguna
struct User {
    string username;
    string password;
};

// Struktur untuk menyimpan profil data pribadi pelamar
struct ApplicantProfile {
    string nama;
    string ttl;
    int usia;
    string pendidikanTerakhir;
    string jurusan;
    string alamat;
    string noTelp;
    string email;
};

// Fungsi untuk memeriksa apakah username sudah digunakan
bool isUsernameTaken(const vector<User>& users, const string& username) {
    for (const User& user : users) {
        if (user.username == username) {
            return true;
        }
    }
    return false;
}

// Fungsi untuk meminta dan menyimpan profil data pelamar
ApplicantProfile enterApplicantProfile() {
    ApplicantProfile profile;
    cout << "Masukkan nama lengkap: ";
    cin.ignore(); // Membersihkan buffer input
    getline(cin, profile.nama);
    cout << "Masukkan tanggal lahir (format: DD/MM/YYYY): ";
    getline(cin, profile.ttl);
    cout << "Masukkan usia: ";
    cin >> profile.usia;
    cin.ignore(); // Membersihkan buffer input
    cout << "Masukkan pendidikan terakhir: ";
    getline(cin, profile.pendidikanTerakhir);
    cout << "Masukkan jurusan: ";
    getline(cin, profile.jurusan);
    cout << "Masukkan alamat: ";
    getline(cin, profile.alamat);
    cout << "Masukkan nomor telepon: ";
    getline(cin, profile.noTelp);
    cout << "Masukkan email: ";
    getline(cin, profile.email);
    return profile;
}

// Fungsi untuk menyimpan profil ke dalam file
void saveProfileToFile(const string& username, const ApplicantProfile& profile) {
    ofstream profileFile("C:\\Users\\Raihana\\RekruitmenKaryawan\\profil.txt", ios::app);
    if (profileFile.is_open()) {
        profileFile << "Username: " << username << endl; // Menambahkan username
        profileFile << "Nama: " << profile.nama << endl;
        profileFile << "TTL: " << profile.ttl << endl;
        profileFile << "Usia: " << profile.usia << endl;
        profileFile << "Pendidikan Terakhir: " << profile.pendidikanTerakhir << endl;
        profileFile << "Jurusan: " << profile.jurusan << endl;
        profileFile << "Alamat: " << profile.alamat << endl;
        profileFile << "Nomor Telepon: " << profile.noTelp << endl;
        profileFile << "Email: " << profile.email << endl;
        profileFile << "-------------------------------------------\n"; // Separator antar profil
        profileFile.close();
    } else {
        cerr << "Gagal menyimpan file profil." << endl;
    }
}

// Fungsi untuk melakukan login sebagai pelamar
bool loginApplicant(const vector<User>& users, const string& username, const string& password) {
    for (const User& user : users) {
        if (user.username == username && user.password == password) {
            return true;
        }
    }
    return false;
}

// Fungsi untuk melakukan registrasi pelamar
void registerApplicant(vector<User>& users) {
    User newUser;
    ApplicantProfile profile;

    cout << "Masukkan username: ";
    cin >> newUser.username;
    // Validasi apakah username sudah digunakan
    while (isUsernameTaken(users, newUser.username)) {
        cout << "Username sudah digunakan. Masukkan username lain: ";
        cin >> newUser.username;
    }
    cout << "Masukkan password: ";
    cin >> newUser.password;

    // Memasukkan profil data
    profile = enterApplicantProfile();

    // Menyimpan data pelamar ke dalam vektor
    users.push_back(newUser);

    // Menyimpan data pelamar ke dalam file
    ofstream outFile("C:\\Users\\Raihana\\RekruitmenKaryawan\\pelamar.txt", ios::app);
    if (outFile.is_open()) {
        outFile << newUser.username << " " << newUser.password << endl;
        outFile.close();
    } else {
        cerr << "Gagal menyimpan file pelamar." << endl;
        return;
    }

    // Menyimpan profil ke dalam file dengan username
    saveProfileToFile(newUser.username, profile);

    cout << "Registrasi berhasil!" << endl;
}

int main() {
    vector<User> hrdUsers;
    vector<User> applicantUsers;

    // Membaca data HRD dari file
    ifstream hrdFile("C:\\Users\\Raihana\\RekruitmenKaryawan\\hrd.txt");
    if (hrdFile.is_open()) {
        string username, password;
        while (hrdFile >> username >> password) {
            User user;
            user.username = username;
            user.password = password;
            hrdUsers.push_back(user);
        }
        hrdFile.close();
    } else {
        cout << "File hrd.txt tidak ditemukan." << endl;
        return 1;
    }

    // Membaca data pelamar dari file
    ifstream applicantFile("C:\\Users\\Raihana\\RekruitmenKaryawan\\pelamar.txt");
    if (applicantFile.is_open()) {
        string username, password;
        while (applicantFile >> username >> password) {
            User user;
            user.username = username;
            user.password = password;
            applicantUsers.push_back(user);
        }
        applicantFile.close();
    } else {
        cout << "File pelamar.txt tidak ditemukan." << endl;
        return 1;
    }

    int choice;
    cout << "Selamat datang!" << endl;
    cout << "1. Login sebagai HRD" << endl;
    cout << "2. Registrasi sebagai pelamar" << endl;
    cout << "3. Login sebagai pelamar" << endl;
    cout << "Pilihan Anda: ";
    while (!(cin >> choice)) {
        // Jika input bukan angka, membersihkan buffer
        cout << "Pilihan tidak valid. Silakan masukkan angka: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (choice) {
        case 1: {
            string username, password;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            if (loginApplicant(hrdUsers, username, password)) {
                cout << "Login berhasil sebagai HRD." << endl;
            } else {
                cout << "Username atau password salah." << endl;
            }
            break;
        }
        case 2: {
            registerApplicant(applicantUsers);
            break;
        }
        case 3: {
            string username, password;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            if (loginApplicant(applicantUsers, username, password)) {
                cout << "Login berhasil sebagai pelamar." << endl;
            } else {
                cout << "Username atau password salah." << endl;
            }
            break;
        }
        default:
            cout << "Pilihan tidak valid." << endl;
    }

    return 0;
}
