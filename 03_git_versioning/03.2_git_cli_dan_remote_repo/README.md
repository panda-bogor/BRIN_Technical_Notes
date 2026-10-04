# 03.2 Git CLI dan Remote Repository

## 1. Tujuan

Bagian ini membahas penggunaan Git melalui **Command Line Interface (CLI)** mulai dari memeriksa instalasi Git, membuat local repository, memahami staging area dan commit, hingga menghubungkan repository lokal dengan GitHub sebagai remote repository.

Setiap command dijelaskan berdasarkan:

- fungsi;
- struktur command;
- arti argument atau option;
- perubahan yang terjadi pada repository;
- hubungan command dengan Git workflow.

---

# 2. Struktur Dasar Command Git

Secara umum command Git memiliki bentuk:

```text
git <subcommand> [options] [arguments]
```

Contoh:

```bash
git commit -m "Add README"
```

Strukturnya:

```text
git      commit      -m      "Add README"
│           │         │            │
│           │         │            └── argument / nilai
│           │         └── option
│           └── subcommand
└── executable Git
```

### `git`

`git` adalah executable atau program utama yang dijalankan.

### Subcommand

Subcommand menentukan operasi yang dilakukan.

Contoh:

```text
status
add
commit
push
pull
clone
```

### Option

Option mengubah atau menambahkan perilaku command.

Contoh:

```text
--global
--staged
--oneline
-u
-v
```

Option panjang biasanya menggunakan dua tanda minus:

```text
--global
```

sedangkan bentuk pendek biasanya menggunakan satu tanda minus:

```text
-v
```

---

# 3. Memeriksa Instalasi Git

## Command

```bash
git --version
```

## Fungsi

Memeriksa apakah Git telah terpasang dan dapat ditemukan oleh sistem operasi.

## Struktur

```text
git        --version
│              │
│              └── tampilkan versi Git
└── executable Git
```

Contoh output:

```text
git version 2.x.x.windows.x
```

Jika nomor versi muncul, Git dapat dijalankan dari terminal.

Jika command tidak dikenali, kemungkinan:

- Git belum terpasang; atau
- lokasi executable Git belum tersedia pada `PATH`.

---

# 4. Mengatur Identitas Commit

Git menyimpan informasi author pada setiap commit.

## Mengatur Nama

```bash
git config --global user.name "YOUR_NAME"
```

## Mengatur Email

```bash
git config --global user.email "YOUR_EMAIL_OR_GITHUB_NOREPLY"
```

## Struktur

```text
git   config   --global   user.name   "YOUR_NAME"
│       │          │          │             │
│       │          │          │             └── nilai
│       │          │          └── configuration key
│       │          └── scope konfigurasi
│       └── mengelola konfigurasi Git
└── executable Git
```

### `config`

`config` berasal dari **configuration**.

Git menyimpan konfigurasi dalam bentuk pasangan:

```text
key = value
```

Contoh:

```text
user.name = YOUR_NAME
```

### `--global`

`--global` membuat konfigurasi menjadi default untuk repository yang digunakan oleh user tersebut pada komputer.

Tanpa `--global`, konfigurasi dapat dibuat khusus pada repository tertentu.

### `user.name`

Menentukan nama author pada commit.

### `user.email`

Menentukan email author pada commit.

`user.email` **bukan password dan bukan mekanisme login GitHub**.

Untuk memeriksa konfigurasi:

```bash
git config --global user.name
git config --global user.email
```

atau:

```bash
git config --global --list
```

---

# 5. Membuat Local Repository

## Command

```bash
git init
```

## Fungsi

Menginisialisasi sebuah direktori sebagai Git repository.

`init` berasal dari kata:

```text
initialize
```

## Sebelum `git init`

```text
project/
├── README.md
└── hello.py
```

Folder tersebut hanya merupakan folder biasa.

## Setelah `git init`

```text
project/
├── .git/
├── README.md
└── hello.py
```

Git membuat direktori internal:

```text
.git/
```

Direktori `.git` menyimpan metadata repository, object database, references, konfigurasi lokal, dan informasi lain yang digunakan oleh Git.

Karena adanya `.git/`, folder tersebut dapat dikenali sebagai Git repository.

