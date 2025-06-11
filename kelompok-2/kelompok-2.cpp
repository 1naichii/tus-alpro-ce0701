#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

struct User {
    string username;
    string password;
    string namaLengkap;
    string email;
    string noHp;
    string alamat;
};

struct Transaksi {
    string resi, namaPengirim, noHpPengirim;
    string namaPenerima, noHpPenerima, alamatPenerima;
    string namaBarang, jenisPengiriman;
    int hargaBarang, ongkir, totalHarga;
    string metodePembayaran, bank;
    string usernameOwner;
};

vector<User> databaseUser;
vector<Transaksi> databaseTransaksi;
User currentUser;
bool isLoggedIn = false;

bool isValidHp(const string& noHp) {
    if (noHp.length() > 12 || noHp.empty()) return false;
    for (char c : noHp) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool isValidEmail(const string& email) {
    return email.find('@') != string::npos && email.find('.') != string::npos;
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

string inputEmail() {
    string email;
    while (true) {
        cout << "Masukkan Email: ";
        getline(cin, email);
        if (isValidEmail(email)) break;
        else cout << "Format email tidak valid! Harus mengandung @ dan . \n";
    }
    return email;
}

bool isUsernameExists(const string& username) {
    for (const auto& user : databaseUser) {
        if (user.username == username) {
            return true;
        }
    }
    return false;
}

void registerUser() {
    User newUser;

    cout << "\n==========================================\n";
    cout << "               FORM REGISTRASI             \n";
    cout << "==========================================\n";

    while (true) {
        cout << "Masukkan Username: ";
        getline(cin, newUser.username);

        if (newUser.username.empty()) {
            cout << "Username tidak boleh kosong!\n";
            continue;
        }

        if (isUsernameExists(newUser.username)) {
            cout << "Username sudah terdaftar! Pilih username lain.\n";
            continue;
        }

        break;
    }

    while (true) {
        cout << "Masukkan Password: ";
        getline(cin, newUser.password);
        if (!newUser.password.empty() && newUser.password.length() >= 4) {
            break;
        }
        cout << "Password minimal 4 karakter!\n";
    }

    cout << "Masukkan Nama Lengkap: ";
    getline(cin, newUser.namaLengkap);

    newUser.email = inputEmail();
    newUser.noHp = inputNoHp("Anda");

    cout << "Masukkan Alamat Lengkap: ";
    getline(cin, newUser.alamat);

    databaseUser.push_back(newUser);

    cout << "\n REGISTRASI BERHASIL!\n";
    cout << "Silakan login dengan username dan password yang telah Anda buat.\n";
    cout << "Tekan Enter untuk melanjutkan...";
    cin.get();
}

bool loginUser() {
    string username, password;

    cout << "\n==========================================\n";
    cout << "                   FORM LOGIN                \n";
    cout << "==========================================\n";

    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);

    for (const auto& user : databaseUser) {
        if (user.username == username && user.password == password) {
            currentUser = user;
            isLoggedIn = true;
            cout << "\n LOGIN BERHASIL!\n";
            cout << "Selamat datang, " << currentUser.namaLengkap << "!\n";
            cout << "Tekan Enter untuk melanjutkan...";
            cin.get();
            return true;
        }
    }

    cout << "\n LOGIN GAGAL!\n";
    cout << "Username atau password salah.\n";
    cout << "Tekan Enter untuk melanjutkan...";
    cin.get();
    return false;
}

void logoutUser() {
    isLoggedIn = false;
    currentUser = User{};
    cout << "\n Anda telah logout. Terima kasih!\n";
}

int menuAuth() {
    int pilihan;
    cout << "\n==========================================\n";
    cout << "     SELAMAT DATANG DI FAST DELIVERY     \n";
    cout << "        Aplikasi Pengiriman Paket        \n";
    cout << "==========================================\n";
    cout << "1. LOGIN\n";
    cout << "2. REGISTER\n";
    cout << "3. KELUAR\n";
    cout << "Pilih menu (1-3): ";
    cin >> pilihan;
    cin.ignore();
    return pilihan;
}

void tampilkanProfil() {
    cout << "\n==========================================\n";
    cout << "                   PROFIL SAYA               \n";
    cout << "==========================================\n";
    cout << "Username    : " << currentUser.username << "\n";
    cout << "Nama Lengkap: " << currentUser.namaLengkap << "\n";
    cout << "Email       : " << currentUser.email << "\n";
    cout << "No. HP      : " << currentUser.noHp << "\n";
    cout << "Alamat      : " << currentUser.alamat << "\n";
    cout << "Tekan Enter untuk kembali...";
    cin.get();
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
        cout << "\n==========================================\n";
        cout << "             JENIS PENGIRIMAN            \n";
        cout << "==========================================\n";
        cout << "1. Hemat (Rp 25.000) - 3-5 hari\n";
        cout << "2. Reguler (Rp 50.000) - 1-2 hari\n";
        cout << "3. Instan (Rp 75.000) - Same day\n";
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
    string resi = "FD";
    string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < 8; ++i) {
        resi += charset[rand() % charset.size()];
    }
    return resi;
}

