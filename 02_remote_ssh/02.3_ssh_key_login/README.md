# 02.3 SSH Key Login

## 1. Tujuan

Bagian ini membahas autentikasi SSH menggunakan pasangan cryptographic key sehingga client dapat membuktikan identitas tanpa mengirimkan password akun server sebagai metode autentikasi utama.

Praktik meliputi:

- memahami public key dan private key;
- membuat SSH key pair menggunakan `ssh-keygen`;
- memahami algoritma Ed25519;
- memasang public key pada Ubuntu Server;
- memahami `authorized_keys`;
- mengatur permission direktori `.ssh`;
- menguji public-key authentication;
- memahami perbedaan `authorized_keys` dan `known_hosts`;
- membuat SSH client configuration dan alias;
- melakukan troubleshooting menggunakan verbose output.

---

# 2. Password Authentication dan Public-Key Authentication

Pada password authentication:

```text
Client
  │
  │ username + password
  ▼
Server
```

Pada public-key authentication:

```text
Client
├── Private Key
│
└──────────────┐
               │ authentication proof
               ▼
Server
└── Public Key
    di authorized_keys
```

Private key tidak dikirimkan ke server.

Client menggunakan private key untuk membuktikan bahwa ia memiliki secret key yang sesuai dengan public key yang diotorisasi pada server.

---

# 3. Public Key dan Private Key

SSH key pair terdiri dari:

```text
Private Key
+
Public Key
```

## Private Key

Private key harus tetap berada pada client.

Pada praktik ini file defaultnya:

```text
%USERPROFILE%\.ssh\id_ed25519
```

Private key:

```text
Tidak boleh dibagikan
Tidak boleh dikirim ke server
Tidak boleh ditempel ke laporan
Tidak boleh di-upload ke GitHub
Tidak boleh dimasukkan ke screenshot
```

## Public Key

Public key boleh didistribusikan ke server yang akan memberikan akses.

File default:

```text
%USERPROFILE%\.ssh\id_ed25519.pub
```

Extension:

```text
.pub
```

menandakan file public key.

---

# 4. Membuat SSH Key Pair

## Command

```powershell
ssh-keygen -t ed25519 -C "windows-client"
```

## Fungsi

Membuat authentication key pair menggunakan algoritma Ed25519 dan memberikan comment pada key.

---

# 5. Anatomy `ssh-keygen`

```text
ssh-keygen      -t      ed25519      -C      "windows-client"
    │            │          │         │              │
    │            │          │         │              └── key comment
    │            │          │         └── comment option
    │            │          └── key type
    │            └── type option
    └── OpenSSH key utility
```

---

## 5.1 `ssh-keygen`

`ssh-keygen` merupakan utility OpenSSH untuk membuat dan mengelola authentication keys.

Nama command dapat dibaca sebagai:

```text
SSH key generator
```

---

## 5.2 `-t`

Option:

```text
-t
```

menentukan **type** key yang akan dibuat.

Dalam praktik ini:

```text
-t ed25519
```

berarti membuat key bertipe:

```text
Ed25519
```

---

## 5.3 `ed25519`

Ed25519 merupakan algoritma digital signature berbasis elliptic-curve cryptography yang didukung OpenSSH.

Pada konteks SSH, pasangan key Ed25519 dapat digunakan untuk public-key authentication.

File default yang biasanya dibuat:

```text
id_ed25519
id_ed25519.pub
```

---

## 5.4 `-C`

Option:

```text
-C
```

digunakan untuk menentukan **comment** pada key.

Contoh:

```text
-C "windows-client"
```

Comment membantu manusia mengidentifikasi asal atau fungsi sebuah key.

Comment bukan password dan tidak digunakan sebagai secret.

---

# 6. Output `ssh-keygen`

Saat dijalankan, program meminta lokasi penyimpanan.

Jika default digunakan, pada Windows biasanya berada di:

```text
%USERPROFILE%\.ssh\
```

