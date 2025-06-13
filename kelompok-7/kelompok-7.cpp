#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX_PENGGUNA = 100;
const int MAX_PENGIRIMAN = 100;

struct Pengiriman {
    string nomorResi;
    string negaraAsal;
    string ibuKotaAsal;
    string negaraTujuan;
    string ibuKotaTujuan;
    float berat;
    string jenisMuatan;
    string namaMuatan;
    string layanan;
    int estimasiHari;
    long long estimasiBiaya;
    string status;
};

struct Pengguna {
    string nama;
    string noKTP;
    string noHP;
    string asalNegara;
    string email;
    string password;
};

struct Negara {
    string namaNegara;
    string ibuKota;
};

Pengguna daftarPengguna[MAX_PENGGUNA];
int jumlahPengguna = 0;

Pengiriman daftarPengiriman[MAX_PENGIRIMAN];
int jumlahPengiriman = 0;

Negara negaraASEAN[10] = {
    {"Brunei Darussalam", "Bandar Seri Begawan"},
    {"Indonesia", "Jakarta"},
    {"Kamboja", "Phnom Penh"},
    {"Laos", "Vientiane"},
    {"Malaysia", "Kuala Lumpur"},
    {"Myanmar", "Naypyidaw"},
    {"Filipina", "Manila"},
    {"Singapura", "Singapura"},
    {"Thailand", "Bangkok"},
    {"Vietnam", "Hanoi"}
};

bool validEmail(const string& email) {
    int atCount = 0;
    for (char c : email) {
        if (!(isalnum(c) || c == '.' || c == '@')) return false;
        if (c == '@') atCount++;
    }
    return atCount == 1;
}

int estimasiHariPerjalanan(string asal, string tujuan) {
    if (asal == tujuan) return 1;
    int indexAsal = -1, indexTujuan = -1;
    for (int i = 0; i < 10; i++) {
        if (negaraASEAN[i].namaNegara == asal) indexAsal = i;
        if (negaraASEAN[i].namaNegara == tujuan) indexTujuan = i;
    }
    return 3 + abs(indexAsal - indexTujuan);
}

void tampilkanNegaraASEAN() {
    for (int i = 0; i < 10; i++) {
        cout << i + 1 << ". " << negaraASEAN[i].namaNegara << " - " << negaraASEAN[i].ibuKota << endl;
    }
}

string generateNomorResi() {
    string resi = "RESI";
    for (int i = 0; i < 6; i++) {
        resi += to_string(rand() % 10);
    }
    return resi;
}

long long hitungBiaya(int hari, string layanan) {
    long long tarifPerHari = (layanan == "ekspres") ? 30000000 : 2250000;
    return static_cast<long long>(hari) * tarifPerHari;
}

void registrasi() {
    if (jumlahPengguna >= MAX_PENGGUNA) {
        cout << "Jumlah pengguna maksimum!\n";
        return;
    }

    cout << "\n--- Input Data Profil ---\n";
    Pengguna penggunaBaru;
    cin.ignore();  // Membersihkan newline
    cout << "Nama Lengkap : ";
    getline(cin, penggunaBaru.nama);

    cout << "No. KTP      : ";
    getline(cin, penggunaBaru.noKTP);

    cout << "No. HP       : ";
    getline(cin, penggunaBaru.noHP);

    cout << "Asal Negara  : ";
    getline(cin, penggunaBaru.asalNegara);

    cout << "\n--- Buat Akun ---\n";
    string email;
    cout << "Email    : ";
    cin >> email;

    while (!validEmail(email)) {
        cout << "Email tidak valid! Hanya huruf, angka, titik (.) dan '@' yang diperbolehkan.\n";
        cout << "Masukkan ulang email: ";
        cin >> email;
    }

    string password;
    cout << "Password : ";
    cin >> password;

    while (password.length() != 8) {
        cout << "anda harus memasukkan 8 karakter password\n";
        cout << "Masukkan ulang password: ";
        cin >> password;
    }

    penggunaBaru.email = email;
    penggunaBaru.password = password;

    daftarPengguna[jumlahPengguna++] = penggunaBaru;
    cout << "Registrasi berhasil!\n";
}

bool login(string email, string password) {
    for (int i = 0; i < jumlahPengguna; i++) {
        if (daftarPengguna[i].email == email && daftarPengguna[i].password == password) {
            cout << "Login berhasil.\n";
            return true;
        }
    }
    cout << "Login gagal!\n";
    return false;
}

