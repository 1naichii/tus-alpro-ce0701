#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;

// Maksimal data yang bisa disimpan
const int MAX_DATA = 100;
const int MAX_PELANGGARAN = 10;
const int MAX_USERS = 20;

// Struktur data sederhana
struct Identitas {
    string nama;
    string alamat;
    string noKTP;
    string jenisKendaraan;
    string noPlat;
};

struct DataPelanggaran {
    int id;
    Identitas identitas;
    int jenisPelanggaran[MAX_PELANGGARAN];
    int jumlahPelanggaran;
    double totalDenda;
    string tanggal;
};

struct User {
    string username;
    string password;
    string level;
};

// Array untuk menyimpan data
DataPelanggaran dataPelanggaran[MAX_DATA];
int jumlahData = 0;
User users[MAX_USERS];
int jumlahUsers = 0;

// Array 2D untuk data master pelanggaran (nama dan denda dalam satu struktur)
string masterPelanggaran[11][2] = {
    {"", "0"},                                          // index 0 kosong
    {"Menerobos lampu merah", "50000"},                // 1
    {"Tidak menggunakan helm", "25000"},               // 2
    {"Kendaraan tidak layak jalan", "100000"},         // 3
    {"Melebihi batas kecepatan", "75000"},             // 4
    {"Melawan arus (one way)", "80000"},               // 5
    {"Parkir di tempat terlarang", "45000"},           // 6
    {"Tidak membawa SIM", "30000"},                    // 7
    {"Tidak membawa STNK", "35000"},                   // 8
    {"Menggunakan ponsel saat berkendara", "60000"},   // 9
    {"Tidak menggunakan sabuk pengaman", "40000"}      // 10
};

// Forward declarations
string getTanggalOtomatis();
void clearScreen();
void tampilkanHeader();
bool login();
void loadUsers();
void saveUsers();
void loadData();
void saveData();
void tampilkanMenu();
void tampilkanMenuDashboard();
void tampilkanDaftarPelanggaran();
void tambahData();
void tampilkanData();
void updateData();
void hapusData();
void printData();
void exportData();
void dashboardStatistik();
bool validasiNama(string nama);
bool validasiKTP(string ktp);
bool validasiPlat(string plat);
bool validasiAlamat(string alamat);
string formatRupiah(double nilai);

// Fungsi untuk mendapatkan tanggal otomatis
string getTanggalOtomatis() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    string hari = to_string(ltm->tm_mday);
    string bulan = to_string(1 + ltm->tm_mon);
    string tahun = to_string(1900 + ltm->tm_year);
    
    if (hari.length() == 1) hari = "0" + hari;
    if (bulan.length() == 1) bulan = "0" + bulan;
    
    return hari + "/" + bulan + "/" + tahun;
}

// Fungsi untuk membersihkan layar
void clearScreen() {
    system("cls");  // Windows
    // system("clear");  // Linux/Mac
}

// Fungsi untuk menampilkan header
void tampilkanHeader() {
    cout << "\n=================================================" << endl;
    cout << "    SISTEM DENDA PELANGGARAN LALU LINTAS" << endl;
    cout << "=================================================" << endl;
}

// Fungsi untuk memuat data user dari file
void loadUsers() {
    ifstream file("users.txt");
    jumlahUsers = 0;
    
    if (file.is_open()) {
        string line;
        while (getline(file, line) && jumlahUsers < MAX_USERS) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            
            if (pos1 != string::npos && pos2 != string::npos) {
                users[jumlahUsers].username = line.substr(0, pos1);
                users[jumlahUsers].password = line.substr(pos1 + 1, pos2 - pos1 - 1);
                users[jumlahUsers].level = line.substr(pos2 + 1);
                jumlahUsers++;
            }
        }
        file.close();
    }
    
    // Jika file tidak ada atau kosong, buat user default
    if (jumlahUsers == 0) {
        users[0] = {"rizqi", "rizqi123", "admin"};
        users[1] = {"bagus", "bagus123", "operator"};
        users[2] = {"khirzi", "khirzi123", "operator"};
        jumlahUsers = 3;
        saveUsers();
    }
}

// Fungsi untuk menyimpan data user ke file
void saveUsers() {
    ofstream file("users.txt");
    if (file.is_open()) {
        for (int i = 0; i < jumlahUsers; i++) {
            file << users[i].username << "," << users[i].password << "," << users[i].level << endl;
        }
        file.close();
    }
}