Contoh:

```text
C:\Users\<user>\.ssh\
```

dan menghasilkan:

```text
id_ed25519
└── private key

id_ed25519.pub
└── public key
```

---

# 7. Passphrase

`ssh-keygen` juga dapat meminta:

```text
Enter passphrase
```

Passphrase digunakan untuk melindungi private key yang tersimpan pada disk.

Ini berbeda dengan password akun server.

```text
Server Password
→ credential akun server

SSH Key Passphrase
→ melindungi private key lokal
```

Jika private key menggunakan passphrase, SSH masih dapat meminta passphrase saat key digunakan.

Hal tersebut **tidak berarti public-key authentication gagal**.

Agar pengguna tidak memasukkan passphrase berulang kali, key dapat dikelola menggunakan SSH agent sesuai environment yang digunakan.

Untuk demonstrasi laboratorium, passphrase dapat dikosongkan jika memang itu ruang lingkup latihan, tetapi untuk key penting penggunaan passphrase merupakan pilihan keamanan yang lebih baik.

---

# 8. Jangan Menyebutnya "Keyless Authentication"

Autentikasi ini bukan:

```text
keyless authentication
```

karena autentikasi justru menggunakan cryptographic key.

Istilah yang lebih tepat adalah:

```text
Public-Key Authentication
```

atau:

```text
Key-Based Authentication
```

Jika pengguna tidak perlu mengetik password akun server, kondisi tersebut dapat disebut:

```text
passwordless login using public-key authentication
```

Namun SSH key tetap digunakan.

---

# 9. Memasang Public Key pada Ubuntu Server

Pada Windows OpenSSH environment, `ssh-copy-id` tidak selalu tersedia.

Dalam praktik ini digunakan PowerShell pipeline:

```powershell
Get-Content "$env:USERPROFILE\.ssh\id_ed25519.pub" | ssh -p 2222 vboxuser@127.0.0.1 "umask 077; mkdir -p ~/.ssh; cat >> ~/.ssh/authorized_keys"
```

Command ini terlihat panjang karena sebenarnya menggabungkan beberapa operasi.

---

# 10. Gambaran Besar Command

```text
Public Key File pada Windows
          │
          │ Get-Content
          ▼
PowerShell Pipeline
          │
          │ |
          ▼
SSH Connection
          │
          ▼
Ubuntu Remote Shell
          │
          ├── umask 077
          ├── mkdir -p ~/.ssh
          └── cat >> ~/.ssh/authorized_keys
```

---

# 11. `Get-Content`

Bagian pertama:

```powershell
Get-Content "$env:USERPROFILE\.ssh\id_ed25519.pub"
```

## Fungsi

Membaca isi public key pada Windows dan menuliskannya ke output pipeline.

## Struktur

```text
Get-Content      "$env:USERPROFILE\.ssh\id_ed25519.pub"
     │                              │
     │                              └── path public key
     └── PowerShell cmdlet
```

---

# 12. `$env:USERPROFILE`

PowerShell menggunakan:

```powershell
$env:USERPROFILE
```

untuk membaca environment variable Windows:

```text
USERPROFILE
```

yang biasanya menunjuk ke home directory user.

Contoh:

```text
C:\Users\username
```

Sehingga:

```powershell
"$env:USERPROFILE\.ssh\id_ed25519.pub"
```

akan mengarah ke:

```text
C:\Users\username\.ssh\id_ed25519.pub
```

tanpa perlu menulis username secara hard-coded.

---

# 13. PowerShell Pipe `|`

Bagian:

```text
|
```

merupakan pipeline operator.

Secara konsep:

```text
Get-Content public-key
        │
        │ output
        ▼
       ssh
```

Isi public key dikirim sebagai input ke process SSH.

---

# 14. Bagian SSH

```powershell
ssh -p 2222 vboxuser@127.0.0.1 "..."
```

Strukturnya:

```text
ssh      -p      2222      vboxuser@127.0.0.1      "remote command"
 │        │        │                  │                    │
 │        │        │                  │                    └── dijalankan pada server
 │        │        │                  └── remote user/host
 │        │        └── port
 │        └── port option
 └── SSH client
```

Berbeda dengan login interaktif biasa, kali ini SSH diberi **remote command**.

Artinya setelah koneksi dibuat, server menjalankan string command tersebut.

---

# 15. `umask 077`

Bagian pertama pada remote command:

```bash
umask 077
```

## Fungsi

Mengatur file creation mask untuk shell tersebut sehingga permission group dan other dibatasi saat file/directory baru dibuat.

Nilai:

```text
077
```

secara konsep menghilangkan permission:

```text
group
other
```

dari default permission baru.

Command ini membantu membuat direktori/file SSH dengan permission yang lebih ketat.

---

# 16. Pemisah Command `;`

Remote command menggunakan:

```text
;
```

Contoh:

```bash
umask 077; mkdir -p ~/.ssh; cat >> ~/.ssh/authorized_keys
```

Semicolon memisahkan beberapa shell command.

Secara urutan:

```text
Command 1
;
Command 2
;
Command 3
```

Masing-masing dijalankan secara berurutan.

Perlu dicatat bahwa `;` tetap melanjutkan ke command berikutnya meskipun command sebelumnya gagal.

Untuk script yang lebih ketat, shell operator lain dapat digunakan, tetapi praktik ini mengikuti command yang digunakan pada eksperimen.

---

# 17. `mkdir -p ~/.ssh`

```bash
mkdir -p ~/.ssh
```

## Struktur

```text
mkdir      -p      ~/.ssh
  │         │        │
  │         │        └── directory target
  │         └── parents / tidak error jika sudah ada
  └── make directory
```

`mkdir` berasal dari:

```text
make directory
```

### `-p`

Option `-p` memungkinkan pembuatan parent directory yang diperlukan dan tidak menganggap existing directory sebagai error dalam penggunaan biasa.

### `~`

Tilde:

```text
~
```

merepresentasikan home directory user pada shell.

Untuk user:

```text
vboxuser
```

maka:

```text
~/.ssh
```

biasanya berarti:

```text
/home/vboxuser/.ssh
```

---

# 18. `cat >> ~/.ssh/authorized_keys`

```bash
cat >> ~/.ssh/authorized_keys
```

Bagian ini membaca standard input lalu mengarahkannya ke file.

## `cat`

`cat` dapat membaca input/file dan menuliskannya ke standard output.

Pada command ini tidak diberikan input file secara eksplisit, sehingga data yang datang melalui standard input pipeline digunakan.

---

## `>>`

Operator:

```text
>>
```

merupakan **append redirection**.

Artinya output ditambahkan ke akhir file.

Berbeda dengan:

```text
>
```

yang mengganti/truncate isi file target pada penggunaan shell normal.

Karena itu digunakan:

```text
>>
```

agar public key baru ditambahkan ke:

```text
authorized_keys
```

tanpa sengaja mengganti entry yang sudah ada.

---

# 19. `authorized_keys`

File:

```bash
~/.ssh/authorized_keys
```

berada pada **server**.

File ini berisi public key yang diperbolehkan digunakan untuk login sebagai user pemilik file tersebut.

Contoh konsep:

```text
Ubuntu Server
└── /home/vboxuser/
    └── .ssh/
        └── authorized_keys
            ├── public key client A
            └── public key client B
```

Key yang ada di `authorized_keys` berkaitan dengan akun tersebut.

Public key di:

```text
/home/vboxuser/.ssh/authorized_keys
```

memberikan kemungkinan autentikasi sebagai:

```text
vboxuser
```

sesuai konfigurasi SSH server.

---

# 20. Mengatur Permission `.ssh`

Setelah public key dipasang, praktik menggunakan:

```powershell
ssh -p 2222 vboxuser@127.0.0.1 "chmod 700 ~/.ssh; chmod 600 ~/.ssh/authorized_keys"
```

Command tersebut membuat SSH connection lalu menjalankan dua `chmod` pada server.

---

# 21. Memahami `chmod`

`chmod` berarti:

```text
change mode
```

dan digunakan untuk mengubah file mode/permission.

Permission dasar Unix terdiri dari:

```text
Read    = 4
Write   = 2
Execute = 1
```

Setiap digit mewakili:

```text
Owner
Group
Others
```

---

# 22. Permission `700`

```bash
chmod 700 ~/.ssh
```

Angka:

```text
7 = 4 + 2 + 1
```

berarti:

```text
read + write + execute
```

Sehingga:

```text
700
│││
││└── Others = 0 = ---
│└─── Group  = 0 = ---
└──── Owner  = 7 = rwx
```

Hasil:

```text
Owner  : rwx
Group  : ---
Others : ---
```

Pada directory, execute permission diperlukan untuk dapat melakukan traversal/access terhadap entry di dalam directory.

---

# 23. Permission `600`

```bash
chmod 600 ~/.ssh/authorized_keys
```

Angka:

```text
6 = 4 + 2
```

berarti:

```text
read + write
```

Sehingga:

```text
600
│││
││└── Others = 0 = ---
│└─── Group  = 0 = ---
└──── Owner  = 6 = rw-
```

Hasil:

```text
Owner  : rw-
Group  : ---
Others : ---
```

---

# 24. Kenapa Permission SSH Penting?

SSH mempertimbangkan keamanan file yang digunakan untuk autentikasi.

Direktori/file autentikasi yang terlalu terbuka terhadap user lain dapat menimbulkan risiko keamanan dan pada beberapa konfigurasi dapat menyebabkan SSH menolak penggunaannya.

Pada praktik ini digunakan:

```text
~/.ssh                = 700
~/.ssh/authorized_keys = 600
```

---

# 25. Memeriksa Direktori `.ssh`

## Command

```bash
ls -la ~/.ssh
```

## Struktur

```text
ls      -l      -a      ~/.ssh
│        │       │        │
│        │       │        └── directory
│        │       └── include hidden entries
│        └── long listing format
└── list directory contents
```

Options dapat digabung:

```text
-la
```

---

## 25.1 `-l`

Menampilkan informasi dalam long listing format, termasuk data seperti permission, owner, size, dan timestamp.

---

## 25.2 `-a`

`a` berasal dari:

```text
all
```

Digunakan agar nama yang diawali titik ikut ditampilkan.

Pada Unix-like systems, nama seperti:

```text
.ssh
```

merupakan hidden-style filename/directory karena diawali `.`.

---

# 26. Menghitung Entry `authorized_keys`

## Command

```bash
wc -l ~/.ssh/authorized_keys
```

## Struktur

```text
wc      -l      ~/.ssh/authorized_keys
│        │                 │
│        │                 └── file
│        └── count newline/lines
└── word count utility
```

`wc` berasal dari:

```text
word count
```

Namun utility ini dapat menghitung lebih dari sekadar kata.

Option:

```text
-l
```

meminta line count.

Jika setiap public key tersimpan sebagai satu baris, output dapat membantu memeriksa jumlah entry key.

Namun command ini **tidak membuktikan bahwa key tertentu pasti benar**; ia hanya menghitung line.

---

# 27. Jangan Menampilkan Private Key

Jangan menjalankan atau memasukkan ke laporan:

```powershell
Get-Content "$env:USERPROFILE\.ssh\id_ed25519"
```

untuk tujuan dokumentasi.

File tersebut adalah private key.

Untuk bukti praktik, cukup tampilkan:

```text
nama file
lokasi file
fingerprint
proses key generation
status koneksi
```

tanpa mengekspos private key.

