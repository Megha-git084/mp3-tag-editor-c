# 🎵 MP3 Tag Reader & Editor in C

This project is a command-line application to **view and edit MP3 metadata (ID3v2 tags)**.

## 🚀 Features

* View MP3 tags
* Edit:

  * Title
  * Artist
  * Album
  * Year
  * Genre
  * Comment

## 🛠️ Tech Used

* C Programming
* File Handling (fseek, fread, fwrite)

## ▶️ How to Run

Compile:

```
gcc *.c
```

Run:

```
./a.out -v sample.mp3
./a.out -e -t "New Title" sample.mp3
```

## 💡 Learning

* Binary file handling
* ID3 tag structure