// Fungsi untuk memuat data pelanggaran dari file
void loadData() {
    ifstream file("pelanggar.csv");
    jumlahData = 0;
    
    if (file.is_open()) {
        string line;
        // Skip header
        getline(file, line);
        
        while (getline(file, line) && jumlahData < MAX_DATA) {
            size_t pos = 0;
            string data[8];
            int index = 0;
            
            // Parse CSV line
            while (pos < line.length() && index < 8) {
                size_t nextPos = line.find(',', pos);
                if (nextPos == string::npos) nextPos = line.length();
                
                data[index] = line.substr(pos, nextPos - pos);
                pos = nextPos + 1;
                index++;
            }
            
            if (index >= 7) {
                dataPelanggaran[jumlahData].id = stoi(data[0]);
                dataPelanggaran[jumlahData].identitas.nama = data[1];
                dataPelanggaran[jumlahData].identitas.alamat = data[2];
                dataPelanggaran[jumlahData].identitas.noKTP = data[3];
                dataPelanggaran[jumlahData].identitas.jenisKendaraan = data[4];
                dataPelanggaran[jumlahData].identitas.noPlat = data[5];
                dataPelanggaran[jumlahData].totalDenda = stod(data[6]);
                dataPelanggaran[jumlahData].tanggal = data[7];
                dataPelanggaran[jumlahData].jumlahPelanggaran = 1; // Simplified
                jumlahData++;
            }
        }
        file.close();
    }
}

// Fungsi untuk menyimpan data pelanggaran ke file
void saveData() {
    ofstream file("pelanggar.csv");
    if (file.is_open()) {
        // Header CSV
        file << "ID,Nama,Alamat,NoKTP,JenisKendaraan,NoPlat,TotalDenda,Tanggal" << endl;
        
        for (int i = 0; i < jumlahData; i++) {
            file << dataPelanggaran[i].id << ","
                 << dataPelanggaran[i].identitas.nama << ","
                 << dataPelanggaran[i].identitas.alamat << ","
                 << dataPelanggaran[i].identitas.noKTP << ","
                 << dataPelanggaran[i].identitas.jenisKendaraan << ","
                 << dataPelanggaran[i].identitas.noPlat << ","
                 << dataPelanggaran[i].totalDenda << ","
                 << dataPelanggaran[i].tanggal << endl;
        }
        file.close();
    }
}

// Fungsi login dengan sistem dinamis
bool login() {
    loadUsers();
    
    string username, password;
    int percobaan = 0;
    
    while (percobaan < 3) {
        clearScreen();
        tampilkanHeader();
        cout << "\n--- LOGIN SISTEM ---" << endl;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        
        // Cek username dan password dari array users
        bool loginBerhasil = false;
        for (int i = 0; i < jumlahUsers; i++) {
            if (users[i].username == username && users[i].password == password) {
                loginBerhasil = true;
                break;
            }
        }
        
        if (loginBerhasil) {
            cout << "\nLogin berhasil! Selamat datang " << username << "!" << endl;
            cout << "Tekan Enter untuk melanjutkan...";
            cin.ignore();
            string dummy;
            getline(cin, dummy);
            return true;
        } else {
            percobaan++;
            cout << "\nUsername atau password salah!" << endl;
            cout << "Percobaan ke-" << percobaan << " dari 3" << endl;
            if (percobaan < 3) {
                cout << "Tekan Enter untuk mencoba lagi...";
                cin.ignore();
                string dummy;
                getline(cin, dummy);
            }
        }
    }
    
    cout << "\nAnda telah salah 3 kali. Program akan keluar." << endl;
    return false;
}

// Fungsi validasi nama
bool validasiNama(string nama) {
    if (nama.length() > 50 || nama.empty()) return false;
    
    for (char c : nama) {
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ')) {
            return false;
        }
    }
    return true;
}

// Fungsi validasi KTP
bool validasiKTP(string ktp) {
    if (ktp.length() != 16) return false;
    
    for (char c : ktp) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

// Fungsi validasi plat nomor
bool validasiPlat(string plat) {
    if (plat.length() < 5 || plat.length() > 10) return false;
    
    // Validasi sederhana untuk format plat Indonesia
    bool hasLetter = false, hasNumber = false;
    for (char c : plat) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) hasLetter = true;
        if (c >= '0' && c <= '9') hasNumber = true;
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || 
              (c >= '0' && c <= '9') || c == ' ')) return false;
    }
    return hasLetter && hasNumber;
}

// Fungsi validasi alamat
bool validasiAlamat(string alamat) {
    if (alamat.empty() || alamat.length() > 100) return false;
    
    // Tidak boleh mengandung karakter khusus berbahaya
    string karakterTerlarang = "!@#$%^&*()=+[]{}|;:'\",<>?/\\`~";
    for (char c : alamat) {
        for (char forbidden : karakterTerlarang) {
            if (c == forbidden) return false;
        }
    }
    return true;
}

