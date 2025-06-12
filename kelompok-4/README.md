# Sistem Pemesanan Tiket Kapal Laut

## Tim Pengembang
| No | Nama | NIM |
|----|------|-----|
| 1 | Rafi Ayfa Rusydan | 101102400032 |
| 2 | Muhammad Zaki Baridwan | 101102400012 |
| 3 | Najwa Nur Hafiyyani | 101102400019 |
| 4 | Dani Prasetiyo | 101102400023 |

## Deskripsi Program
Program ini adalah sistem pemesanan tiket kapal laut yang dibuat menggunakan bahasa pemrograman C++. Sistem ini memungkinkan pengguna untuk melakukan operasi CRUD (Create, Read, Update, Delete) terhadap data pemesanan tiket kapal beserta informasi lengkap perjalanan dan harga tiket.

## Rekomendasi Perbaikan Program

### 1. **Perbaikan Error Multi-Character Character Constant**
Mengatasi warning compiler pada baris 60 dan 174 dengan mengubah perbandingan string dari `'iya'` menjadi `"iya"` atau menggunakan perbandingan karakter tunggal seperti `'y'`. Implementasi ini akan menghilangkan warning multi-character character constant dan membuat kode lebih efisien dalam pemrosesan input konfirmasi user.

### 2. **Migrasi dari Vector ke Array untuk Struktur Data**
Mengganti penggunaan `vector<TiketKapal>` dengan array statis untuk menyimpan data tiket sesuai dengan requirement. Implementasi akan menggunakan array 1 dimensi dengan ukuran maksimum yang telah ditentukan, disertai dengan variabel counter untuk melacak jumlah tiket yang tersimpan. Struktur ini akan meningkatkan performa dan mempermudah manajemen memori.

### 3. **Implementasi Press Enter untuk Kembali ke Menu**
Mengganti sistem konfirmasi "Kembali ke menu utama? (iya/tidak)" dengan sistem yang lebih user-friendly menggunakan "Press Enter to continue..." atau "Tekan Enter untuk kembali ke menu utama...". Implementasi ini akan menggunakan `cin.get()` untuk menunggu input Enter dari user, memberikan pengalaman yang lebih intuitif dan mengurangi langkah navigasi.

### 4. **Validasi Input Kontekstual dan Sanitasi Data**
Menerapkan validasi input yang ketat untuk mencegah input karakter tidak valid seperti yang terlihat pada contoh (!@#$%^&*). Validasi akan mencakup:
- Nama Penumpang: hanya huruf dan spasi, maksimal 50 karakter
- Asal/Tujuan Keberangkatan: hanya huruf, spasi, dan tanda hubung
- Tanggal: format DD/MM/YYYY dengan validasi tanggal yang benar
- Jumlah Tiket: hanya angka positif, maksimal 10 tiket per transaksi
- Class: validasi pilihan class yang tersedia (Ekonomi, Bisnis, VIP)

### 5. **Penambahan Field Data Tiket Komprehensif**
Memperluas struktur data `TiketKapal` dengan menambahkan field-field baru:
- Jenis Kapal: Ferry, Speedboat, Kapal Pesiar, dll.
- Asal Keberangkatan: pelabuhan atau kota asal
- Tujuan Keberangkatan: mengganti "Tujuan Kapal"
- Class: Ekonomi, Bisnis, VIP dengan fasilitas berbeda
- Harga: kalkulasi otomatis berdasarkan jenis kapal, class, dan jarak
- Waktu Keberangkatan: jam dan menit keberangkatan
- Estimasi Tiba: perhitungan otomatis waktu tiba

### 6. **Perbaikan Bug Batalkan Pemesanan**
Mengatasi masalah looping pada fitur batalkan pemesanan yang menyebabkan data tidak terhapus dengan benar. Implementasi perbaikan akan mencakup:
- Refactoring logika penghapusan data dari array
- Penambahan konfirmasi yang jelas sebelum menghapus
- Validasi ID yang lebih robust
- Pengurangan counter tiket setelah penghapusan berhasil
- Pesan konfirmasi yang informatif setelah operasi selesai

### 7. **Fitur Pencarian Tiket Berdasarkan ID**
Menambahkan menu pencarian khusus yang memungkinkan user mencari tiket berdasarkan ID pemesanan. Fitur ini akan mencakup:
- Input ID dengan validasi format
- Tampilan detail tiket yang ditemukan
- Pesan error yang informatif jika ID tidak ditemukan
- Opsi untuk melakukan operasi lanjutan (edit/hapus) setelah pencarian
- Quick search dari menu utama

### 8. **Sistem Perhitungan Harga Otomatis**
Implementasi sistem pricing yang dinamis berdasarkan:
- Jarak perjalanan antar pelabuhan
- Jenis kapal yang dipilih
- Class perjalanan (Ekonomi: 1x, Bisnis: 1.5x, VIP: 2x)
- Seasonal pricing (high season, low season)
- Discount untuk pembelian multiple tiket
- Tax dan service charge

### 9. **Fitur Print Out/Struk Tiket Individual**
Implementasi sistem cetak struk tiket untuk satu pemesanan dengan format profesional boarding pass yang mencakup:
- Header dengan logo dan nama perusahaan kapal
- Informasi lengkap pemesanan (ID, nama penumpang, rute, tanggal, class)
- Barcode simulasi menggunakan karakter ASCII
- QR Code representation untuk validasi digital
- Terms and conditions perjalanan
- Format output ke file: `struk_tiket_{id}_{nama}.txt`
- Layout yang rapi dengan border dan alignment yang tepat
- Informasi tambahan: waktu cetak, nomor kursi, gate keberangkatan

## Struktur File Program
```
kelompok-4/
├── kelompok-4.cpp          # File source code utama
├── kelompok-4.exe          # File executable
├── README.md               # Dokumentasi program
├── data_tiket.txt          # Database data pemesanan tiket
└── struk/                  # Folder untuk file struk tiket individual
    └── struk_tiket_{id}_{nama}.txt
```

## Teknologi yang Digunakan
- Bahasa Pemrograman: C++
- Compiler: GCC/MinGW
- Struktur Data: Array dan Struct
- Format Data: TXT files dengan delimiter
- Platform: Windows

---
**Catatan**: Dokumen ini merupakan panduan pengembangan untuk meningkatkan fungsionalitas dan kualitas sistem pemesanan tiket kapal laut.
