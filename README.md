# DP-Week2-Task1 — Balatro-Like Run

**Nama:** Omar Ginza | **NRP:** 5224600063  
**Course:** Design Patterns — Week 1

---

## Cara Build & Jalankan

```bash
cd "C:\Ginza\Unity Project\DP-Week1-5224600063-Omar-Ginza\Task1"
g++ -std=c++17 main.cpp -o balatro
.\balatro.exe
```

---

## Struktur File

```
Task1/
├── main.cpp                  # Entry point — menghubungkan semua komponen
├── TurnInput.h               # Struct data yang dioper antar fase
├── IInputGenerator.h         # Interface: menghasilkan TurnInput
├── IScoringRule.h            # Interface: menghitung base score
├── IRewardRule.h             # Interface: menghitung reward dari score
├── FixedInputGenerator.h     # Implementasi awal: selalu menghasilkan nilai 3
├── RandomInputGenerator.h    # Implementasi baru (Modifikasi 1): nilai acak 1–10
├── BasicScoringRule.h        # Implementasi scoring: score = nilai input
├── SimpleRewardRule.h        # Implementasi reward awal: reward = base score
├── EvenDoubleRewardRule.h    # Implementasi reward baru (Modifikasi 2): rumus berbeda
├── ShopSystem.h              # Logika fase shop
└── RunSession.h              # Pengontrol game loop utama (invariant)
```

---

## Urutan Fase (Invariant)

Setiap round selalu berjalan dalam urutan ini dan **tidak boleh berubah**:

```
1. Generate input
2. Hitung base score
3. Hitung reward
4. Update uang
5. Fase shop
6. Lanjut ke round berikutnya
```

---

## Contoh Output

```
=== RUN START ===

Round 1
[PLAY]   input generated: 7
[SCORE]  base score: 7
[REWARD] gain: 9 | money: 9
[SHOP]   offered: Bonus(+2) cost 2
[SHOP]   purchased! money left: 7
[ROUND 1 END] money: 7

Round 2
[PLAY]   input generated: 4
[SCORE]  base score: 4
[REWARD] gain: 8 | money: 15
[SHOP]   offered: Bonus(+2) cost 2
[SHOP]   purchased! money left: 13
[ROUND 2 END] money: 13

Round 3
[PLAY]   input generated: 9
[SCORE]  base score: 9
[REWARD] gain: 11 | money: 24
[SHOP]   offered: Bonus(+2) cost 2
[SHOP]   purchased! money left: 22
[ROUND 3 END] money: 22

=== RUN END ===
Final money: 22
```

---

## Penjelasan Modifikasi

### Modifikasi 1 — Ganti Input Generator

Dibuat class baru bernama `RandomInputGenerator` yang menghasilkan angka acak antara 1 sampai 10 setiap roundnya. Class ini menggantikan `FixedInputGenerator` yang sebelumnya selalu mengembalikan nilai tetap yaitu 3.

Perubahan hanya dilakukan di `main.cpp` pada bagian pemilihan class — `RunSession` **tidak disentuh sama sekali**.

### Modifikasi 2 — Ubah Logika Reward

Dibuat class baru bernama `EvenDoubleRewardRule` dengan rumus reward yang berbeda dari base score:

- **Round ganjil** → reward = base score + 2
- **Round genap** → reward = base score × 2

Sama seperti Modifikasi 1, perubahan hanya di `main.cpp` — `RunSession` **tidak disentuh sama sekali**.

---

## Refleksi

### 1. Apa yang dimaksud dengan invariant dalam program ini?

Invariant adalah **urutan fase** yang dikunci di dalam `RunSession::run()`. Setiap round harus selalu menjalankan keenam fase secara berurutan: generate input, hitung score, hitung reward, update uang, shop, lalu lanjut ke round berikutnya. Urutan ini tidak boleh berubah dalam kondisi apapun. `RunSession` adalah penjaga invariant tersebut — ia menentukan *kapan* setiap fase dijalankan, tapi tidak menentukan *bagaimana* logikanya bekerja.

### 2. Bagian mana yang bersifat mutable?

Bagian yang bisa berubah adalah **implementasi konkrit** yang dimasukkan ke dalam `RunSession` melalui dependency injection:

- `IInputGenerator` → bisa diganti antara `FixedInputGenerator` atau `RandomInputGenerator`
- `IScoringRule` → bisa diganti dengan rumus scoring apapun
- `IRewardRule` → bisa diganti antara `SimpleRewardRule` atau `EvenDoubleRewardRule`
- `ShopSystem` → bisa dikembangkan dengan logika toko yang lebih kompleks

Semua bagian ini bisa diubah atau diganti tanpa menyentuh struktur utama program.

### 3. Ketika InputGenerator diganti, kenapa RunSession tidak ikut berubah?

Karena `RunSession` hanya bergantung pada **interface** `IInputGenerator`, bukan pada implementasi spesifiknya. Ia hanya memanggil `inputGen->generate()` tanpa peduli bagaimana nilai itu dihasilkan. Ketika `FixedInputGenerator` diganti dengan `RandomInputGenerator`, hanya `main.cpp` yang berubah untuk mengganti koneksi antar komponen. `RunSession` tidak perlu tahu soal perubahan itu. Inilah keuntungan dari **dependency injection** — perubahan perilaku terjadi di bagian pinggir program, bukan di inti loop-nya.

### 4. Apa yang terjadi jika logika scoring diletakkan di dalam RunSession?

Jika logika scoring ada di dalam `RunSession`, maka class tersebut memiliki dua tanggung jawab sekaligus: mengatur urutan fase *dan* menghitung score. Ini melanggar prinsip **Single Responsibility**. Setiap kali rumus scoring perlu diubah, `RunSession` harus ikut dimodifikasi. Lama-kelamaan class ini akan menjadi besar, sulit dibaca, dan rawan bug. Selain itu, invariant yang seharusnya stabil menjadi ikut terganggu hanya karena perubahan logika yang seharusnya bisa dilakukan secara terpisah.
