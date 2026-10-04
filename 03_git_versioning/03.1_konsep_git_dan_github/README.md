# 03.1 Konsep Git dan GitHub

## 1. Tujuan

Bagian ini membahas konsep dasar Git, GitHub, status file, staging area, commit, branch, remote repository, dan hubungan antara local repository dengan remote repository.

## 2. Git

Git adalah **distributed version control system** yang digunakan untuk mencatat perubahan file dari waktu ke waktu.

Setiap perubahan dapat disimpan sebagai **commit**, sehingga riwayat project dapat ditelusuri kembali.

Contoh sederhana:

```text
Commit A
   │
   ▼
Commit B
   │
   ▼
Commit C
```

Setiap commit merepresentasikan kondisi project pada suatu titik waktu.

## 3. GitHub

GitHub adalah layanan yang dapat digunakan untuk menyimpan Git repository secara remote.

Secara sederhana:

```text
Git
=
Version control system

GitHub
=
Hosting service untuk Git repository
```

Git dapat digunakan tanpa GitHub.

GitHub digunakan ketika repository lokal ingin disimpan, dibagikan, disinkronkan, atau digunakan bersama melalui jaringan.

## 4. Working Directory

Working directory adalah folder tempat file project sedang dikerjakan.

Contoh:

```text
project/
├── README.md
├── src/
└── main.cpp
```

Perubahan pada file pertama kali terjadi di working directory.

## 5. Status File pada Git

### Untracked

File terdapat dalam folder project, tetapi belum pernah dicatat oleh Git.

```text
Untracked
```

Contoh:

```bash
git status
```

dapat menampilkan:

```text
Untracked files:
    hello.py
```

### Tracked

File sudah dikenal dan dipantau oleh Git.

### Modified

File tracked telah mengalami perubahan sejak commit terakhir.

```text
Tracked
   │
   └── Modified
```

### Staged

Perubahan pada file telah dimasukkan ke **staging area** menggunakan:

```bash
git add
```

### Committed

Perubahan yang sudah staged disimpan sebagai commit di local repository.

```bash
git commit
```

## 6. Staging Area

Staging area merupakan area persiapan untuk menentukan perubahan apa saja yang akan masuk ke commit berikutnya.

Workflow:

```text
Working Directory
       │
       │ git add
       ▼
Staging Area
       │
       │ git commit
       ▼
Local Repository
```

Perintah:

```bash
git add file.txt
```

menambahkan isi atau perubahan file pada saat command dijalankan ke index atau staging area.

File tetap berada pada working directory.

## 7. Commit

Commit merupakan snapshot perubahan yang telah berada pada staging area.

Contoh:

```bash
git commit -m "Add initial program"
```

Commit memiliki informasi seperti:

```text
Commit hash
Author
Date
Commit message
Snapshot perubahan
```

Riwayat commit dapat dilihat menggunakan:

```bash
git log
```

atau:

```bash
git log --oneline
```

## 8. HEAD

`HEAD` merupakan referensi yang menunjukkan posisi aktif pada repository.

Dalam kondisi normal:

```text
A --- B --- C
          ↑
        main
        HEAD
```

Artinya:

```text
HEAD
↓
main
↓
commit terbaru
```

## 9. Branch

Branch merupakan jalur pengembangan dalam Git.

Branch utama pada repository ini digunakan dengan nama:

```text
main
```

Contoh:

```text
A --- B --- C
          ↑
        main
```

Branch memungkinkan pengembangan dilakukan tanpa langsung mengubah jalur utama.

Pembahasan branching lanjutan tidak menjadi fokus utama pada Technical Notes ini.

## 10. Local Repository

Local repository berada pada komputer pengguna.

Setelah menjalankan:

```bash
git init
```

Git membuat direktori internal:

```text
.git/
```

Direktori tersebut menyimpan metadata dan riwayat Git.

Folder `.git` tidak perlu diubah secara manual.

## 11. Remote Repository

Remote repository merupakan Git repository yang berada pada lokasi lain, misalnya GitHub.

Contoh:

```text
Local Repository
       │
       │ git push
       ▼
GitHub Repository
```

Remote umumnya diberi nama:

```text
origin
```

## 12. `origin` dan `origin/main`

`origin` merupakan nama remote.

Contoh:

```bash
git remote -v
```

dapat menampilkan:

```text
origin  git@github.com:username/project.git
```

Sedangkan:

```text
origin/main
```

merupakan **remote-tracking branch** yang merepresentasikan kondisi branch `main` pada remote `origin` yang diketahui oleh local repository.

Secara sederhana:

```text
origin
=
nama remote

origin/main
=
representasi branch main pada remote origin
```

## 13. Push

`git push` digunakan untuk mengirim commit dari local repository ke remote repository.

```text
Local Commit
     │
     │ git push
     ▼
GitHub
```

`git push` tidak mengirim file langsung dari staging area.

Commit harus dibuat terlebih dahulu.

## 14. Pull

`git pull` digunakan untuk mengambil perubahan dari remote repository dan mengintegrasikannya ke repository lokal.

Secara umum:

```text
Remote Repository
       │
       │ git pull
       ▼
Local Repository
```

## 15. Clone

`git clone` digunakan untuk membuat salinan local repository dari remote repository beserta riwayat Git-nya.

Contoh:

```bash
git clone <repository-url>
```

Berbeda dengan membuat folder baru dan menjalankan `git init`, clone mengambil repository yang sudah ada.

## 16. `git diff`

Untuk melihat perubahan pada working directory yang belum masuk staging area:

```bash
git diff
```

Hubungannya:

```text
Working Directory
       ↕
    git diff
       ↕
Staging Area
```

Untuk melihat perubahan yang sudah staged tetapi belum menjadi commit:

```bash
git diff --staged
```

atau:

```bash
git diff --cached
```

Hubungannya:

```text
Staging Area
       ↕
git diff --staged
       ↕
Last Commit
```

## 17. `.gitignore`

File `.gitignore` digunakan untuk menentukan file atau direktori yang tidak ingin dicatat Git.

Contoh:

```gitignore
.pio/
.vscode/
*.tmp
.env
```

Contoh struktur:

```text
project/
├── .gitignore
├── README.md
├── src/
└── .pio/          ← ignored
```

`gitignore` tidak otomatis menghentikan tracking terhadap file yang sudah terlanjur tracked.

## 18. Basic Restore

Untuk membatalkan perubahan pada working directory yang belum staged:

```bash
git restore file.txt
```

Untuk mengeluarkan perubahan dari staging area tanpa membuang perubahan pada working directory:

```bash
git restore --staged file.txt
```

Gunakan command tersebut dengan hati-hati dan selalu periksa:

```bash
git status
```

sebelum melakukan perubahan pada state repository.

## 19. Ringkasan Workflow

```text
Create / Modify File
        │
        ▼
Working Directory
        │
        │ git add
        ▼
Staging Area
        │
        │ git commit
        ▼
Local Repository
        │
        │ git push
        ▼
Remote Repository
        │
        └── GitHub
```

## 20. Kesimpulan

Git digunakan untuk mencatat dan mengelola perubahan pada project.

Konsep utama yang perlu dipahami adalah:

```text
Working Directory
Staging Area
Commit
Local Repository
Remote Repository
```

GitHub berfungsi sebagai remote repository, sedangkan Git tetap mengelola riwayat project pada komputer lokal.