/*M!999999\- enable the sandbox mode */ 
-- MariaDB dump 10.19-11.5.2-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: test
-- ------------------------------------------------------
-- Server version	11.5.2-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*M!100616 SET @OLD_NOTE_VERBOSITY=@@NOTE_VERBOSITY, NOTE_VERBOSITY=0 */;

--
-- Table structure for table `new`
--

DROP TABLE IF EXISTS `new`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `new` (
  `age` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `new`
--

LOCK TABLES `new` WRITE;
/*!40000 ALTER TABLE `new` DISABLE KEYS */;
INSERT INTO `new` VALUES
(999),
(999);
/*!40000 ALTER TABLE `new` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `oskar`
--

DROP TABLE IF EXISTS `oskar`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `oskar` (
  `name` varchar(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `oskar`
--

LOCK TABLES `oskar` WRITE;
/*!40000 ALTER TABLE `oskar` DISABLE KEYS */;
INSERT INTO `oskar` VALUES
('oskar');
/*!40000 ALTER TABLE `oskar` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `simple`
--

DROP TABLE IF EXISTS `simple`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `simple` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `age` int(11) NOT NULL,
  `email` varchar(100) DEFAULT NULL,
  `nickname` varchar(100) NOT NULL DEFAULT 'snibri',
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=432 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `simple`
--

LOCK TABLES `simple` WRITE;
/*!40000 ALTER TABLE `simple` DISABLE KEYS */;
INSERT INTO `simple` VALUES
(1,'s',0,NULL,'i'),
(49,'Snibri',99,NULL,'snibri'),
(50,'Bennis',34,NULL,'snibri'),
(51,'Oskibri',30,NULL,'snibri'),
(61,'gibbgibb',99,NULL,'snibri'),
(62,'subsni',99,NULL,'snibri'),
(63,'happy',99,NULL,'snibri'),
(64,'sepsni',99,NULL,'snibri'),
(65,'gabb',99,NULL,'snibri'),
(66,'gbb',99,NULL,'brebbi'),
(67,'anothername',45,NULL,'something'),
(68,'longnameentry',23,NULL,'example'),
(69,'exampleuser',56,NULL,'test'),
(70,'demonstration',44,NULL,'showcase'),
(71,'randomuser',22,NULL,'random'),
(72,'anotherentry',31,NULL,'sample'),
(73,'addition',27,NULL,'insert'),
(74,'extra',33,NULL,'addition'),
(75,'moredata',28,NULL,'info'),
(76,'sampletext',99,NULL,'data'),
(77,'username',54,NULL,'reference'),
(78,'placeholder',29,NULL,'filler'),
(79,'testuser',32,NULL,'insert'),
(80,'dataentry',36,NULL,'storage'),
(81,'record',47,NULL,'database'),
(82,'entrypoint',51,NULL,'values'),
(83,'testing',38,NULL,'entry'),
(84,'extralongname',43,NULL,'overflow'),
(85,'additional',25,NULL,'data'),
(86,'recordname',37,NULL,'information'),
(131,'testing1',999,NULL,'snibri'),
(132,'testing2',999,NULL,'snibri'),
(133,'testing3',999,NULL,'snibri'),
(134,'testing4',999,NULL,'snibri'),
(135,'testing5',999,NULL,'snibri'),
(136,'testing6',999,NULL,'snibri'),
(137,'testing7',999,NULL,'snibri'),
(138,'testing8',999,NULL,'snibri'),
(139,'testing9',999,NULL,'snibri'),
(140,'testing10',999,NULL,'snibri'),
(141,'testing11',999,NULL,'snibri'),
(142,'testing12',999,NULL,'snibri'),
(143,'testing13',999,NULL,'snibri'),
(144,'testing14',999,NULL,'snibri'),
(145,'testing15',999,NULL,'snibri'),
(146,'testing16',999,NULL,'snibri'),
(147,'testing17',999,NULL,'snibri'),
(148,'testing18',999,NULL,'snibri'),
(149,'testing19',999,NULL,'snibri'),
(150,'testing20',999,NULL,'snibri'),
(151,'testing21',999,NULL,'snibri'),
(152,'testing22',999,NULL,'snibri'),
(153,'testing23',999,NULL,'snibri'),
(154,'testing24',999,NULL,'snibri'),
(155,'testing25',999,NULL,'snibri'),
(156,'testing26',999,NULL,'snibri'),
(157,'testing27',999,NULL,'snibri'),
(158,'testing28',999,NULL,'snibri'),
(159,'testing29',999,NULL,'snibri'),
(160,'testing30',999,NULL,'snibri'),
(161,'testing31',999,NULL,'snibri'),
(162,'testing32',999,NULL,'snibri'),
(163,'testing33',999,NULL,'snibri'),
(164,'testing34',999,NULL,'snibri'),
(165,'testing35',999,NULL,'snibri'),
(166,'testing36',999,NULL,'snibri'),
(167,'testing37',999,NULL,'snibri'),
(168,'testing38',999,NULL,'snibri'),
(169,'testing39',999,NULL,'snibri'),
(170,'testing40',999,NULL,'snibri'),
(171,'testing41',999,NULL,'snibri'),
(172,'testing42',999,NULL,'snibri'),
(173,'testing43',999,NULL,'snibri'),
(174,'testing44',999,NULL,'snibri'),
(175,'testing45',999,NULL,'snibri'),
(176,'testing46',999,NULL,'snibri'),
(177,'testing47',999,NULL,'snibri'),
(178,'testing48',999,NULL,'snibri'),
(179,'testing49',999,NULL,'snibri'),
(180,'testing50',999,NULL,'snibri'),
(181,'testing51',999,NULL,'snibri'),
(182,'testing52',999,NULL,'snibri'),
(183,'testing53',999,NULL,'snibri'),
(184,'testing54',999,NULL,'snibri'),
(185,'testing55',999,NULL,'snibri'),
(186,'testing56',999,NULL,'snibri'),
(187,'testing57',999,NULL,'snibri'),
(188,'testing58',999,NULL,'snibri'),
(189,'testing59',999,NULL,'snibri'),
(190,'testing60',999,NULL,'snibri'),
(191,'testing61',999,NULL,'snibri'),
(192,'testing62',999,NULL,'snibri'),
(193,'testing63',999,NULL,'snibri'),
(194,'testing64',999,NULL,'snibri'),
(195,'testing65',999,NULL,'snibri'),
(196,'testing66',999,NULL,'snibri'),
(197,'testing67',999,NULL,'snibri'),
(198,'testing68',999,NULL,'snibri'),
(199,'testing69',999,NULL,'snibri'),
(200,'testing70',999,NULL,'snibri'),
(201,'testing71',999,NULL,'snibri'),
(202,'testing72',999,NULL,'snibri'),
(203,'testing73',999,NULL,'snibri'),
(204,'testing74',999,NULL,'snibri'),
(205,'testing75',999,NULL,'snibri'),
(206,'testing76',999,NULL,'snibri'),
(207,'testing77',999,NULL,'snibri'),
(208,'testing78',999,NULL,'snibri'),
(209,'testing79',999,NULL,'snibri'),
(210,'testing80',999,NULL,'snibri'),
(211,'testing81',999,NULL,'snibri'),
(212,'testing82',999,NULL,'snibri'),
(213,'testing83',999,NULL,'snibri'),
(214,'testing84',999,NULL,'snibri'),
(215,'testing85',999,NULL,'snibri'),
(216,'testing86',999,NULL,'snibri'),
(217,'testing87',999,NULL,'snibri'),
(218,'testing88',999,NULL,'snibri'),
(219,'testing89',999,NULL,'snibri'),
(220,'testing90',999,NULL,'snibri'),
(221,'testing91',999,NULL,'snibri'),
(222,'testing92',999,NULL,'snibri'),
(223,'testing93',999,NULL,'snibri'),
(224,'testing94',999,NULL,'snibri'),
(225,'testing95',999,NULL,'snibri'),
(226,'testing96',999,NULL,'snibri'),
(227,'testing97',999,NULL,'snibri'),
(228,'testing98',999,NULL,'snibri'),
(229,'testing99',999,NULL,'snibri'),
(230,'testing100',999,NULL,'snibri'),
(232,'testing101',999,NULL,'snibri'),
(233,'testing102',999,NULL,'snibri'),
(234,'testing103',999,NULL,'snibri'),
(235,'testing104',999,NULL,'snibri'),
(236,'testing105',999,NULL,'snibri'),
(237,'testing106',999,NULL,'snibri'),
(238,'testing107',999,NULL,'snibri'),
(239,'testing108',999,NULL,'snibri'),
(240,'testing109',999,NULL,'snibri'),
(241,'testing110',999,NULL,'snibri'),
(242,'testing111',999,NULL,'snibri'),
(243,'testing112',999,NULL,'snibri'),
(244,'testing113',999,NULL,'snibri'),
(245,'testing114',999,NULL,'snibri'),
(246,'testing115',999,NULL,'snibri'),
(247,'testing116',999,NULL,'snibri'),
(248,'testing117',999,NULL,'snibri'),
(249,'testing118',999,NULL,'snibri'),
(250,'testing119',999,NULL,'snibri'),
(251,'testing120',999,NULL,'snibri'),
(252,'testing121',999,NULL,'snibri'),
(253,'testing122',999,NULL,'snibri'),
(254,'testing123',999,NULL,'snibri'),
(255,'testing124',999,NULL,'snibri'),
(256,'testing125',999,NULL,'snibri'),
(257,'testing126',999,NULL,'snibri'),
(258,'testing127',999,NULL,'snibri'),
(259,'testing128',999,NULL,'snibri'),
(260,'testing129',999,NULL,'snibri'),
(261,'testing130',999,NULL,'snibri'),
(262,'testing131',999,NULL,'snibri'),
(263,'testing132',999,NULL,'snibri'),
(264,'testing133',999,NULL,'snibri'),
(265,'testing134',999,NULL,'snibri'),
(266,'testing135',999,NULL,'snibri'),
(267,'testing136',999,NULL,'snibri'),
(268,'testing137',999,NULL,'snibri'),
(269,'testing138',999,NULL,'snibri'),
(270,'testing139',999,NULL,'snibri'),
(271,'testing140',999,NULL,'snibri'),
(272,'testing141',999,NULL,'snibri'),
(273,'testing142',999,NULL,'snibri'),
(274,'testing143',999,NULL,'snibri'),
(275,'testing144',999,NULL,'snibri'),
(276,'testing145',999,NULL,'snibri'),
(277,'testing146',999,NULL,'snibri'),
(278,'testing147',999,NULL,'snibri'),
(279,'testing148',999,NULL,'snibri'),
(280,'testing149',999,NULL,'snibri'),
(281,'testing150',999,NULL,'snibri'),
(282,'testing151',999,NULL,'snibri'),
(283,'testing152',999,NULL,'snibri'),
(284,'testing153',999,NULL,'snibri'),
(285,'testing154',999,NULL,'snibri'),
(286,'testing155',999,NULL,'snibri'),
(287,'testing156',999,NULL,'snibri'),
(288,'testing157',999,NULL,'snibri'),
(289,'testing158',999,NULL,'snibri'),
(290,'testing159',999,NULL,'snibri'),
(291,'testing160',999,NULL,'snibri'),
(292,'testing161',999,NULL,'snibri'),
(293,'testing162',999,NULL,'snibri'),
(294,'testing163',999,NULL,'snibri'),
(295,'testing164',999,NULL,'snibri'),
(296,'testing165',999,NULL,'snibri'),
(297,'testing166',999,NULL,'snibri'),
(298,'testing167',999,NULL,'snibri'),
(299,'testing168',999,NULL,'snibri'),
(300,'testing169',999,NULL,'snibri'),
(301,'testing170',999,NULL,'snibri'),
(302,'testing171',999,NULL,'snibri'),
(303,'testing172',999,NULL,'snibri'),
(304,'testing173',999,NULL,'snibri'),
(305,'testing174',999,NULL,'snibri'),
(306,'testing175',999,NULL,'snibri'),
(307,'testing176',999,NULL,'snibri'),
(308,'testing177',999,NULL,'snibri'),
(309,'testing178',999,NULL,'snibri'),
(310,'testing179',999,NULL,'snibri'),
(311,'testing180',999,NULL,'snibri'),
(312,'testing181',999,NULL,'snibri'),
(313,'testing182',999,NULL,'snibri'),
(314,'testing183',999,NULL,'snibri'),
(315,'testing184',999,NULL,'snibri'),
(316,'testing185',999,NULL,'snibri'),
(317,'testing186',999,NULL,'snibri'),
(318,'testing187',999,NULL,'snibri'),
(319,'testing188',999,NULL,'snibri'),
(320,'testing189',999,NULL,'snibri'),
(321,'testing190',999,NULL,'snibri'),
(322,'testing191',999,NULL,'snibri'),
(323,'testing192',999,NULL,'snibri'),
(324,'testing193',999,NULL,'snibri'),
(325,'testing194',999,NULL,'snibri'),
(326,'testing195',999,NULL,'snibri'),
(327,'testing196',999,NULL,'snibri'),
(328,'testing197',999,NULL,'snibri'),
(329,'testing198',999,NULL,'snibri'),
(330,'testing199',999,NULL,'snibri'),
(331,'testing200',999,NULL,'snibri'),
(332,'testing201',999,NULL,'snibri'),
(333,'testing202',999,NULL,'snibri'),
(334,'testing203',999,NULL,'snibri'),
(335,'testing204',999,NULL,'snibri'),
(336,'testing205',999,NULL,'snibri'),
(337,'testing206',999,NULL,'snibri'),
(338,'testing207',999,NULL,'snibri'),
(339,'testing208',999,NULL,'snibri'),
(340,'testing209',999,NULL,'snibri'),
(341,'testing210',999,NULL,'snibri'),
(342,'testing211',999,NULL,'snibri'),
(343,'testing212',999,NULL,'snibri'),
(344,'testing213',999,NULL,'snibri'),
(345,'testing214',999,NULL,'snibri'),
(346,'testing215',999,NULL,'snibri'),
(347,'testing216',999,NULL,'snibri'),
(348,'testing217',999,NULL,'snibri'),
(349,'testing218',999,NULL,'snibri'),
(350,'testing219',999,NULL,'snibri'),
(351,'testing220',999,NULL,'snibri'),
(352,'testing221',999,NULL,'snibri'),
(353,'testing222',999,NULL,'snibri'),
(354,'testing223',999,NULL,'snibri'),
(355,'testing224',999,NULL,'snibri'),
(356,'testing225',999,NULL,'snibri'),
(357,'testing226',999,NULL,'snibri'),
(358,'testing227',999,NULL,'snibri'),
(359,'testing228',999,NULL,'snibri'),
(360,'testing229',999,NULL,'snibri'),
(361,'testing230',999,NULL,'snibri'),
(362,'testing231',999,NULL,'snibri'),
(363,'testing232',999,NULL,'snibri'),
(364,'testing233',999,NULL,'snibri'),
(365,'testing234',999,NULL,'snibri'),
(366,'testing235',999,NULL,'snibri'),
(367,'testing236',999,NULL,'snibri'),
(368,'testing237',999,NULL,'snibri'),
(369,'testing238',999,NULL,'snibri'),
(370,'testing239',999,NULL,'snibri'),
(371,'testing240',999,NULL,'snibri'),
(372,'testing241',999,NULL,'snibri'),
(373,'testing242',999,NULL,'snibri'),
(374,'testing243',999,NULL,'snibri'),
(375,'testing244',999,NULL,'snibri'),
(376,'testing245',999,NULL,'snibri'),
(377,'testing246',999,NULL,'snibri'),
(378,'testing247',999,NULL,'snibri'),
(379,'testing248',999,NULL,'snibri'),
(380,'testing249',999,NULL,'snibri'),
(381,'testing250',999,NULL,'snibri'),
(382,'testing251',999,NULL,'snibri'),
(383,'testing252',999,NULL,'snibri'),
(384,'testing253',999,NULL,'snibri'),
(385,'testing254',999,NULL,'snibri'),
(386,'testing255',999,NULL,'snibri'),
(387,'testing256',999,NULL,'snibri'),
(388,'testing257',999,NULL,'snibri'),
(389,'testing258',999,NULL,'snibri'),
(390,'testing259',999,NULL,'snibri'),
(391,'testing260',999,NULL,'snibri'),
(392,'testing261',999,NULL,'snibri'),
(393,'testing262',999,NULL,'snibri'),
(394,'testing263',999,NULL,'snibri'),
(395,'testing264',999,NULL,'snibri'),
(396,'testing265',999,NULL,'snibri'),
(397,'testing266',999,NULL,'snibri'),
(398,'testing267',999,NULL,'snibri'),
(399,'testing268',999,NULL,'snibri'),
(400,'testing269',999,NULL,'snibri'),
(401,'testing270',999,NULL,'snibri'),
(402,'testing271',999,NULL,'snibri'),
(403,'testing272',999,NULL,'snibri'),
(404,'testing273',999,NULL,'snibri'),
(405,'testing274',999,NULL,'snibri'),
(406,'testing275',999,NULL,'snibri'),
(407,'testing276',999,NULL,'snibri'),
(408,'testing277',999,NULL,'snibri'),
(409,'testing278',999,NULL,'snibri'),
(410,'testing279',999,NULL,'snibri'),
(411,'testing280',999,NULL,'snibri'),
(412,'testing281',999,NULL,'snibri'),
(413,'testing282',999,NULL,'snibri'),
(414,'testing283',999,NULL,'snibri'),
(415,'testing284',999,NULL,'snibri'),
(416,'testing285',999,NULL,'snibri'),
(417,'testing286',999,NULL,'snibri'),
(418,'testing287',999,NULL,'snibri'),
(419,'testing288',999,NULL,'snibri'),
(420,'testing289',999,NULL,'snibri'),
(421,'testing290',999,NULL,'snibri'),
(422,'testing291',999,NULL,'snibri'),
(423,'testing292',999,NULL,'snibri'),
(424,'testing293',999,NULL,'snibri'),
(425,'testing294',999,NULL,'snibri'),
(426,'testing295',999,NULL,'snibri'),
(427,'testing296',999,NULL,'snibri'),
(428,'testing297',999,NULL,'snibri'),
(429,'testing298',999,NULL,'snibri'),
(430,'testing299',999,NULL,'snibri'),
(431,'testing300',999,NULL,'snibri');
/*!40000 ALTER TABLE `simple` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `table1`
--

DROP TABLE IF EXISTS `table1`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `table1` (
  `name` varchar(100) DEFAULT NULL,
  `age` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `table1`
--

LOCK TABLES `table1` WRITE;
/*!40000 ALTER TABLE `table1` DISABLE KEYS */;
INSERT INTO `table1` VALUES
('User0',20),
('User1',21),
('User2',22),
('User3',23),
('User4',24);
/*!40000 ALTER TABLE `table1` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `table2`
--

DROP TABLE IF EXISTS `table2`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `table2` (
  `name` varchar(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `table2`
--

LOCK TABLES `table2` WRITE;
/*!40000 ALTER TABLE `table2` DISABLE KEYS */;
/*!40000 ALTER TABLE `table2` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(100) NOT NULL,
  `age` int(11) NOT NULL,
  `email` varchar(100) DEFAULT NULL,
  `created` timestamp NULL DEFAULT current_timestamp(),
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`),
  UNIQUE KEY `email` (`email`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES
(1,'oskar',30,NULL,'2024-11-07 21:59:56'),
(2,'benedicte',34,NULL,'2024-11-07 23:27:56');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*M!100616 SET NOTE_VERBOSITY=@OLD_NOTE_VERBOSITY */;

-- Dump completed on 2024-11-15 10:41:20
