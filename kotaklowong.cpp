// JANGAN KESINI, ini ak baru upload dl
// jangan baca, bsk aja
#include <iostream>
#include <string>

using namespace std;

struct JobPosition {
    string title;  // Judul lowongan kerja
    string description;  // Deskripsi lowongan kerja
};

// Fungsi untuk mengajukan CV dan portofolio
void applyForJob(const string& jobTitle) {
    string cv, portfolio;
    
    cout << "Anda sedang mengajukan lamaran untuk posisi: " << jobTitle << endl;
    cout << "Masukkan nama file CV Anda: ";
    cin.ignore();  // Membersihkan buffer input
    getline(cin, cv);
    cout << "Masukkan nama file portofolio Anda: ";
    getline(cin, portfolio);
    
    // Proses pengajuan lamaran (misalnya, simpan file CV dan portofolio)
    cout << "CV: " << cv << " dan portofolio: " << portfolio << " telah diajukan untuk posisi " << jobTitle << endl;
}

// Fungsi untuk menampilkan menu lowongan kerja
void displayMenu(const JobPosition jobs[], int numJobs) {
    cout << "Menu Lowongan Kerja:\n";
    for (int i = 0; i < numJobs; i++) {
        cout << i + 1 << ". " << jobs[i].title << endl;
    }
    cout << "Pilih nomor posisi yang ingin Anda lamar: ";
}

// Fungsi utama
int main() {
    const int numJobs = 3;  // Jumlah lowongan kerja
    JobPosition jobs[numJobs] = {
        {"Software Engineer", "Pengembang perangkat lunak."},
        {"Web Developer", "Pengembang situs web."},
        {"Data Analyst", "Analis data."}
    };
    
    int choice;
    bool exit = false;
    
    while (!exit) {
        displayMenu(jobs, numJobs);
        cin >> choice;
        
        if (choice >= 1 && choice <= numJobs) {
            applyForJob(jobs[choice - 1].title);
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
        
        cout << "Apakah Anda ingin melamar lowongan lain? (y/n): ";
        char response;
        cin >> response;
        if (response == 'n' || response == 'N') {
            exit = true;
        }
    }
    
    cout << "Terima kasih telah menggunakan program ini.\n";
    return 0;
}
