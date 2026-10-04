# 02.2 Instalasi dan Koneksi SSH

## 1. Tujuan

Bagian ini mendokumentasikan proses menyiapkan Ubuntu Server 24.04 LTS sebagai SSH server di Oracle VirtualBox dan melakukan koneksi remote dari Windows sebagai SSH client.

Pembahasan meliputi:

- instalasi dan pemeriksaan OpenSSH Server;
- pemeriksaan service SSH;
- pemeriksaan listening port;
- pemeriksaan alamat jaringan server;
- konfigurasi NAT Port Forwarding pada VirtualBox;
- pemeriksaan OpenSSH Client pada Windows;
- koneksi SSH menggunakan password;
- verifikasi bahwa shell yang diperoleh benar-benar berasal dari Ubuntu Server.

Setiap command dijelaskan berdasarkan fungsi, struktur command, serta arti option dan argument yang digunakan.

---

# 2. Environment Praktik

Konfigurasi yang digunakan adalah:

| Komponen | Peran |
|---|---|
| Windows | Host dan SSH Client |
| PowerShell / Windows Terminal | Terminal client |
| Oracle VirtualBox | Hypervisor |
| Ubuntu Server 24.04 LTS | Guest OS dan SSH Server |
| OpenSSH Server | Menyediakan service `sshd` |
| OpenSSH Client | Menyediakan command `ssh` |

Arsitektur praktik:

```text
Laptop Fisik
│
├── Windows
│   └── OpenSSH Client
│
└── Oracle VirtualBox
    └── Ubuntu Server 24.04 LTS
        └── OpenSSH Server (sshd)
```

Walaupun Windows dan Ubuntu berjalan pada laptop fisik yang sama, keduanya merupakan dua sistem operasi berbeda yang berkomunikasi melalui virtual networking milik VirtualBox.

---

# 3. SSH Client dan SSH Server

SSH menggunakan model client-server.

```text
SSH Client
    │
    │ membuat koneksi
    ▼
SSH Server
```

Pada praktik ini:

```text
Windows
= SSH Client

Ubuntu Server
= SSH Server
```

Client menjalankan program:

```text
ssh
```

sedangkan server menjalankan daemon:

```text
sshd
```

`sshd` merupakan OpenSSH daemon yang menerima dan menangani koneksi SSH masuk.

Secara default, SSH server menggunakan TCP port:

```text
22
```

---

# 4. Login Lokal ke Ubuntu Server

Sebelum melakukan remote login, login terlebih dahulu secara lokal melalui console Ubuntu Server.

Contoh:

```text
BelajarSSH24 login: vboxuser
Password:

vboxuser@BelajarSSH24:~$
```

Prompt:

```text
vboxuser@BelajarSSH24:~$
```

dapat dibaca sebagai:

```text
vboxuser
│
└── username

BelajarSSH24
│
└── hostname

~
│
└── home directory

$
│
└── shell prompt untuk user biasa
```

Saat mengetik password pada terminal Linux, karakter password umumnya tidak ditampilkan.

Tidak munculnya karakter `*` bukan berarti keyboard tidak bekerja.

---

# 5. Memeriksa OpenSSH Server

## Command

```bash
dpkg -l | grep openssh-server
```

Command ini digunakan untuk memeriksa apakah package `openssh-server` telah terpasang pada sistem berbasis Debian/Ubuntu.

---

## 5.1 Struktur Command

```text
dpkg      -l      |      grep      openssh-server
 │         │      │        │             │
 │         │      │        │             └── teks yang dicari
 │         │      │        └── program pencarian teks
 │         │      └── pipe
 │         └── list package
 └── Debian package manager utility
```

### `dpkg`

`dpkg` merupakan tool package management tingkat dasar pada Debian dan distribusi turunannya seperti Ubuntu.

### `-l`

Option:

```text
-l
```

digunakan untuk menampilkan daftar package.

### Pipe `|`

Karakter:

```text
|
```

disebut **pipe**.

Pipe mengirim standard output command di sebelah kiri sebagai standard input untuk command di sebelah kanan.

Secara konsep:

```text
dpkg -l
   │
   │ output
   ▼
 grep openssh-server
```

### `grep`

`grep` digunakan untuk mencari baris yang cocok dengan suatu pola teks.

Di sini pola yang dicari adalah:

```text
openssh-server
```

Sehingga command lengkap dapat dibaca sebagai:

> Tampilkan daftar package, kemudian tampilkan hanya baris yang mengandung `openssh-server`.

