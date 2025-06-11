#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

struct Transaksi {
    string resi, namaPengirim, noHpPengirim;
    string namaPenerima, noHpPenerima, alamatPenerima;
    string namaBarang, jenisPengiriman;
    int hargaBarang, ongkir, totalHarga;
    string metodePembayaran, bank;
};

vector<Transaksi> databaseTransaksi;

bool isValidHp(const string& noHp) {
    if (noHp.length() > 12 || noHp.empty()) return false;
    for (char c : noHp) {
        if (!isdigit(c)) return false;
    }
    return true;
}

string inputNoHp(const string& siapa) {
    string noHp;
    while (true) {
        cout << "Masukkan No. HP " << siapa << ": ";
        getline(cin, noHp);
        if (isValidHp(noHp)) break;
        else cout << "No HP hanya boleh angka dan maksimal 12 digit! Coba lagi.\n";
    }
    return noHp;
}

int hitungHargaBarang(const string& namaBarang) {
    int len = namaBarang.length();
    if (len < 4) return 50000;
    else if (len < 6) return 75000;
    else if (len < 10) return 100000;
    else return 150000;
}

int pilihJenisPengiriman() {
    int pilihan;
    while (true) {
        cout << "\n=== JENIS PENGIRIMAN ===\n";
        cout << "1. Hemat (Rp 25.000)\n";
        cout << "2. Reguler (Rp 50.000)\n";
        cout << "3. Instan (Rp 75.000)\n";
        cout << "Pilih jenis pengiriman (1-3): ";
        cin >> pilihan;
        cin.ignore();
        if (pilihan >= 1 && pilihan <= 3) break;
        else cout << "Pilihan tidak valid! Harap pilih 1, 2, atau 3.\n";
    }
    return pilihan;
}

int getHargaPengiriman(int pilihan) {
    switch (pilihan) {
        case 1: return 25000;
        case 2: return 50000;
        case 3: return 75000;
        default: return 0;
    }
}

string getNamaPengiriman(int pilihan) {
    switch (pilihan) {
        case 1: return "Hemat";
        case 2: return "Reguler";
        case 3: return "Instan";
        default: return "Tidak valid";
    }
}

string generateResi() {
    string resi = "";
    string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < 10; ++i) {
        resi += charset[rand() % charset.size()];
    }
    return resi;
}

void tampilkanStruk(const Transaksi& t) {
    cout << "\n\n=========== STRUK PENGIRIMAN ===========\n";
    cout << "NO RESI : " << t.resi << "\n";
    cout << "Pengirim : " << t.namaPengirim << " | No HP: " << t.noHpPengirim << "\n";
    cout << "Penerima : " << t.namaPenerima << " | No HP: " << t.noHpPenerima << "\n";
    cout << "Alamat Penerima: " << t.alamatPenerima << "\n";
    cout << "Barang : " << t.namaBarang << " | Harga: Rp" << t.hargaBarang << "\n";
    cout << "Pengiriman: " << t.jenisPengiriman << " | Ongkir: Rp" << t.ongkir << "\n";
    cout << "----------------------------------------\n";
    cout << "TOTAL HARGA: Rp" << t.totalHarga << "\n";
    if (t.metodePembayaran == "Transfer") {
        cout << "Biaya Admin Transfer: Rp2500\n";
        cout << "TOTAL BAYAR: Rp" << t.totalHarga + 2500 << "\n";
        cout << "Transfer ke BANK " << t.bank << " - Nomor Rekening: ";
        if (t.bank == "BCA") cout << "1234567890\n";
        else if (t.bank == "MANDIRI") cout << "9876543210\n";
        else if (t.bank == "BRI") cout << "1122334455\n";
        else if (t.bank == "SEABANK") cout << "5566778899\n";
    } else {
        cout << "Metode: CASH\n";
        cout << "Silakan serahkan uang ke kurir saat barang sampai.\n";
    }
    cout << "========================================\n";
}