// Fungsi format rupiah
string formatRupiah(double nilai) {
    return "Rp " + to_string((long long)nilai);
}

// Fungsi untuk menampilkan menu utama
void tampilkanMenu() {
    cout << "\n--- MENU UTAMA ---" << endl;
    cout << "1. Tambah Data Pelanggaran (CREATE)" << endl;
    cout << "2. Tampilkan Data Pelanggaran (READ)" << endl;
    cout << "3. Update Data Pelanggaran (UPDATE)" << endl;
    cout << "4. Hapus Data Pelanggaran (DELETE)" << endl;
    cout << "5. Print & Export Data" << endl;
    cout << "6. Dashboard & Statistik" << endl;
    cout << "7. Keluar" << endl;
    cout << "Pilihan Anda: ";
}

// Fungsi untuk menampilkan menu dashboard
void tampilkanMenuDashboard() {
    cout << "\n--- DASHBOARD & STATISTIK ---" << endl;
    cout << "1. Statistik Umum" << endl;
    cout << "2. Pelanggaran Terbanyak" << endl;
    cout << "3. Denda Tertinggi" << endl;
    cout << "4. Kembali ke Menu Utama" << endl;
    cout << "Pilihan: ";
}

// Fungsi untuk menampilkan daftar pelanggaran menggunakan array 2D
void tampilkanDaftarPelanggaran() {
    cout << "\n--- DAFTAR JENIS PELANGGARAN ---" << endl;
    cout << "ID | Jenis Pelanggaran | Denda" << endl;
    cout << "---|-------------------|--------" << endl;
    
    for (int i = 1; i <= 10; i++) {
        cout << i << "  | " << masterPelanggaran[i][0] << " | " 
             << formatRupiah(stod(masterPelanggaran[i][1])) << endl;
    }
    cout << "-----------------------------------" << endl;
}

