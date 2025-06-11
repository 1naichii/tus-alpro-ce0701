#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

struct Produk {
    string nama;
    int harga;
};

struct ItemKeranjang {
    Produk produk;
    int jumlah;
};

void tampilkanProduk(const vector<Produk>& produk) {
    cout << fixed << setprecision(0);
    for (size_t i = 0; i < produk.size(); ++i) {
        cout << i + 1 << ". " << produk[i].nama << " - Rp" << produk[i].harga << endl;
    }
}

void cetakStruk(const vector<ItemKeranjang>& keranjang) {
     cout << "====================================";
     cout << "\n---------- STRUK BELANJA -----------\n";
     cout << "          kentintang mart ";
     cout << "\n            11 juni 2025  \n";
     cout << "====================================\n";
    int total = 0;
    if (keranjang.empty()) {
        cout << "Keranjang kosong.\n";
    } else {
        for (const auto& item : keranjang) {
            int subtotal = item.produk.harga * item.jumlah;
            cout << "- " << item.produk.nama << " x" << item.jumlah << " = Rp" << subtotal << endl;
            total += subtotal;
        }
      cout << "------------------------------------\n";
        cout << "Total bayar: Rp" << total << "\n";
      cout << "====================================\n";
    }
}

void pilihProduk(const vector<Produk>& daftarProduk, vector<ItemKeranjang>& keranjang) {
    tampilkanProduk(daftarProduk);
    int pilih;
    while (true) {
        cout << "Masukkan nomor produk yang ingin dibeli (0 untuk selesai): ";
        cin >> pilih;
        if (pilih == 0) break;

        if (pilih > 0 && pilih <= daftarProduk.size()) {
            int jumlah;
            cout << "Jumlah barang: ";
            cin >> jumlah;

            if (jumlah <= 0) {
                cout << "Jumlah harus minimal 1.\n";
                continue;
            }

            bool sudahAda = false;
            for (auto& item : keranjang) {
                if (item.produk.nama == daftarProduk[pilih - 1].nama) {
                    item.jumlah += jumlah;
                    sudahAda = true;
                    break;
                }
            }
            if (!sudahAda) {
                keranjang.push_back({daftarProduk[pilih - 1], jumlah});
            }
            cout << jumlah << " x " << daftarProduk[pilih - 1].nama << " ditambahkan ke keranjang.\n";

            cetakStruk(keranjang);
        } else {
            cout << "Nomor produk tidak valid.\n";
        }
    }
}

void editPesanan(vector<ItemKeranjang>& keranjang) {
    if (keranjang.empty()) {
        cout << "Keranjang kosong, tidak ada pesanan untuk diedit.\n";
        return;
    }
    cetakStruk(keranjang);
    cout << "Masukkan nomor item yang ingin diedit: ";
    int nomor;
    cin >> nomor;
    if (nomor <= 0 || nomor > (int)keranjang.size()) {
        cout << "Nomor tidak valid.\n";
        return;
    }
    cout << "Jumlah baru untuk " << keranjang[nomor - 1].produk.nama << ": ";
    int jumlahBaru;
    cin >> jumlahBaru;
    if (jumlahBaru <= 0) {
        cout << "Jumlah harus minimal 1.\n";
        return;
    }
    keranjang[nomor - 1].jumlah = jumlahBaru;
    cout << "Pesanan berhasil diperbarui.\n";
}

void hapusPesanan(vector<ItemKeranjang>& keranjang) {
    if (keranjang.empty()) {
        cout << "Keranjang kosong, tidak ada pesanan untuk dihapus.\n";
        return;
    }
    cetakStruk(keranjang);
    cout << "Masukkan nomor item yang ingin dihapus: ";
    int nomor;
    cin >> nomor;
    if (nomor <= 0 || nomor > (int)keranjang.size()) {
        cout << "Nomor tidak valid.\n";
        return;
    }
    cout << keranjang[nomor - 1].produk.nama << " berhasil dihapus dari keranjang.\n";
    keranjang.erase(keranjang.begin() + nomor - 1);
}