Public key sendiri bukan secret seperti private key, tetapi tidak perlu dipublikasikan utuh di laporan jika tidak diperlukan.

---

# 28. Menguji Public-Key Authentication

Setelah public key tersimpan pada server, jalankan kembali:

```powershell
ssh -p 2222 vboxuser@127.0.0.1
```

Alurnya sekarang:

```text
Windows Client
      │
      │ menawarkan public-key identity
      ▼
Ubuntu SSH Server
      │
      │ cek authorized_keys
      ▼
Cryptographic Authentication
      │
      ▼
Remote Session
```

Jika konfigurasi berhasil dan tidak ada metode lain yang meminta password akun, session dapat terbuka tanpa prompt password akun Ubuntu.

---

# 29. Public-Key Login Bukan Berarti Tanpa Autentikasi

Kondisi:

```text
tidak mengetik password server
```

bukan berarti:

```text
tidak ada authentication
```

Authentication tetap terjadi.

Perbedaannya adalah credential/proof yang digunakan.

```text
Password Authentication
→ knowledge of server account password

Public-Key Authentication
→ cryptographic proof of private-key possession
```

---

# 30. `authorized_keys` dan `known_hosts`

Dua file ini sering tertukar.

## `authorized_keys`

Berada pada:

```text
server
```

dan menjawab pertanyaan:

```text
"Public key client mana yang diizinkan login ke akun ini?"
```

Contoh:

```text
Ubuntu Server
~/.ssh/authorized_keys
```

---

## `known_hosts`

Berada pada:

```text
client
```

dan membantu menjawab:

```text
"Apakah ini host/server yang sama dengan yang sebelumnya saya kenal?"
```

Contoh pada client:

```text
~/.ssh/known_hosts
```

Secara konsep:

```text
CLIENT
├── Private Key
└── known_hosts
     │
     └── identitas server yang dikenal

SERVER
└── authorized_keys
     │
     └── public key client yang diizinkan
```

Jadi:

```text
authorized_keys
≠
known_hosts
```

---

# 31. Membuat SSH Client Alias

Tanpa config, command koneksi adalah:

```powershell
ssh -p 2222 vboxuser@127.0.0.1
```

Parameter tersebut dapat disimpan dalam SSH client configuration.

Pada Windows, buka:

```powershell
notepad $env:USERPROFILE\.ssh\config
```

Kemudian isi:

```sshconfig
Host belajarssh
    HostName 127.0.0.1
    User vboxuser
    Port 2222
    IdentityFile ~/.ssh/id_ed25519
```

Setelah itu:

```powershell
ssh belajarssh
```

dapat digunakan.

---

# 32. Anatomy SSH Config

```sshconfig
Host belajarssh
    HostName 127.0.0.1
    User vboxuser
    Port 2222
    IdentityFile ~/.ssh/id_ed25519
```

---

## 32.1 `Host`

```text
Host belajarssh
```

`Host` mendefinisikan pola/nama yang digunakan user saat memanggil SSH.

Pada praktik ini:

```text
belajarssh
```

menjadi alias yang digunakan pada command:

```bash
ssh belajarssh
```

---

## 32.2 `HostName`

```text
HostName 127.0.0.1
```

`HostName` menentukan hostname atau IP address sebenarnya yang akan dihubungi.

Alias:

```text
belajarssh
```

diterjemahkan menjadi:

```text
127.0.0.1
```

---

## 32.3 `User`

```text
User vboxuser
```

Menentukan remote username.

Setara dengan bagian:

```text
vboxuser@
```

pada:

```text
vboxuser@127.0.0.1
```

---

## 32.4 `Port`

```text
Port 2222
```

Menentukan remote port yang digunakan SSH client.

Setara dengan:

```text
-p 2222
```

pada command CLI.

---

## 32.5 `IdentityFile`

```text
IdentityFile ~/.ssh/id_ed25519
```

Menentukan authentication identity file yang digunakan SSH client.

