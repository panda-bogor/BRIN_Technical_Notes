# 02 Remote SSH

Technical Notes ini mendokumentasikan implementasi **Remote SSH** menggunakan Windows sebagai SSH client dan Ubuntu Server 24.04 LTS pada Oracle VirtualBox sebagai SSH server.

## Environment

| Komponen         | Keterangan                  |
|------------------|-----------------------------|
|  Host            |   Windows                   | 
| SSH Client       | OpenSSH Client / PowerShell |
| Virtualization   |           Oracle VirtualBox |
| SSH Server       |     Ubuntu Server 24.04 LTS |
| SSH Service      |     OpenSSH Server (`sshd`) |
| Default SSH Port |                      TCP 22 |

## Learning Objectives

Setelah menyelesaikan bagian ini, diharapkan dapat:

- Memahami konsep SSH sebagai mekanisme remote login.
- Memahami arsitektur client-server pada SSH.
- Menyiapkan Ubuntu Server sebagai SSH server.
- Menggunakan Windows sebagai SSH client.
- Melakukan koneksi SSH menggunakan username dan password.
- Membuat pasangan public-private key menggunakan `ssh-keygen`.
- Mengimplementasikan key-based authentication.
- Melakukan remote login tanpa memasukkan password akun server.
- Membuat SSH alias untuk menyederhanakan perintah koneksi.

## System Overview

Implementasi menggunakan satu laptop fisik yang menjalankan dua lingkungan sistem operasi.

```text
Laptop Fisik
│
├── Windows
│   └── OpenSSH Client / PowerShell
│
└── Oracle VirtualBox
    └── Ubuntu Server 24.04 LTS
        └── OpenSSH Server (sshd)
```

Walaupun client dan server berada pada laptop fisik yang sama, keduanya tetap merupakan dua sistem operasi berbeda yang berkomunikasi melalui jaringan virtual VirtualBox.

## Topics

1. [02.1 Konsep Client-Server](./02.1_Konsep_Client_Server/)
2. [02.2 Instalasi dan Koneksi](./02.2_Instalasi_dan_Koneksi/)
3. [02.3 SSH Key Login](./02.3_SSH_Key_Login/)

## General Workflow

```text
Ubuntu Server VM
      ↓
OpenSSH Server
      ↓
Port 22 aktif
      ↓
VirtualBox NAT Port Forwarding
2222 → 22
      ↓
Windows OpenSSH Client
      ↓
Password Authentication
      ↓
SSH Key Generation
      ↓
Public Key → authorized_keys
      ↓
Key-Based Authentication
      ↓
SSH Alias
```

## Security Notes

- Private key tidak boleh dibagikan atau dimasukkan ke repository.
- Public key dapat disimpan pada server.
- Jangan menonaktifkan password authentication sebelum key-based authentication telah berhasil diuji.
- Pada koneksi ke server nyata, host fingerprint sebaiknya diverifikasi sebelum menerima host key.

link TN Remote SSH: https://docs.google.com/document/d/1vjV_cBtdJ3h0RezJ2DhKTvkMXl71VHVM/edit?usp=drive_link&ouid=117361866800692097676&rtpof=true&sd=true

