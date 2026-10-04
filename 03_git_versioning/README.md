# 03 Git Versioning

Technical Notes ini membahas penggunaan **Git** sebagai version control system dan **GitHub** sebagai remote repository.

Pembelajaran dimulai dari konsep dasar Git, dilanjutkan dengan penggunaan Git melalui Command Line Interface (CLI), kemudian integrasi Git dan GitHub melalui Visual Studio Code.

## Learning Objectives

Setelah menyelesaikan bagian ini, diharapkan dapat:

- Memahami fungsi Git sebagai distributed version control system.
- Memahami perbedaan working directory, staging area, local repository, dan remote repository.
- Memahami status file seperti untracked, tracked, modified, staged, dan committed.
- Menggunakan command Git dasar melalui CLI.
- Membuat commit dan memeriksa riwayat perubahan.
- Menghubungkan local repository dengan GitHub.
- Melakukan push ke remote repository.
- Menggunakan SSH atau HTTPS untuk mengakses GitHub.
- Menggunakan fitur Source Control pada Visual Studio Code.
- Membedakan operasi Save, Stage, Commit, Push, Pull, dan Clone.

## Topics

1. [03.1 Konsep Git dan GitHub](./03.1_Konsep_Git_dan_GitHub/)
2. [03.2 Git CLI dan Remote Repository](./03.2_Git_CLI_dan_Remote_Repo/)
3. [03.3 Git di Visual Studio Code](./03.3_Git_di_VSCode/)

## General Git Workflow

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
       │
       └── GitHub
```

## Main Commands

```bash
git status
git add
git commit
git log
git diff
git push
git pull
git clone
```

## Security Notes

Jangan menyimpan credential atau informasi sensitif ke repository.

Contoh file yang tidak boleh di-upload:

```text
Private SSH key
Password
Personal Access Token
.env
Credential files
API keys
```

Gunakan `.gitignore` untuk mengecualikan file yang tidak perlu disimpan pada repository.

Link TN GIT Versioning: https://docs.google.com/document/d/1iuaSmVvoDwFx3FC0EaaakM651hGCxtPJ/edit?usp=drive_link&ouid=117361866800692097676&rtpof=true&sd=true