int main() {
    cout << "========================================\n";
    cout << "--- Selamat datang di Ketintang Mart ---\n";
    cout << "========================================\n";

    vector<ItemKeranjang> keranjang;

    while (true) {
        
        cout << "\nMenu Utama:\n";
        cout << "1. Pesan Barang\n";
        cout << "2. Edit Pesanan\n";
        cout << "3. Hapus Pesanan\n";
        cout << "4. Lihat Struk\n";
        cout << "5. Keluar untuk membayar\n";
         cout << "\n========================================\n";
        cout << "Pilihan: ";
        
        int menu;
        cin >> menu;

        if (menu == 5) {
            if (!keranjang.empty()) {
                 
                
             cetakStruk(keranjang);


                string metodePembayaran, opsiPengiriman;
                cout << "Pilih metode pembayaran (tunai/qris/transfer): ";
                cin >> metodePembayaran;
                cout << "Pilih opsi pengiriman (alamat/toko): ";
                cin >> opsiPengiriman;

                if (opsiPengiriman == "alamat") {
                    cout << "Pesanan akan dikirim ke alamat Anda. (Gratis ongkir, estimasi 1 jam)\n";
                } else {
                    cout << "Silakan ambil pesanan langsung di toko.\n";
                }

                cout << "Pembayaran berhasil dengan metode " << metodePembayaran << ". Terima kasih sudah berbelanja!\n";
            } else {
                cout << "Terima kasih, Anda keluar tanpa pembelian.\n";
            }
            break;
        }

        switch (menu) {
            case 1: {
                 cout << "\n========================================\n";
                cout << "\n=== Pilih Kategori Produk ===\n";
                cout << "1. Produk Segar & Beku\n";
                cout << "2. Makanan & Minuman\n";
                cout << "3. Kebutuhan Dapur\n";
                cout << "4. Personal Care\n";
                 cout << "\n========================================\n";
                cout << "Pilihan: ";
                int kategori;
                cin >> kategori;

                vector<Produk> produkKategori;

                switch (kategori) {
                   case 1:
    produkKategori = {
       
        {"Wall's", 19000}, {"Sonice", 8000}, {"Campina", 15000},
        {"Kornet", 30000}, {"Nugget Kenzler", 50000}, {"Cornetto", 8000},
        {"Magnum", 15000}, {"Sarden", 10000}, {"Kiko", 20000},
        {"Es Pino", 10000}
        
    };
    break;
case 2:
    produkKategori = {
        
        {"Lexus", 10000}, {"Kokokrunch", 17900}, {"Lays Stax", 9900},
        {"Kitkat", 12500}, {"SilverQueen", 12500},
        {"Energen", 14700}, {"Fanta", 5000}, {"Teh Pucuk", 3500},
        {"Ultra Milk", 6000}, {"Aqua", 3300}, {"Nescafe", 7900}
    };
    break;
case 3:
    produkKategori = {
        {"Minyak 1L", 27000}, {"Beras 5KG", 75000}, {"Gula 1KG", 20000},
        {"Garam 500G", 5000}, {"Kecap 130mL", 10000},
        {"Tepung Bumbu / pcs", 3000}, {"Masako / pcs", 2000},
        {"Saos Tomat 150mL", 16000}, {"Santan 65mL", 7500},
        {"Mayonise 1KG", 23000}
    };
    break;
case 4:
    produkKategori = {
      
      
        {"Garnier face wash 100mL", 33250},
        {"Kahf face wash 100mL", 138000},
        {"Pantene Shampo 400mL", 43100},
        {"Lifebuoy Body wash 800mL", 41000},
        {"Bedak Kabur Emina 55G", 25560},
        {"Sun Screen Azarine 45+SPF PE+++ 50mL", 69900},
        {"Npure Toner 150mL", 64900},
        {"Pepsodent 150G", 15900},
        {"Charm Safe Night 35cm 12 Pads", 25000}
    };
                        break;
                    default:
                        cout << "Kategori tidak valid.\n";
                        continue;
                }

                pilihProduk(produkKategori, keranjang);
                break;
            }
            case 2:
                editPesanan(keranjang);
                break;
            case 3:
                hapusPesanan(keranjang);
                break;
            case 4:
                cetakStruk(keranjang);
                break;
            default:
                cout << "Pilihan menu tidak valid.\n";
        }
    }

    return 0;
}