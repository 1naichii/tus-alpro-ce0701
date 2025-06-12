# Sistem Kasir Ketintang Mart

## Tim Pengembang
| No | Nama | NIM |
|----|------|-----|
| 1 | Seraphim Virgine Tadja | 101102400004 |
| 2 | Praja Ghupta Vira Denta | 101102400047 |
| 3 | Ahmad Naufal | 101102400045 |
| 4 | Zakaria Nugraha Afandi | 101102400040 |

## Deskripsi Program
Program ini adalah sistem kasir untuk toko retail Ketintang Mart yang dibuat menggunakan bahasa pemrograman C++. Sistem ini memungkinkan kasir untuk melakukan transaksi penjualan dengan berbagai kategori produk, mengelola keranjang belanja, dan mencetak struk pembayaran. Program dirancang menggunakan array sesuai dengan modul algoritma dan pemrograman yang diajarkan.

## Rekomendasi Perbaikan Program

### 1. **No Vector: Menggunakan Array Sesuai Modul yang Diajarkan**
Mengganti penggunaan `vector` dengan array statis untuk menyesuaikan dengan materi yang diajarkan dalam modul algoritma dan pemrograman. Implementasi menggunakan array dengan ukuran tetap seperti `ItemKeranjang keranjang[MAX_KERANJANG]` dan `Produk produkKategori[MAX_PRODUK]` untuk memudahkan pemahaman konsep dasar array dan pengelolaan memori.

### 2. **Login System: Keamanan Akses Kasir**
Implementasi sistem autentikasi untuk memastikan hanya petugas kasir yang berwenang dapat mengakses sistem. Sistem login akan membaca data user dari file eksternal users.txt dengan format CSV yang mencakup username, password, nama lengkap, dan role. Fitur ini mencakup validasi username/password dan session management untuk keamanan sistem dengan multiple user dan berbagai level akses.

### 3. **Clear Screen: Interface Lebih Bersih**
Menambahkan fungsi `system("cls")` untuk membersihkan layar dan `system("pause")` untuk memberikan kontrol alur program yang lebih baik. Implementasi ini membuat interface lebih professional dan mudah dibaca oleh pengguna dengan tampilan yang selalu bersih setiap pergantian menu.

### 4. **ID Barang: Memudahkan Identifikasi saat Edit/Delete**
Menambahkan ID unik untuk setiap produk dalam format kategori-nomor seperti 101, 201, 301, 401 yang akan ditampilkan dalam struk belanja. Format struk yang diperbaiki akan menampilkan ID produk untuk memudahkan proses edit dan delete item dalam keranjang belanja. Setiap kategori produk akan memiliki range ID yang berbeda untuk kemudahan identifikasi.

### 5. **Opsi Numerik: Lebih User-Friendly**
Mengganti input berbasis teks dengan opsi numerik untuk semua pilihan menu:
- **Metode Pembayaran**: 1. Tunai, 2. QRIS, 3. Transfer Bank
- **Opsi Pengambilan**: 1. Diantar ke alamat, 2. Diambil di toko
- **Kategori Produk**: 1. Produk Segar & Beku, 2. Makanan & Minuman, 3. Kebutuhan Dapur, 4. Personal Care

### 6. **Data Persistence: Menyimpan Transaksi dan Struk**
Implementasi sistem penyimpanan data ke file eksternal untuk mempertahankan riwayat transaksi:
- **Database Transaksi**: `data_transaksi/transaksi.csv` dengan format: `nomor_transaksi,nama_pembeli,total_harga,tanggal`
- **Printout Struk**: `printout/{nomor_transaksi}_{nama_pembeli}.txt` untuk dokumentasi
- Auto-save setiap selesai transaksi dan auto-load saat program dimulai

### 7. **Folder Organization: Struktur File yang Rapi**
Organisasi file yang terstruktur untuk kemudahan maintenance dengan pemisahan folder berdasarkan fungsi. Database sistem disimpan dalam folder database, transaksi harian dalam folder data_transaksi, dan struk hasil cetak dalam folder printout. Struktur ini memudahkan backup data dan maintenance sistem secara keseluruhan.

### 8. **Clear Keranjang: Reset setelah Checkout**
Implementasi pembersihan keranjang otomatis setelah transaksi selesai untuk mempersiapkan transaksi berikutnya. Sistem akan mereset variabel `jumlahItemKeranjang = 0` dan membersihkan array keranjang setelah konfirmasi pembayaran berhasil, memastikan tidak ada data transaksi sebelumnya yang tercampur.

### 9. **Nama Pembeli: Personalisasi Transaksi**
Menambahkan input nama pembeli di awal transaksi untuk personalisasi dan tracking yang lebih baik. Nama pembeli akan ditampilkan dalam struk dan digunakan untuk penamaan file printout, memberikan pengalaman yang lebih personal bagi pelanggan dan memudahkan identifikasi transaksi untuk keperluan administrasi toko.

### 10. **Function Optimization: Kode Lebih Modular dan Efisien**
Refactoring kode dengan memisahkan fungsi-fungsi spesifik untuk meningkatkan readability dan maintainability. Pemisahan fungsi mencakup tampilan produk per kategori, generate nomor transaksi, penyimpanan data, export struk, reset keranjang, dan kalkulasi total. Struktur modular ini memudahkan debugging, testing, dan pengembangan fitur baru.

### 11. **Database untuk User Login**
Implementasi sistem database user dengan file eksternal untuk fleksibilitas manajemen akun. Database akan menyimpan informasi username, password, nama lengkap, dan role user dalam format CSV. Sistem mendukung multiple user dengan role berbeda seperti admin, kasir, dan supervisor. Fitur login mencakup validasi credential dari file, session management, dan audit trail untuk monitoring akses sistem. Implementasi ini memungkinkan penambahan user baru tanpa perlu mengubah source code program.

## Struktur File Program
```
kelompok-5/
├── kelompok-5.cpp          # File source code utama
├── kelompok-5.exe          # File executable
├── README.md               # Dokumentasi program
├── note.txt                # Catatan pengembangan
├── database/               # Database sistem
│   └── users.txt          # Database user login
├── data_transaksi/         # Database transaksi
│   └── transaksi.csv      # Log semua transaksi
└── printout/               # Folder struk belanja
    └── {nomor_transaksi}_{nama_pembeli}.txt
```

## Teknologi yang Digunakan
- Bahasa Pemrograman: C++
- Compiler: GCC/MinGW
- Format Data: CSV/TXT files
- Platform: Windows
- Array untuk struktur data (sesuai modul pembelajaran)

---
**Catatan**: Dokumen ini merupakan panduan pengembangan untuk meningkatkan fungsionalitas dan kualitas sistem kasir Ketintang Mart.
