# 02.1 Konsep Client-Server pada SSH

## 1. Tujuan

Bagian ini membahas konsep dasar **Secure Shell (SSH)**, arsitektur client-server, OpenSSH, serta mekanisme autentikasi yang digunakan dalam remote login.

## 2. SSH dan Remote Login

SSH (**Secure Shell**) adalah protokol jaringan yang digunakan untuk mengakses sistem lain dari jarak jauh melalui koneksi terenkripsi.

Dengan SSH, pengguna dapat memperoleh shell pada komputer remote dan menjalankan perintah seolah-olah sedang bekerja langsung pada sistem tersebut.

Secara umum, komunikasi SSH terdiri dari:

```text
SSH Client
    │
    │ Encrypted SSH Connection
    ▼
SSH Server
```

## 3. Konsep Client-Server

Dalam arsitektur SSH terdapat dua pihak utama:

### SSH Client

SSH client merupakan perangkat atau aplikasi yang **memulai koneksi** ke sistem remote.

Pada implementasi ini:

```text
Windows
└── OpenSSH Client
    └── PowerShell / Windows Terminal
```

Windows digunakan untuk menjalankan perintah seperti:

```powershell
ssh
ssh-keygen
```

### SSH Server

SSH server merupakan perangkat yang **menerima koneksi SSH** dan menyediakan layanan remote login.

Pada implementasi ini:

```text
Ubuntu Server 24.04 LTS
└── OpenSSH Server
    └── sshd
```

Service `sshd` menerima koneksi SSH dari client.

## 4. Arsitektur Sistem

Implementasi dilakukan menggunakan satu laptop fisik.

```text
Laptop Fisik
│
├── Windows
│   │
│   └── OpenSSH Client
│
└── Oracle VirtualBox
    │
    └── Ubuntu Server 24.04 LTS
        │
        └── OpenSSH Server (sshd)
```

Windows berperan sebagai client, sedangkan Ubuntu Server yang berjalan di dalam VirtualBox berperan sebagai server.

Walaupun berada pada satu laptop yang sama, Windows dan Ubuntu Server merupakan dua sistem operasi berbeda dan berkomunikasi melalui jaringan virtual.

## 5. OpenSSH

OpenSSH merupakan implementasi SSH yang menyediakan berbagai program untuk kebutuhan remote communication.

Beberapa komponen yang digunakan pada praktik ini adalah:

| Program | Fungsi |
|---|---|
| `ssh` | Membuat koneksi SSH dari client |
| `ssh-keygen` | Membuat pasangan public-private key |
| `sshd` | SSH daemon yang menerima koneksi pada server |

Pada Ubuntu Server, layanan SSH tersedia melalui package:

```bash
openssh-server
```

## 6. Password Authentication

Pada password authentication, client melakukan login menggunakan:

```text
Username
+
Password akun server
```

Contoh:

```powershell
ssh username@server
```

Server kemudian memverifikasi username dan password sebelum memberikan akses shell.

Password authentication digunakan terlebih dahulu pada praktik ini untuk memastikan:

- SSH server dapat diakses.
- Network configuration sudah benar.
- Username server benar.
- Password akun server benar.

## 7. Key-Based Authentication

Selain password, SSH mendukung autentikasi menggunakan pasangan cryptographic key.

Pasangan tersebut terdiri dari:

```text
Private Key
+
Public Key
```

### Private Key

Private key disimpan pada sisi client.

```text
Client
└── Private Key
```

Private key:

- Tidak boleh dibagikan.
- Tidak dikirim ke server.
- Tidak boleh dimasukkan ke GitHub repository.
- Sebaiknya dilindungi menggunakan passphrase pada penggunaan nyata.

### Public Key

Public key dapat dipindahkan ke server.

Pada server, public key client yang diperbolehkan melakukan login disimpan pada:

```bash
~/.ssh/authorized_keys
```

Alur sederhananya:

```text
Windows Client
│
├── Private Key
│
└── Public Key
        │
        ▼
Ubuntu Server
└── ~/.ssh/authorized_keys
```

Ketika client melakukan koneksi, server memverifikasi apakah client memiliki private key yang sesuai dengan public key yang tersimpan pada `authorized_keys`.

## 8. `authorized_keys`

File:

```bash
~/.ssh/authorized_keys
```

berada pada **server**.

File ini berisi public key dari client yang diperbolehkan melakukan login menggunakan key-based authentication.

Permission yang umum digunakan adalah:

```bash
chmod 700 ~/.ssh
chmod 600 ~/.ssh/authorized_keys
```

## 9. `known_hosts`

File `known_hosts` berada pada sisi **client**.

File ini menyimpan identitas SSH host/server yang pernah dihubungi.

Secara konsep:

```text
Client
├── Private Key
└── known_hosts

Server
└── authorized_keys
```

`known_hosts` dan `authorized_keys` memiliki fungsi yang berbeda dan tidak boleh tertukar.

## 10. SSH Port

Secara default, SSH server menggunakan:

```text
TCP Port 22
```

Pada implementasi menggunakan VirtualBox NAT, port pada host dapat berbeda karena menggunakan port forwarding.

Contoh:

```text
Windows Host
127.0.0.1:2222
      │
      │ NAT Port Forwarding
      ▼
Ubuntu VM
TCP Port 22
```

Dengan demikian, port `2222` digunakan pada sisi Windows, sedangkan OpenSSH Server pada Ubuntu tetap menerima koneksi melalui port `22`.

## 11. Kesimpulan

SSH menggunakan arsitektur client-server untuk menyediakan remote login melalui koneksi terenkripsi.

Pada implementasi ini:

- Windows bertindak sebagai SSH client.
- Ubuntu Server 24.04 LTS bertindak sebagai SSH server.
- OpenSSH menyediakan program client `ssh` serta server daemon `sshd`.
- Password authentication digunakan untuk pengujian koneksi awal.
- Key-based authentication menggunakan public-private key pair.
- Private key tetap berada pada client.
- Public key disimpan pada `~/.ssh/authorized_keys` di server.