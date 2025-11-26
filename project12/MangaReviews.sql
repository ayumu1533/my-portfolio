-- MySQL dump 10.13  Distrib 8.4.5, for Win64 (x86_64)
--
-- Host: localhost    Database: MangaReviews
-- ------------------------------------------------------
-- Server version	8.4.5

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `affiliation_table`
--

DROP TABLE IF EXISTS `affiliation_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `affiliation_table` (
  `workID` int NOT NULL,
  `genreID` int NOT NULL,
  PRIMARY KEY (`workID`,`genreID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `affiliation_table`
--

LOCK TABLES `affiliation_table` WRITE;
/*!40000 ALTER TABLE `affiliation_table` DISABLE KEYS */;
INSERT INTO `affiliation_table` VALUES (1,1),(2,2),(3,3),(4,4),(5,3),(6,5),(7,6),(8,7),(9,8),(10,9),(11,10),(12,3),(13,11),(14,11),(15,12),(16,13),(17,14),(18,15),(19,11),(20,16);
/*!40000 ALTER TABLE `affiliation_table` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `author_favorite_table`
--

DROP TABLE IF EXISTS `author_favorite_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `author_favorite_table` (
  `authorID` int NOT NULL,
  `userID` int NOT NULL,
  PRIMARY KEY (`authorID`,`userID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `author_favorite_table`
--

LOCK TABLES `author_favorite_table` WRITE;
/*!40000 ALTER TABLE `author_favorite_table` DISABLE KEYS */;
INSERT INTO `author_favorite_table` VALUES (1,1),(2,2),(3,3),(4,4),(5,5),(6,6),(7,7),(8,8),(9,9),(10,10),(11,11),(12,12),(13,13),(14,14),(15,15),(16,16),(17,17),(18,18),(19,19),(20,20);
/*!40000 ALTER TABLE `author_favorite_table` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `author_table`
--

DROP TABLE IF EXISTS `author_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `author_table` (
  `authorID` int NOT NULL,
  `authorname` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`authorID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `author_table`
--

LOCK TABLES `author_table` WRITE;
/*!40000 ALTER TABLE `author_table` DISABLE KEYS */;
INSERT INTO `author_table` VALUES (1,'龍幸伸'),(2,'赤坂アカ×横槍メンゴ'),(3,'芥見下々'),(4,'遠藤達哉'),(5,'石田スイ'),(6,'深山フギン・丸山くがね'),(7,'山田鐘人・アベツカサ'),(8,'原泰久'),(9,'堀越耕平'),(10,'松本直也'),(11,'尾田栄一郎'),(12,'諫山創'),(13,'小林有吾'),(14,'金城宗幸・ノ村優介'),(15,'日向夏・ねこクラゲ'),(16,'藤本タツキ'),(17,'野田サトル'),(18,'泰三子'),(19,'つるまいかだ'),(20,'鈴木祐斗');
/*!40000 ALTER TABLE `author_table` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `genre_table`
--

DROP TABLE IF EXISTS `genre_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `genre_table` (
  `genreID` int NOT NULL,
  `genrename` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`genreID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `genre_table`
--

LOCK TABLES `genre_table` WRITE;
/*!40000 ALTER TABLE `genre_table` DISABLE KEYS */;
INSERT INTO `genre_table` VALUES (1,'怪奇バトル'),(2,'芸能界'),(3,'ダークファンタジー'),(4,'ホームコメディ'),(5,'異世界'),(6,'ファンタジー'),(7,'歴史・戦記'),(8,'ヒーローアクション'),(9,'SF'),(10,'海洋冒険'),(11,'サッカー・スポーツ'),(12,'ミステリー'),(13,'ダークヒーロー'),(14,'サバイバル'),(15,'お仕事コメディ'),(16,'アクションコメディ');
/*!40000 ALTER TABLE `genre_table` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `publication_table`
--

DROP TABLE IF EXISTS `publication_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `publication_table` (
  `isbn` varchar(20) NOT NULL,
  `publisherID` int DEFAULT NULL,
  `workID` int DEFAULT NULL,
  PRIMARY KEY (`isbn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `publication_table`
--

LOCK TABLES `publication_table` WRITE;
/*!40000 ALTER TABLE `publication_table` DISABLE KEYS */;
INSERT INTO `publication_table` VALUES ('9784041030246',2,6),('9784063842760',4,12),('9784065103839',4,18),('9784065122496',4,14),('9784065207438',4,19),('9784088725093',1,11),('9784088771808',1,8),('9784088792759',1,5),('9784088802653',1,9),('9784088815165',1,3),('9784088817800',1,16),('9784088820114',1,4),('9784088825256',1,10),('9784088826574',1,20),('9784088832629',1,1),('9784088900827',1,17),('9784088916507',1,2),('9784091875069',3,13),('9784098501460',3,7),('9784757554895',5,15);
/*!40000 ALTER TABLE `publication_table` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `publisher_table`
--

DROP TABLE IF EXISTS `publisher_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `publisher_table` (
  `publisherID` int NOT NULL,
  `publishername` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`publisherID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `publisher_table`
--

LOCK TABLES `publisher_table` WRITE;
/*!40000 ALTER TABLE `publisher_table` DISABLE KEYS */;
INSERT INTO `publisher_table` VALUES (1,'集英社'),(2,'KADOKAWA'),(3,'小学館'),(4,'講談社'),(5,'スクウェア・エニックス');
/*!40000 ALTER TABLE `publisher_table` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `review_table`
--

DROP TABLE IF EXISTS `review_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `review_table` (
  `reviewID` int NOT NULL,
  `rating` int DEFAULT NULL,
  `reviewarticle` varchar(200) DEFAULT NULL,
  `Posting` datetime DEFAULT NULL,
  `userID` int DEFAULT NULL,
  `workID` int DEFAULT NULL,
  PRIMARY KEY (`reviewID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `review_table`
--

LOCK TABLES `review_table` WRITE;
/*!40000 ALTER TABLE `review_table` DISABLE KEYS */;
INSERT INTO `review_table` VALUES (1,5,'面白かったです！','2025-07-10 16:20:00',1,1),(2,4,'続きが気になります。','2025-07-10 16:21:00',2,2),(3,5,'最高！','2025-07-10 16:22:00',3,3),(4,4,'家族で楽しめます。','2025-07-10 16:23:00',4,4),(5,5,'ダークな世界観が秀逸。','2025-07-10 16:24:00',5,5),(6,4,'異世界ものが好きなら。','2025-07-10 16:25:00',6,6),(7,5,'静かで美しい物語','2025-07-10 16:26:00',7,7),(8,5,'熱い。とにかく熱い','2025-07-10 16:27:00',8,8),(9,4,'王道のヒーローもの','2025-07-10 16:28:00',9,9),(10,4,'怪獣好きにはたまらない。','2025-07-10 16:29:00',10,10),(11,5,'言わずと知れた名作。','2025-07-10 16:30:00',11,11),(12,5,'衝撃的な展開の連続。','2025-07-10 16:31:00',12,12),(13,4,'サッカー漫画の新しい形。','2025-07-10 16:32:00',13,13),(14,4,'エゴイストであれ！','2025-07-10 16:33:00',14,14),(15,4,'謎解きが心地よい。','2025-07-10 16:34:00',15,15),(16,5,'ぶっ飛んでる！','2025-07-10 16:35:00',16,16),(17,5,'文化、グルメ、冒険の融合','2025-07-10 16:36:00',17,17),(18,4,'リアルで笑える警察の日常','2025-07-10 16:37:00',18,18),(19,5,'氷の上の熱いドラマ','2025-07-10 16:38:00',19,19),(20,4,'最強の殺し屋、時々日常','2025-07-10 16:39:00',20,20),(21,4,'テンポが良い。','2025-07-10 16:40:00',5,18),(22,3,'後味が良かった。','2025-07-10 16:43:00',9,14),(23,4,'原作ファンも満足。','2025-07-10 16:45:00',12,20),(24,5,'原作ファンも満足。','2025-07-10 16:50:00',9,14),(25,1,'展開が読めず面白い。','2025-07-10 16:54:00',2,19),(26,3,'キャラが立ってる。','2025-07-10 16:57:00',5,11),(27,2,'シリーズ最高傑作。','2025-07-10 17:01:00',18,4),(28,5,'ラストが衝撃的だった。','2025-07-10 17:06:00',2,12),(29,3,'原作ファンも満足。','2025-07-10 17:07:00',14,1),(30,5,'感動しました！','2025-07-10 17:09:00',1,14),(31,2,'アクション満載。','2025-07-10 17:12:00',9,12),(32,3,'泣きました。','2025-07-10 17:15:00',6,2),(33,3,'テーマが深い。','2025-07-10 17:18:00',13,15),(34,1,'設定が斬新。','2025-07-10 17:22:00',15,7),(35,4,'キャラ同士の関係が良い。','2025-07-10 17:27:00',5,8),(36,3,'セリフが印象的。','2025-07-10 17:31:00',2,6),(37,4,'テンポが良い。','2025-07-10 17:34:00',13,4),(38,3,'映像が美しい。','2025-07-10 17:35:00',17,11),(39,5,'ずっと観ていたい。','2025-07-10 17:40:00',6,4),(40,4,'ラストが衝撃的だった。','2025-07-10 17:42:00',11,6),(41,4,'キャラが立ってる。','2025-07-10 17:47:00',8,7),(42,5,'ずっと観ていたい。','2025-07-10 17:50:00',14,9),(43,2,'感動しました！','2025-07-10 17:53:00',20,13),(44,2,'後味が良かった。','2025-07-10 17:57:00',15,14),(45,5,'映像が美しい。','2025-07-10 18:02:00',19,3),(46,5,'ずっと観ていたい。','2025-07-10 18:04:00',1,9),(47,2,'後味が良かった。','2025-07-10 18:09:00',5,6),(48,4,'テンポが良い。','2025-07-10 18:13:00',19,10),(49,5,'テーマが深い。','2025-07-10 18:16:00',8,4),(50,5,'テンポが良い。','2025-07-10 18:21:00',13,7),(51,1,'泣きました。','2025-07-10 18:25:00',5,3),(52,3,'展開が読めず面白い。','2025-07-10 18:26:00',1,14),(53,4,'原作ファンも満足。','2025-07-10 18:29:00',2,11),(54,5,'キャラ同士の関係が良い。','2025-07-10 18:34:00',17,13),(55,2,'キャラが立ってる。','2025-07-10 18:35:00',8,1),(56,3,'原作ファンも満足。','2025-07-10 18:36:00',20,18),(57,4,'シリーズ最高傑作。','2025-07-10 18:38:00',19,12),(58,2,'アクション満載。','2025-07-10 18:42:00',1,9),(59,2,'テーマが深い。','2025-07-10 18:46:00',4,13),(60,1,'1話から引き込まれた。','2025-07-10 18:47:00',14,2),(61,4,'泣きました。','2025-07-10 18:50:00',16,17),(62,4,'テンポが良い。','2025-07-10 18:55:00',13,15),(63,1,'ずっと観ていたい。','2025-07-10 18:57:00',7,19),(64,1,'テーマが深い。','2025-07-10 18:59:00',1,16),(65,5,'キャラ同士の関係が良い。','2025-07-10 19:03:00',11,12),(66,5,'展開が読めず面白い。','2025-07-10 19:08:00',9,15),(67,2,'ゆったりとした世界観が良い。','2025-07-10 19:09:00',12,10),(68,3,'感動しました！','2025-07-10 19:14:00',6,6),(69,1,'映像が美しい。','2025-07-10 19:15:00',1,7),(70,5,'シリーズ最高傑作。','2025-07-10 19:16:00',17,18),(71,4,'アクション満載。','2025-07-10 19:18:00',4,4),(72,2,'声優が豪華。','2025-07-10 19:21:00',10,9),(73,3,'テンポが良い。','2025-07-10 19:26:00',8,13),(74,3,'設定が斬新。','2025-07-10 19:30:00',7,16),(75,2,'1話から引き込まれた。','2025-07-10 19:35:00',18,5),(76,3,'セリフが印象的。','2025-07-10 19:36:00',20,3),(77,3,'声優が豪華。','2025-07-10 19:38:00',6,4),(78,5,'映像が美しい。','2025-07-10 19:39:00',12,17),(79,4,'後味が良かった。','2025-07-10 19:40:00',4,1),(80,2,'感動しました！','2025-07-10 19:42:00',5,8),(81,2,'設定が斬新。','2025-07-10 19:47:00',6,10),(82,3,'セリフが印象的。','2025-07-10 19:50:00',14,5),(83,1,'声優が豪華。','2025-07-10 19:52:00',3,17),(84,2,'アクション満載。','2025-07-10 19:53:00',3,15),(85,4,'キャラが立ってる。','2025-07-10 19:55:00',16,18),(86,3,'テーマが深い。','2025-07-10 19:59:00',2,12),(87,5,'ゆったりとした世界観が良い。','2025-07-10 20:04:00',15,19),(88,1,'展開が読めず面白い。','2025-07-10 20:07:00',8,2),(89,4,'1話から引き込まれた。','2025-07-10 20:10:00',12,1),(90,3,'後味が良かった。','2025-07-10 20:13:00',17,20),(91,2,'原作ファンも満足。','2025-07-10 20:16:00',4,6),(92,5,'テンポが良い。','2025-07-10 20:18:00',7,15),(93,4,'シリーズ最高傑作。','2025-07-10 20:21:00',10,5),(94,2,'展開が読めず面白い。','2025-07-10 20:26:00',1,8),(95,3,'キャラ同士の関係が良い。','2025-07-10 20:27:00',9,10),(96,1,'映像が美しい。','2025-07-10 20:31:00',16,3),(97,5,'テンポが良い。','2025-07-10 20:33:00',6,16),(98,2,'セリフが印象的。','2025-07-10 20:35:00',20,11),(99,3,'泣きました。','2025-07-10 20:39:00',5,7),(100,1,'声優が豪華。','2025-07-10 20:43:00',19,6),(101,4,'原作ファンも満足。','2025-07-10 20:46:00',14,15),(102,5,'設定が斬新。','2025-07-10 20:49:00',11,9),(103,4,'キャラが立ってる。','2025-07-10 20:52:00',18,17),(104,5,'感動しました！','2025-07-10 20:56:00',10,14),(105,2,'アクション満載。','2025-07-10 20:59:00',2,13),(106,3,'泣きました。','2025-07-10 21:02:00',3,10),(107,1,'後味が良かった。','2025-07-10 21:04:00',4,6),(108,2,'映像が美しい。','2025-07-10 21:07:00',13,1),(109,5,'シリーズ最高傑作。','2025-07-10 21:11:00',7,18),(110,3,'テーマが深い。','2025-07-10 21:14:00',1,12),(111,4,'設定が斬新。','2025-07-10 21:18:00',17,20),(112,5,'声優が豪華。','2025-07-10 21:20:00',8,9),(113,2,'展開が読めず面白い。','2025-07-10 21:22:00',6,4),(114,3,'テンポが良い。','2025-07-10 21:25:00',15,11),(115,1,'感動しました！','2025-07-10 21:27:00',9,7),(116,5,'キャラが立ってる。','2025-07-10 21:29:00',20,16),(117,3,'シリーズ最高傑作。','2025-07-10 21:33:00',12,8),(118,1,'ゆったりとした世界観が良い。','2025-07-10 21:37:00',5,5),(119,4,'1話から引き込まれた。','2025-07-10 21:41:00',6,2),(120,5,'泣きました。','2025-07-10 21:45:00',11,3);
/*!40000 ALTER TABLE `review_table` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_table`
--

DROP TABLE IF EXISTS `user_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `user_table` (
  `userID` int NOT NULL,
  `nickname` varchar(20) DEFAULT NULL,
  `email` varchar(20) DEFAULT NULL,
  `password` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`userID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_table`
--

LOCK TABLES `user_table` WRITE;
/*!40000 ALTER TABLE `user_table` DISABLE KEYS */;
INSERT INTO `user_table` VALUES (1,'ユーザー1','user1@example.com','000001'),(2,'ユーザー2','user2@example.com','000002'),(3,'ユーザー3','user3@example.com','000003'),(4,'ユーザー4','user4@example.com','000004'),(5,'ユーザー5','user5@example.com','000005'),(6,'ユーザー6','user6@example.com','000006'),(7,'ユーザー7','user7@example.com','000007'),(8,'ユーザー8','user8@example.com','000008'),(9,'ユーザー9','user9@example.com','000009'),(10,'ユーザー10','user10@example.com','000010'),(11,'ユーザー11','user11@example.com','000011'),(12,'ユーザー12','user12@example.com','000012'),(13,'ユーザー13','user13@example.com','000013'),(14,'ユーザー14','user14@example.com','000014'),(15,'ユーザー15','user15@example.com','000015'),(16,'ユーザー16','user16@example.com','000016'),(17,'ユーザー17','user17@example.com','000017'),(18,'ユーザー18','user18@example.com','000018'),(19,'ユーザー19','user19@example.com','000019'),(20,'ユーザー20','user20@example.com','000020');
/*!40000 ALTER TABLE `user_table` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `work_favorite_table`
--

DROP TABLE IF EXISTS `work_favorite_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `work_favorite_table` (
  `userID` int NOT NULL,
  `workID` int NOT NULL,
  PRIMARY KEY (`userID`,`workID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `work_favorite_table`
--

LOCK TABLES `work_favorite_table` WRITE;
/*!40000 ALTER TABLE `work_favorite_table` DISABLE KEYS */;
INSERT INTO `work_favorite_table` VALUES (1,1),(2,2),(3,3),(4,4),(5,5),(6,6),(7,7),(8,8),(9,9),(10,10),(11,11),(12,12),(13,13),(14,14),(15,15),(16,16),(17,17),(18,18),(19,19),(20,20);
/*!40000 ALTER TABLE `work_favorite_table` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `work_table`
--

DROP TABLE IF EXISTS `work_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `work_table` (
  `workID` int DEFAULT NULL,
  `title` varchar(20) DEFAULT NULL,
  `summary` varchar(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `work_table`
--

LOCK TABLES `work_table` WRITE;
/*!40000 ALTER TABLE `work_table` DISABLE KEYS */;
INSERT INTO `work_table` VALUES (1,'ダンダダン','幽霊とUFO、相反する二つのオカルトが交差する怪奇バトル。'),(2,'「【推しの子】」','アイドルの隠し子に転生した主人公が芸能界の闇に迫る。'),(3,'呪術廻戦','負の感情から生まれる呪霊と呪術師の戦いを描くダークファンタジー。'),(4,'SPY×FAMILY','スパイ、殺し屋、超能力者が偽りの家族を築くホームコメディ。'),(5,'東京喰種','人を喰らう怪人「喰種」になってしまった青年の苦悩と戦いの物語。'),(6,'オーバーロード','ゲームの世界に閉じ込められた主人公が絶対者として君臨する異世界もの。'),(7,'葬送のフリーレン','魔王討伐後の世界で、長寿のエルフが人間の死と向き合う旅を描く。'),(8,'キングダム','中国春秋戦国時代を舞台に、大将軍を目指す少年と後の始皇帝の物語。'),(9,'僕のヒーローアカデミア','誰もが超常能力を持つ世界で、最高のヒーローを目指す少年の成長譚。'),(10,'怪獣8号','怪獣を討伐する防衛隊員になる夢を諦めた男が、怪獣の力を手に入れる。'),(11,'ONE PIECE','「ひとつなぎの大秘宝」を巡る、麦わらの一味の海洋冒険ロマン。'),(12,'進撃の巨人','巨大な壁に囲まれた世界で、人類と巨人の壮絶な戦いを描く。'),(13,'アオアシ','Jリーグのユースチームを舞台に、プロを目指す少年の成長を描くサッカー漫画。'),(14,'ブルーロック','日本をW杯優勝させるため、300人の高校生FWを競わせるサバイバル。'),(15,'薬屋のひとりごと','薬師の少女が後宮の謎を薬学的知識で解き明かすミステリー。'),(16,'チェンソーマン','チェンソーの悪魔の力を手に入れた少年が悪魔と戦うダークヒーローアクション。'),(17,'ゴールデンカムイ','明治末期の北海道を舞台に、アイヌの埋蔵金を巡るサバイバルバトル。'),(18,'ハコヅメ～交番女子の逆襲～','元警察官が描く、リアルでコミカルな交番勤務の日常。'),(19,'メダリスト','フィギュアスケートで世界を目指す少女とコーチの熱い物語。'),(20,'サカモトデイズ','最強の殺し屋だった男が、愛する家族を守るため日常と戦うアクションコメディ。');
/*!40000 ALTER TABLE `work_table` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `writing_table`
--

DROP TABLE IF EXISTS `writing_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `writing_table` (
  `authorID` int NOT NULL,
  `workID` int NOT NULL,
  PRIMARY KEY (`authorID`,`workID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `writing_table`
--

LOCK TABLES `writing_table` WRITE;
/*!40000 ALTER TABLE `writing_table` DISABLE KEYS */;
INSERT INTO `writing_table` VALUES (1,1),(2,2),(3,3),(4,4),(5,5),(6,6),(7,7),(8,8),(9,9),(10,10),(11,11),(12,12),(13,13),(14,14),(15,15),(16,16),(17,17),(18,18),(19,19),(20,20);
/*!40000 ALTER TABLE `writing_table` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-07-11 15:05:36
