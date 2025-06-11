#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Maksimal data yang bisa disimpan
const int MAX_DATA = 100;
const int MAX_PELANGGARAN = 10;

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
    int jenisPelanggaran[MAX_PELANGGARAN];  // Array untuk menyimpan ID pelanggaran
    int jumlahPelanggaran;
    double totalDenda;
    string tanggal;
};

// Array untuk menyimpan data
DataPelanggaran dataPelanggaran[MAX_DATA];
int jumlahData = 0;

// Data jenis pelanggaran menggunakan array
string namaPelanggaran[11] = {
    "",  // index 0 kosong
    "Menerobos lampu merah",
    "Tidak menggunakan helm", 
    "Kendaraan tidak layak jalan",
    "Melebihi batas kecepatan",
    "Melawan arus (one way)",
    "Parkir di tempat terlarang",
    "Tidak membawa SIM",
    "Tidak membawa STNK",
    "Menggunakan ponsel saat berkendara",
    "Tidak menggunakan sabuk pengaman"
};

double dendaPelanggaran[11] = {
    0,      // index 0 kosong
    50000,  // Menerobos lampu merah
    25000,  // Tidak menggunakan helm
    100000, // Kendaraan tidak layak jalan
    75000,  // Melebihi batas kecepatan
    80000,  // Melawan arus
    45000,  // Parkir terlarang
    30000,  // Tidak bawa SIM
    35000,  // Tidak bawa STNK
    60000,  // Pakai ponsel
    40000   // Tidak pakai sabuk pengaman
};

// Forward declarations (deklarasi fungsi)
string getTanggal();
void clearScreen();
void tampilkanHeader();
bool login();
void tampilkanMenu();
void tampilkanDaftarPelanggaran();
void tambahData();
void tampilkanData();
void updateData();
void hapusData();

// Fungsi untuk mendapatkan tanggal sederhana
string getTanggal() {
    return "29/05/2025";  // Tanggal sederhana untuk contoh
}

// Fungsi untuk membersihkan layar
void clearScreen() {
    system("cls");  // Windows
    // system("clear");  // Linux/Mac (uncomment jika pakai Linux/Mac)
}

// Fungsi untuk menampilkan header
void tampilkanHeader() {
    cout << "\n=================================================" << endl;
    cout << "    SISTEM DENDA PELANGGARAN LALU LINTAS" << endl;
    cout << "=================================================" << endl;
}

// Fungsi login sederhana
bool login() {
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
        
        // Cek username dan password
        if ((username == "rizqi" && password == "rizqi123") ||
            (username == "bagus" && password == "bagus123") ||
            (username == "khirzi" && password == "khirzi123")) {
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

// Fungsi untuk menampilkan menu utama
void tampilkanMenu() {
    cout << "\n--- MENU UTAMA ---" << endl;
    cout << "1. Tambah Data Pelanggaran (CREATE)" << endl;
    cout << "2. Tampilkan Data Pelanggaran (READ)" << endl;
    cout << "3. Update Data Pelanggaran (UPDATE)" << endl;
    cout << "4. Hapus Data Pelanggaran (DELETE)" << endl;
    cout << "5. Keluar" << endl;
    cout << "Pilihan Anda: ";
}

// Fungsi untuk menampilkan daftar pelanggaran
void tampilkanDaftarPelanggaran() {
    cout << "\n--- DAFTAR JENIS PELANGGARAN ---" << endl;
    cout << "ID | Jenis Pelanggaran | Denda" << endl;
    cout << "---|-------------------|--------" << endl;
    
    for (int i = 1; i <= 10; i++) {
        cout << i << "  | " << namaPelanggaran[i] << " | Rp " << dendaPelanggaran[i] << endl;
    }
    cout << "-----------------------------------" << endl;
}

// Fungsi CREATE - Menambah data pelanggaran
void tambahData() {
    clearScreen();
    tampilkanHeader();
    
    if (jumlahData >= MAX_DATA) {
        cout << "\nData sudah penuh! Maksimal " << MAX_DATA << " data." << endl;
        return;
    }
    
    cout << "\n--- TAMBAH DATA PELANGGARAN ---" << endl;
    
    // Set ID otomatis
    dataPelanggaran[jumlahData].id = jumlahData + 1;
    dataPelanggaran[jumlahData].tanggal = getTanggal();
    dataPelanggaran[jumlahData].jumlahPelanggaran = 0;
    dataPelanggaran[jumlahData].totalDenda = 0;
    
    // Input identitas
    cout << "\nMasukkan Identitas Pelanggar:" << endl;
    cout << "Nama: ";
    cin.ignore();
    getline(cin, dataPelanggaran[jumlahData].identitas.nama);
    
    cout << "Alamat: ";
    getline(cin, dataPelanggaran[jumlahData].identitas.alamat);
    
    cout << "No. KTP: ";
    getline(cin, dataPelanggaran[jumlahData].identitas.noKTP);
    
    cout << "Jenis Kendaraan: ";
    getline(cin, dataPelanggaran[jumlahData].identitas.jenisKendaraan);
    
    cout << "No. Plat: ";
    getline(cin, dataPelanggaran[jumlahData].identitas.noPlat);
    
    // Input pelanggaran
    char lagi = 'y';
    while (lagi == 'y' || lagi == 'Y') {
        tampilkanDaftarPelanggaran();
        
        int idPelanggaran;
        cout << "\nPilih ID pelanggaran (1-10): ";
        cin >> idPelanggaran;
        
        if (idPelanggaran >= 1 && idPelanggaran <= 10) {
            // Tambah pelanggaran ke array
            dataPelanggaran[jumlahData].jenisPelanggaran[dataPelanggaran[jumlahData].jumlahPelanggaran] = idPelanggaran;
            dataPelanggaran[jumlahData].jumlahPelanggaran++;
            dataPelanggaran[jumlahData].totalDenda += dendaPelanggaran[idPelanggaran];
            
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
        cout << (i+1) << "  | " << namaPelanggaran[idPelanggaran] 
             << " | Rp " << dendaPelanggaran[idPelanggaran] << endl;
    }
    
    cout << "--------------------------------" << endl;
    cout << "TOTAL DENDA: Rp " << dataPelanggaran[jumlahData].totalDenda << endl;
    cout << "================================" << endl;
    
    jumlahData++;
    cout << "\nData berhasil disimpan!" << endl;
    cout << "Tekan Enter untuk kembali ke menu...";
    cin.ignore();
    string dummy;
    getline(cin, dummy);
}

// Fungsi READ - Menampilkan data pelanggaran
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
                 << dataPelanggaran[i].jumlahPelanggaran << " | Rp "
                 << dataPelanggaran[i].totalDenda << endl;
        }
        
        // Pilihan untuk melihat detail
        int idDetail;
        cout << "\nMasukkan ID untuk melihat detail (0 untuk kembali): ";
        cin >> idDetail;
        
        if (idDetail > 0 && idDetail <= jumlahData) {
            // Cari data berdasarkan ID
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
                    cout << (i+1) << "  | " << namaPelanggaran[idPelanggaran] 
                         << " | Rp " << dendaPelanggaran[idPelanggaran] << endl;
                }
                
                cout << "--------------------------------" << endl;
                cout << "TOTAL DENDA: Rp " << dataPelanggaran[index].totalDenda << endl;
            }
        }
    }
    
    cout << "\nTekan Enter untuk kembali ke menu...";
    cin.ignore();
    string dummy;
    getline(cin, dummy);
}

