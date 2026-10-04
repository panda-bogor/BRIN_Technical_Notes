# 03.3 Git di Visual Studio Code

## 1. Tujuan

Bagian ini membahas penggunaan Git melalui antarmuka Visual Studio Code dan hubungan antara operasi pada Source Control VS Code dengan konsep Git yang telah dipelajari melalui CLI.

Tujuan utamanya bukan mengganti pemahaman command Git, tetapi memahami bahwa VS Code menyediakan graphical interface terhadap Git repository yang sama.

---

# 2. Hubungan VS Code, Git, dan GitHub

Ketiga komponen memiliki fungsi berbeda.

```text
Visual Studio Code
        │
        │ interface/editor
        ▼
       Git
        │
        │ remote operations
        ▼
      GitHub
```

## Visual Studio Code

Berfungsi sebagai:

```text
Code editor
Terminal
Source Control interface
Diff viewer
```

## Git

Berfungsi sebagai:

```text
Version Control System
```

Git mengelola:

```text
Working directory
Staging area
Commits
Branches
History
Remotes
```

## GitHub

Berfungsi sebagai layanan hosting remote Git repository.

VS Code tidak menggantikan Git.

VS Code menggunakan instalasi Git yang tersedia pada komputer untuk melakukan operasi Git.

---

# 3. UI VS Code dan CLI Menggunakan Repository yang Sama

Misalnya sebuah project berada pada:

```text
project/
├── .git/
├── README.md
└── src/
```

Jika folder tersebut dibuka di VS Code, operasi Git melalui:

```text
Source Control
```

dan operasi melalui:

```text
Terminal
```

mengakses repository `.git` yang sama.

Contoh:

```text
Klik Stage Changes di VS Code
             │
             ▼
Git Index / Staging Area
             ▲
             │
      git add README.md
```

Tidak ada repository Git khusus yang dibuat hanya untuk VS Code.

---

# 4. Membuka Project

Gunakan:

```text
File
→ Open Folder
```

VS Code membuka folder yang sama dengan folder pada File Explorer.

Tidak ada proses:

```text
"upload folder ke VS Code"
```

VS Code hanya membuka dan mengedit file pada filesystem komputer.

---

# 5. Save Bukan Commit

Saat melakukan:

```text
Ctrl + S
```

VS Code menyimpan perubahan file ke disk.

Alurnya:

```text
Editor
  │
  │ Save
  ▼
Working Directory
```

Save tidak otomatis:

```text
Stage
Commit
Push
```

---

# 6. Empat Operasi yang Harus Dibedakan

```text
SAVE
│
└── menyimpan perubahan file pada PC

STAGE
│
└── memilih versi perubahan untuk next commit

COMMIT
│
└── mencatat staged snapshot ke local Git history

PUSH
│
└── mengirim local commits ke remote repository
```

Alur:

```text
Edit
 │
 ▼
Save
 │
 ▼
Working Directory
 │
 ▼
Stage
 │
 ▼
Staging Area
 │
 ▼
Commit
 │
 ▼
Local Repository
 │
 ▼
Push
 │
 ▼
GitHub
```

---

# 7. Membuka Source Control

Shortcut:

```text
Ctrl + Shift + G
```

Source Control menampilkan kondisi file Git pada workspace.

Secara umum terdapat:

```text
Changes
```

dan:

```text
Staged Changes
```

---

# 8. Arti `Changes`

File pada bagian:

```text
Changes
```

merupakan perubahan yang belum staged.

Contoh:

```text
Changes
├── README.md      M
└── example.txt    U
```

Status yang umum:

```text
U = Untracked
M = Modified
D = Deleted
```

Secara konsep:

```text
VS Code "Changes"
        │
        ▼
Working Directory Changes
```

---

# 9. Stage Changes

Pada Source Control, klik tanda:

```text
+
```

di sebelah file.

Contoh:

```text
README.md
    │
    │ + Stage Changes
    ▼
Staged Changes
```

Secara konsep hal ini setara dengan:

```bash
git add README.md
```