Pada praktik ini file tersebut adalah:

```text
private key
```

Bukan:

```text
id_ed25519.pub
```

Public key berada di server, sedangkan client menggunakan private key untuk autentikasi.

---

# 33. Dari Command Panjang Menjadi Alias

Sebelum config:

```powershell
ssh -p 2222 vboxuser@127.0.0.1
```

Informasinya:

```text
HostName = 127.0.0.1
User     = vboxuser
Port     = 2222
Identity = default / specified key
```

Setelah config:

```powershell
ssh belajarssh
```

SSH membaca:

```text
Host belajarssh
```

kemudian menerapkan parameter yang cocok.

Secara konsep:

```text
ssh belajarssh
       │
       ▼
Read ~/.ssh/config
       │
       ├── HostName 127.0.0.1
       ├── User vboxuser
       ├── Port 2222
       └── IdentityFile ~/.ssh/id_ed25519
       │
       ▼
Create SSH Connection
```

---

# 34. Pengujian Akhir

Jalankan:

```powershell
ssh belajarssh
```

Setelah masuk:

```bash
whoami
hostname
pwd
```

Kemudian:

```bash
exit
```

Target hasil:

```text
Alias berhasil dipakai
Username sesuai
Hostname sesuai
Remote shell berhasil
Public-key authentication berfungsi
Session dapat ditutup
```

---

# 35. Verbose Troubleshooting

Jika koneksi tidak bekerja seperti yang diharapkan, gunakan:

```powershell
ssh -v belajarssh
```

atau:

```powershell
ssh -v -p 2222 vboxuser@127.0.0.1
```

## `-v`

Option:

```text
-v
```

berarti:

```text
verbose
```

Verbose mode menampilkan informasi diagnostik tambahan mengenai proses koneksi.

Output dapat membantu melihat hal seperti:

```text
config yang dibaca
host yang dihubungi
identity/key yang dicoba
tahap authentication
```

Jangan menyalin diagnostic output ke publik tanpa memeriksa apakah terdapat informasi yang sebaiknya disensor.

---

# 36. Troubleshooting

## Masih Meminta Password Akun Server

Periksa apakah public key berada pada:

```bash
~/.ssh/authorized_keys
```

Periksa:

```bash
ls -la ~/.ssh
```

Kemudian gunakan:

```powershell
ssh -v belajarssh
```

untuk melihat metode authentication dan identity yang dicoba.

---

## `Permission denied (publickey)`

Periksa:

```text
public key client benar
authorized_keys milik user yang benar
permission .ssh sesuai
permission authorized_keys sesuai
IdentityFile menunjuk private key yang benar
```

Periksa:

```bash
chmod 700 ~/.ssh
chmod 600 ~/.ssh/authorized_keys
```

---

## Alias Tidak Berfungsi

Periksa file:

```text
%USERPROFILE%\.ssh\config
```

Pastikan:

```text
Host
HostName
User
Port
IdentityFile
```

sesuai.

Bandingkan dengan koneksi manual:

```powershell
ssh -p 2222 vboxuser@127.0.0.1
```

Jika command manual berhasil tetapi alias gagal, kemungkinan masalah berada pada client config.

---

## Host Key Changed

Jika SSH memberi peringatan host identity berubah, jangan langsung menghapus entry `known_hosts`.

Pastikan dahulu apakah server benar-benar berubah.

Contoh alasan sah:

```text
VM dibuat ulang
host key diregenerate
server diganti
```

Perubahan yang tidak diharapkan harus diperiksa sebelum menerima identitas baru.

---

# 37. Jangan Langsung Menonaktifkan Password Authentication

Setelah public-key authentication berhasil, SSH server dapat di-hardening lebih lanjut.

Namun jangan langsung menonaktifkan password authentication sebelum:

```text
Public key telah terpasang
Key login sudah diuji
Koneksi baru menggunakan key berhasil
Akses alternatif tersedia jika konfigurasi salah
```