// Fungsi CREATE dengan validasi input
void tambahData() {
    clearScreen();
    tampilkanHeader();
    
    if (jumlahData >= MAX_DATA) {
        cout << "\nData sudah penuh! Maksimal " << MAX_DATA << " data." << endl;
        return;
    }
    
    cout << "\n--- TAMBAH DATA PELANGGARAN ---" << endl;
    
    dataPelanggaran[jumlahData].id = jumlahData + 1;
    dataPelanggaran[jumlahData].tanggal = getTanggalOtomatis();
    dataPelanggaran[jumlahData].jumlahPelanggaran = 0;
    dataPelanggaran[jumlahData].totalDenda = 0;
    
    cout << "\nMasukkan Identitas Pelanggar:" << endl;
    
    // Input nama dengan validasi
    string nama;
    do {
        cout << "Nama (hanya huruf dan spasi, max 50 karakter): ";
        cin.ignore();
        getline(cin, nama);
        if (!validasiNama(nama)) {
            cout << "Nama tidak valid! Hanya boleh huruf dan spasi, maksimal 50 karakter." << endl;
        }
    } while (!validasiNama(nama));
    dataPelanggaran[jumlahData].identitas.nama = nama;
    
    // Input alamat dengan validasi
    string alamat;
    do {
        cout << "Alamat (tanpa karakter khusus): ";
        getline(cin, alamat);
        if (!validasiAlamat(alamat)) {
            cout << "Alamat tidak valid! Tidak boleh mengandung karakter khusus." << endl;
        }
    } while (!validasiAlamat(alamat));
    dataPelanggaran[jumlahData].identitas.alamat = alamat;
    
    // Input KTP dengan validasi
    string ktp;
    do {
        cout << "No. KTP (16 digit angka): ";
        getline(cin, ktp);
        if (!validasiKTP(ktp)) {
            cout << "No. KTP tidak valid! Harus tepat 16 digit angka." << endl;
        }
    } while (!validasiKTP(ktp));
    dataPelanggaran[jumlahData].identitas.noKTP = ktp;
    
    // Input jenis kendaraan dengan pilihan
    cout << "\nPilih Jenis Kendaraan:" << endl;
    cout << "1. Motor" << endl;
    cout << "2. Mobil" << endl;
    cout << "3. Truk" << endl;
    cout << "4. Bus" << endl;
    int pilihanKendaraan;
    cout << "Pilihan (1-4): ";
    cin >> pilihanKendaraan;
    
    string jenisKendaraan[] = {"", "Motor", "Mobil", "Truk", "Bus"};
    if (pilihanKendaraan >= 1 && pilihanKendaraan <= 4) {
        dataPelanggaran[jumlahData].identitas.jenisKendaraan = jenisKendaraan[pilihanKendaraan];
    } else {
        dataPelanggaran[jumlahData].identitas.jenisKendaraan = "Motor";
    }
    
    // Input plat dengan validasi
    string plat;
    do {
        cout << "No. Plat (format Indonesia): ";
        cin.ignore();
        getline(cin, plat);
        if (!validasiPlat(plat)) {
            cout << "No. Plat tidak valid! Format tidak sesuai." << endl;
        }
    } while (!validasiPlat(plat));
    dataPelanggaran[jumlahData].identitas.noPlat = plat;
    
    // Input pelanggaran
    char lagi = 'y';
    while (lagi == 'y' || lagi == 'Y') {
        tampilkanDaftarPelanggaran();
        
        int idPelanggaran;
        cout << "\nPilih ID pelanggaran (1-10): ";
        cin >> idPelanggaran;
        
        if (idPelanggaran >= 1 && idPelanggaran <= 10) {
            dataPelanggaran[jumlahData].jenisPelanggaran[dataPelanggaran[jumlahData].jumlahPelanggaran] = idPelanggaran;
            dataPelanggaran[jumlahData].jumlahPelanggaran++;
            dataPelanggaran[jumlahData].totalDenda += stod(masterPelanggaran[idPelanggaran][1]);
            
            cout << "Pelanggaran berhasil ditambahkan!" << endl;
        } else {
            cout << "ID pelanggaran tidak valid!" << endl;
        }
        
        cout << "Tambah pelanggaran lain? (y/n): ";
        cin >> lagi;
    }
    
    // Tampilkan nota
    clearScreen();
    tampilkanHeader();
    cout << "\n--- NOTA DENDA PELANGGARAN ---" << endl;
    cout << "ID: " << dataPelanggaran[jumlahData].id << endl;
    cout << "Tanggal: " << dataPelanggaran[jumlahData].tanggal << endl;
    
    cout << "\nIdentitas Pelanggar:" << endl;
    cout << "Nama: " << dataPelanggaran[jumlahData].identitas.nama << endl;
    cout << "Alamat: " << dataPelanggaran[jumlahData].identitas.alamat << endl;
    cout << "No. KTP: " << dataPelanggaran[jumlahData].identitas.noKTP << endl;
    cout << "Jenis Kendaraan: " << dataPelanggaran[jumlahData].identitas.jenisKendaraan << endl;
    cout << "No. Plat: " << dataPelanggaran[jumlahData].identitas.noPlat << endl;
    
    cout << "\nDaftar Pelanggaran:" << endl;
    cout << "No | Jenis Pelanggaran | Denda" << endl;
    cout << "--------------------------------" << endl;
    
    for (int i = 0; i < dataPelanggaran[jumlahData].jumlahPelanggaran; i++) {
        int idPelanggaran = dataPelanggaran[jumlahData].jenisPelanggaran[i];
        cout << (i+1) << "  | " << masterPelanggaran[idPelanggaran][0] 
             << " | " << formatRupiah(stod(masterPelanggaran[idPelanggaran][1])) << endl;
    }
    
    cout << "--------------------------------" << endl;
    cout << "TOTAL DENDA: " << formatRupiah(dataPelanggaran[jumlahData].totalDenda) << endl;
    cout << "================================" << endl;
    
    jumlahData++;
    saveData(); // Auto-save
    cout << "\nData berhasil disimpan!" << endl;
    cout << "Tekan Enter untuk kembali ke menu...";
    cin.ignore();
    string dummy;
    getline(cin, dummy);
}

