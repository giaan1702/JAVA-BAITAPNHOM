-- MySQL dump 10.13  Distrib 8.0.42, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: qlks_db
-- ------------------------------------------------------
-- Server version	8.4.5

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `khachhang`
--

DROP TABLE IF EXISTS `khachhang`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `khachhang` (
  `id` int NOT NULL,
  `ho_ten` varchar(100) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `quoc_tich` varchar(50) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `loai_giay_to` enum('CCCD','Hochieu') COLLATE utf8mb4_general_ci NOT NULL,
  `so_giay_to` varchar(50) COLLATE utf8mb4_general_ci NOT NULL,
  `sdt` varchar(20) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `email` varchar(100) COLLATE utf8mb4_general_ci DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `so_giay_to` (`so_giay_to`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `khachhang`
--

LOCK TABLES `khachhang` WRITE;
/*!40000 ALTER TABLE `khachhang` DISABLE KEYS */;
INSERT INTO `khachhang` VALUES (100,'Linh Nguyen','Vietnam','CCCD','012345678001','1256','linh.nguyen@aaa.com'),(101,'Linh Tran','Vietnam','CCCD','012345678002','6823','linh.tran@aaa.com'),(102,'John Smith','USA','Hochieu','A12345678','1981','john.smith@eee.com'),(103,'Linh Pham','Vietnam','Hochieu','B98765432','1353','linh.pham@ddd.com'),(104,'Lien Hoang','Vietnam','CCCD','012345678003','5625','lien.hoang@ddd.com'),(105,'Lia Pham','Vietnam','Hochieu','C56789123','5668','lia.pham@asdas.com'),(106,'Hassan Khan','India','CCCD','IN45678910','1283','hassan.khan@tdg.com'),(107,'Hung Huy','Vietnam','CCCD','012345678004','1589','hung.huy@asdd.com'),(108,'Anna Lee','Finland','Hochieu','FIN99887766','1191','anna.lee@2frd.com'),(109,'Alice Adams','USA','Hochieu','US998877','911','alice.adams@1.com'),(110,'George Ford','USA','Hochieu','US223344','1119','george.ford@5.com'),(111,'David S.','USA','CCCD','US112233','5826','david.s@ooo.com'),(112,'Jane Doe','USA','CCCD','US332211','5689','jane.doe@256.com'),(113,'Kevin A.','USA','CCCD','US445566','5662','kevin.a@153.com'),(114,'Ian J.','USA','CCCD','US556677','15','ian.j@335.com'),(115,'Alex D.','USA','CCCD','US667788','1891','alex.d@13.com'),(116,'Dan F.','USA','CCCD','US778899','1961','dan.f@13.com'),(117,'Huy Hoang','Vietnam','CCCD','012345678005','6584','huy.hoang@152.com');
/*!40000 ALTER TABLE `khachhang` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-05-13 10:57:07
