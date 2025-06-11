# Sistem Denda Pelanggaran Lalu Lintas

## Tim Pengembang
| No | Nama | NIM |
|----|------|-----|
| 1 | Rizqimuhadli Sutarno | 101102400007 |
| 2 | Muhammad Khirzi Aqilah Zufar | 101102400001 |
| 3 | Bagus Karani | 101102400035 |

## Deskripsi Program
Program ini adalah sistem manajemen denda pelanggaran lalu lintas yang dibuat menggunakan bahasa pemrograman C++. Sistem ini memungkinkan pengguna untuk melakukan operasi CRUD (Create, Read, Update, Delete) terhadap data pelanggar lalu lintas beserta jenis pelanggaran dan dendanya.

## Rekomendasi Perbaikan Program

### 1. **Implementasi Array 2 Dimensi untuk Data Master Pelanggaran**
Menggabungkan array `namaPelanggaran` dan `dendaPelanggaran` yang terpisah menjadi satu array 2 dimensi untuk meningkatkan efisiensi dan kemudahan maintenance. Struktur data terpadu ini akan memudahkan pengelolaan data master pelanggaran dan mengurangi risiko inkonsistensi data. Array 2D akan menyimpan nama pelanggaran dan nilai denda dalam satu struktur yang lebih terorganisir.

### 2. **Sistem Autentikasi Dinamis dengan Database File**
Mengganti sistem login statis hardcoded dengan sistem yang membaca data user dari file eksternal (users.txt atau users.csv). Implementasi ini memungkinkan penambahan, penghapusan, dan modifikasi user tanpa perlu mengubah source code. Sistem akan mendukung berbagai level akses user dan menyediakan fleksibilitas dalam manajemen akun pengguna.

### 3. **Validasi Input Kontekstual dan Sanitasi Data**
Menerapkan validasi input yang sesuai dengan konteks masing-masing field untuk mencegah input karakter tidak valid seperti yang terlihat pada contoh nota (nama: !@#$%^^&&*(^&$^&*(*%). Validasi akan mencakup:
- Nama: hanya huruf dan spasi, maksimal 50 karakter
- No. KTP: tepat 16 digit angka
- No. Plat: sesuai format plat nomor Indonesia
- Alamat: tidak mengandung karakter khusus berbahaya
- Jenis Kendaraan: pilihan dropdown dari kategori yang tersedia

### 4. **Sistem Persistensi Data dengan File CSV/TXT**
Implementasi penyimpanan data ke file eksternal (pelanggar.csv) untuk mempertahankan data setelah program ditutup. Sistem akan dilengkapi dengan fitur auto-save saat keluar program dan auto-load saat program dimulai. Format CSV dipilih untuk kompatibilitas dengan aplikasi spreadsheet dan kemudahan dalam analisis data lebih lanjut.

### 5. **Fitur Print dan Export Data Pelanggar**
Menambahkan kemampuan untuk mencetak detail data pelanggar dalam format yang rapi dan professional. Fitur ini akan mencakup:
- Print individual berdasarkan ID pelanggar
- Print semua data dalam format laporan
- Export ke file text untuk dokumentasi disimpan dalam folder `printout/`
- Template nota denda yang dapat dicetak langsung
- Opsi filter berdasarkan tanggal, jenis pelanggaran, atau range denda
- Format nama file export: `{id}_{nama}_{no.ktp}.txt` (contoh: `001_John_Doe_1234567890123456.txt`)

### 6. **Dashboard Laporan dan Statistik Komprehensif**
Mengembangkan sistem pelaporan yang memberikan insight tentang data pelanggaran, meliputi:
- Total pendapatan denda per periode
- Statistik jenis pelanggaran yang paling sering terjadi
- Ranking pelanggar dengan denda tertinggi
- Analisis tren pelanggaran berdasarkan waktu
- Grafik distribusi jenis kendaraan yang melanggar
- Summary harian, mingguan, dan bulanan

## Struktur File Program
```
kelompok-1/
├── kelompok-1.cpp          # File source code utama
├── kelompok-1.exe          # File executable
├── README.md               # Dokumentasi program
├── users.txt               # Database user login
├── pelanggar.csv           # Database data pelanggaran
└── printout/               # Folder untuk file export data pelanggar
    └── {id}_{nama}_{no.ktp}.txt
```

## Teknologi yang Digunakan
- Bahasa Pemrograman: C++
- Compiler: GCC/MinGW
- Format Data: CSV/TXT files
- Platform: Windows

---
**Catatan**: Dokumen ini merupakan panduan pengembangan untuk meningkatkan fungsionalitas dan kualitas sistem denda pelanggaran lalu lintas.
