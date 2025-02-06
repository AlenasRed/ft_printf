# 🖨️ ft_printf - Custom printf Implementation

`ft_printf` is a **custom implementation** of the standard `printf` function in C. It provides formatted output capabilities while following the structure and behavior of the original function.

---

## 🚀 Features
✅ Handles **basic format specifiers** (`c`, `s`, `d`, `i`, `u`, `x`, `X`, `p`, `%`).  
✅ Supports **width, precision, and flags** (`-`, `0`, `.`).  
✅ Fully written in **C**, adhering to coding best practices.  
✅ Efficient handling of variable arguments using `va_list`.  

---

## 🛠 Installation & Usage

### 1️⃣ Clone the Repository
```sh
git clone https://github.com/AlenasRed/ft_printf.git
cd ft_printf
```

### 2️⃣ Compile the Library
Run the following command to compile the library:
```sh
make
```

### 3️⃣ Use ft_printf in Your Project
To use `ft_printf` in another project, include `ft_printf.h` and link the compiled library:
```sh
gcc your_program.c -L. -lftprintf -o your_program
```

Or include it in your **Makefile**:
```makefile
LIBFTPRINTF = ./ft_printf/libftprintf.a

all:
	gcc your_program.c $(LIBFTPRINTF) -o your_program
```

---

## 📂 Project Structure
```
/ft_printf
├── src/             # Source files for functions
├── includes/        # Header files
├── Makefile         # Build system
├── libftprintf.a    # Compiled library (after running `make`)
├── README.md        # Documentation
```

---

## 📌 Supported Format Specifiers
| Specifier | Description |
|-----------|-------------|
| `%c` | Prints a character |
| `%s` | Prints a string |
| `%d` | Prints a decimal integer |
| `%i` | Prints an integer |
| `%u` | Prints an unsigned integer |
| `%x` | Prints a hexadecimal (lowercase) |
| `%X` | Prints a hexadecimal (uppercase) |
| `%p` | Prints a pointer address |
| `%%` | Prints a percentage sign |

---

## 🔥 Example Usage
```c
#include "ft_printf.h"

int main() {
    ft_printf("Hello, %s!\n", "World");
    ft_printf("Decimal: %d, Hex: %x\n", 42, 42);
    return 0;
}
```

---

## 🛠 Cleaning & Recompiling
```sh
make clean   # Remove object files
make fclean  # Remove compiled library
make re      # Recompile everything
```

---

## 📜 License
This project is **open-source** and free to use under the MIT License.

🎉 **Happy Coding!** 🚀