void tampilkanStruk(const Transaksi& t) {
    cout << "\n==========================================\n";
    cout << "             STRUK PENGIRIMAN            \n";
    cout << "==========================================\n";
    cout << "NO RESI     : " << t.resi << "\n";
    cout << "Pengirim    : " << t.namaPengirim << "\n";
    cout << "HP Pengirim : " << t.noHpPengirim << "\n";
    cout << "Penerima    : " << t.namaPenerima << "\n";
    cout << "HP Penerima : " << t.noHpPenerima << "\n";
    cout << "Alamat      : " << t.alamatPenerima << "\n";
    cout << "Barang      : " << t.namaBarang << "\n";
    cout << "Harga Barang: Rp " << t.hargaBarang << "\n";
    cout << "Pengiriman  : " << t.jenisPengiriman << "\n";
    cout << "Ongkir      : Rp " << t.ongkir << "\n";
    cout << "------------------------------------------\n";
    cout << "TOTAL HARGA : Rp " << t.totalHarga << "\n";

    if (t.metodePembayaran == "Transfer") {
        cout << "Biaya Admin : Rp 2.500\n";
        cout << "TOTAL BAYAR : Rp " << t.totalHarga + 2500 << "\n";
        cout << "Transfer ke BANK " << t.bank << "\n";
        cout << "No. Rekening: ";
        if (t.bank == "BCA") cout << "1234567890\n";
        else if (t.bank == "MANDIRI") cout << "9876543210\n";
        else if (t.bank == "BRI") cout << "1122334455\n";
        else if (t.bank == "SEABANK") cout << "5566778899\n";
    } else {
        cout << "Metode      : CASH\n";
        cout << "Bayar saat barang sampai\n";
    }
    cout << "==========================================\n";
}

void pengirimanPaket() {
    char lagi;
    do {
        Transaksi t;
        t.usernameOwner = currentUser.username;

        cout << "\n==========================================\n";
        cout << "         PENGIRIMAN PAKET BARU           \n";
        cout << "==========================================\n";

        t.namaPengirim = currentUser.namaLengkap;
        t.noHpPengirim = currentUser.noHp;

        cout << "Data Pengirim (dari profil Anda):\n";
        cout << "Nama    : " << t.namaPengirim << "\n";
        cout << "No. HP  : " << t.noHpPengirim << "\n\n";

        cout << "Masukkan Nama Penerima: ";
        getline(cin, t.namaPenerima);
        t.noHpPenerima = inputNoHp("Penerima");
        cout << "Masukkan Alamat Penerima: ";
        getline(cin, t.alamatPenerima);

        cout << "Masukkan Nama Barang Elektronik: ";
        getline(cin, t.namaBarang);
        t.hargaBarang = hitungHargaBarang(t.namaBarang);
        cout << "Harga barang otomatis: Rp " << t.hargaBarang << "\n";

        int pilihan = pilihJenisPengiriman();
        t.jenisPengiriman = getNamaPengiriman(pilihan);
        t.ongkir = getHargaPengiriman(pilihan);
        t.totalHarga = t.hargaBarang + t.ongkir;

        cout << "\n==========================================\n";
        cout << "           METODE PEMBAYARAN             \n";
        cout << "==========================================\n";
        cout << "1. Cash (Bayar saat barang sampai)\n";
        cout << "2. Transfer Bank\n";
        cout << "Pilih metode pembayaran (1/2): ";
        string metode;
        getline(cin, metode);
        t.metodePembayaran = (metode == "2") ? "Transfer" : "Cash";

        if (t.metodePembayaran == "Transfer") {
            cout << "Pilih bank:\n";
            cout << "1. BCA\n2. MANDIRI\n3. BRI\n4. SEABANK\n";
            cout << "Pilihan (1-4): ";
            string bankChoice;
            getline(cin, bankChoice);

            if (bankChoice == "1") t.bank = "BCA";
            else if (bankChoice == "2") t.bank = "MANDIRI";
            else if (bankChoice == "3") t.bank = "BRI";
            else if (bankChoice == "4") t.bank = "SEABANK";
            else t.bank = "BCA";
        }

        t.resi = generateResi();
        tampilkanStruk(t);
        databaseTransaksi.push_back(t);

        cout << "\n Transaksi berhasil disimpan!\n\n";
        cout << "Apakah Anda ingin melakukan pengiriman paket lagi? (y/n): ";
        cin >> lagi;
        cin.ignore();

    } while (lagi == 'y' || lagi == 'Y');
    
    cout << "\nTekan Enter untuk kembali ke menu utama...";
    cin.get();
}