---

# 6. Memeriksa Status Service SSH

## Command

```bash
sudo systemctl status ssh
```

## Fungsi

Memeriksa kondisi service SSH yang dikelola oleh `systemd`.

## Struktur

```text
sudo      systemctl      status      ssh
 │            │             │         │
 │            │             │         └── nama unit/service
 │            │             └── operasi yang diminta
 │            └── control interface untuk systemd
 └── jalankan command dengan privilege user lain
```

---

## 6.1 `sudo`

`sudo` digunakan untuk menjalankan command dengan privilege user lain sesuai konfigurasi sistem.

Pada penggunaan administrasi Ubuntu, privilege yang diperoleh biasanya privilege `root`.

Tidak semua command membutuhkan `sudo`, tetapi beberapa informasi atau operasi administratif membutuhkan privilege lebih tinggi.

---

## 6.2 `systemctl`

`systemctl` merupakan command-line interface untuk mengontrol dan memeriksa unit yang dikelola oleh:

```text
systemd
```

Unit dapat berupa:

```text
service
socket
timer
mount
target
```

Dalam praktik ini yang diperiksa adalah service SSH.

---

## 6.3 `status`

Subcommand:

```text
status
```

meminta informasi kondisi unit.

Informasi yang dapat terlihat antara lain:

```text
Loaded
Active
Main PID
Recent log messages
```

Target utama pada praktik ini:

```text
Active: active (running)
```

Artinya service SSH sedang berjalan.

---

## 6.4 `ssh`

Pada Ubuntu, service OpenSSH Server umumnya dikelola dengan nama unit:

```text
ssh
```

Karena itu digunakan:

```bash
sudo systemctl status ssh
```

Bukan berarti program servernya bernama `ssh`.

Program daemon server tetap:

```text
sshd
```

Sedangkan:

```text
ssh
```

juga merupakan nama SSH client command.

Perbedaan konteks ini perlu diperhatikan.

---

# 7. Menginstal OpenSSH Server

Jika package belum terpasang, jalankan:

```bash
sudo apt update
```

kemudian:

```bash
sudo apt install openssh-server
```

---

## 7.1 `sudo apt update`

Struktur:

```text
sudo      apt      update
 │         │          │
 │         │          └── refresh package metadata
 │         └── package management frontend
 └── elevated privilege
```

`apt update` memperbarui informasi package yang tersedia dari repository.

Command ini **tidak sama** dengan meng-upgrade seluruh package.

---

## 7.2 `sudo apt install openssh-server`

Struktur:

```text
sudo      apt      install      openssh-server
 │         │          │               │
 │         │          │               └── package
 │         │          └── install package
 │         └── package manager
 └── elevated privilege
```

Command ini memasang package OpenSSH Server.

---

# 8. Mengaktifkan dan Menjalankan SSH

## Command

```bash
sudo systemctl enable --now ssh
```

## Struktur

```text
sudo   systemctl   enable   --now   ssh
 │         │          │       │      │
 │         │          │       │      └── service
 │         │          │       └── langsung start juga
 │         │          └── aktifkan untuk startup
 │         └── systemd control
 └── elevated privilege
```

### `enable`

`enable` mengonfigurasi unit agar dapat dimulai secara otomatis pada boot sesuai dependency/target systemd.

### `--now`

Option:

```text
--now
```

meminta systemd menjalankan operasi runtime juga.

Dengan demikian:

```bash
sudo systemctl enable --now ssh
```

secara praktis berarti:

```text
enable SSH untuk startup
+
jalankan SSH sekarang
```

Setelah itu verifikasi kembali:

```bash
sudo systemctl status ssh
```

---

# 9. Memeriksa Listening Port SSH

## Command

```bash
sudo ss -tlnp | grep ':22'
```

Command ini digunakan untuk memeriksa apakah terdapat TCP socket yang sedang `LISTEN` pada port 22.

---

## 9.1 Struktur Command

```text
sudo      ss      -tlnp      |      grep      ':22'
 │         │         │       │        │          │
 │         │         │       │        │          └── pola port yang dicari
 │         │         │       │        └── filter teks
 │         │         │       └── pipe
 │         │         └── options
 │         └── socket statistics utility
 └── elevated privilege
```

---

## 9.2 `ss`

`ss` merupakan utility untuk menampilkan informasi socket pada Linux.

Nama command berasal dari:

```text
socket statistics
```

---

## 9.3 Option `-tlnp`

