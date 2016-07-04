DROP DATABASE IF EXISTS `c_test01`;

CREATE DATABASE  IF NOT EXISTS `c_test01` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `c_test01`;

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `lang` (languages)
--   engname: Language name in english
--   origname: Language name in its own language
--

DROP TABLE IF EXISTS `c_lang`;

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `c_lang` (
  `id` int(3) unsigned NOT NULL AUTO_INCREMENT,
  `isocode` varchar(10) NOT NULL,
  `engname`  varchar(45) NOT NULL,
  `origname` varchar(45) NOT NULL,
  `active` tinyint(1) unsigned NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

-- Try to keep 'code' in alphabetical order
INSERT INTO `c_lang` (`id`, `isocode`, `engname`, `origname`, `active`) VALUES ('1', 'en_US', 'Default (English USA)', 'Default (English USA)', '1');
INSERT INTO `c_lang` (`isocode`, `engname`, `origname`, `active`) VALUES ('eu', 'Basque', 'Euskara', '1');

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `c_user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `c_user` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `langID` int(3) unsigned NOT NULL DEFAULT '0',
  `salt` varchar(20) NOT NULL,
  `username` varchar(45) DEFAULT NULL UNIQUE,
  `password` varchar(129) DEFAULT NULL,
  `firstName` varchar(45) DEFAULT NULL,
  `lastName` varchar(45) DEFAULT NULL,
  `birthday` datetime NOT NULL DEFAULT 0,
  `address` varchar(45) DEFAULT NULL,
  `city` varchar(45) DEFAULT NULL,
  `postcode` varchar(5) DEFAULT NULL,
  `email` varchar(45) DEFAULT NULL,
  `active` tinyint(1) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  FOREIGN KEY (`langID`) 
    REFERENCES c_lang (id)
    ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;