void trackingPaket() {
    string cariResi;
    cout << "\n==========================================\n";
    cout << "               TRACKING PAKET              \n";
    cout << "==========================================\n";
    cout << "Masukkan Nomor Resi: ";
    getline(cin, cariResi);

    bool ditemukan = false;
    for (const auto& t : databaseTransaksi) {
        if (t.resi == cariResi) {
            cout << "\n==========================================\n";
            cout << "             STATUS PENGIRIMAN             \n";
            cout << "==========================================\n";
            cout << "Nomor Resi  : " << t.resi << "\n";
            cout << "Pengirim    : " << t.namaPengirim << "\n";
            cout << "Penerima    : " << t.namaPenerima << "\n";
            cout << "Alamat      : " << t.alamatPenerima << "\n";
            cout << "Jenis       : " << t.jenisPengiriman << "\n";
            cout << "Status      : Dalam perjalanan\n";

            if (t.jenisPengiriman == "Instan") {
                cout << "Estimasi    : Hari ini\n";
            } else if (t.jenisPengiriman == "Reguler") {
                cout << "Estimasi    : 1-2 hari\n";
            } else {
                cout << "Estimasi    : 3-5 hari\n";
            }

            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) {
        cout << "\n Data tidak ditemukan untuk resi: " << cariResi << "\n";
    }

    cout << "Tekan Enter untuk melanjutkan...";
    cin.get();
}

void cancelPengiriman() {
    string resiHapus;
    cout << "\n==========================================\n";
    cout << "             CANCEL PENGIRIMAN             \n";
    cout << "==========================================\n";
    cout << "Masukkan Nomor Resi yang ingin dibatalkan: ";
    getline(cin, resiHapus);

    auto it = remove_if(databaseTransaksi.begin(), databaseTransaksi.end(),
                        [&](const Transaksi& t){
                            return t.resi == resiHapus && t.usernameOwner == currentUser.username;
                        });

    if (it != databaseTransaksi.end()) {
        cout << "Pengiriman ke " << it->namaPenerima << " (" << it->namaBarang << ") akan dibatalkan.\n";
        cout << "Apakah Anda yakin? (y/n): ";
        char konfirmasi;
        cin >> konfirmasi;
        cin.ignore();
        if (konfirmasi == 'y' || konfirmasi == 'Y') {
            databaseTransaksi.erase(it, databaseTransaksi.end());
            cout << "\n Pengiriman dengan No. Resi " << resiHapus << " berhasil dibatalkan.\n";
        } else {
            cout << "Pembatalan dibatalkan.\n";
        }
    } else {
        cout << "\n Nomor Resi " << resiHapus << " tidak ditemukan atau bukan milik Anda.\n";
    }

    cout << "Tekan Enter untuk melanjutkan...";
    cin.get();
}

void riwayatTransaksi() {
    cout << "\n==========================================\n";
    cout << "             RIWAYAT TRANSAKSI             \n";
    cout << "==========================================\n";

    bool adaTransaksi = false;
    for (const auto& t : databaseTransaksi) {
        if (t.usernameOwner == currentUser.username) {
            cout << "Resi: " << t.resi << " | " << t.namaBarang
                 << " | Ke: " << t.namaPenerima << " | Rp " << t.totalHarga << "\n";
            adaTransaksi = true;
        }
    }

    if (!adaTransaksi) {
        cout << "Belum ada transaksi.\n";
    }

    cout << "Tekan Enter untuk melanjutkan...";
    cin.get();
}

int menuUtama() {
    int pilihan;
    cout << "\n==========================================\n";
    cout << "                   MENU UTAMA                \n";
    cout << "  Selamat datang, " << currentUser.namaLengkap << "\n";
    cout << "==========================================\n";
    cout << "1. PENGIRIMAN PAKET\n";
    cout << "2. TRACKING PAKET\n";
    cout << "3. CANCEL PENGIRIMAN\n";
    cout << "4. RIWAYAT TRANSAKSI\n";
    cout << "5. PROFIL SAYA\n";
    cout << "6. LOGOUT\n";
    cout << "Pilih menu (1-6): ";
    cin >> pilihan;
    cin.ignore();
    return pilihan;
}

int main() {
    srand(time(0));

    while (true) {
        if (!isLoggedIn) {
            int pilihan = menuAuth();

            switch (pilihan) {
                case 1:
                    if (databaseUser.empty()) {
                        cout << "\n  Belum ada user yang terdaftar!\n";
                        cout << "Silakan register terlebih dahulu.\n";
                        cout << "Tekan Enter untuk melanjutkan...";
                        cin.get();
                    } else {
                        loginUser();
                    }
                    break;
                case 2:
                    registerUser();
                    break;
                case 3:
                    cout << "\nTerima kasih telah menggunakan Fast Delivery!\n";
                    return 0;
                default:
                    cout << "Pilihan tidak valid.\n";
            }
        }
        
        if (isLoggedIn) {
            int pilihan = menuUtama();
            
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
                case 4:
                    riwayatTransaksi();
                    break;
                case 5:
                    tampilkanProfil();
                    break;
                case 6:
                    logoutUser();
                    break;
                default:
                    cout << "Pilihan tidak valid.\n";
            }
        }
    }

    return 0;
}