> Jangan mengubah isi `.git/` secara manual pada penggunaan normal.

---

# 6. Menentukan Nama Branch Utama

## Command

```bash
git branch -M main
```

## Fungsi

Mengubah nama branch yang sedang aktif menjadi:

```text
main
```

## Struktur

```text
git      branch      -M      main
│           │         │        │
│           │         │        └── nama branch baru
│           │         └── rename branch dengan force
│           └── operasi branch
└── Git
```

### `branch`

Digunakan untuk operasi yang berkaitan dengan branch.

### `-M`

`-M` merupakan bentuk rename branch dengan kemampuan menggantikan nama tujuan jika diperlukan.

Pada latihan ini digunakan untuk memastikan branch utama bernama:

```text
main
```

---

# 7. Memeriksa Kondisi Repository

## Command

```bash
git status
```

## Fungsi

Menampilkan kondisi working tree dan staging area.

`status` berarti keadaan atau kondisi repository.

Command ini dapat menunjukkan:

```text
Untracked files
Modified files
Changes not staged for commit
Changes to be committed
Branch information
Working tree clean
```

Contoh kondisi awal:

```text
On branch main

No commits yet

nothing to commit
```

`git status` merupakan command yang aman dan berguna untuk dijalankan sebelum melakukan operasi Git lainnya.

---

# 8. Status File dalam Git

File dapat berada dalam beberapa kondisi.

## Untracked

File berada di working directory tetapi belum dikenal Git sebagai file yang dicatat.

```text
hello.py
↓
Untracked
```

## Tracked

File sudah pernah dicatat Git.

## Modified

File tracked telah berubah sejak snapshot terakhir.

```text
Tracked
   │
   └── Modified
```

## Staged

Isi/perubahan file telah dimasukkan ke **Git index**, yang juga disebut staging area.

## Committed

Snapshot staged changes sudah disimpan ke local repository.

---

# 9. Menambahkan Perubahan ke Staging Area

## Command

```bash
git add hello.py
```

## Fungsi

Menambahkan **isi file pada kondisi saat command dijalankan** ke Git index atau staging area.

## Struktur

```text
git      add      hello.py
│         │           │
│         │           └── path/file yang dipilih
│         └── menambahkan content ke index
└── Git
```

Git tidak memindahkan file secara fisik.

File tetap berada di:

```text
Working Directory
```

sedangkan versi kontennya dicatat ke:

```text
Index / Staging Area
```

Alurnya:

```text
Working Directory
       │
       │ git add
       ▼
Staging Area / Index
```

### Contoh Satu File

```bash
git add README.md
```

### Contoh Direktori

```bash
git add src/
```

### Semua Perubahan pada Path Saat Ini

```bash
git add .
```

Sebelum menjalankan:

```bash
git add .
```

sebaiknya periksa:

```bash
git status
```

agar file sensitif atau file sementara tidak ikut masuk staging area.

---

# 10. Mengapa Stage dan Commit Dipisahkan?

Git tidak langsung membuat commit ketika file disimpan.

Contoh:

```text
Edit file
   ↓
Save
   ↓
Working Directory
```

Kemudian pengguna memilih perubahan yang ingin masuk ke commit:

```text
Working Directory
   ↓
git add
   ↓
Staging Area
```

Baru setelah itu:

```text
Staging Area
   ↓
git commit
   ↓
Local Repository
```

Pemisahan ini memungkinkan satu working directory memiliki banyak perubahan, tetapi hanya perubahan tertentu yang dimasukkan ke commit tertentu.

---

# 11. Melihat Perubahan Belum Staged

## Command

```bash
git diff
```

## Fungsi

Menampilkan perbedaan antara working tree dengan versi yang saat ini berada pada index/staging area.

Secara sederhana:

```text
Working Directory
       ↕
    git diff
       ↕
Staging Area
```

Command ini berguna sebelum `git add` untuk memeriksa perubahan yang baru dilakukan.

---

# 12. Melihat Perubahan yang Sudah Staged

## Command

```bash
git diff --staged
```

Alternatif:

```bash
git diff --cached
```

## Fungsi

Menampilkan staged changes dibandingkan dengan snapshot dasar commit yang relevan.

Secara sederhana:

