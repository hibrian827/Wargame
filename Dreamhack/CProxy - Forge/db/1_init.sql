CREATE USER 'cproxy'@'%' IDENTIFIED BY 'cproxy';

CREATE DATABASE cproxy;

GRANT ALL PRIVILEGES ON cproxy.* TO 'cproxy'@'%';

USE `cproxy`;

CREATE TABLE `responses` (
  `_id` int(11) NOT NULL AUTO_INCREMENT,
  `uid` int(11) NOT NULL,
  `res` JSON NOT NULL,
  PRIMARY KEY (`_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4;

CREATE TABLE `users` (
  `_id` int(11) NOT NULL AUTO_INCREMENT,
  `id` varchar(64) NOT NULL,
  `pw` varchar(64) NOT NULL,
  PRIMARY KEY (`_id`),
  UNIQUE KEY `id` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4;