// Fungsi READ
void tampilkanData() {
    clearScreen();
    tampilkanHeader();
    cout << "\n--- DAFTAR DATA PELANGGARAN ---" << endl;
    
    if (jumlahData == 0) {
        cout << "\nBelum ada data pelanggaran!" << endl;
    } else {
        cout << "\nJumlah data: " << jumlahData << endl;
        cout << "ID | Nama | No. Plat | Jumlah Pelanggaran | Total Denda" << endl;
        cout << "-------------------------------------------------------" << endl;
        
        for (int i = 0; i < jumlahData; i++) {
            cout << dataPelanggaran[i].id << "  | " 
                 << dataPelanggaran[i].identitas.nama << " | "
                 << dataPelanggaran[i].identitas.noPlat << " | "
                 << dataPelanggaran[i].jumlahPelanggaran << " | "
                 << formatRupiah(dataPelanggaran[i].totalDenda) << endl;
        }
        
        int idDetail;
        cout << "\nMasukkan ID untuk melihat detail (0 untuk kembali): ";
        cin >> idDetail;
        
        if (idDetail > 0 && idDetail <= jumlahData) {
            int index = -1;
            for (int i = 0; i < jumlahData; i++) {
                if (dataPelanggaran[i].id == idDetail) {
                    index = i;
                    break;
                }
            }
            
            if (index != -1) {
                clearScreen();
                tampilkanHeader();
                cout << "\n--- DETAIL PELANGGARAN ---" << endl;
                cout << "ID: " << dataPelanggaran[index].id << endl;
                cout << "Tanggal: " << dataPelanggaran[index].tanggal << endl;
                
                cout << "\nIdentitas Pelanggar:" << endl;
                cout << "Nama: " << dataPelanggaran[index].identitas.nama << endl;
                cout << "Alamat: " << dataPelanggaran[index].identitas.alamat << endl;
                cout << "No. KTP: " << dataPelanggaran[index].identitas.noKTP << endl;
                cout << "Jenis Kendaraan: " << dataPelanggaran[index].identitas.jenisKendaraan << endl;
                cout << "No. Plat: " << dataPelanggaran[index].identitas.noPlat << endl;
                
                cout << "\nDaftar Pelanggaran:" << endl;
                cout << "No | Jenis Pelanggaran | Denda" << endl;
                cout << "--------------------------------" << endl;
                
                for (int i = 0; i < dataPelanggaran[index].jumlahPelanggaran; i++) {
                    int idPelanggaran = dataPelanggaran[index].jenisPelanggaran[i];
                    cout << (i+1) << "  | " << masterPelanggaran[idPelanggaran][0] 
                         << " | " << formatRupiah(stod(masterPelanggaran[idPelanggaran][1])) << endl;
                }
                
                cout << "--------------------------------" << endl;
                cout << "TOTAL DENDA: " << formatRupiah(dataPelanggaran[index].totalDenda) << endl;
            }
        }
    }
    
    cout << "\nTekan Enter untuk kembali ke menu...";
    cin.ignore();
    string dummy;
    getline(cin, dummy);
}

// Fungsi UPDATE dengan validasi
void updateData() {
    clearScreen();
    tampilkanHeader();
    cout << "\n--- UPDATE DATA PELANGGARAN ---" << endl;
    
    if (jumlahData == 0) {
        cout << "\nBelum ada data pelanggaran!" << endl;
    } else {
        cout << "\nDaftar Data:" << endl;
        cout << "ID | Nama | No. Plat" << endl;
        cout << "---------------------" << endl;
        
        for (int i = 0; i < jumlahData; i++) {
            cout << dataPelanggaran[i].id << "  | " 
                 << dataPelanggaran[i].identitas.nama << " | "
                 << dataPelanggaran[i].identitas.noPlat << endl;
        }
        
        int idUpdate;
        cout << "\nMasukkan ID yang akan diupdate (0 untuk batal): ";
        cin >> idUpdate;
        
        if (idUpdate > 0 && idUpdate <= jumlahData) {
            int index = -1;
            for (int i = 0; i < jumlahData; i++) {
                if (dataPelanggaran[i].id == idUpdate) {
                    index = i;
                    break;
                }
            }
            
            if (index != -1) {
                cout << "\n--- UPDATE DATA ID: " << idUpdate << " ---" << endl;
                cout << "Kosongkan input untuk tidak mengubah data" << endl;
                
                // Update nama dengan validasi
                string newNama;
                cout << "Nama [" << dataPelanggaran[index].identitas.nama << "]: ";
                cin.ignore();
                getline(cin, newNama);
                if (!newNama.empty() && validasiNama(newNama)) {
                    dataPelanggaran[index].identitas.nama = newNama;
                } else if (!newNama.empty()) {
                    cout << "Nama tidak valid, tidak diubah." << endl;
                }
                
                // Update alamat dengan validasi
                string newAlamat;
                cout << "Alamat [" << dataPelanggaran[index].identitas.alamat << "]: ";
                getline(cin, newAlamat);
                if (!newAlamat.empty() && validasiAlamat(newAlamat)) {
                    dataPelanggaran[index].identitas.alamat = newAlamat;
                } else if (!newAlamat.empty()) {
                    cout << "Alamat tidak valid, tidak diubah." << endl;
                }
                
                // Update plat dengan validasi
                string newPlat;
                cout << "No. Plat [" << dataPelanggaran[index].identitas.noPlat << "]: ";
                getline(cin, newPlat);
                if (!newPlat.empty() && validasiPlat(newPlat)) {
                    dataPelanggaran[index].identitas.noPlat = newPlat;
                } else if (!newPlat.empty()) {
                    cout << "No. Plat tidak valid, tidak diubah." << endl;
                }
                
                saveData(); // Auto-save
                cout << "\nData berhasil diupdate!" << endl;
            }
        }
    }
    
    cout << "\nTekan Enter untuk kembali ke menu...";
    cin.ignore();
    string dummy;
    getline(cin, dummy);
}