```text
Last Commit
       ↕
git diff --staged
       ↕
Staging Area
```

## Struktur

```text
git      diff      --staged
│         │             │
│         │             └── lihat staged changes
│         └── tampilkan difference
└── Git
```

Command ini berguna untuk memeriksa **apa yang benar-benar akan dimasukkan ke commit**.

---

# 13. Membuat Commit

## Command

```bash
git commit -m "Add initial program"
```

## Fungsi

Mencatat staged snapshot ke local Git repository.

## Struktur

```text
git      commit      -m      "Add initial program"
│           │         │               │
│           │         │               └── commit message
│           │         └── message option
│           └── membuat commit
└── Git
```

### `commit`

Digunakan untuk mencatat snapshot perubahan.

### `-m`

`-m` berarti:

```text
message
```

Dengan demikian:

```bash
git commit -m "Add initial program"
```

dapat dibaca sebagai:

> Buat commit dengan message "Add initial program".

Commit menyimpan informasi seperti:

```text
Commit identifier/hash
Author
Timestamp
Parent commit
Commit message
Snapshot
```

---

# 14. Melihat Riwayat Commit

## Command

```bash
git log
```

Menampilkan riwayat commit.

Untuk tampilan lebih ringkas:

```bash
git log --oneline
```

## Struktur

```text
git      log      --oneline
│         │            │
│         │            └── satu baris per commit
│         └── melihat history
└── Git
```

Contoh:

```text
f4c4cf3 Update program to version 2
b0b992b Add initial program
```

Bagian seperti:

```text
f4c4cf3
```

merupakan abbreviated commit hash.

Bagian:

```text
Update program to version 2
```

merupakan commit message.

---

# 15. HEAD

`HEAD` menunjukkan posisi yang sedang aktif dalam repository.

Contoh:

```text
A --- B --- C
          ↑
         main
         HEAD
```

Pada kondisi tersebut:

```text
HEAD
↓
main
↓
Commit C
```

Artinya branch aktif adalah `main`, dan `main` sedang menunjuk ke Commit C.

---

# 16. Local dan Remote Repository

Git repository pada komputer disebut:

```text
Local Repository
```

Repository lain yang dihubungkan melalui suatu nama disebut:

```text
Remote Repository
```

Contoh:

```text
Local Repository
        │
        │ network
        ▼
GitHub Repository
```

GitHub merupakan layanan hosting Git repository.

Git dan GitHub bukan hal yang sama.

---

# 17. Remote

Git menggunakan nama **remote** sebagai referensi bernama menuju repository lain.

Contoh remote yang umum:

```text
origin
```

`origin` bukan nama khusus yang diwajibkan oleh GitHub.

`origin` hanyalah nama konvensional yang umum diberikan pada remote utama.

---

# 18. Menambahkan Remote

## Command

```bash
git remote add origin git@github.com:USERNAME/REPOSITORY.git
```

## Fungsi

Menambahkan remote baru bernama `origin`.

## Struktur

```text
git   remote   add   origin   git@github.com:USERNAME/REPOSITORY.git
│       │       │      │                      │
│       │       │      │                      └── remote URL
│       │       │      └── nama remote
│       │       └── tambah remote
│       └── operasi remote
└── Git
```

Setelah command ini, Git mengetahui bahwa:

```text
origin
```

mengacu ke:

```text
git@github.com:USERNAME/REPOSITORY.git
```

Namun menambahkan remote **belum mengirim commit apa pun**.

---

# 19. Memeriksa Remote

## Command

```bash
git remote -v
```

## Fungsi

Menampilkan remote beserta URL yang digunakan.

## Struktur

```text
git      remote      -v
│          │          │
│          │          └── verbose
│          └── operasi remote
└── Git
```

`-v` merupakan singkatan dari:

```text
verbose
```

Contoh:

```text
origin  git@github.com:USERNAME/project.git (fetch)
origin  git@github.com:USERNAME/project.git (push)
```

### Fetch URL

Digunakan saat mengambil informasi dari remote.

### Push URL

Digunakan saat mengirim update ke remote.

Pada konfigurasi sederhana, keduanya biasanya menggunakan URL yang sama.

---

# 20. Mengubah URL Remote

Jika `origin` sudah ada tetapi URL salah, gunakan:

```bash
git remote set-url origin git@github.com:USERNAME/REPOSITORY.git
```

Jangan menjalankan:

```bash
git remote add origin ...
```

lagi jika remote bernama `origin` sudah ada.

Periksa setelah perubahan:

```bash
git remote -v
```

---

# 21. Autentikasi GitHub Menggunakan SSH

Jika remote menggunakan format:

```text
git@github.com:USERNAME/REPOSITORY.git
```

Git menggunakan koneksi SSH.

Sebelum itu, SSH key harus sudah dikonfigurasi dan public key telah ditambahkan ke akun GitHub.

Private key tetap berada pada client.

```text
Client
├── Private Key
│
└── Public Key
        │
        ▼
      GitHub
```

Private key tidak boleh dimasukkan ke repository.

---

# 22. Menguji SSH ke GitHub

## Command

```bash
ssh -T git@github.com
```

## Struktur

```text
ssh      -T      git@github.com
│         │            │
│         │            └── user dan host tujuan
│         └── tidak meminta pseudo-terminal
└── SSH client
```

### `ssh`

Program SSH client.

### `git@github.com`

Pada koneksi GitHub SSH:

```text
git
```

merupakan user SSH yang digunakan GitHub.

```text
github.com
```

merupakan host.

### `-T`

Meminta SSH tidak mengalokasikan pseudo-terminal.

GitHub menggunakan koneksi ini untuk autentikasi Git, bukan untuk menyediakan interactive shell.

Pada koneksi pertama, SSH dapat menunjukkan host fingerprint.

Fingerprint harus diverifikasi terhadap fingerprint resmi GitHub sebelum menerima host key.

Jika autentikasi berhasil, GitHub akan mengidentifikasi akun yang terhubung tetapi tidak menyediakan shell access.

---

# 23. Push Pertama

## Command

```bash
git push -u origin main
```

## Fungsi

Mengirim branch lokal `main` ke remote `origin` sekaligus mengatur upstream branch.

## Struktur

```text
git      push      -u      origin      main
│         │         │         │          │
│         │         │         │          └── branch lokal
│         │         │         └── remote tujuan
│         │         └── set upstream
│         └── kirim update
└── Git
```

### `push`

Mengirim commit/reference dari local repository menuju remote repository.

```text
Local Repository
       │
       │ push
       ▼
Remote Repository
```

### `origin`

Nama remote tujuan.

### `main`

Nama branch yang dikirim.

Sehingga:

```bash
git push origin main
```

secara sederhana berarti:

> Push branch `main` ke remote `origin`.

### `-u`

`-u` merupakan bentuk pendek dari:

```text
--set-upstream
```

Upstream merupakan remote branch yang diasosiasikan dengan local branch.

Setelah:

```bash
git push -u origin main
```

hubungan umumnya menjadi:

```text
Local:
main
 │
 │ upstream
 ▼
origin/main
```

Setelah upstream tersedia, push berikutnya biasanya cukup:

```bash
git push
```

---

# 24. `origin` dan `origin/main`

Keduanya berbeda.

## `origin`

Nama remote.

```text
origin
↓
GitHub repository
```

## `origin/main`

Remote-tracking branch.

```text
origin/main
```

merupakan referensi lokal yang merepresentasikan kondisi branch `main` pada remote `origin` yang terakhir diketahui Git.

Jadi:

```text
origin
≠
origin/main
```

---

# 25. Memeriksa Branch dan Upstream

## Command

```bash
git branch -vv
```

## Fungsi

Menampilkan informasi branch secara lebih detail, termasuk upstream jika tersedia.

Contoh:

```text
* main f4c4cf3 [origin/main] Update documentation
```

Artinya:

```text
*
→ branch aktif

main
→ nama local branch

f4c4cf3
→ commit yang sedang ditunjuk

[origin/main]
→ upstream

Update documentation
→ commit message terbaru
```

---

# 26. Push Berikutnya

Setelah upstream tersedia:

```bash
git push
```

tidak perlu lagi selalu menuliskan:

```bash
git push -u origin main
```

karena Git sudah memiliki tracking information untuk branch tersebut.

---

# 27. Clone

## Command

```bash
git clone <repository-url>
```

