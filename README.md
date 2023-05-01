-----------------------------------------------------------------------------------------------------------------------------------------------
# Plane_Fighting_NTD of bongbong1001
- Game sử dụng thư viện SDL_2.
- Game sử dụng ngôn ngữ c++.
- Đây là game được lấy ý tưởng từ game bắn gà cổ điển nhưng được thay thế bằng bắn phi cơ vô cùng hấp dẫn.
- Game được tham khảo từ phattrienphanmem123az cùng sự trợ giúp của chatgpt và lazyfoo.

## Giới Thiệu
- Plane fighting là 1 game chiến đấu. Người chơi sẽ được điều khiển 1 phi cơ chiến đấu để tiêu diệt mục tiêu vật cản ngăn mình 
đến với chiến thắng trong thời gian cho phép, ải cuối người chơi sẽ phải vượt qua boss với sức mạnh vô cùng mạnh mẽ, chờ đợi người 
chơi ở cuối là số điểm mà mình đạt được.

## Luật chơi game
- Người chơi sẽ dùng các phím UP-DOWN-RIGHT-LEFT để di chuyển phi cơ của mình đồng thời né các máy bay và đạn của địch, sau đó nhấn chuột trái 
  hoặc chuột phải để bắn ra các viên đạn tiêu diệt địch.
- Với mỗi con quái nhỏ sau khi tiêu diệt người chơi sẽ dành được 1 điểm thưởng.
- Đặc biệt tiêu diệt được con boss người chơi sẽ nhận được 50 điểm thưởng.
- Sau khi hết thời gian cho phép hiện ra màn hình là số điểm mà người chơi đạt được.
## Nội dung chương trình
- Chương trình được chia làm 19 file bao gồm 8 class để quản lí các dữ liệu game.
- Class ThreatObject để quản lí các phi cơ của địch.
- Class BossObject để quản lí con boss ở cuối game.
- Class ExploreObject để quản lí hiệu ứng vụ nổ khi va chạm của các đối tượng.
- Class Ltexture để quản lí phi cơ chính.
- Class Ltimer để quản lí thời gian game.
- Class PlayPower để quản lí hp hay mạng của nhân vật.
- Class TextObject để quản lí chữ text in lên game.
- Class AmoObject để quản lí đạn của địch và phi cơ chính.
## Hướng cải thiện game
- Dựa theo những class mà game có sẵn, người lập trình có thể tạo thêm các năng lượng hỗ trợ trên đường chơi để người chơi có thể ăn giúp 
  tăng hp hoặc tăng sức mạnh của viên đạn mà mình bắn ra.
- Người lập trình có thể cải thiện đồ hoạ đẹp hơn, dài hơn để người chơi có thể cảm nhận background không bị lặp.
- Người lập trình có thể tạo ra sự bất tử sau khi hồi sinh cho nhân vật để tránh va chạm với địch khi mới hồi sinh.
## Đồ hoạ
- Các nút của menu được lấy từ nguồn : https://www.shutterstock.com/vi/image-vector/cartoon-buttons-set-game-illustration-1119396701.
- Các hoạt hoạ của nhân vật và background được lấy từ nguồn : https://phattrienphanmem123az.com/lap-trinh-game-cpp/goi-image-gia-re.html.

## Music

- Được lấy từ nguồn : https://www.freesoundeffects.com/free-sounds/explosion-10070/.
-------------------------------------------------------------------------------------------------------------------------------------------------