// Fungsi DELETE
void hapusData() {
    clearScreen();
    tampilkanHeader();
    cout << "\n--- HAPUS DATA PELANGGARAN ---" << endl;
    
    if (jumlahData == 0) {
        cout << "\nBelum ada data pelanggaran!" << endl;
    } else {
        cout << "\nDaftar Data:" << endl;
        cout << "ID | Nama | No. Plat" << endl;
        cout << "---------------------" << endl;
        
        for (int i = 0; i < jumlahData; i++) {
            cout << dataPelanggaran[i].id << "  | " 
                 << dataPelanggaran[i].identitas.nama << " | "
                 << dataPelanggaran[i].identitas.noPlat << endl;
        }
        
        int idHapus;
        cout << "\nMasukkan ID yang akan dihapus (0 untuk batal): ";
        cin >> idHapus;
        
        if (idHapus > 0 && idHapus <= jumlahData) {
            int index = -1;
            for (int i = 0; i < jumlahData; i++) {
                if (dataPelanggaran[i].id == idHapus) {
                    index = i;
                    break;
                }
            }
            
            if (index != -1) {
                char konfirmasi;
                cout << "\nYakin ingin menghapus data " << dataPelanggaran[index].identitas.nama << "? (y/n): ";
                cin >> konfirmasi;
                
                if (konfirmasi == 'y' || konfirmasi == 'Y') {
                    // Geser data ke kiri untuk menghapus
                    for (int i = index; i < jumlahData - 1; i++) {
                        dataPelanggaran[i] = dataPelanggaran[i + 1];
                    }
                    jumlahData--;
                    
                    // Update ID setelah penghapusan
                    for (int i = 0; i < jumlahData; i++) {
                        dataPelanggaran[i].id = i + 1;
                    }
                    
                    saveData(); // Auto-save
                    cout << "\nData berhasil dihapus!" << endl;
                } else {
                    cout << "\nPenghapusan dibatalkan!" << endl;
                }
            }
        }
    }
    
    cout << "\nTekan Enter untuk kembali ke menu...";
    cin.ignore();
    string dummy;
    getline(cin, dummy);
}

