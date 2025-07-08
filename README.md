# PRNGAlgorithm - Bộ sinh số ngẫu nhiên giả sử dụng Linear Congruential Generator (LCG)

## 1. Giới thiệu

Dự án này hiện thực một thuật toán **Pseudo-Random Number Generator (PRNG)** đơn giản dựa trên phương pháp **Linear Congruential Generator (LCG)**. Mục đích là minh họa cách hoạt động cơ bản của PRNG và so sánh với các thư viện hiện đại như `<random>` trong C++.

Ngôn ngữ sử dụng: `C++17`.

---

## 2. Lý thuyết: Pseudo-Random Number Generator (PRNG)

### PRNG là gì?

PRNG là **bộ sinh số ngẫu nhiên giả**, tạo ra một chuỗi số trông giống như ngẫu nhiên nhưng được sinh ra theo một thuật toán xác định. Mỗi lần chạy với cùng một giá trị khởi tạo (seed), PRNG sẽ cho ra cùng một chuỗi số.

> Lưu ý: PRNG **không phù hợp cho mục đích mã hóa hoặc bảo mật** do tính chất xác định (deterministic).

### Linear Congruential Generator (LCG)

LCG là một trong những thuật toán PRNG đơn giản và phổ biến nhất, có dạng công thức:

```

Xₙ₊₁ = (a * Xₙ + c) mod m

````

Trong đó:
- `Xₙ`: số sinh ra ở bước thứ `n` (gọi là trạng thái hiện tại hay seed),
- `a`: hệ số nhân (multiplier),
- `c`: gia số (increment),
- `m`: modulus (giới hạn giá trị),
- `X₀`: giá trị khởi tạo (initial seed).

Nếu các tham số `a`, `c`, `m` được chọn hợp lý, chuỗi sinh ra sẽ có chu kỳ dài và phân bố tốt.

### So sánh với `<random>` trong C++

C++ cung cấp các bộ PRNG hiện đại trong thư viện `<random>`, ví dụ như `std::mt19937` (Mersenne Twister), cho chất lượng và hiệu năng cao hơn rất nhiều so với LCG:

```cpp
#include <random>

std::mt19937 gen(seed);
std::uniform_int_distribution<> dist(min, max);
int random_val = dist(gen);
````
---

## 3. Mô tả lớp `SimplePRNG`

### Các thuộc tính:

```cpp
unsigned long long current_seed;
unsigned long long multiplier;
unsigned long long increment;
unsigned long long modulus;
```

* `current_seed`: trạng thái hiện tại của PRNG.
* `multiplier` (`a`): hệ số nhân trong công thức LCG.
* `increment` (`c`): gia số cộng thêm sau mỗi bước.
* `modulus` (`m`): giá trị modulo để giữ kết quả trong một giới hạn.

### Constructor:

```cpp
SimplePRNG(unsigned long long initial_seed);
```

Khởi tạo đối tượng với `initial_seed`. Gán các giá trị `a`, `c`, `m` cố định có tính toán để đảm bảo chu kỳ dài (dựa trên giá trị phổ biến trong LCG).

### Phương thức `next()`:

```cpp
unsigned long long next();
```

Trả về số ngẫu nhiên tiếp theo theo công thức LCG.

### Phương thức `set_seed()`:

```cpp
void set_seed(unsigned long long new_seed);
```

Đặt lại seed để khởi động lại chuỗi ngẫu nhiên từ cùng trạng thái.

### Phương thức `get_random_range()`:

```cpp
int get_random_range(int min_val, int max_val);
```

Trả về một số ngẫu nhiên nằm trong đoạn `[min_val, max_val]`. Có xử lý hoán đổi giá trị nếu `min > max`.

---

## 4. Hàm `main()`: Kiểm thử và minh họa

Gồm các đoạn test minh họa tính năng của `SimplePRNG`:

1. **Sinh chuỗi số từ cùng một seed**:

   * Minh họa tính **xác định (deterministic)** của PRNG.
   * Reset lại seed sẽ sinh lại đúng chuỗi ban đầu.

2. **So sánh hai seed khác nhau**:

   * Seed khác -> chuỗi kết quả khác hoàn toàn.

3. **Test sinh số trong khoảng**:

   * Sử dụng `get_random_range(min, max)` để sinh số nguyên nằm trong đoạn `[min, max]`.

4. **Test với seed động (thời gian hệ thống)**:

   * Dùng `std::chrono` để tạo seed mới mỗi lần chạy chương trình.

---

## 5. Biên dịch và chạy

```bash
g++ -o simple_prng main.cpp
./simple_prng
```

---

## 6. Kết luận

Dự án này cung cấp cái nhìn trực quan về hoạt động bên trong của một PRNG cơ bản bằng C++. Mặc dù đơn giản, kiến thức này là nền tảng để hiểu cách hoạt động của các thư viện PRNG phức tạp hơn như `<random>` trong C++ hoặc các giải pháp trong mật mã học.

Không nên sử dụng LCG cho các ứng dụng thực tế yêu cầu độ ngẫu nhiên cao hoặc bảo mật.