## Fungsi

Membuat local repository dari repository yang sudah ada.

`clone` bukan sekadar menyalin file terbaru.

Clone mengambil repository beserta data Git yang diperlukan, termasuk history dan references.

Secara default, remote sumber biasanya diberi nama:

```text
origin
```

Alurnya:

```text
Remote Repository
       │
       │ git clone
       ▼
Local Repository Baru
```

Jika project sudah ada di GitHub dan ingin digunakan pada komputer baru, gunakan `clone` daripada membuat repository baru dengan `git init`.

---

# 28. Fetch

## Command

```bash
git fetch
```

## Fungsi

Mengambil data baru dari remote repository dan memperbarui remote-tracking references tanpa langsung mengintegrasikannya ke current branch.

Secara sederhana:

```text
GitHub
  │
  │ git fetch
  ▼
origin/main diperbarui

local main
tetap tidak otomatis berubah
```

Fetch berguna untuk mengetahui perkembangan remote sebelum melakukan integrasi.

---

# 29. Pull

## Command

```bash
git pull
```

## Fungsi

Mengambil perubahan dari remote lalu mengintegrasikan perubahan tersebut ke current branch.

Secara konsep:

```text
git pull
   │
   ├── fetch
   │
   └── integrate
```

Metode integrasi dapat menggunakan merge atau rebase bergantung pada konfigurasi dan option yang digunakan.

Sebelum pull, periksa:

```bash
git status
```

terutama jika working directory memiliki perubahan yang belum selesai.

---

# 30. Restore

## Membatalkan Perubahan Unstaged

```bash
git restore hello.py
```

Pada penggunaan dasar, command ini mengembalikan working-tree file dari index.

Akibatnya, perubahan unstaged pada file dapat hilang.

Gunakan dengan hati-hati.

---

## Mengeluarkan File dari Staging

```bash
git restore --staged hello.py
```

Command ini mengubah staging area tanpa membuang perubahan pada working directory.

Sebelum:

```text
Working Directory
        +
Staging Area
```

Setelah:

```text
Working Directory
        │
        └── perubahan tetap ada

Staging Area
        └── perubahan dikeluarkan
```

---

# 31. `.gitignore`

`.gitignore` berisi pola file atau direktori yang seharusnya tidak ditambahkan ke Git secara normal.

Contoh:

```gitignore
.pio/
.env
*.tmp
```

Contoh penggunaan:

```text
project/
├── .gitignore
├── README.md
├── src/
├── .env        ← ignored
└── .pio/       ← ignored
```

`.gitignore` terutama memengaruhi file yang belum tracked.

Jika sebuah file sudah tracked, menambahkannya ke `.gitignore` tidak otomatis menghapus file tersebut dari tracking Git.

---

# 32. Git Workflow Keseluruhan

```text
File dibuat / diubah
        │
        │ Save
        ▼
Working Directory
        │
        │ git diff
        │
        │ git add
        ▼
Staging Area / Index
        │
        │ git diff --staged
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

---

# 33. Command Checklist

Sebelum commit:

```bash
git status
git diff
```

Setelah staging:

```bash
git status
git diff --staged
```

Membuat commit:

```bash
git commit -m "Describe the change"
```

Memeriksa history:

```bash
git log --oneline
```

Memeriksa remote:

```bash
git remote -v
```

Memeriksa branch/upstream:

```bash
git branch -vv
```

Push:

```bash
git push
```

---

# 34. Security Notes

Jangan memasukkan file berikut ke repository:

```text
Private SSH key
Password
Personal Access Token
API key
Secret
.env
Credential file
```

Sebelum commit selalu periksa:

```bash
git status
git diff --staged
```

untuk mengetahui isi yang akan masuk commit.

---

# 35. Kesimpulan

Git CLI memungkinkan setiap tahap versioning terlihat dengan jelas.

Alur utama yang digunakan adalah:

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
       │
       │ git push
       ▼
Remote Repository
```

Command Git bukan sekadar urutan yang harus dihafal. Setiap command melakukan operasi terhadap bagian tertentu dari repository.

Memahami working directory, staging area, local repository, remote, branch, dan upstream membuat penggunaan Git lebih mudah dianalisis ketika terjadi masalah.