// Fungsi UPDATE - Mengubah data pelanggaran
void updateData() {
    clearScreen();
    tampilkanHeader();
    cout << "\n--- UPDATE DATA PELANGGARAN ---" << endl;
    
    if (jumlahData == 0) {
        cout << "\nBelum ada data pelanggaran!" << endl;
    } else {
        // Tampilkan daftar data
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
            // Cari data berdasarkan ID
            int index = -1;
            for (int i = 0; i < jumlahData; i++) {
                if (dataPelanggaran[i].id == idUpdate) {
                    index = i;
                    break;
                }
            }
            
            if (index != -1) {
                cout << "\n--- UPDATE DATA ID: " << idUpdate << " ---" << endl;
                
                cout << "Nama [" << dataPelanggaran[index].identitas.nama << "]: ";
                cin.ignore();
                string newNama;
                getline(cin, newNama);
                if (!newNama.empty()) {
                    dataPelanggaran[index].identitas.nama = newNama;
                }
                
                cout << "Alamat [" << dataPelanggaran[index].identitas.alamat << "]: ";
                string newAlamat;
                getline(cin, newAlamat);
                if (!newAlamat.empty()) {
                    dataPelanggaran[index].identitas.alamat = newAlamat;
                }
                
                cout << "No. Plat [" << dataPelanggaran[index].identitas.noPlat << "]: ";
                string newPlat;
                getline(cin, newPlat);
                if (!newPlat.empty()) {
                    dataPelanggaran[index].identitas.noPlat = newPlat;
                }
                
                cout << "\nData berhasil diupdate!" << endl;
            }
        }
    }
    
    cout << "\nTekan Enter untuk kembali ke menu...";
    cin.ignore();
    string dummy;
    getline(cin, dummy);
}

// Fungsi DELETE - Menghapus data pelanggaran
void hapusData() {
    clearScreen();
    tampilkanHeader();
    cout << "\n--- HAPUS DATA PELANGGARAN ---" << endl;
    
    if (jumlahData == 0) {
        cout << "\nBelum ada data pelanggaran!" << endl;
    } else {
        // Tampilkan daftar data
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
            // Cari data berdasarkan ID
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

// Fungsi utama
int main() {
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
                clearScreen();
                tampilkanHeader();
                cout << "\nTerima kasih telah menggunakan sistem ini!" << endl;
                cout << "Program selesai." << endl;
                break;
            default:
                cout << "\nPilihan tidak valid!" << endl;
                cout << "Tekan Enter untuk melanjutkan...";
                cin.ignore();
                string dummy;
                getline(cin, dummy);
        }
    } while (pilihan != 5);
    
    return 0;
}