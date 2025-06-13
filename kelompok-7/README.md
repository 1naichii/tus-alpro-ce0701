# Sistem Pengiriman Kargo Kapal ASEAN

## Tim Pengembang
| No | Nama | NIM |
|----|------|-----|
| 1 | [Nama Anggota 1] | [NIM] |
| 2 | [Nama Anggota 2] | [NIM] |
| 3 | [Nama Anggota 3] | [NIM] |

## Deskripsi Program
Program ini adalah sistem manajemen pengiriman kargo kapal untuk negara-negara ASEAN yang dibuat menggunakan bahasa pemrograman C++. Sistem ini memungkinkan pengguna untuk melakukan operasi CRUD (Create, Read, Update, Delete) terhadap data pengiriman kargo dengan berbagai jenis muatan (Pangan dan Non-Pangan) serta tracking status pengiriman antar negara ASEAN.

## Rekomendasi Perbaikan Program

### 1. **Implementasi Array 2 Dimensi untuk Data Master Muatan**
Menggabungkan array `namaMuatan` dan `jenisMuatan` yang terpisah menjadi satu array 2 dimensi untuk meningkatkan efisiensi dan kemudahan maintenance. Struktur data akan diorganisir berdasarkan kategori:
- **Muatan Pangan**: Beras, Gandum, Jagung, Kedelai, Sorghum, Biji Bunga matahari, Biji kapas
- **Muatan Non-Pangan**: Logam, Kayu, Karet, Pupuk, Pestisida, Semen, Pasir, Batu Bara

Array 2D akan menyimpan kategori muatan dan jenisnya dalam satu struktur yang lebih terorganisir, memudahkan pengelolaan data master dan mengurangi risiko inkonsistensi data.

### 2. **Sistem Database User dengan File Eksternal**
Implementasi sistem penyimpanan data user dalam file eksternal (users.txt atau users.csv) untuk mempertahankan data login setelah program ditutup. Database akan menyimpan informasi lengkap pengguna termasuk nama, no KTP, no HP, email, dan password yang telah di-hash untuk keamanan.

### 3. **Validasi Input Kontekstual dan Sanitasi Data**
Menerapkan validasi input yang ketat untuk setiap field data pengiriman:
- **No. KTP**: tepat 16 digit angka
- **No. HP**: format Indonesia dimulai dengan "08" dan minimal 10 digit
- **Email**: validasi format dengan minimal 3 karakter setelah titik (.)
- **Password**: minimal 8 karakter untuk keamanan yang lebih baik
- **Nama**: hanya huruf dan spasi, tidak mengandung karakter khusus

### 4. **Sistem Cetak Struk dengan Input Resi**
Implementasi fitur cetak struk yang mengharuskan input nomor resi, bukan berdasarkan pemesanan terakhir. Fitur ini akan mencakup:
- Input nomor resi dengan validasi format
- Pencarian data pengiriman berdasarkan resi
- Pembentukan struk dalam format profesional
- Penyimpanan file struk di folder `printout/` dengan format nama: `{resi}_{nama_pengirim}_{tanggal}.txt`

### 5. **Penambahan Database Kapal Sesuai Jenis Muatan**
Implementasi database kapal yang disesuaikan dengan kebutuhan jenis muatan:
- **Kapal Pangan**: Kapal khusus untuk transportasi bahan makanan dengan sistem refrigerasi
- **Kapal Non-Pangan**: Kapal kargo umum untuk barang industri dan bahan baku
- Spesifikasi kapasitas, kecepatan, dan rute yang berbeda untuk setiap jenis kapal

### 6. **Sistem Pelacakan Resi Komprehensif**
Mengembangkan sistem tracking yang mirip dengan struk pemesanan, memberikan informasi lengkap status pengiriman:
- Status real-time: Diproses, Dalam Perjalanan, Tiba di Pelabuhan Tujuan, Siap Diambil
- Estimasi waktu tiba berdasarkan jarak antar negara ASEAN
- Riwayat perjalanan kapal
- Informasi kontak untuk customer service

### 7. **Fitur Update Status Pengiriman**
Implementasi fitur khusus untuk mengupdate status pengiriman yang fokus pada:
- Perubahan status pengiriman saja (bukan edit data lengkap)
- Tracking progress berdasarkan posisi kapal
- Notifikasi perubahan status
- Log history perubahan status untuk audit trail

### 8. **Konfirmasi Data Sebelum Penyimpanan**
Menambahkan sistem konfirmasi yang menampilkan seluruh data pesanan kepada user sebelum data disimpan ke database:
- Review lengkap data pengiriman
- Konfirmasi final sebelum commit
- Opsi edit jika ada kesalahan
- Pembentukan nomor resi setelah konfirmasi final

### 9. **Sistem Keamanan Password dengan Hashing (Optional)**
Implementasi enkripsi password menggunakan algoritma hashing untuk meningkatkan keamanan:
- Penggunaan hash function untuk menyimpan password
- Salt untuk mencegah rainbow table attack
- Validasi login dengan perbandingan hash

## Struktur File Program
```
kelompok-7/
├── kelompok-7.cpp          # File source code utama
├── kelompok-7.exe          # File executable
├── README.md               # Dokumentasi program
├── users.txt               # Database user login
├── pengiriman.csv          # Database data pengiriman kargo
├── printout/               # Folder untuk file struk pengiriman
    └── {resi}_{nama_pengirim}_{tanggal}.txt

```

## Teknologi yang Digunakan
- Bahasa Pemrograman: C++
- Compiler: GCC/MinGW
- Struktur Data: Array dan Struct
- Format Data: CSV/TXT files
- Platform: Windows
- Sistem: Pengiriman Kargo Kapal ASEAN

## Fitur Utama Sistem
- **Manajemen User**: Registrasi, login, dan manajemen profil pengguna
- **Pemesanan Kargo**: Input data pengiriman dengan pilihan muatan pangan/non-pangan
- **Tracking Resi**: Pelacakan status pengiriman real-time
- **Cetak Struk**: Generate dan print struk pengiriman berdasarkan nomor resi
- **Database Negara ASEAN**: 10 negara dengan ibu kota masing-masing
- **Kalkulasi Biaya**: Perhitungan otomatis berdasarkan jarak, jenis muatan, dan layanan
- **Status Management**: Update dan tracking status pengiriman

---
**Catatan**: Dokumen ini merupakan panduan pengembangan untuk meningkatkan fungsionalitas dan kualitas sistem pengiriman kargo kapal ASEAN.
