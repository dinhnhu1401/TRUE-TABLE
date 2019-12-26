# TRUE TABLE - C++

## `Polish Notation  Algorithm`

## Mission

Give a file named **logic_expression.txt** includes one-line  logic expression with 23 variables in ["a", "z"] \ {"v"}.

| Operation |      Meaning     |
| :-------- | :--------------: |
| ~         |     Negative     |
| v         |        Or        |
| ^         |       And        |
| ->        |     Kéo theo     |
| <->       | Kéo theo 2 chiều |
| (         |     Mở ngoặc     |
| )         |    Đóng ngoặc    |

Write a program to return a true table of the logic expression given by the file.

### Input: logic_expression.txt

    (pvq)->r

### Output: output.txt

| p   | q   | r   | pvq | (pvq)->r |
| :-- | :-- | :-- | :-- | :------- |
| 0   | 0   | 0   | 0   | 1        |
| 0   | 0   | 1   | 0   | 1        |
| 0   | 1   | 0   | 1   | 0        |
| 0   | 1   | 1   | 1   | 1        |
| 1   | 0   | 0   | 1   | 0        |
| 1   | 0   | 1   | 1   | 1        |
| 1   | 1   | 0   | 1   | 0        |
| 1   | 1   | 1   | 1   | 1        |

## Solution

### Step 1: Pre-process the string

| Operation |  Symbol | Priority Level |
| :-------- | :------ | :------------- |
| ~         | 1       | 3              |
| v         | 2       | 2              |
| ^         | 3       | 2              |
| ->        | 4       | 1              |
| <->       | 5       | 1              |
| (         | 6       | 0              |
| )         | 7       | 0              |

Example:

    Logic Expression: ((tvq)^~p)<->(z->(uvq))
    Convert Operator: 6 6 t 2 q 7 3 1 p 7 5 6 z 4 6 u 2 q 7 7

### Bước 2: Chuyển về dạng hậu tố

Dùng giải thuật Ba Lan chuyển biểu thức trung tố về dạng hậu tố

- Nếu là biến logic thì đưa vào mảng B.
- Nếu là dấu `(` thì đưa vào stack.
- Nếu là dấu `)` thì đưa lần lượt từng phần tử trong stack vào mảng B đến khi gặp dấu `(`.
- Nếu là phép toàn:
  - Nếu stack rỗng thì đưa vào stack.
  - Nếu stack khác rỗng:
    - Phép toán có độ ưu tiên lớn hơn độ ưu tiên của phần tử cuối của stack thì đưa vào stack.
    - Ngược lại lấy phàna tử cuối stack đưa vào mảng B và tiếp tục kiểm tra phép toán với phần tử cuối stack.
- Kết thúc thuật toán, đưa lần lượt các phần tử còn lại vào trong stack B.

Ví dụ:

    Logic Expression: ((tvq)^~p)<->(z->(uvq))
    Convert Operator: 6 6 t 2 q 7 3 1 p 7 5 6 z 4 6 u 2 q 7 7
    Polish Notation: t q 2 p 1 3 z u q 2 4 5

### Bước 3: Tính toán giá trị của bảng chân trị

Giả sử list B là biểu thức logic dạng hậu tố, khởi tạo một stack A rỗng, duyệt list B từ trái qua phải:

- Nếu là biến logic thì đưa giá trị của biến (0/1) vào stack A
- Nếu là phép toán:
  - Nếu là phép toán hai ngôi thì lấy lần lượt 2 phần tử cuối cùng trong stack A và thực hiện phép toán.
  - Nếu là phép toán 1 ngôi thì lấy một phần tử cuối cùng trong stack và thực hiện phép toán
  - Sau khi thực hiện xong mỗi phép toán, đưa kết quả lại vào stack A
- Kết thúc, giá trị của biểu thức là phần tử cuối cùng trong stack A

## Sử dụng:

```bash
git clone 
cat logic_expression.txt # đổi biểu thức logic đầu vào ở đây
g++ MainPro.cpp -o run # compile file
./run # execute file


cat output.txt ## xem kết quả bảng chân trị qua file .txt

# Đối chiếu so sánh kết quả với
# https://web.stanford.edu/class/cs103/tools/truth-table-tool/
```