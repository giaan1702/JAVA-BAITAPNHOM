-- Tài khoản người dùng
CREATE TABLE users (
    id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) NOT NULL UNIQUE,
    password VARCHAR(100) NOT NULL,
    role INT NOT NULL CHECK (role IN (0, 1))
);

-- Khách hàng
CREATE TABLE khachhang (
    id INT PRIMARY KEY,
    ho_ten VARCHAR(100),
    quoc_tich VARCHAR(50),
    loai_giay_to ENUM('CCCD', 'Hochieu') NOT NULL,
    so_giay_to VARCHAR(50) NOT NULL UNIQUE,
    sdt VARCHAR(20),
    email VARCHAR(100)
);

-- Loại phòng
CREATE TABLE loaiphong (
    id INT PRIMARY KEY,
    ten_loai_phong VARCHAR(100),
    gia INT NOT NULL
);

-- Phòng
CREATE TABLE phong (
    so_phong INT PRIMARY KEY,
    id_loaiphong INT,
    FOREIGN KEY (id_loaiphong) REFERENCES loaiphong(id)
);

-- Đặt phòng
CREATE TABLE datphong (
    id INT PRIMARY KEY,
    so_phong INT,
    id_khachhang INT,
    ngay_den DATE,
    ngay_di DATE,
    FOREIGN KEY (so_phong) REFERENCES phong(so_phong),
    FOREIGN KEY (id_khachhang) REFERENCES khachhang(id)
);
