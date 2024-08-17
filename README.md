# Flappy Girl
Tựa game là sản phẩm của bài tập lớn môn Lập trình nâng cao (INT2215 70) dưới sự giảng dạy của giảng viên Lê Đức Trọng và giảng viên Hoàng Thị Ngọc Trang. 
Demo game và cấu trúc của code:
# Giới thiệu game
Flappy Girl là tựa game được lấy cảm hứng từ trò chơi nổi tiếng Flappy Bird được phát triển bởi Nguyễn Hà Đông. Thoạt nhìn thì cơ chế của trò chơi khá là đơn giản và dễ hiểu. Người chơi chỉ có mục tiêu duy nhất là điều khiển con chim bay qua các thân cây, tránh để chim đâm vào cây hoặc rơi xuống đất. Tuy nhiên chính lối chơi không phức tạp đó lại vô cùng cuốn hút người chơi, giúp người chơi có thể giải trí trong khoảng thời gian ngắn ngủi mà không tốn quá nhiều thời gian với thao tác game.

Phiên bản Flappy Bird của Nguyễn Hà Đông là nguồn cảm hứng vô cùng to lớn đối với sự ra đời của Flappy Girl. Flappy Girl vẫn giữ nguyên tiêu chí cốt lõi của phiên bản gốc là tinh gọn, đơn giản, dễ hiểu và giết thời gian nhưng ngoài ra Flappy Girl đã phát triển thêm tính năng mới giúp con chim có thể ăn vật phẩm trong game để dễ dàng vượt qua chướng ngại vật hơn.
# 1. Menu game
Bấm nút Start để bắt đầu màn chơi