Alurnya:

```text
Working Directory
      │
      │ Stage Changes
      ▼
Git Index / Staging Area
```

Staging menangkap versi perubahan pada saat itu.

Jika file diedit kembali setelah staging, perubahan baru tersebut belum otomatis termasuk dalam staged snapshot.

Akibatnya satu file dapat memiliki:

```text
Staged Changes
+
Unstaged Changes
```

secara bersamaan.

---

# 10. Staged Changes

Bagian:

```text
Staged Changes
```

menunjukkan perubahan yang dipilih untuk next commit.

Sebelum commit, file pada bagian ini dapat direview kembali.

Konsep CLI yang setara untuk memeriksa staged changes adalah:

```bash
git diff --staged
```

---

# 11. Unstage Changes

Jika file sudah staged tetapi ternyata belum ingin dimasukkan ke commit, gunakan:

```text
Unstage Changes
```

Secara konsep serupa dengan:

```bash
git restore --staged <file>
```

Unstage tidak berarti menghapus file atau membuang edit.

Perubahan tetap berada pada working directory.

```text
Staged Changes
      │
      │ Unstage
      ▼
Changes
```

---

# 12. Commit melalui VS Code

Setelah file berada pada `Staged Changes`, masukkan commit message.

Contoh:

```text
Add Git documentation
```

Kemudian pilih:

```text
Commit
```

Secara konsep setara dengan:

```bash
git commit -m "Add Git documentation"
```

Commit mencatat staged snapshot pada:

```text
Local Git Repository
```

Commit **belum otomatis berada di GitHub**.

---

# 13. Initialize Repository

Jika folder belum merupakan Git repository, Source Control dapat menampilkan:

```text
Initialize Repository
```

Operasi tersebut secara konsep setara dengan:

```bash
git init
```

Hasilnya:

```text
folder biasa
     │
     │ Initialize Repository
     ▼
Git repository
```

Git membuat metadata repository di:

```text
.git/
```

---

# 14. Memeriksa Repository dari Terminal VS Code

Walaupun menggunakan UI, terminal tetap sangat berguna untuk verifikasi.

Buka:

```text
Terminal
→ New Terminal
```

Periksa lokasi PowerShell:

```powershell
Get-Location
```

Kemudian:

```bash
git status
```

Untuk mengetahui root repository:

```bash
git rev-parse --show-toplevel
```

Command tersebut berguna untuk memastikan Git repository mana yang sedang digunakan.

---

# 15. Menambahkan Remote

Remote dapat ditambahkan melalui CLI:

```bash
git remote add origin <repository-url>
```

VS Code juga menyediakan operasi:

```text
Source Control
→ More Actions (...)
→ Remotes
→ Add Remote
```

atau melalui Command Palette:

```text
Git: Add Remote
```

Keduanya pada akhirnya mengubah konfigurasi remote pada repository Git yang sama.

---

# 16. Apa yang Terjadi Saat Add Remote?

Misalnya remote:

```text
origin
```

mengarah ke:

```text
GitHub Repository
```

Maka:

```text
Local Repository
       │
       └── origin
              │
              ▼
        GitHub Repository
```

Menambahkan remote **tidak langsung meng-upload commit**.

Remote hanya mendefinisikan hubungan/nama menuju repository lain.

---

# 17. Memeriksa Remote

Dari terminal VS Code:

```bash
git remote -v
```

Contoh:

```text
origin  git@github.com:USERNAME/project.git (fetch)
origin  git@github.com:USERNAME/project.git (push)
```

Hal ini membuktikan remote sudah dikonfigurasi.

Namun:

```text
remote ada
```

tidak sama dengan:

```text
push sudah berhasil
```

Untuk memastikan push berhasil, periksa commit pada GitHub.

---

# 18. Push melalui VS Code

Setelah commit dibuat, gunakan:

```text
More Actions (...)
→ Push
```

Secara konsep:

```text
Local Repository
       │
       │ Push
       ▼
Remote Repository
```

Setara dengan operasi CLI:

```bash
git push
```

Push mengirim commit lokal ke remote branch.

---

# 19. Publish Branch

Jika branch lokal belum memiliki upstream, VS Code dapat menawarkan:

```text
Publish Branch
```

Publish Branch berarti branch lokal dikirim ke remote dan upstream-nya dikonfigurasi.

Secara konsep mirip dengan:

```bash
git push -u origin main
```

untuk kasus branch `main` dan remote `origin`.

Setelah upstream tersedia:

```text
main
 │
 └── tracks
        │
        ▼
    origin/main
```

VS Code dapat mengetahui remote branch tujuan untuk push/pull berikutnya.

---

# 20. Publish to GitHub

Ini berbeda dengan:

```text
Publish Branch
```

## Publish to GitHub

Digunakan ketika local repository belum memiliki hosted repository yang sesuai di GitHub.

VS Code dapat:

```text
Create GitHub Repository
        +
Add Remote
        +
Push Local Commits
```

alur sederhananya:

```text
Local Git Repository
        │
        │ Publish to GitHub
        ▼
Create GitHub Repository
        │
        ▼
Configure Remote
        │
        ▼
Push
```

Jika repository GitHub sudah dibuat sebelumnya, tidak perlu membuat repository baru dengan Publish to GitHub.

Cukup tambahkan repository tersebut sebagai remote.

---

# 21. Clone Repository

Jika repository sudah berada di GitHub dan ingin dibuat salinan lokal, gunakan:

```text
Ctrl + Shift + P
```

kemudian:

```text
Git: Clone
```

Masukkan repository URL dan pilih folder tujuan.

Secara konsep operasi ini menjalankan Git clone.

```text
Remote Repository
       │
       │ Clone
       ▼
Local Repository
```

Clone membawa:

```text
Project files
Commit history
Repository information
Remote configuration
```

Remote sumber biasanya diberi nama:

```text
origin
```

---

# 22. Fetch

VS Code menyediakan:

```text
More Actions (...)
→ Fetch
```

Fetch mengambil informasi/commit terbaru dari remote tanpa langsung mengintegrasikannya ke current branch.

Secara konsep:

```text
GitHub
 │
 │ Fetch
 ▼
Remote-tracking references

Current local branch
tidak otomatis diubah
```

Ini berguna ketika ingin memeriksa perubahan remote sebelum melakukan pull.

---

# 23. Pull

VS Code menyediakan:

```text
Pull
```

Pull mengambil perubahan remote kemudian mengintegrasikannya ke current local branch.

Secara konsep:

```text
Remote
   │
   │ Fetch
   ▼
Remote data
   │
   │ Integrate
   ▼
Current Local Branch
```

Sebelum pull, periksa kondisi working tree agar tidak ada perubahan lokal yang terlupakan.

---

# 24. Push

Push hanya mengirim local commits ke remote.

```text
Local Commits
      │
      │ Push
      ▼
Remote
```

Push tidak otomatis mengambil perubahan remote terlebih dahulu.

---

# 25. Sync Changes

VS Code juga menyediakan:

```text
Sync Changes
```

Sync bukan sekadar Push.

Secara umum:

```text
Sync Changes
     │
     ├── Pull
     │
     └── Push
```

VS Code melakukan pull terlebih dahulu, kemudian push.

Karena itu:

```text
Push
```

dan:

```text
Sync Changes
```

tidak identik.

Jika hanya ingin mengirim commit lokal tanpa melakukan pull, gunakan Push.

---

# 26. Hubungan Operasi VS Code dengan Git CLI

| VS Code | Konsep / CLI |
|---|---|
| Initialize Repository | `git init` |
| Stage Changes | `git add <file>` |
| Unstage Changes | `git restore --staged <file>` |
| Commit | `git commit` |
| Add Remote | `git remote add` |
| Push | `git push` |
| Publish Branch | Push + set upstream |
| Fetch | `git fetch` |
| Pull | `git pull` |
| Clone | `git clone` |
| Sync Changes | Pull kemudian Push |