// Fungsi Print Data
void printData() {
    clearScreen();
    tampilkanHeader();
    cout << "\n--- PRINT & EXPORT DATA ---" << endl;
    
    if (jumlahData == 0) {
        cout << "\nBelum ada data untuk di-print!" << endl;
    } else {
        cout << "1. Print Individual (berdasarkan ID)" << endl;
        cout << "2. Print Semua Data" << endl;
        cout << "3. Export ke File" << endl;
        cout << "4. Kembali" << endl;
        cout << "Pilihan: ";
        
        int pilihan;
        cin >> pilihan;
        
        switch (pilihan) {
            case 1: {
                cout << "\nMasukkan ID yang akan di-print: ";
                int id;
                cin >> id;
                
                int index = -1;
                for (int i = 0; i < jumlahData; i++) {
                    if (dataPelanggaran[i].id == id) {
                        index = i;
                        break;
                    }
                }
                
                if (index != -1) {
                    // Buat nama file
                    string namaFile = "printout/" + to_string(dataPelanggaran[index].id) + "_" + 
                                    dataPelanggaran[index].identitas.nama + "_" + 
                                    dataPelanggaran[index].identitas.noKTP + ".txt";
                    
                    ofstream file(namaFile);
                    if (file.is_open()) {
                        file << "=================================================" << endl;
                        file << "    NOTA DENDA PELANGGARAN LALU LINTAS" << endl;
                        file << "=================================================" << endl;
                        file << "ID: " << dataPelanggaran[index].id << endl;
                        file << "Tanggal: " << dataPelanggaran[index].tanggal << endl;
                        file << endl;
                        file << "Identitas Pelanggar:" << endl;
                        file << "Nama: " << dataPelanggaran[index].identitas.nama << endl;
                        file << "Alamat: " << dataPelanggaran[index].identitas.alamat << endl;
                        file << "No. KTP: " << dataPelanggaran[index].identitas.noKTP << endl;
                        file << "Jenis Kendaraan: " << dataPelanggaran[index].identitas.jenisKendaraan << endl;
                        file << "No. Plat: " << dataPelanggaran[index].identitas.noPlat << endl;
                        file << endl;
                        file << "Daftar Pelanggaran:" << endl;
                        file << "No | Jenis Pelanggaran | Denda" << endl;
                        file << "--------------------------------" << endl;
                        
                        for (int i = 0; i < dataPelanggaran[index].jumlahPelanggaran; i++) {
                            int idPelanggaran = dataPelanggaran[index].jenisPelanggaran[i];
                            file << (i+1) << "  | " << masterPelanggaran[idPelanggaran][0] 
                                 << " | " << formatRupiah(stod(masterPelanggaran[idPelanggaran][1])) << endl;
                        }
                        
                        file << "--------------------------------" << endl;
                        file << "TOTAL DENDA: " << formatRupiah(dataPelanggaran[index].totalDenda) << endl;
                        file << "================================" << endl;
                        file.close();
                        
                        cout << "\nData berhasil di-print ke file: " << namaFile << endl;
                    } else {
                        cout << "\nGagal membuat file print!" << endl;
                    }
                } else {
                    cout << "\nID tidak ditemukan!" << endl;
                }
                break;
            }
            case 2: {
                string namaFile = "printout/semua_data_" + getTanggalOtomatis() + ".txt";
                
                ofstream file(namaFile);
                if (file.is_open()) {
                    file << "=================================================" << endl;
                    file << "    LAPORAN DENDA PELANGGARAN LALU LINTAS" << endl;
                    file << "=================================================" << endl;
                    file << "Tanggal Cetak: " << getTanggalOtomatis() << endl;
                    file << "Jumlah Data: " << jumlahData << endl;
                    file << endl;
                    
                    for (int i = 0; i < jumlahData; i++) {
                        file << "--- DATA " << (i+1) << " ---" << endl;
                        file << "ID: " << dataPelanggaran[i].id << endl;
                        file << "Nama: " << dataPelanggaran[i].identitas.nama << endl;
                        file << "No. Plat: " << dataPelanggaran[i].identitas.noPlat << endl;
                        file << "Total Denda: " << formatRupiah(dataPelanggaran[i].totalDenda) << endl;
                        file << "Tanggal: " << dataPelanggaran[i].tanggal << endl;
                        file << endl;
                    }
                    file.close();
                    
                    cout << "\nSemua data berhasil di-print ke file: " << namaFile << endl;
                } else {
                    cout << "\nGagal membuat file print!" << endl;
                }
                break;
            }
            case 3: {
                exportData();
                break;
            }
        }
    }
    
    cout << "\nTekan Enter untuk kembali...";
    cin.ignore();
    string dummy;
    getline(cin, dummy);
}

// Fungsi Export Data
void exportData() {
    cout << "\n--- EXPORT DATA ---" << endl;
    cout << "Data akan di-export ke file CSV..." << endl;
    
    string namaFile = "printout/export_data_" + getTanggalOtomatis() + ".csv";
    
    ofstream file(namaFile);
    if (file.is_open()) {
        // Header CSV
        file << "ID,Nama,Alamat,NoKTP,JenisKendaraan,NoPlat,TotalDenda,Tanggal,JumlahPelanggaran" << endl;
        
        for (int i = 0; i < jumlahData; i++) {
            file << dataPelanggaran[i].id << ","
                 << dataPelanggaran[i].identitas.nama << ","
                 << dataPelanggaran[i].identitas.alamat << ","
                 << dataPelanggaran[i].identitas.noKTP << ","
                 << dataPelanggaran[i].identitas.jenisKendaraan << ","
                 << dataPelanggaran[i].identitas.noPlat << ","
                 << dataPelanggaran[i].totalDenda << ","
                 << dataPelanggaran[i].tanggal << ","
                 << dataPelanggaran[i].jumlahPelanggaran << endl;
        }
        file.close();
        
        cout << "Data berhasil di-export ke file: " << namaFile << endl;
    } else {
        cout << "Gagal membuat file export!" << endl;
    }
}

