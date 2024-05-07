#include <iostream>
#include <fstream>
#include <string>
#include <functional> // Untuk std::hash
#include <unordered_map> // Untuk memudahkan pencarian data

using namespace std;

const string DATA_FILE = "users.txt";

// Fungsi untuk meng-hash password menggunakan std::hash
size_t hashPassword(const string& password) {
    return hash<string>{}(password);
}

// Fungsi untuk mendaftarkan pengguna baru
void registerUser() {
    string role, username, password;
    
    cout << "Daftar sebagai (hrd/pelamar): ";
    cin >> role;
    
    // Validasi input role
    while (role != "hrd" && role != "pelamar") {
        cout << "Peran tidak valid. Silakan masukkan 'hrd' atau 'pelamar': ";
        cin >> role;
    }
    
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;
    
    // Hash password sebelum disimpan
    size_t hashedPassword = hashPassword(password);
    
    // Simpan data pengguna ke file teks
    ofstream file(DATA_FILE, ios::app);
    if (file.is_open()) {
        file << role << " " << username << " " << hashedPassword << endl;
        file.close();
        cout << "Pendaftaran berhasil.\n";
    } else {
        cout << "Gagal membuka file untuk menyimpan data.\n";
    }
}

// Fungsi untuk login pengguna
void loginUser() {
    string role, username, password;
    
    cout << "Masuk sebagai (hrd/pelamar): ";
    cin >> role;
    
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;
    
    // Hash password yang dimasukkan
    size_t hashedPassword = hashPassword(password);
    
    // Cari data pengguna dalam file teks
    ifstream file(DATA_FILE);
    string line;
    bool isValid = false;
    
    if (file.is_open()) {
        while (getline(file, line)) {
            // Pisahkan data dengan ruang
            string fileRole, fileUsername;
            size_t fileHashedPassword;
            
            size_t pos1 = line.find(" ");
            fileRole = line.substr(0, pos1);
            size_t pos2 = line.find(" ", pos1 + 1);
            fileUsername = line.substr(pos1 + 1, pos2 - pos1 - 1);
            fileHashedPassword = stoull(line.substr(pos2 + 1));
            
            // Validasi login
            if (fileRole == role && fileUsername == username && fileHashedPassword == hashedPassword) {
                isValid = true;
                break;
            }
        }
        file.close();
    } else {
        cout << "Gagal membuka file untuk membaca data.\n";
    }
    
    // Menampilkan hasil login
    if (isValid) {
        cout << "Login berhasil.\n";
    } else {
        cout << "Login gagal. Periksa kembali username dan password.\n";
    }
}

// Fungsi utama
int main() {
    int choice;
    
    while (true) {
        cout << "Menu:\n";
        cout << "1. Daftar\n";
        cout << "2. Login\n";
        cout << "3. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Keluar dari program.\n";
                return 0;
            default:
                cout << "Opsi tidak valid. Silakan coba lagi.\n";
        }
        
        cout << endl;
    }
}