Jika password authentication dimatikan ketika key authentication belum bekerja, user dapat kehilangan akses remote.

Pada praktik ini fokus utama adalah memastikan public-key login bekerja terlebih dahulu.

---

# 38. Security Notes

Hal penting yang harus dijaga:

```text
Private key tetap berada pada client
Private key tidak di-upload ke GitHub
Private key tidak dimasukkan ke laporan
Public key saja yang ditempatkan pada authorized_keys
Host key/fingerprint diperiksa ketika memungkinkan
Permission .ssh dibuat terbatas
```

Jika private key diduga bocor, jangan hanya mengganti comment atau filename.

Key tersebut sebaiknya dianggap tidak lagi terpercaya dan public key terkait perlu dicabut dari server, kemudian pasangan key baru dibuat.

---

# 39. Alur Public-Key Authentication

```text
Windows Client
      │
      ├── id_ed25519
      │   Private Key
      │
      └── id_ed25519.pub
          Public Key
              │
              │ copy
              ▼
Ubuntu Server
~/.ssh/authorized_keys
              │
              ▼
Client connects
              │
              ▼
Server checks allowed public keys
              │
              ▼
Client proves possession of private key
              │
              ▼
Authentication succeeds
              │
              ▼
Remote Session
```

---

# 40. Alur Lengkap Praktik

```text
Password SSH Login Berhasil
        │
        ▼
ssh-keygen
        │
        ▼
Ed25519 Key Pair
        │
        ├── Private Key → tetap di Windows
        │
        └── Public Key
                │
                ▼
        Ubuntu authorized_keys
                │
                ▼
        Permission diperiksa
                │
                ▼
        Public-Key Login Test
                │
                ▼
        SSH Client Config
                │
                ▼
        Host alias "belajarssh"
                │
                ▼
        ssh belajarssh
```

---

# 41. Command Summary

Generate key:

```powershell
ssh-keygen -t ed25519 -C "windows-client"
```

Copy public key:

```powershell
Get-Content "$env:USERPROFILE\.ssh\id_ed25519.pub" | ssh -p 2222 vboxuser@127.0.0.1 "umask 077; mkdir -p ~/.ssh; cat >> ~/.ssh/authorized_keys"
```

Set permission:

```powershell
ssh -p 2222 vboxuser@127.0.0.1 "chmod 700 ~/.ssh; chmod 600 ~/.ssh/authorized_keys"
```

Inspect server SSH directory:

```bash
ls -la ~/.ssh
```

Count authorized key lines:

```bash
wc -l ~/.ssh/authorized_keys
```

Test login:

```powershell
ssh -p 2222 vboxuser@127.0.0.1
```

Open SSH client config:

```powershell
notepad $env:USERPROFILE\.ssh\config
```

Connect using alias:

```powershell
ssh belajarssh
```

Verbose troubleshooting:

```powershell
ssh -v belajarssh
```

---

# 42. Kesimpulan

Public-key authentication menggunakan pasangan private key dan public key.

Pada implementasi ini:

```text
Windows
└── Private Key
    id_ed25519

Ubuntu Server
└── Public Key
    ~/.ssh/authorized_keys
```

Private key tidak dikirimkan ke server.

Public key ditempatkan pada `authorized_keys`, kemudian SSH menggunakan cryptographic authentication untuk membuktikan kepemilikan private key yang sesuai.

SSH client configuration:

```sshconfig
Host belajarssh
    HostName 127.0.0.1
    User vboxuser
    Port 2222
    IdentityFile ~/.ssh/id_ed25519
```

menyederhanakan:

```powershell
ssh -p 2222 vboxuser@127.0.0.1
```

menjadi:

```powershell
ssh belajarssh
```

Dengan memahami fungsi setiap command, key, permission, dan configuration field, konfigurasi SSH tidak hanya dapat dijalankan tetapi juga dapat dianalisis ketika terjadi masalah.