Option tersebut merupakan gabungan dari:

```text
-t
-l
-n
-p
```

### `-t`

```text
--tcp
```

Menampilkan TCP sockets.

### `-l`

```text
--listening
```

Menampilkan socket yang sedang menunggu koneksi masuk.

### `-n`

```text
--numeric
```

Menampilkan alamat dan port secara numerik tanpa mencoba mengubahnya menjadi nama service.

Contoh:

```text
22
```

tidak diubah menjadi:

```text
ssh
```

### `-p`

```text
--processes
```

Menampilkan informasi process yang menggunakan socket jika informasi tersebut tersedia untuk user yang menjalankan command.

Karena informasi process dapat membutuhkan privilege, command pada praktik ini menggunakan `sudo`.

---

## 9.4 `grep ':22'`

Output `ss` kemudian difilter:

```bash
grep ':22'
```

untuk mencari baris yang mengandung:

```text
:22
```

Artinya kita tertarik pada socket yang terkait dengan port 22.

---

## 9.5 Interpretasi

Jika OpenSSH Server listening pada port 22, output dapat menunjukkan kondisi seperti:

```text
LISTEN ... :22 ...
```

Hal ini memberikan bukti bahwa ada TCP socket listening pada port tersebut.

Untuk memastikan process yang terkait memang SSH, perhatikan informasi process dari output `ss -p`.

---

# 10. Memeriksa Alamat IP Server

## Command

```bash
hostname -I
```

Perhatikan bahwa option yang digunakan adalah:

```text
-I
```

huruf **I kapital**, bukan `-i`.

## Fungsi

Menampilkan alamat jaringan yang dikonfigurasi pada host.

## Struktur

```text
hostname      -I
    │          │
    │          └── tampilkan all IP addresses
    └── hostname utility
```

Ubuntu VM pada mode VirtualBox NAT sering memperoleh alamat seperti:

```text
10.0.2.x
```

Namun jangan mengasumsikan bahwa output hanya akan berisi satu alamat.

Sebuah mesin dapat memiliki lebih dari satu network interface atau alamat.

---

# 11. Mengapa Tidak Langsung Menggunakan IP NAT VM?

Pada praktik ini VirtualBox menggunakan mode:

```text
NAT
```

NAT memberi VM akses jaringan melalui network virtualization.

Namun jaringan guest NAT tidak diperlakukan sama seperti perangkat yang berada langsung pada LAN host.

Untuk membuat koneksi tertentu dari host menuju guest, praktik ini menggunakan:

```text
NAT Port Forwarding
```

---

# 12. VirtualBox NAT Port Forwarding

Konfigurasi yang digunakan:

| Field | Value |
|---|---|
| Name | SSH |
| Protocol | TCP |
| Host IP | `127.0.0.1` |
| Host Port | `2222` |
| Guest IP | Kosong atau IP VM sesuai konfigurasi |
| Guest Port | `22` |

Alurnya:

```text
Windows Host
127.0.0.1:2222
        │
        │ NAT Port Forwarding
        ▼
Ubuntu Guest
TCP Port 22
        │
        ▼
OpenSSH Server
```

---

# 13. Memahami `127.0.0.1`

Alamat:

```text
127.0.0.1
```

merupakan IPv4 loopback address.

Dalam konteks Windows host, alamat ini menunjuk kembali ke host itu sendiri.

Pada praktik ini:

```text
127.0.0.1:2222
```

berarti client Windows membuat koneksi ke port `2222` pada host Windows sendiri.

VirtualBox kemudian menerima koneksi tersebut berdasarkan rule port forwarding dan meneruskannya ke guest.

---

# 14. Mengapa Host Port `2222` dan Guest Port `22`?

OpenSSH Server pada Ubuntu tetap listening pada default SSH port:

```text
22
```

Namun pada sisi host digunakan:

```text
2222
```

Sehingga pemetaan menjadi:

```text
Host :2222
    ↓
VirtualBox NAT
    ↓
Guest :22
```

Host port tidak harus sama dengan guest port.

Dalam praktik ini port `2222` dipilih untuk membedakan endpoint pada host dari SSH port server di guest.

---

# 15. Memeriksa OpenSSH Client pada Windows

Buka PowerShell kemudian jalankan:

```powershell
ssh -V
```

Perhatikan bahwa option di sini menggunakan:

```text
-V
```

huruf V kapital.

## Struktur

```text
ssh      -V
 │        │
 │        └── tampilkan versi
 └── OpenSSH client
```

