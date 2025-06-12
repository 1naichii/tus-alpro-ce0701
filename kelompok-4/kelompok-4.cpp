#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct TiketKapal {
    int id;
    string nama;
    string tujuan;
    string tanggal;
    int jumlah;
};

vector<TiketKapal> daftarTiket;
int nextId = 1;
const string NAMA_FILE = "data_tiket.txt";

// Fungsi untuk menyimpan data ke file
void simpanKeFile() {
    ofstream file(NAMA_FILE);
    for (const auto& tiket : daftarTiket) {
        file << tiket.id << "|" << tiket.nama << "|" << tiket.tujuan << "|"
             << tiket.tanggal << "|" << tiket.jumlah << endl;
    }
    file.close();
}

// Fungsi untuk memuat data dari file
void muatDariFile() {
    ifstream file(NAMA_FILE);
    string baris;

    while (getline(file, baris)) {
        stringstream ss(baris);
        TiketKapal tiket;
        string idStr, jumlahStr;

        getline(ss, idStr, '|'); tiket.id = stoi(idStr);
        getline(ss, tiket.nama, '|');
        getline(ss, tiket.tujuan, '|');
        getline(ss, tiket.tanggal, '|');
        getline(ss, jumlahStr); tiket.jumlah = stoi(jumlahStr);

        daftarTiket.push_back(tiket);
        if (tiket.id >= nextId) {
            nextId = tiket.id + 1;
        }
    }
    file.close();
}

// Fungsi konfirmasi kembali ke menu
void kembaliKeMenu() {
    char kembali;
    cout << "\nKembali ke menu utama? (iya/tidak): ";
    cin >> kembali;
    if (tolower(kembali) != 'iya') {
        cout << "\nTerima kasih telah menggunakan layanan kami.\n";
        exit(0);
    }
}

// Fitur 1: Tambah Tiket
void tambahTiket() {
    TiketKapal tiket;
    tiket.id = nextId++;

    cin.ignore();
    cout << "\n=== Formulir Pemesanan Tiket ===\n";
    cout << "Nama Penumpang         : ";
    getline(cin, tiket.nama);
    cout << "Tujuan Kapal           : ";
    getline(cin, tiket.tujuan);
    cout << "Tanggal Keberangkatan  : ";
    getline(cin, tiket.tanggal);
    cout << "Jumlah Tiket           : ";
    cin >> tiket.jumlah;

    daftarTiket.push_back(tiket);
    simpanKeFile();

    cout << "\n-------------------------------------------\n";
    cout << "  Tiket berhasil dipesan!\n";
    cout << "  Nomor Pemesanan Anda: " << tiket.id << endl;
    cout << "-------------------------------------------\n";

    kembaliKeMenu();
}

// Fitur 2: Lihat Daftar Tiket
void tampilkanTiket() {
    cout << "\n=== Daftar Pemesanan Tiket ===\n";
    if (daftarTiket.empty()) {
        cout << "Belum ada pemesanan tiket.\n";
    } else {
        for (const auto& tiket : daftarTiket) {
            cout << "\n-------------------------------------------\n";
            cout << "ID Pemesanan     : " << tiket.id << endl;
            cout << "Nama Penumpang   : " << tiket.nama << endl;
            cout << "Tujuan Kapal     : " << tiket.tujuan << endl;
            cout << "Tanggal Berangkat: " << tiket.tanggal << endl;
            cout << "Jumlah Tiket     : " << tiket.jumlah << endl;
        }
    }

    kembaliKeMenu();
}

// Fitur 3: Ubah Tiket
void ubahTiket() {
    int id;
    cout << "\nMasukkan ID pemesanan yang ingin diubah: ";
    cin >> id;

    for (auto& tiket : daftarTiket) {
        if (tiket.id == id) {
            cin.ignore();
            cout << "\n=== Ubah Data Pemesanan ===\n";
            cout << "Nama Penumpang baru         : ";
            getline(cin, tiket.nama);
            cout << "Tujuan Kapal baru           : ";
            getline(cin, tiket.tujuan);
            cout << "Tanggal Keberangkatan baru  : ";
            getline(cin, tiket.tanggal);
            cout << "Jumlah Tiket baru           : ";
            cin >> tiket.jumlah;

            simpanKeFile();

            cout << "\n-------------------------------------------\n";
            cout << "  Data pemesanan berhasil diperbarui.\n";
            cout << "-------------------------------------------\n";

            kembaliKeMenu();
            return;
        }
    }

    cout << "\n-------------------------------------------\n";
    cout << "  Maaf, ID pemesanan tidak ditemukan.\n";
    cout << "-------------------------------------------\n";

    kembaliKeMenu();
}

// Fitur 4: Hapus Tiket dengan Konfirmasi
void hapusTiket() {
    int id;
    cout << "\nMasukkan ID pemesanan yang ingin dibatalkan: ";
    cin >> id;

    bool ditemukan = false;

    for (auto it = daftarTiket.begin(); it != daftarTiket.end(); ++it) {
        if (it->id == id) {
            ditemukan = true;

            // Tampilkan detail
            cout << "\n=== Detail Pemesanan ===\n";
            cout << "ID Pemesanan     : " << it->id << endl;
            cout << "Nama Penumpang   : " << it->nama << endl;
            cout << "Tujuan Kapal     : " << it->tujuan << endl;
            cout << "Tanggal Berangkat: " << it->tanggal << endl;
            cout << "Jumlah Tiket     : " << it->jumlah << endl;

            // Konfirmasi
            char konfirmasi;
            cout << "\nApakah Anda yakin ingin membatalkan pemesanan ini? (iya/tidak): ";
            cin >> konfirmasi;

            if (tolower(konfirmasi) == 'iya') {
                daftarTiket.erase(it);
                simpanKeFile();

                cout << "\n-------------------------------------------\n";
                cout << "  Pemesanan berhasil dibatalkan dan dihapus.\n";
                cout << "-------------------------------------------\n";
            } else {
                cout << "\n-------------------------------------------\n";
                cout << "  Pembatalan dibatalkan oleh pengguna.\n";
                cout << "-------------------------------------------\n";
            }
            break;
        }
    }

    if (!ditemukan) {
        cout << "\n-------------------------------------------\n";
        cout << "  Maaf, ID pemesanan tidak ditemukan.\n";
        cout << "-------------------------------------------\n";
    }
}

// Menu utama
void menu() {
    int pilihan;
    do {
        cout << "\n===========================================\n";
        cout << "     SISTEM PEMESANAN TIKET KAPAL LAUT\n";
        cout << "===========================================\n";
        cout << "\nSilakan pilih salah satu menu berikut:\n\n";
        cout << "[1] Pesan Tiket Baru\n";
        cout << "[2] Lihat Daftar Pemesanan\n";
        cout << "[3] Ubah Data Pemesanan\n";
        cout << "[4] Batalkan Pemesanan\n";
        cout << "[5] Keluar dari Aplikasi\n\n";
        cout << "Masukkan pilihan Anda (1-5): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahTiket(); break;
            case 2: tampilkanTiket(); break;
            case 3: ubahTiket(); break;
            case 4: hapusTiket(); break;
            case 5:
                cout << "\nTerima kasih telah menggunakan layanan kami.\n";
                break;
            default:
                cout << "\nPilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 5);
}

// Fungsi utama
int main() {
    muatDariFile(); // Load data dari file jika ada
    menu();         // Tampilkan menu utama
    return 0;
}