UI dan CLI mengoperasikan Git repository yang sama.

---

# 27. Contoh Workflow melalui UI

```text
Open Folder
    │
    ▼
Edit README.md
    │
    ▼
Ctrl + S
    │
    ▼
Source Control
    │
    ▼
Changes
    │
    │ Stage Changes (+)
    ▼
Staged Changes
    │
    │ Commit
    ▼
Local Repository
    │
    │ Push
    ▼
GitHub
```

---

# 28. Workflow Campuran UI dan CLI

UI dan CLI dapat digunakan bersama.

Contoh:

Stage melalui VS Code:

```text
+ Stage Changes
```

kemudian verifikasi melalui terminal:

```bash
git status
git diff --staged
```

Commit melalui VS Code:

```text
Commit
```

kemudian periksa melalui:

```bash
git log --oneline
```

Push melalui VS Code:

```text
Push
```

kemudian periksa:

```bash
git status
git branch -vv
```

Ini memungkinkan pengguna memanfaatkan kenyamanan GUI tanpa kehilangan pemahaman terhadap state repository.

---

# 29. Contoh Pemeriksaan Sebelum Commit

Dari terminal VS Code:

```bash
git status
```

Periksa file yang staged.

Kemudian:

```bash
git diff --staged
```

Pastikan tidak terdapat:

```text
Password
Token
Private key
API key
.env
Credential
Temporary files
```

Setelah aman, lakukan commit.

---

# 30. `.gitignore`

Contoh project:

```gitignore
.pio/
.env
*.tmp
```

`.gitignore` digunakan agar file tertentu tidak ditambahkan ke repository secara normal.

Contoh:

```text
project/
├── README.md
├── .gitignore
├── src/
├── .env      ← ignored
└── .pio/     ← ignored
```

Perlu diingat bahwa `.gitignore` tidak otomatis menghentikan tracking file yang sudah sebelumnya tracked.

---

# 31. Troubleshooting

## VS Code Tidak Mengenali Git

Periksa:

```bash
git --version
```

Jika Git baru diinstal, restart VS Code agar environment baru terbaca.

---

## `fatal: not a git repository`

Periksa lokasi:

```powershell
Get-Location
```

Kemudian:

```bash
git rev-parse --show-toplevel
```

Pastikan folder yang dibuka merupakan repository yang benar.

---

## `remote origin already exists`

Periksa:

```bash
git remote -v
```

Jika URL salah:

```bash
git remote set-url origin <correct-url>
```

Jangan membuat `origin` kedua.

---

## `Permission denied (publickey)`

Jika menggunakan SSH, uji:

```bash
ssh -T git@github.com
```

Periksa:

- SSH key tersedia;
- public key sudah terdaftar pada GitHub;
- akun GitHub yang terhubung benar.

---

## Commit Sudah Ada tetapi Tidak Terlihat di GitHub

Commit bersifat lokal sampai dilakukan push.

Periksa:

```bash
git status
git log --oneline
git remote -v
git branch -vv
```

Kemudian:

```bash
git push
```

---

## Tombol `Publish Branch` Muncul

Branch kemungkinan belum memiliki upstream remote branch.

Publish Branch akan mengirim branch dan mengonfigurasi upstream.

---

## Repository Salah

Periksa:

```bash
git rev-parse --show-toplevel
git remote -v
```

Pastikan root lokal dan remote GitHub sesuai dengan project yang sedang dikerjakan.

---

# 32. Kesimpulan

Visual Studio Code memberikan graphical interface terhadap Git.

Hubungannya:

```text
VS Code
  │
  │ user interface
  ▼
Git Repository
  │
  │ remote operations
  ▼
GitHub
```

Operasi seperti Stage, Commit, Pull, Push, dan Clone bukan mekanisme khusus VS Code.

Operasi tersebut tetap merupakan operasi Git yang dijalankan melalui antarmuka VS Code.

Karena UI dan terminal bekerja pada repository yang sama, pengguna dapat berpindah antara keduanya tanpa membuat repository baru.