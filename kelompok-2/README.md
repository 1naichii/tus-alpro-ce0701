# Fast Delivery - Aplikasi Pengiriman Paket

## Tim Pengembang
| No | Nama | NIM |
|----|------|-----|
| 1 | [Nama Anggota 1] | [NIM 1] |
| 2 | [Nama Anggota 2] | [NIM 2] |
| 3 | [Nama Anggota 3] | [NIM 3] |

## Deskripsi Program
Fast Delivery adalah aplikasi console berbasis C++ untuk mengelola sistem pengiriman paket elektronik. Aplikasi ini menyediakan fitur registrasi pengguna, login, pembuatan pengiriman, tracking paket, dan manajemen data pengiriman.

## Rekomendasi Perbaikan Program

### 1. **Implementasi Hash Password untuk Keamanan Data**
Mengganti sistem penyimpanan password plain text dengan hash password menggunakan algoritma hashing untuk meningkatkan keamanan data pengguna. Implementasi ini akan melindungi password user dari akses tidak sah dan memenuhi standar keamanan aplikasi modern. Hash password akan disimpan dalam file user.txt menggantikan password asli.

### 2. **Sistem Status Pengiriman Dinamis dengan Timeline**
Mengembangkan sistem status pengiriman yang lebih realistis dengan multiple status seperti "Menunggu Pickup", "Sudah Dipickup", "Dalam Perjalanan", "Sedang Diantar", dan "Terkirim". Setiap perubahan status akan disimpan dengan timestamp untuk memberikan tracking yang lebih akurat dan informatif kepada pengguna.

### 3. **Validasi Input Kontekstual dengan Format Indonesia**
Menerapkan validasi input yang sesuai dengan standar Indonesia untuk meningkatkan akurasi data. Validasi akan mencakup:
- Username: minimal 3 karakter, hanya huruf, angka, dan underscore
- Password: minimal 6 karakter dengan kombinasi huruf dan angka
- Nama: hanya huruf dan spasi, format nama Indonesia
- Email: regex validation sesuai standar email internasional
- No. HP: format Indonesia 08xxxxxxxxxx (10-15 digit)
- Alamat: tidak mengandung karakter khusus berbahaya

### 4. **Sistem Database File dengan Format Terstruktur**
Implementasi penyimpanan data menggunakan array statis (sesuai modul pembelajaran) dengan backup ke file user.txt dan transaksi.txt. Sistem akan dilengkapi dengan auto-save saat keluar program dan auto-load saat program dimulai. Format file menggunakan delimiter (|) untuk memudahkan parsing data dan kompatibilitas dengan aplikasi lain.

### 5. **Fitur Export dan Print Data Pengiriman**
Menambahkan kemampuan untuk mencetak dan export data pengiriman dalam format yang rapi dan professional. Fitur ini akan mencakup:
- Print struk pengiriman individual berdasarkan nomor resi
- Export data pengiriman ke file text
- Format laporan lengkap dengan header dan footer
- Template struk yang dapat dicetak langsung
- Opsi filter berdasarkan tanggal atau status pengiriman
- Format nama file export: `{resi}_{nama_penerima}_{tanggal}.txt`

### 6. **Dashboard Analytics dan Laporan Bisnis**
Mengembangkan sistem pelaporan yang memberikan insight tentang operasional pengiriman, meliputi:
- Total pendapatan per periode (harian, mingguan, bulanan)
- Statistik jenis pengiriman yang paling populer (Hemat/Reguler/Instan)
- Analisis metode pembayaran (Cash vs Transfer)
- Top 10 pengirim paling aktif
- Grafik distribusi pengiriman berdasarkan wilayah
- Summary performa pengiriman dan customer satisfaction

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