bool inputDataPengiriman(Pengiriman &p) {
    cout << "=======================================\n";
    cout << "  Silahkan Pilih Negara Keberangkatan  \n";
    cout << "=======================================\n";
    cout << "\nPilih Negara Asal:\n";
    tampilkanNegaraASEAN();
    int asalIdx;
    cout << "Nomor: "; cin >> asalIdx;
    if (asalIdx < 1 || asalIdx > 10) return false;
    p.negaraAsal = negaraASEAN[asalIdx - 1].namaNegara;
    p.ibuKotaAsal = negaraASEAN[asalIdx - 1].ibuKota;

    cout << "=======================================\n";
    cout << "   Silahkan Pilih Negara Tujuan anda   \n";
    cout << "=======================================\n";
    cout << "\nPilih Negara Tujuan:\n";
    tampilkanNegaraASEAN();
    int tujuanIdx;
    cout << "Nomor: "; cin >> tujuanIdx;
    if (tujuanIdx < 1 || tujuanIdx > 10) return false;
    p.negaraTujuan = negaraASEAN[tujuanIdx - 1].namaNegara;
    p.ibuKotaTujuan = negaraASEAN[tujuanIdx - 1].ibuKota;

    if (p.negaraAsal == p.negaraTujuan) {
        cout << "================================================================\n";
        cout << "\t\tDATA YANG DI MASUKKAN TIDAK VALID\n";
        cout << "Anda Tidak Dapat Memilih Tujuan Yang Sama Dengan Negara Asal\n";
        cout << "================================================================\n";
        return false;
    }

    p.estimasiHari = estimasiHariPerjalanan(p.negaraAsal, p.negaraTujuan);

    cout << "\nPilih Jenis Muatan:\n";
    cout << "1. Pangan\n";
    cout << "2. Non-Pangan\n";
    cout << "Pilihan: ";
    int jenisMuatan; 
    cin >> jenisMuatan;

    if (jenisMuatan == 1) {
        p.jenisMuatan = "Pangan";
        string daftar[] = {
            "Beras", 
            "Gandum", 
            "Jagung", 
            "Kedelai", 
            "Sorghum", 
            "Biji Bunga matahari", 
            "Biji kapas"};

        for (int i = 0; i < 7; ++i) {
            cout << i + 1 << ". " << daftar[i] << endl;
        }
        int pilihan; cout << "Pilihan: "; cin >> pilihan;
        if (pilihan >= 1 && pilihan <= 7) p.namaMuatan = daftar[pilihan - 1];
        else return false;
    } else if (jenisMuatan == 2) {
        p.jenisMuatan = "Non-Pangan";
        string daftar[] = {
            "Logam", 
            "Kayu", 
            "Karet", 
            "Pupuk", 
            "Pestisida", 
            "Semen", 
            "Pasir", 
            "Batu Bara"};

        for (int i = 0; i < 8; ++i) {
            cout << i + 1 << ". " << daftar[i] << endl;
        }
        int pilihan; cout << "Pilihan: "; cin >> pilihan;
        if (pilihan >= 1 && pilihan <= 8) p.namaMuatan = daftar[pilihan - 1];
        else return false;
    } else return false;

    cout << "Berat (ton) [min 100000, max 300000]: "; cin >> p.berat;
    if (p.berat < 100000 || p.berat > 300000) return false;

    cout << "Layanan (reguler/ekspres): "; cin >> p.layanan;

    p.estimasiBiaya = hitungBiaya(p.estimasiHari, p.layanan);
    p.status = "Sedang Di Muat";
    return true;
}

void orderPengiriman() {
    if (jumlahPengiriman >= MAX_PENGIRIMAN) {
        cout << "Kapasitas pengiriman penuh.\n";
        return;
    }
    Pengiriman &p = daftarPengiriman[jumlahPengiriman];
    p.nomorResi = generateNomorResi();
    if (!inputDataPengiriman(p)) {
        cout << "\n\tPengisian data gagal. Pengiriman dibatalkan.\n";
        return;
    }
    jumlahPengiriman++;
    cout << "\nPengiriman berhasil dipesan.\n";
    cout << "Nomor Resi Anda: " << p.nomorResi << endl;
    cout << "Estimasi Biaya: Rp " << p.estimasiBiaya << endl;
}

void tampilkanStruk() {
    if (jumlahPengiriman == 0) {
        cout << "Belum ada pemesanan.\n";
        return;
    }
    Pengiriman &p = daftarPengiriman[jumlahPengiriman - 1];
    cout << "\n=== STRUK PEMESANAN ===\n";
    cout << "Nomor Resi     : " << p.nomorResi << endl;
    cout << "Negara Asal    : " << p.negaraAsal << " - " << p.ibuKotaAsal << endl;
    cout << "Negara Tujuan  : " << p.negaraTujuan << " - " << p.ibuKotaTujuan << endl;
    cout << "Jenis Muatan   : " << p.jenisMuatan << endl;
    cout << "Nama Muatan    : " << p.namaMuatan << endl;
    cout << "Estimasi Hari  : " << p.estimasiHari << " hari\n";
    cout << "Berat          : " << p.berat << " ton\n";
    cout << "Layanan        : " << p.layanan << endl;
    cout << "Status         : " << p.status << endl;
    cout << "Biaya Estimasi : Rp " << p.estimasiBiaya << endl;
}

