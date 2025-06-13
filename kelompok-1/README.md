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

### 1. **Perbaikan Error Handling dan Input Validation**
Mengatasi masalah looping infinite saat user memasukkan input selain angka pada pilihan menu dan jenis kendaraan. Implementasi fungsi validasi input numerik yang robust untuk mencegah crash program dan memberikan feedback yang jelas kepada user tentang format input yang benar.

### 2. **Validasi Format Plat Nomor Indonesia**
Implementasi validasi plat nomor sesuai standar Indonesia dengan aturan:
- Huruf wajib di depan (minimal 1 karakter)
- Angka setelah huruf wajib (minimal 1 digit)
- Huruf setelah angka (opsional)
- Format contoh: B1234ABC, D567H, AA123BB
- Mencegah input format yang tidak sesuai dengan standar plat nomor Indonesia

### 3. **Perbaikan Sistem File Management**
Membuat struktur baru untuk penyimpanan data pelanggaran ke CSV dengan format yang lebih terorganisir. Implementasi auto-create folder `printout/` jika belum ada, dan penanganan error saat file tidak dapat dibuat atau diakses.

### 4. **Implementasi Search dan Filter Data**
Menambahkan fitur pencarian data berdasarkan:
- Nama pelanggar
- Nomor plat kendaraan
- Nomor KTP
- Range tanggal pelanggaran
- Jenis pelanggaran tertentu

### 5. **Perbaikan Format Tampilan Tabel Pelanggaran**
Merapikan tampilan daftar jenis pelanggaran dengan alignment yang konsisten:
```
--- DAFTAR JENIS PELANGGARAN ---
ID | Jenis Pelanggaran                    | Denda
---|--------------------------------------|----------
1  | Menerobos lampu merah               | Rp 50000
2  | Tidak menggunakan helm              | Rp 25000
...
```

### 6. **Perbaikan Fitur Dashboard Statistik**
Mengatasi masalah "Pelanggaran terbanyak belum muncul datanya" dengan implementasi algoritma sorting dan counting yang benar untuk menampilkan statistik pelanggaran yang paling sering terjadi.

### 7. **Perbaikan Fitur Print dan Export Data**
Mengatasi masalah pada opsi 2 (Print Semua Data) dan opsi 3 (Export ke File) yang tidak bekerja dengan benar. Implementasi yang diperbaiki akan mencakup:
- Print individual berdasarkan ID pelanggar (sudah berfungsi)
- Perbaikan Print semua data dalam format laporan yang terstruktur
- Perbaikan Export ke file CSV dengan error handling yang proper
- Format nama file export: `{id}_{nama}_{no.ktp}.txt`
- Validasi keberadaan folder `printout/` sebelum menyimpan file

### 8. **Optimalisasi Struktur Data untuk CSV**
Membuat struktur data baru yang lebih efisien untuk penyimpanan dan pembacaan data CSV:
- Implementasi field tambahan untuk metadata
- Optimalisasi format penyimpanan array pelanggaran
- Penanganan karakter khusus dalam data CSV
- Backup otomatis sebelum operasi write

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
