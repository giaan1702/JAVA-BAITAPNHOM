INSERT INTO users (id, username, password, role) VALUES
(1, 'admin', 'admin', 1),
(2, 'user02', '241', 0),
(3, '1', '1', 1),
(4, 'hao', '123', 1);
 
 INSERT INTO khachhang (id, ho_ten, quoc_tich, loai_giay_to, so_giay_to, sdt, email) VALUES
(100, 'Linh Nguyen', 'Vietnam', 'CCCD', '012345678001', '1256', 'linh.nguyen@aaa.com'),
(101, 'Linh Tran', 'Vietnam', 'CCCD', '012345678002', '6823', 'linh.tran@aaa.com'),
(102, 'John Smith', 'USA', 'Hochieu', 'A12345678', '1981', 'john.smith@eee.com'),
(103, 'Linh Pham', 'Vietnam', 'Hochieu', 'B98765432', '1353', 'linh.pham@ddd.com'),
(104, 'Lien Hoang', 'Vietnam', 'CCCD', '012345678003', '5625', 'lien.hoang@ddd.com'),
(105, 'Lia Pham', 'Vietnam', 'Hochieu', 'C56789123', '5668', 'lia.pham@asdas.com'),
(106, 'Hassan Khan', 'India', 'CCCD', 'IN45678910', '1283', 'hassan.khan@tdg.com'),
(107, 'Hung Huy', 'Vietnam', 'CCCD', '012345678004', '1589', 'hung.huy@asdd.com'),
(108, 'Anna Lee', 'Finland', 'Hochieu', 'FIN99887766', '1191', 'anna.lee@2frd.com'),
(109, 'Alice Adams', 'USA', 'Hochieu', 'US998877', '911', 'alice.adams@1.com'),
(110, 'George Ford', 'USA', 'Hochieu', 'US223344', '1119', 'george.ford@5.com'),
(111, 'David S.', 'USA', 'CCCD', 'US112233', '5826', 'david.s@ooo.com'),
(112, 'Jane Doe', 'USA', 'CCCD', 'US332211', '5689', 'jane.doe@256.com'),
(113, 'Kevin A.', 'USA', 'CCCD', 'US445566', '5662', 'kevin.a@153.com'),
(114, 'Ian J.', 'USA', 'CCCD', 'US556677', '15', 'ian.j@335.com'),
(115, 'Alex D.', 'USA', 'CCCD', 'US667788', '1891', 'alex.d@13.com'),
(116, 'Dan F.', 'USA', 'CCCD', 'US778899', '1961', 'dan.f@13.com'),
(117, 'Huy Hoang', 'Vietnam', 'CCCD', '012345678005', '6584', 'huy.hoang@152.com');


INSERT INTO loaiphong (id, ten_loai_phong, gia) VALUES
(1, 'PhongDon', 200000),
(2, 'PhongDoi', 300000),
(3, 'PhongDeluxe', 500000),
(4, 'PhongGiaDinh', 650000),
(5, 'test', 5555);
 
 INSERT INTO phong (so_phong, id_loaiphong) VALUES
(101, 1), (102, 2), (201, 1), (202, 2), (402, 2), (203, 3), (103, 3),
(303, 3), (104, 4), (204, 4), (304, 4), (404, 4), (501, 1);

INSERT INTO datphong (id, so_phong, id_khachhang, ngay_den, ngay_di) VALUES
(1, 101, 100, '2024-05-01', '2024-05-04'),
(2, 201, 101, '2024-05-05', '2024-05-10'),
(3, 101, 102, '2024-05-05', '2024-05-06'),
(4, 102, 102, '2024-05-05', '2024-05-06'),
(6, 101, 102, '2024-05-09', '2024-05-31'),
(7, 102, 103, '2024-05-01', '2024-05-05'),
(8, 201, 102, '2024-05-01', '2024-05-02'),
(9, 101, 106, '2024-05-01', '2024-05-01'),
(10, 202, 107, '2024-05-05', '2024-05-05'),
(11, 103, 117, '2024-05-02', '2024-05-07'),
(12, 304, 115, '2024-05-02', '2024-05-10'),
(14, 104, 116, '2024-05-20', '2024-05-25'),
(15, 203, 111, '2024-05-02', '2024-05-06'),
(16, 501, 101, '2024-05-02', '2024-05-06');
 
 