![image](https://github.com/user-attachments/assets/e73171fc-7b0a-4f95-8765-902f76558da1)
# 2. Các thành phần trong game
- Lady bird: người chơi điều khiển chim vượt qua các cây.

<img src="https://github.com/user-attachments/assets/5916c15d-4e09-4b2d-8675-2c9ae76bacee" width="100" >

- Thân cây: chướng ngại vật chính của game có tác dụng ngăn chặn chim vượt qua.

<img src="https://github.com/user-attachments/assets/3b4bc679-a494-4d17-940f-f98601cb0517" height="300" >

- Quả táo: khi ăn vào con chim sẽ thu nhỏ lại giúp dễ dàng vượt qua các cây.

<img src="https://github.com/user-attachments/assets/a8435077-c9c0-436a-b7dd-11fcf91fb260" width="100" >

- Đồng hồ: khi ăn vào tốc độ game sẽ chậm lại giúp con chim dễ dàng vượt qua các cây.

<img src="https://github.com/user-attachments/assets/057422d1-649b-4a4e-aec5-62463a8c342d" width="100" >

- Mặt đất: chim không được rơi xuống đất, nếu chạm đất màn chơi sẽ kết thúc.

<img src="https://github.com/user-attachments/assets/02e81ce7-416f-455a-ae0a-5c768216a23b" width="400" height="20">

- Pause: ấn ESC để tạm dừng game, khi tạm dừng sẽ xuất hiện hình Pause.

<img src="https://github.com/user-attachments/assets/6eaa7b1b-a323-4f86-a794-3e394d4fa398" width="80" >

- Replay: ấn nút Replay để chơi lại màn tiếp theo.

<img src="https://github.com/user-attachments/assets/61d026c1-fdf4-477f-afdc-2729d3919e4b" width="80" >

- Bố cục game cơ bản:

![image](https://github.com/user-attachments/assets/e5f71a10-da34-4307-9ad2-0b55a4e83ef0)

- Màn hình khi kết thúc màn chơi: Dòng chữ "Congratulations, you've won ..." sẽ hiện ra bên trên nút Replay.

![image](https://github.com/user-attachments/assets/a88b5f46-f95f-4551-9409-3ead116e46e2)

# 3. Cơ chế chơi
- Nút điều khiển trong quá trình chơi
  + Chuột trái: Ấn chuột trái để điều khiển con chim, giúp nó bay lên cao.
  + ESC: Ấn ESC trong quá trình chơi để tạm dừng game, ấn thêm 1 lần nữa game sẽ tiếp tục.
  + Màn hình khi tạm dừng game
 
![image](https://github.com/user-attachments/assets/45992ee2-7d13-413a-ac0c-dea4089661cc)

- Cách chơi:
  + Mục tiêu của trò chơi là giúp cho con chim đạt được số điểm cao nhất có thể. Bằng việc click chuột trái để khiến con chim bay lên, người chơi sẽ như được hòa mình vào con chim để vượt qua các thân cây phía trước, những vật cản chính của game.
  + Để giúp người chơi thuận tiện và dễ dàng hơn trong quá trình chơi, 2 vật phẩm sẽ xuất hiện ngẫu nhiên trong màn chơi bao gồm quả táo và đồng hồ, mỗi vật phẩm sẽ có chức năng riêng của nó.
  + Về quả táo, khi con chim ăn phải thì kích thước sẽ thu nhỏ lại giúp dễ dàng vượt qua các thân cây hơn. Quá trình thu nhỏ sẽ kết thúc khi người chơi đạt thêm được 10 điểm kể từ lúc ăn quả táo.
  + Về đồng hồ, nó sẽ khiến cho tốc độ game giảm đi và điều này sẽ giúp cho người chơi dễ xử lí các tình huống bất ngờ có thể xảy ra. Quá trình làm chậm tốc độ game sẽ kết thúc khi người chơi đạt thêm được 5 điểm kể từ lúc ăn đồng hồ.
- Con chim khi thu nhỏ

![image](https://github.com/user-attachments/assets/e046c77c-b3f0-4db1-99c9-866cc550a78e)

- Đồng hồ trong game

![image](https://github.com/user-attachments/assets/0dc7e3f3-162a-4de1-b875-6e0d040088d8)

# 4. Các kỹ thuật sử dụng
- Sử dụng thư viện SFML.
- Sử dụng nhiều class và vector:
  + Tạo các class cho các đối tượng trong game như Bird, Pipe, Apple, Clock, mỗi class chứa thuộc tính và phương thức riêng để quản lý hành vi của các đối tượng này.
  + Sử dụng vector để lưu trữ các đối tượng động như pipes, apples, clocks giúp dễ dàng quản lý và cập nhật vị trí, trạng thái của chúng trong game.
- Xử lý va chạm:
  + Kiểm tra va chạm giữa con chim với các thân cây, quả táo, và đồng hồ.
  + Kiểm tra va chạm giữa các đối tượng với biên giới của cửa sổ game.
  + Xử lý va chạm để thay đổi kích thước của con chim hoặc kích hoạt hiệu ứng chậm thời gian khi ăn táo hoặc đồng hồ.
- Xử lý trọng lực và chuyển động:
  + Áp dụng trọng lực cho con chim, khiến nó rơi tự do khi không nhấn chuột trái.
  + Tạo chuyển động cho các thân cây di chuyển từ phải sang trái.
- Xử lý thời gian và trạng thái:
  + Sử dụng các biến thời gian để kiểm soát việc sinh ra các đối tượng như Pipe, Apple, Clock.
  + Chuyển đổi giữa các trạng thái khác nhau của game như MENU, GAME, PAUSE, GAME_OVER.
- Tạo và sử dụng hiệu ứng âm thanh:
  + Âm thanh xuất hiện khi con chim va chạm hoặc đạt điểm số.
- Xử lý giao diện người dùng:
  + Tạo các nút như startButton, replayButton để bắt đầu và chơi lại game.
  + Hiển thị các văn bản như điểm số, thông điệp chúc mừng khi kết thúc game.
- Sử dụng các kỹ thuật vẽ và hiển thị:
  + Tạo background và các hình ảnh khác như ground, logo, pauseImage.
  + Hiển thị hình ảnh chim, thân cây, quả táo và đồng hồ trong quá trình chơi game.
- Tạo hiệu ứng đặc biệt:
  + Thay đổi kích thước con chim khi ăn quả táo.
  + Kích hoạt chế độ chậm thời gian khi ăn đồng hồ, và kết thúc khi đạt được một số điểm nhất định.
- Sử dụng kỹ thuật edit và cắt ghép để lấy hình ảnh từ các nguồn trên mạng.

# 5. Nguồn tham khảo
- Tham khảo cách cài đặt thư viện SFML vào Visual Studio 2022 https://www.youtube.com/watch?v=4fcTqmT0Hhg&t=0s
- Âm thanh, hình ảnh và phông chữ được mượn từ các file fonts, textures và sounds của tài khoản Github AlexZihaoXu https://github.com/AlexZihaoXu/CppFlappyBird
- Logo "Flappy Girl" và hình ảnh con chim trong game được tạo ra nhờ sử dụng AI Chatgpt.
- Kỹ thuật xóa background ảnh nhờ sử dụng web RemoveBG https://remove-bg.ai/vi

# 6. Hướng phát triển game
- Cập nhật chế độ chơi dễ, trung bình và khó.
- Tạo ra nhiều vật phẩm trong game hơn. VD:
  + Ăn quả cam con chim sẽ bị đảo lộn ngược lại khiến trò chơi thêm thử thách.
  + Ăn khiên bảo vệ giúp con chim đâm vào thân cây mà không chết.
  + Ăn trái tim giúp con chim có thể hồi sinh 1 lần.
- Thêm các hình ảnh mới vào game. VD:
  + Với mỗi chế độ thì background sẽ khác nhau.
  + Thay vì là thân cây có thể con chim phải vượt qua cột điện hay tảng đá,...