Jika OpenSSH Client tersedia, informasi versi akan tampil.

Jika command:

```text
ssh
```

tidak dikenali, OpenSSH Client pada Windows perlu diperiksa atau diaktifkan terlebih dahulu.

---

# 16. Melakukan Login dengan Password

## Command

```powershell
ssh -p 2222 vboxuser@127.0.0.1
```

Command ini meminta SSH client membuat koneksi ke:

```text
Host : 127.0.0.1
Port : 2222
User : vboxuser
```

---

# 17. Anatomy Command SSH

```text
ssh      -p      2222      vboxuser@127.0.0.1
 │        │        │                  │
 │        │        │                  ├── username: vboxuser
 │        │        │                  └── hostname/address: 127.0.0.1
 │        │        └── port tujuan
 │        └── option untuk menentukan port
 └── SSH client
```

---

## 17.1 `ssh`

Menjalankan OpenSSH client.

---

## 17.2 `-p`

Option:

```text
-p
```

digunakan untuk menentukan port remote yang akan dihubungi oleh SSH client.

Karena VirtualBox menerima koneksi host pada port:

```text
2222
```

maka digunakan:

```bash
-p 2222
```

Jika server dapat diakses langsung pada default port 22, option `-p 22` biasanya tidak perlu ditulis.

---

## 17.3 `vboxuser@127.0.0.1`

Format umum target SSH adalah:

```text
username@hostname
```

Pada praktik ini:

```text
vboxuser
```

adalah akun Ubuntu Server.

Sedangkan:

```text
127.0.0.1
```

adalah endpoint host yang digunakan untuk NAT port forwarding.

Jadi:

```text
vboxuser@127.0.0.1
```

dapat dibaca:

> Hubungkan sebagai user `vboxuser` ke host `127.0.0.1`.

---

# 18. Apa yang Terjadi Saat Command SSH Dijalankan?

Secara sederhana:

```text
Windows
OpenSSH Client
      │
      │ TCP connection
      ▼
127.0.0.1:2222
      │
      │ VirtualBox forwarding
      ▼
Ubuntu VM :22
      │
      ▼
sshd
      │
      ▼
Authentication
      │
      ▼
Remote Session
```

SSH tidak hanya membuka TCP connection.

Setelah koneksi terbentuk, protocol SSH melakukan tahapan seperti:

```text
Host identification
Key exchange
Encrypted session establishment
User authentication
Remote session
```

---

# 19. Host Key pada Koneksi Pertama

Pada koneksi pertama, client dapat menampilkan pesan seperti:

```text
The authenticity of host ... can't be established.
...
Are you sure you want to continue connecting?
```

SSH server memiliki **host key** yang digunakan untuk mengidentifikasi server.

Fingerprint host key sebaiknya diverifikasi terlebih dahulu jika sumber fingerprint tersedia.

Setelah host key diterima, identitas tersebut disimpan pada sisi client di file:

```text
known_hosts
```

Pada koneksi berikutnya, SSH dapat mendeteksi jika host key berubah.

---

# 20. Password Authentication

Setelah identitas server diterima, client dapat meminta:

```text
vboxuser@127.0.0.1's password:
```

Password yang diminta adalah password akun:

```text
vboxuser
```

pada Ubuntu Server.

Password tersebut **bukan password Windows** dan bukan password VirtualBox.

Jika autentikasi berhasil, prompt server muncul:

```text
vboxuser@BelajarSSH24:~$
```

Artinya terminal Windows sekarang memiliki remote shell session pada Ubuntu Server.

---

# 21. Memverifikasi Remote Session

Setelah login, beberapa command digunakan untuk memastikan terminal benar-benar menjalankan command pada Ubuntu Server.

---

## 21.1 `whoami`

```bash
whoami
```

### Fungsi

Menampilkan username efektif dari user yang sedang menjalankan session.

Contoh:

```text
vboxuser
```

Nama `whoami` dapat dibaca sebagai:

```text
who am I?
```

---

## 21.2 `hostname`

```bash
hostname
```

### Fungsi

Menampilkan hostname sistem.

Contoh:

```text
BelajarSSH24
```

Jika output menunjukkan hostname Ubuntu VM, hal ini membantu membuktikan bahwa command sedang dijalankan pada guest, bukan Windows host.

---

## 21.3 `uname -a`

```bash
uname -a
```

### Fungsi

Menampilkan informasi mengenai kernel dan sistem.