// Fungsi Dashboard Statistik
void dashboardStatistik() {
    clearScreen();
    tampilkanHeader();
    
    int pilihan;
    do {
        tampilkanMenuDashboard();
        cin >> pilihan;
        
        switch (pilihan) {
            case 1: {
                clearScreen();
                tampilkanHeader();
                cout << "\n--- STATISTIK UMUM ---" << endl;
                
                if (jumlahData == 0) {
                    cout << "Belum ada data untuk ditampilkan." << endl;
                } else {
                    double totalPendapatan = 0;
                    int totalPelanggaran = 0;
                    
                    for (int i = 0; i < jumlahData; i++) {
                        totalPendapatan += dataPelanggaran[i].totalDenda;
                        totalPelanggaran += dataPelanggaran[i].jumlahPelanggaran;
                    }
                    
                    cout << "Total Pelanggar: " << jumlahData << endl;
                    cout << "Total Pelanggaran: " << totalPelanggaran << endl;
                    cout << "Total Pendapatan Denda: " << formatRupiah(totalPendapatan) << endl;
                    cout << "Rata-rata Denda per Pelanggar: " << formatRupiah(totalPendapatan / jumlahData) << endl;
                }
                break;
            }
            case 2: {
                clearScreen();
                tampilkanHeader();
                cout << "\n--- STATISTIK PELANGGARAN TERBANYAK ---" << endl;
                
                if (jumlahData == 0) {
                    cout << "Belum ada data untuk ditampilkan." << endl;
                } else {
                    // Hitung frekuensi setiap jenis pelanggaran
                    int hitungPelanggaran[11] = {0}; // index 0 tidak dipakai
                    
                    for (int i = 0; i < jumlahData; i++) {
                        for (int j = 0; j < dataPelanggaran[i].jumlahPelanggaran; j++) {
                            int idPelanggaran = dataPelanggaran[i].jenisPelanggaran[j];
                            hitungPelanggaran[idPelanggaran]++;
                        }
                    }
                    
                    cout << "Ranking Pelanggaran Terbanyak:" << endl;
                    cout << "Rank | Jenis Pelanggaran | Jumlah" << endl;
                    cout << "-----|--------------------|-------" << endl;
                    
                    // Sorting sederhana untuk ranking
                    for (int rank = 1; rank <= 5; rank++) {
                        int maxIndex = 0, maxCount = 0;
                        for (int i = 1; i <= 10; i++) {
                            if (hitungPelanggaran[i] > maxCount) {
                                maxCount = hitungPelanggaran[i];
                                maxIndex = i;
                            }
                        }
                        
                        if (maxCount > 0) {
                            cout << rank << "    | " << masterPelanggaran[maxIndex][0] 
                                 << " | " << maxCount << endl;
                            hitungPelanggaran[maxIndex] = 0; // Reset untuk ranking berikutnya
                        }
                    }
                }
                break;
            }
            case 3: {
                clearScreen();
                tampilkanHeader();
                cout << "\n--- PELANGGAR DENGAN DENDA TERTINGGI ---" << endl;
                
                if (jumlahData == 0) {
                    cout << "Belum ada data untuk ditampilkan." << endl;
                } else {
                    // Sorting sederhana untuk denda tertinggi
                    cout << "Rank | Nama | No. Plat | Total Denda" << endl;
                    cout << "-----|----- |----------|------------" << endl;
                    
                    // Buat array untuk menyimpan index yang sudah diurutkan
                    bool sudahDiurutkan[MAX_DATA] = {false};
                    
                    for (int rank = 1; rank <= 5 && rank <= jumlahData; rank++) {
                        int maxIndex = -1;
                        double maxDenda = 0;
                        
                        for (int i = 0; i < jumlahData; i++) {
                            if (!sudahDiurutkan[i] && dataPelanggaran[i].totalDenda > maxDenda) {
                                maxDenda = dataPelanggaran[i].totalDenda;
                                maxIndex = i;
                            }
                        }
                        
                        if (maxIndex != -1) {
                            cout << rank << "    | " << dataPelanggaran[maxIndex].identitas.nama 
                                 << " | " << dataPelanggaran[maxIndex].identitas.noPlat 
                                 << " | " << formatRupiah(dataPelanggaran[maxIndex].totalDenda) << endl;
                            sudahDiurutkan[maxIndex] = true;
                        }
                    }
                }
                break;
            }
        }
        
        if (pilihan != 4) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore();
            string dummy;
            getline(cin, dummy);
        }
        
    } while (pilihan != 4);
}

// Fungsi utama
int main() {
    // Load data saat program dimulai
    loadData();
    
    // Login terlebih dahulu
    if (!login()) {
        return 0;
    }
    
    int pilihan;
    
    do {
        clearScreen();
        tampilkanHeader();
        tampilkanMenu();
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                tambahData();
                break;
            case 2:
                tampilkanData();
                break;
            case 3:
                updateData();
                break;
            case 4:
                hapusData();
                break;
            case 5:
                printData();
                break;
            case 6:
                dashboardStatistik();
                break;
            case 7:
                clearScreen();
                tampilkanHeader();
                cout << "\nMenyimpan data..." << endl;
                saveData();
                cout << "Terima kasih telah menggunakan sistem ini!" << endl;
                cout << "Program selesai." << endl;
                break;
            default:
                cout << "\nPilihan tidak valid!" << endl;
                cout << "Tekan Enter untuk melanjutkan...";
                cin.ignore();
                string dummy;
                getline(cin, dummy);
        }
    } while (pilihan != 7);
    
    return 0;
}


