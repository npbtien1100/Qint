# `osh` (Simple Shell)



### Thông tin đồ án

-   Đồ án cho môn Hệ Điều Hành , FIT @ HCMUS
-   Nhóm gồm 3 thành viên
    -   `18120592`: Nguyễn Phú Bảo Tiến
    -   `18120629`: Trần Văn Tú
    -   `18120636`: Trần Ngọc Tuấn

#### *Tất cả các chức năng đều đạt độ hoàn thiện 100%

### Hướng thiết kế của đồ án
##### Ngôn ngữ và môi trường lập trình

Đồ án được lập trình bằng ngôn ngữ `C`,biên dịch bằng `gcc` trên hệ điều hành Linux 


##### Kịch bản của chương trình

0. Dùng `makefile` để build chương trình.
1. Khi shell bắt đầu chạy, chương trình sẽ vào vòng lặp while thực hiện chương trình.
2. Chương trình sẽ chạy hàm `prompt` in ra cửa số làm việc, người dùng nhập command vào
3. Command sẽ được đưa vào kiểm tra BuiltIn (Built In là chương trình những lệnh đặc biệt mà execvp không xử lý được như: history, cd, !!, help, hello)
4. Lưu lại lịch sử command
5. Kiểm tra command có Pipe không. Nếu có thì thực hiện Pipe rồi quay lại bước 2 tiếp tục thực hiện command mới.
6. Kiểm tra command có chuyển hướng hay không. Nếu có thì thực hiện hàm chuyển hướng rồi quay lại bước 2 tiếp tục thực hiện command mới.
7. Kiểm tra chương trình có chạy ngầm hay không. Nếu có chạy ngầm cờ `background` sẽ được bật lên 1, nếu không thì cờ `background` sẽ được giữ lại 0.
8. Thực thi chương trình trong hàm `execvpArgs`. Sau đó quay lại bước 2.

#####Note: để thoát chương trình chúng ta có thể sử dụng lệnh exit, hoặc nhấm phím tổ hợp `Ctr + C` hoặc `Ctr + Z`.


##### Các hàm quan trọng



##### Về lớp lệnh built-in

Các lệnh built-in của shell hiện chỉ mang tính sơ khai và phục vụ một số tính năng phụ (như thay đổi kích thước lịch sử lệnh sử dụng `histsize`, xem hướng dẫn sử dụng `histsize`, v.v.). Lớp lệnh này có thể phát triển thêm nếu có thời gian mở rộng.


### Các testcase
**Thực thi lệnh**
![](https://i.imgur.com/fuwVskl.png)





---


### Tài liệu tham khảo:
Linux's man page ở dạng [web](https://linux.die.net/man/) và dạng `CLI` với lệnh `man <lệnh cần tra cứu>.`