### Struktur

```text
uname      -a
  │         │
  │         └── all available information
  └── system information utility
```

Option:

```text
-a
```

berarti menampilkan sekumpulan informasi sistem yang tersedia.

Output biasanya memperlihatkan informasi kernel Linux.

---

## 21.4 `pwd`

```bash
pwd
```

`pwd` merupakan singkatan dari:

```text
print working directory
```

Command ini menampilkan current working directory.

Contoh:

```text
/home/vboxuser
```

---

# 22. Mengakhiri Remote Session

## Command

```bash
exit
```

## Fungsi

Keluar dari remote shell.

Alur:

```text
Ubuntu Remote Shell
       │
       │ exit
       ▼
SSH Session Ditutup
       │
       ▼
Windows PowerShell
```

Setelah `exit`, prompt Windows kembali muncul.

---

# 23. Alur Kerja Keseluruhan

```text
Ubuntu Server VM dibuat
        │
        ▼
Login lokal
        │
        ▼
OpenSSH Server diperiksa
        │
        ▼
Service ssh aktif
        │
        ▼
Port 22 listening
        │
        ▼
VirtualBox NAT Port Forwarding
Host 2222 → Guest 22
        │
        ▼
OpenSSH Client Windows diperiksa
        │
        ▼
ssh -p 2222 user@127.0.0.1
        │
        ▼
Host key verification
        │
        ▼
Password authentication
        │
        ▼
Remote shell Ubuntu
        │
        ▼
Verifikasi whoami / hostname / uname / pwd
        │
        ▼
exit
```

---

# 24. Troubleshooting

## `Connection refused`

Periksa apakah SSH berjalan:

```bash
sudo systemctl status ssh
```

Periksa listening port:

```bash
sudo ss -tlnp | grep ':22'
```

Jika service belum berjalan:

```bash
sudo systemctl enable --now ssh
```

---

## `Connection timed out`

Periksa:

```text
VM menyala
Network Adapter menggunakan konfigurasi yang benar
NAT Port Forwarding tersedia
Host Port = 2222
Guest Port = 22
```

---

## `Permission denied`

Pastikan:

```text
username benar
password akun Ubuntu benar
```

Contoh target:

```text
vboxuser@127.0.0.1
```

berarti SSH mencoba login ke akun Ubuntu bernama:

```text
vboxuser
```

---

## `ssh` Tidak Dikenali pada Windows

Periksa:

```powershell
ssh -V
```

Jika command tidak tersedia, periksa instalasi Windows OpenSSH Client.

---

## Host Key Berubah

Jika SSH memberi peringatan bahwa remote host identification berubah, jangan langsung menghapus entry lama.

Pastikan terlebih dahulu apakah server memang berubah, misalnya:

```text
VM dibuat ulang
OpenSSH host key diregenerate
Server diganti
```

Perubahan host key yang tidak diharapkan juga dapat menunjukkan masalah keamanan.

---

# 25. Security Notes

SSH menyediakan encrypted communication, tetapi konfigurasi dan identitas endpoint tetap perlu diperhatikan.

Hal yang perlu dilakukan:

```text
Verifikasi host fingerprint ketika memungkinkan
Jangan membagikan password
Jangan menyimpan credential di repository
Pastikan service yang diekspos memang diperlukan
Gunakan autentikasi public key untuk penggunaan lanjutan
```

Port forwarding:

```text
127.0.0.1:2222 → guest:22
```

pada praktik ini membuat endpoint host dibind ke loopback address, sehingga ditujukan untuk akses dari host lokal.

---

# 26. Kesimpulan

Ubuntu Server 24.04 LTS berhasil disiapkan sebagai SSH server menggunakan OpenSSH Server.

Windows bertindak sebagai SSH client dan terhubung melalui:

```text
Windows OpenSSH Client
        │
        │ 127.0.0.1:2222
        ▼
VirtualBox NAT Port Forwarding
        │
        │ Guest :22
        ▼
Ubuntu OpenSSH Server
```

Command utama pada tahap ini adalah:

```bash
dpkg -l | grep openssh-server
sudo systemctl status ssh
sudo systemctl enable --now ssh
sudo ss -tlnp | grep ':22'
hostname -I
ssh -V
ssh -p 2222 vboxuser@127.0.0.1
whoami
hostname
uname -a
pwd
exit
```

Setiap command memiliki fungsi berbeda dalam memeriksa package, service, network socket, network address, SSH client, koneksi, dan identitas remote system.