# Fast Delivery - Aplikasi Pengiriman Paket

## Tim Pengembang
| No | Nama | NIM |
|----|------|-----|
| 1 | Raja Malik Chaniago | 101102400030 |
| 2 | Ardiansyah Putra | 101102400018 |
| 3 | Victoria Helena Rice Da Silva | 101102400044 |
| 4 | Ismail Syarif | 101102400014 |

## Deskripsi Program
Fast Delivery adalah aplikasi console berbasis C++ untuk mengelola sistem pengiriman paket elektronik. Aplikasi ini menyediakan fitur registrasi pengguna, login, pembuatan pengiriman, tracking paket, dan manajemen data pengiriman.

## Rekomendasi Perbaikan Program

### 1. **Implementasi Array Statis untuk Struktur Data**
Mengganti penggunaan vector dengan array statis sesuai dengan materi pembelajaran algoritma dan pemrograman. Implementasi ini akan menggunakan array dengan kapasitas tetap untuk menyimpan data user (maksimal 100) dan transaksi (maksimal 500). Struktur data ini lebih sesuai dengan konsep dasar pemrograman C++ yang diajarkan dalam modul pembelajaran dan memberikan kontrol memori yang lebih eksplisit.

### 2. **Sistem Persistensi Data dengan File TXT**
Implementasi penyimpanan data permanen menggunakan file user.txt dan transaksi.txt untuk mempertahankan data setelah program ditutup. Sistem akan dilengkapi dengan fitur auto-save saat keluar program dan auto-load saat program dimulai. Format file menggunakan delimiter (|) untuk memudahkan parsing data dan kompatibilitas dengan sistem file sederhana.

### 3. **Validasi Input Kontekstual dengan Format Indonesia**
Menerapkan validasi input yang ketat sesuai dengan standar Indonesia untuk meningkatkan akurasi data. Validasi akan mencakup:
- Username: minimal 3 karakter, hanya huruf, angka, dan underscore
- Password: minimal 6 karakter untuk keamanan dasar
- Nama Lengkap: hanya huruf dan spasi, format nama Indonesia
- Email: validasi dasar dengan keberadaan @ dan .
- No. HP: format Indonesia 08xxxxxxxxxx (10-15 digit)
- Alamat: tidak mengandung karakter khusus berbahaya

### 4. **User Interface dengan Clear Screen System**
Implementasi sistem pembersihan layar menggunakan system("cls") untuk memberikan tampilan yang bersih dan professional. Setiap perpindahan menu akan membersihkan layar untuk meningkatkan user experience dan memberikan navigasi yang lebih intuitif dalam aplikasi console.

### 5. **Sistem Tracking Publik Tanpa Login**
Menambahkan fitur tracking paket di menu utama yang dapat diakses tanpa perlu login terlebih dahulu. Fitur ini memungkinkan penerima atau pengirim untuk melacak status pengiriman hanya dengan menggunakan nomor resi, meningkatkan aksesibilitas dan kemudahan penggunaan aplikasi.

### 6. **Terminologi dan Penamaan yang Konsisten**
Mengubah penamaan menu dari "RIWAYAT TRANSAKSI" menjadi "DATA PENGIRIMAN" untuk memberikan terminologi yang lebih sesuai dengan konteks aplikasi pengiriman paket. Implementasi validasi pilihan bank menggunakan input angka dengan validasi yang ketat untuk mencegah error input dan meningkatkan user experience dalam pemilihan metode pembayaran transfer.

## Struktur File Program
```
kelompok-2/
├── kelompok-2.cpp          # File source code utama
├── kelompok-2.exe          # File executable
├── README.md               # Dokumentasi program
├── user.txt                # Database user login
├── transaksi.txt           # Database data pengiriman
└── printout/               # Folder untuk file export data pengiriman
    └── {resi}_{nama_penerima}_{tanggal}.txt
```

## Teknologi yang Digunakan
- Bahasa Pemrograman: C++
- Compiler: GCC/MinGW
- Format Data: TXT files dengan delimiter
- Platform: Windows

---
**Catatan**: Dokumen ini merupakan panduan pengembangan untuk meningkatkan fungsionalitas dan kualitas sistem pengiriman paket Fast Delivery.