void lacakPengiriman() {
    string inputResi;
    cout << "Masukkan Nomor Resi: "; cin >> inputResi;
    bool ditemukan = false;
    for (int i = 0; i < jumlahPengiriman; i++) {
        if (daftarPengiriman[i].nomorResi == inputResi) {
            cout << "Tujuan: " << daftarPengiriman[i].negaraTujuan << " - " << daftarPengiriman[i].ibuKotaTujuan << endl;
            cout << "Status: " << daftarPengiriman[i].status << endl;
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) cout << "Nomor Resi tidak ditemukan!\n";
}

void tampilkanRiwayat() {
    if (jumlahPengiriman == 0) {
        cout << "Belum ada riwayat pengiriman.\n";
        return;
    }
    for (int i = 0; i < jumlahPengiriman; i++) {
        cout << "Pengiriman ke-" << i + 1 << ": " << daftarPengiriman[i].negaraAsal
             << " -> " << daftarPengiriman[i].negaraTujuan
             << " (Resi: " << daftarPengiriman[i].nomorResi << ")\n";
    }
}

void updatePengiriman() {
    string inputResi;
    cout << "Masukkan Nomor Resi yang ingin diupdate: "; cin >> inputResi;
    for (int i = 0; i < jumlahPengiriman; i++) {
        if (daftarPengiriman[i].nomorResi == inputResi) {
            cout << "\n--- Update Data Pengiriman ---\n";
            if (inputDataPengiriman(daftarPengiriman[i])) {
                cout << "Data pengiriman berhasil diperbarui.\n";
            } else {
                cout << "Update dibatalkan.\n";
            }
            return;
        }
    }
    cout << "Pengiriman dengan nomor resi tersebut tidak ditemukan.\n";
}

void hapusPengiriman() {
    string inputResi;
    cout << "Masukkan Nomor Resi yang ingin dihapus: "; cin >> inputResi;
    for (int i = 0; i < jumlahPengiriman; i++) {
        if (daftarPengiriman[i].nomorResi == inputResi) {
            for (int j = i; j < jumlahPengiriman - 1; j++) {
                daftarPengiriman[j] = daftarPengiriman[j + 1];
            }
            jumlahPengiriman--;
            cout << "Data pengiriman berhasil dihapus.\n";
            return;
        }
    }
    cout << "Pengiriman dengan nomor resi tersebut tidak ditemukan.\n";
}

void bantuan() {
    cout << "Silakan hubungi CS melalui live chat atau sistem ticketing.\n";
}

void menuUtama() {
    int pilihan;
    do {
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Order Pengiriman\n";
        cout << "2. Pelacakan Resi Pengiriman\n";
        cout << "3. Riwayat Pengiriman\n";
        cout << "4. Cetak Struk Pemesanan\n";
        cout << "5. Update Data Pengiriman\n";
        cout << "6. Hapus Data Order\n";
        cout << "7. Bantuan\n";
        cout << "8. Logout\n\n";
        cout << "Pilih: ";
        cin >> pilihan;
        switch (pilihan) {
            case 1: orderPengiriman(); break;
            case 2: lacakPengiriman(); break;
            case 3: tampilkanRiwayat(); break;
            case 4: tampilkanStruk(); break;
            case 5: updatePengiriman(); break;
            case 6: hapusPengiriman(); break;
            case 7: bantuan(); break;
            case 8: cout << "Logout berhasil.\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 8);
}

int main() {
    srand(time(0));
    int pilihan;
    while (true) {
        cout << "-----------------------------------------------------------";
        cout << "\n\tSelamat datang di pemesanan jasa pengiriman";
        cout << "\n\t kapal kargo antar negara di Asia Tenggara\n";
        cout << "===========================================================\n";
        cout << "\n=== MENU AWAL ===\n1. Registrasi\n2. Login\n3. Keluar\n\nPilih: ";
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                registrasi();
                menuUtama();
                break;
            case 2: {
                string email, password;
                cout << "Email: "; cin >> email;
                cout << "Password: "; cin >> password;
                if (login(email, password)) menuUtama();
                break;
            }
            case 3: {
                string konfirmasi;
                cout << "Apakah Anda yakin ingin keluar? (Ya/Tidak): ";
                cin >> konfirmasi;
                if (konfirmasi == "Ya" || konfirmasi == "ya" || konfirmasi == "YA") {
                    cout << "Terima kasih telah menggunakan layanan kami!\n";
                    return 0;
                } else {
                    cout << "Kembali ke menu utama.\n";
                    break;
                }
            }
            default:
                cout << "Pilihan tidak valid!\n";
        }
    }
}