void pengirimanPaket() {
    Transaksi t;
    cout << "\n=== PENGIRIMAN PAKET ELEKTRONIK ===\n";
    cout << "Masukkan Nama Pengirim: ";
    getline(cin, t.namaPengirim);
    t.noHpPengirim = inputNoHp("Pengirim");

    cout << "Masukkan Nama Penerima: ";
    getline(cin, t.namaPenerima);
    t.noHpPenerima = inputNoHp("Penerima");
    cout << "Masukkan Alamat Penerima: ";
    getline(cin, t.alamatPenerima);

    cout << "Masukkan Nama Barang Elektronik: ";
    getline(cin, t.namaBarang);
    t.hargaBarang = hitungHargaBarang(t.namaBarang);

    int pilihan = pilihJenisPengiriman();
    t.jenisPengiriman = getNamaPengiriman(pilihan);
    t.ongkir = getHargaPengiriman(pilihan);
    t.totalHarga = t.hargaBarang + t.ongkir;

    cout << "\n=== METODE PEMBAYARAN ===\n1. Cash\n2. Transfer\nPilih metode pembayaran (1/2): ";
    string metode;
    getline(cin, metode);
    t.metodePembayaran = (metode == "2") ? "Transfer" : "Cash";

    if (t.metodePembayaran == "Transfer") {
        cout << "Pilih bank (BCA/MANDIRI/BRI/SEABANK): ";
        getline(cin, t.bank);
        t.totalHarga += 2500;
    }

    t.resi = generateResi();
    tampilkanStruk(t);
    databaseTransaksi.push_back(t);
}

void trackingPaket() {
    string cariResi;
    cout << "\n=== TRACKING PAKET ===\n";
    cout << "Masukkan Nomor Resi: ";
    getline(cin, cariResi);

    bool ditemukan = false;
    for (const auto& t : databaseTransaksi) {
        if (t.resi == cariResi) {
            cout << "\n=== STATUS PENGIRIMAN ===\n";
            cout << "Nomor Resi: " << t.resi << "\n";
            cout << "Paket dengan tujuan " << t.alamatPenerima << " diperkirakan akan sampai dalam 1 hari.\n";
            cout << "Status: Masih dalam perjalanan menuju alamat penerima.\n";
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) {
        cout << "Data tidak ditemukan untuk resi tersebut.\n";
    }
}

void cancelPengiriman() {
    string resiHapus;
    cout << "\n=== CANCEL PENGIRIMAN ===\n";
    cout << "Masukkan Nomor Resi yang ingin dibatalkan: ";
    getline(cin, resiHapus);

    auto it = remove_if(databaseTransaksi.begin(), databaseTransaksi.end(),
                        [&](const Transaksi& t){ return t.resi == resiHapus; });

    if (it != databaseTransaksi.end()) {
        cout << "Apakah Anda yakin ingin membatalkan pengiriman dengan No. Resi: " << resiHapus << "? (y/n): ";
        char konfirmasi;
        cin >> konfirmasi;
        cin.ignore();
        if (konfirmasi == 'y' || konfirmasi == 'Y') {
            databaseTransaksi.erase(it, databaseTransaksi.end());
            cout << "Pengiriman dengan No. Resi " << resiHapus << " berhasil dibatalkan.\n";
        } else {
            cout << "Pembatalan dibatalkan.\n";
        }
    } else {
        cout << "Nomor Resi " << resiHapus << " tidak ditemukan.\n";
    }
}

int main() {
    srand(time(0));
    int pilihan;
    char lanjut;

    do {
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. PENGIRIMAN PAKET\n";
        cout << "2. TRACKING PAKET\n";
        cout << "3. CANCEL PENGIRIMAN\n";
        cout << "Pilih menu (1-3): ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                pengirimanPaket();
                break;
            case 2:
                trackingPaket();
                break;
            case 3:
                cancelPengiriman();
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }

        cout << "\nApakah ada transaksi lain? (y/n): ";
        cin >> lanjut;
        cin.ignore();
    } while (lanjut == 'y' || lanjut == 'Y');

    cout << "\nUPDATE DATA...\n";
    cout << "Terima kasih telah menggunakan layanan kami.\n";
    return 0;
}