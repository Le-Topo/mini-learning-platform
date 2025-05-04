-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: May 04, 2025 at 06:36 PM
-- Server version: 8.3.0
-- PHP Version: 8.2.18

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `mini-learning-platform`
--

-- --------------------------------------------------------

--
-- Table structure for table `courses`
--

DROP TABLE IF EXISTS `courses`;
CREATE TABLE IF NOT EXISTS `courses` (
  `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT,
  `instructor_id` bigint UNSIGNED NOT NULL,
  `title` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `description` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `level` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT '1' COMMENT '1 = beginner, 2 = intermediate, 3 = advanced',
  `duration` tinyint NOT NULL DEFAULT '0' COMMENT 'Duration in hours',
  `is_validated` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'Is the course validated by the admin?',
  `validation_message` varchar(191) COLLATE utf8mb4_unicode_ci DEFAULT NULL COMMENT 'Message from the admin if the course is not validated',
  `tags` varchar(191) COLLATE utf8mb4_unicode_ci DEFAULT NULL COMMENT 'Comma-separated list of tags for the course',
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `courses_instructor_id_foreign` (`instructor_id`)
) ENGINE=MyISAM AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `courses`
--

INSERT INTO `courses` (`id`, `instructor_id`, `title`, `description`, `level`, `duration`, `is_validated`, `validation_message`, `tags`, `created_at`, `updated_at`) VALUES
(1, 1, 'Introduction a la programmation', 'Apprenez les bases de la programmation avec ce cours d\'introduction.', '1', 10, 1, NULL, 'programming, introduction', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(2, 2, 'Developpement web avance', 'Approfondissez vos connaissances en developpement web avec ce cours avance.', '3', 20, 1, NULL, 'web development, advanced', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(3, 3, 'Data Science pour les debutants', 'Decouvrez les concepts fondamentaux de la science des donnees.', '1', 15, 1, NULL, 'data science, beginners', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(4, 1, 'Machine Learning avec Python', 'Apprenez a creer des modèles de machine learning avec Python.', '2', 25, 1, NULL, 'machine learning, python', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(5, 2, 'Introduction a l\'intelligence artificielle', 'Explorez les concepts de base de l\'intelligence artificielle.', '1', 12, 1, NULL, 'artificial intelligence, introduction', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(6, 3, 'Developpement mobile avec Flutter', 'Apprenez a creer des applications mobiles avec Flutter.', '2', 18, 1, NULL, 'mobile development, flutter', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(7, 1, 'Cybersecurite pour les debutants', 'Decouvrez les bases de la cybersecurite et comment proteger vos donnees.', '1', 14, 1, NULL, 'cybersecurity, beginners', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(8, 2, 'Blockchain et Cryptomonnaies', 'Comprenez le fonctionnement de la blockchain et des cryptomonnaies.', '2', 22, 1, NULL, 'blockchain, cryptocurrencies', '2025-05-04 22:36:16', '2025-05-04 22:36:16');

-- --------------------------------------------------------

--
-- Table structure for table `course_learner`
--

DROP TABLE IF EXISTS `course_learner`;
CREATE TABLE IF NOT EXISTS `course_learner` (
  `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT,
  `learner_id` bigint UNSIGNED NOT NULL,
  `course_id` bigint UNSIGNED NOT NULL,
  `current_part_id` bigint UNSIGNED DEFAULT NULL,
  `status` tinyint NOT NULL DEFAULT '0' COMMENT 'Status of the learner in the course: 0 = in progress, 1 = completed',
  `progress` tinyint NOT NULL DEFAULT '0' COMMENT 'Progress of the learner in the course, as a percentage',
  `score` tinyint NOT NULL DEFAULT '0' COMMENT 'Score of the learner in the course quiz, if applicable',
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `course_learner_learner_id_foreign` (`learner_id`),
  KEY `course_learner_course_id_foreign` (`course_id`),
  KEY `course_learner_current_part_id_foreign` (`current_part_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `course_parts`
--

DROP TABLE IF EXISTS `course_parts`;
CREATE TABLE IF NOT EXISTS `course_parts` (
  `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT,
  `course_id` bigint UNSIGNED NOT NULL,
  `title` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `is_quiz` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'Is this part a quiz?',
  `content` text COLLATE utf8mb4_unicode_ci COMMENT 'Content of the course part in plain text, if not a quiz',
  `order` tinyint NOT NULL DEFAULT '0' COMMENT 'Order of the course part in the course',
  `score_percentage` tinyint NOT NULL DEFAULT '0' COMMENT 'Score percentage for this part, if it is a quiz',
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `course_parts_course_id_foreign` (`course_id`)
) ENGINE=MyISAM AUTO_INCREMENT=34 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `course_parts`
--

INSERT INTO `course_parts` (`id`, `course_id`, `title`, `is_quiz`, `content`, `order`, `score_percentage`, `created_at`, `updated_at`) VALUES
(1, 1, 'Introduction', 0, 'Bienvenue dans le cours de programmation. Dans cette section, nous allons explorer les concepts de base de la programmation.\nVous apprendrez les differents types de langages de programmation et comment choisir celui qui vous convient le mieux.\nNous aborderons egalement les outils et environnements de developpement que vous utiliserez tout au long de ce cours.\nA la fin de cette section, vous aurez une comprehension solide des bases de la programmation et serez prêt a plonger dans les langages specifiques.\nNous vous encourageons a poser des questions et a interagir avec vos camarades de classe pour tirer le meilleur parti de cette experience d\'apprentissage.', 1, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(2, 1, 'Quiz 1', 1, NULL, 2, 100, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(3, 1, 'Les langages de programmation', 0, 'Dans cette section, nous allons explorer les differents types de langages de programmation.\nVous apprendrez les differences entre les langages compiles et interpretes, ainsi que les langages de haut niveau et de bas niveau.\nNous aborderons egalement les langages orientes objet et fonctionnels, et comment choisir le bon langage pour votre projet.\nA la fin de cette section, vous aurez une comprehension solide des differents types de langages de programmation et serez prêt a choisir celui qui vous convient le mieux.', 1, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(4, 1, 'Quiz 2', 1, NULL, 2, 100, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(5, 1, 'Conclusion', 0, 'Felicitations d\'avoir termine cette section ! Vous avez maintenant une bonne comprehension des bases de la programmation.\nDans la prochaine section, nous allons plonger dans les langages de programmation specifiques et explorer leurs caracteristiques uniques.\nN\'oubliez pas de revoir le materiel et de pratiquer ce que vous avez appris. Bonne chance !', 3, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(6, 2, 'Introduction au developpement web avance', 0, 'Dans ce cours, nous allons explorer les concepts avances du developpement web.\nVous apprendrez a creer des applications web dynamiques et interactives en utilisant les dernières technologies.\nNous aborderons egalement les meilleures pratiques en matière de securite et de performance.', 1, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(7, 2, 'Quiz introduction', 1, NULL, 2, 100, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(8, 2, 'Les meilleures pratiques en developpement web', 0, 'Dans cette section, nous allons explorer les meilleures pratiques en matière de developpement web.\nVous apprendrez a creer des applications web securisees et performantes en suivant les normes de l\'industrie.\nNous aborderons egalement les outils et techniques pour optimiser vos applications web.', 3, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(9, 2, 'Quiz meilleures pratiques', 1, NULL, 4, 100, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(10, 2, 'Conclusion', 0, 'Felicitations d\'avoir termine ce cours avance sur le developpement web ! Vous avez acquis des competences precieuses qui vous aideront a creer des applications web de haute qualite. N\'oubliez pas de continuer a pratiquer et a explorer de nouvelles technologies.', 3, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(11, 3, 'Introduction a la science des donnees', 0, 'Dans cette section, nous allons explorer les concepts fondamentaux de la science des donnees.\nVous apprendrez ce qu\'est la science des donnees, son importance et comment elle est utilisee dans le monde reel.\nNous aborderons egalement les outils et techniques couramment utilises en science des donnees.', 1, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(12, 3, 'Mini QUiz', 1, NULL, 2, 100, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(13, 3, 'Conclusion', 0, 'Felicitations d\'avoir termine cette section sur la science des donnees ! Vous avez acquis une comprehension solide des concepts fondamentaux et des outils utilises en science des donnees. Dans la prochaine section, nous allons plonger dans les techniques d\'analyse de donnees et d\'apprentissage automatique.', 3, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(14, 4, 'Introduction au machine learning', 0, 'Dans cette section, nous allons explorer les concepts fondamentaux du machine learning.\nVous apprendrez ce qu\'est le machine learning, ses applications et comment il fonctionne.\nNous aborderons egalement les differents types de modèles de machine learning et comment choisir celui qui convient le mieux a votre problème.', 1, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(15, 4, 'Questionnaire 1', 1, NULL, 2, 100, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(16, 4, 'Les algorithmes de machine learning', 0, 'Dans cette section, nous allons explorer les differents types d\'algorithmes de machine learning.\nVous apprendrez les differences entre l\'apprentissage supervise et non supervise, ainsi que les algorithmes de classification et de regression.\nNous aborderons egalement les outils et bibliothèques couramment utilises en machine learning.', 3, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(17, 4, 'Questionnaire 2', 1, NULL, 4, 100, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(18, 4, 'Conclusion', 0, 'Felicitations d\'avoir termine cette section sur le machine learning ! Vous avez acquis une comprehension solide des concepts fondamentaux et des outils utilises en machine learning. Dans la prochaine section, nous allons plonger dans les techniques avancees de machine learning et comment les appliquer a des problèmes reels.', 3, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(19, 5, 'Introduction a l\'IA', 0, 'Dans cette section, nous allons explorer les concepts fondamentaux de l\'intelligence artificielle.\nVous apprendrez ce qu\'est l\'IA, ses applications et comment elle fonctionne.\nNous aborderons egalement les differents types d\'algorithmes d\'IA et comment choisir celui qui convient le mieux a votre problème.\nA la fin de cette section, vous aurez une comprehension solide des concepts fondamentaux de l\'IA et serez prêt a plonger dans les algorithmes specifiques.', 1, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(20, 5, 'Quiz introduction', 1, NULL, 2, 100, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(21, 5, 'Les algorithmes d\'IA', 0, 'Dans cette section, nous allons explorer les differents types d\'algorithmes d\'intelligence artificielle.\nVous apprendrez les differences entre l\'apprentissage supervise et non supervise, ainsi que les algorithmes de classification et de regression.\nNous aborderons egalement les outils et bibliothèques couramment utilises en IA.', 3, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(22, 5, 'Quiz algorithmes', 1, NULL, 4, 100, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(23, 5, 'Les applications de l\'IA', 0, 'Dans cette section, nous allons explorer les differentes applications de l\'intelligence artificielle.\nVous apprendrez comment l\'IA est utilisee dans divers domaines tels que la sante, la finance et le divertissement.\nNous aborderons egalement les defis et les opportunites lies a l\'utilisation de l\'IA dans le monde reel.', 1, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(24, 5, 'Conclusion', 0, 'Felicitations d\'avoir termine cette section sur l\'intelligence artificielle ! Vous avez acquis une comprehension solide des concepts fondamentaux et des outils utilises en IA. Dans la prochaine section, nous allons plonger dans les techniques avancees d\'IA et comment les appliquer a des problèmes reels.', 3, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(25, 6, 'Introduction au developpement mobile', 0, 'Dans cette section, nous allons explorer les concepts fondamentaux du developpement mobile.\nVous apprendrez a creer des applications mobiles avec Flutter et Dart.\nNous aborderons egalement les meilleures pratiques en matière de conception d\'interface utilisateur et d\'experience utilisateur.', 1, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(26, 6, 'Petit Quiz', 1, NULL, 2, 100, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(27, 6, 'Conclusion', 0, 'Felicitations d\'avoir termine cette section sur le developpement mobile avec Flutter ! Vous avez acquis une comprehension solide des concepts fondamentaux et des outils utilises en developpement mobile. Dans la prochaine section, nous allons plonger dans les techniques avancees de developpement mobile et comment les appliquer a des problèmes reels.', 3, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(28, 7, 'Introduction a la cybersecurite', 0, 'Dans cette section, nous allons explorer les concepts fondamentaux de la cybersecurite.\nVous apprendrez ce qu\'est la cybersecurite, son importance et comment elle est utilisee dans le monde reel.\nNous aborderons egalement les outils et techniques couramment utilises en cybersecurite.', 1, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(29, 7, 'Quiz introduction', 1, NULL, 2, 100, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(30, 7, 'Conclusion', 0, 'Felicitations d\'avoir termine cette section sur la cybersecurite ! Vous avez acquis une comprehension solide des concepts fondamentaux et des outils utilises en cybersecurite. Dans la prochaine section, nous allons plonger dans les techniques avancees de cybersecurite et comment les appliquer a des problèmes reels.', 3, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(31, 8, 'Introduction a la blockchain', 0, 'Dans cette section, nous allons explorer les concepts fondamentaux de la blockchain.\nVous apprendrez ce qu\'est la blockchain, son importance et comment elle est utilisee dans le monde reel.\nNous aborderons egalement les differents types de blockchains et comment choisir celui qui convient le mieux a votre problème.', 1, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(32, 8, 'Quiz introduction', 1, NULL, 2, 100, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(33, 8, 'Conclusion', 0, 'Felicitations d\'avoir termine cette section sur la blockchain ! Vous avez acquis une comprehension solide des concepts fondamentaux et des outils utilises en blockchain. Dans la prochaine section, nous allons plonger dans les techniques avancees de blockchain et comment les appliquer a des problèmes reels.', 3, 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16');

-- --------------------------------------------------------

--
-- Table structure for table `learner_progress`
--

DROP TABLE IF EXISTS `learner_progress`;
CREATE TABLE IF NOT EXISTS `learner_progress` (
  `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT,
  `learner_id` bigint UNSIGNED NOT NULL,
  `course_part_id` bigint UNSIGNED NOT NULL,
  `score` tinyint NOT NULL DEFAULT '0' COMMENT 'Score of the learner in this part, if applicable',
  `started_at` timestamp NULL DEFAULT NULL COMMENT 'Timestamp when the learner started this part',
  `completed_at` timestamp NULL DEFAULT NULL COMMENT 'Timestamp when the learner completed this part',
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `learner_progress_learner_id_foreign` (`learner_id`),
  KEY `learner_progress_course_part_id_foreign` (`course_part_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `learner_quiz_answers`
--

DROP TABLE IF EXISTS `learner_quiz_answers`;
CREATE TABLE IF NOT EXISTS `learner_quiz_answers` (
  `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT,
  `learner_id` bigint UNSIGNED NOT NULL,
  `question_id` bigint UNSIGNED NOT NULL,
  `answer_id` bigint UNSIGNED NOT NULL,
  `is_correct` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'Is this answer correct?',
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `learner_quiz_answers_learner_id_foreign` (`learner_id`),
  KEY `learner_quiz_answers_question_id_foreign` (`question_id`),
  KEY `learner_quiz_answers_answer_id_foreign` (`answer_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `migrations`
--

DROP TABLE IF EXISTS `migrations`;
CREATE TABLE IF NOT EXISTS `migrations` (
  `id` int UNSIGNED NOT NULL AUTO_INCREMENT,
  `migration` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `batch` int NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `migrations`
--

INSERT INTO `migrations` (`id`, `migration`, `batch`) VALUES
(1, '0001_01_01_000000_create_users_table', 1),
(2, '2025_04_06_161147_create_courses_table', 1),
(3, '2025_04_06_161203_create_course_parts_table', 1),
(4, '2025_04_06_161223_create_quiz_questions_table', 1),
(5, '2025_04_06_161238_create_quiz_answer_suggestions_table', 1),
(6, '2025_04_06_161318_create_learner_quiz_answers_table', 1),
(7, '2025_04_06_161355_create_course_learner_table', 1),
(8, '2025_04_06_161532_create_learner_progress_table', 1),
(9, '2025_04_06_161616_create_sessions_table', 1);

-- --------------------------------------------------------

--
-- Table structure for table `quiz_answer_suggestions`
--

DROP TABLE IF EXISTS `quiz_answer_suggestions`;
CREATE TABLE IF NOT EXISTS `quiz_answer_suggestions` (
  `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT,
  `question_id` bigint UNSIGNED NOT NULL,
  `label` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'Label of the answer suggestion',
  `is_correct` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'Is this answer suggestion correct?',
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `quiz_answer_suggestions_question_id_foreign` (`question_id`)
) ENGINE=MyISAM AUTO_INCREMENT=98 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `quiz_answer_suggestions`
--

INSERT INTO `quiz_answer_suggestions` (`id`, `question_id`, `label`, `is_correct`, `created_at`, `updated_at`) VALUES
(1, 1, '3', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(2, 1, '5', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(3, 1, '2', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(4, 1, '1', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(5, 2, 'Python', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(6, 2, 'Java', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(7, 2, 'C++', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(8, 2, 'Ruby', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(9, 2, 'C', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(10, 3, 'Visual Studio Code', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(11, 3, 'Eclipse', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(12, 3, 'NetBeans', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(13, 3, 'Sublime Text', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(14, 4, 'Python', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(15, 4, 'C++', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(16, 4, 'Java', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(17, 4, 'Ruby', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(18, 5, 'React', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(19, 5, 'Angular', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(20, 5, 'Vue.js', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(21, 5, 'jQuery', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(22, 6, 'HTTPS', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(23, 6, 'HTTP', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(24, 6, 'FTP', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(25, 6, 'SFTP', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(26, 7, 'Hachage et salage', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(27, 7, 'Stockage en clair', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(28, 7, 'Chiffrement symetrique', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(29, 7, 'Chiffrement asymetrique', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(30, 8, 'Postman', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(31, 8, 'Photoshop', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(32, 8, 'Illustrator', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(33, 8, 'Sketch', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(34, 9, 'L\'etude des donnees pour en tirer des informations', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(35, 9, 'Un type de programmation', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(36, 9, 'Une methode de stockage de donnees', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(37, 9, 'Un langage de programmation', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(38, 10, 'Python', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(39, 10, 'HTML', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(40, 10, 'CSS', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(41, 10, 'JavaScript', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(42, 11, 'L\'apprentissage automatique des ordinateurs a partir des donnees', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(43, 11, 'Un type de programmation', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(44, 11, 'Une methode de stockage de donnees', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(45, 11, 'Un langage de programmation', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(46, 12, 'Python', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(47, 12, 'HTML', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(48, 12, 'CSS', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(49, 12, 'JavaScript', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(50, 13, 'Regression lineaire', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(51, 13, 'HTML', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(52, 13, 'CSS', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(53, 13, 'JavaScript', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(54, 14, 'Scikit-learn', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(55, 14, 'HTML', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(56, 14, 'CSS', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(57, 14, 'JavaScript', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(58, 15, 'L\'apprentissage automatique des ordinateurs a partir des donnees', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(59, 15, 'Un type de programmation', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(60, 15, 'Une methode de stockage de donnees', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(61, 15, 'Un langage de programmation', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(62, 16, 'Python', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(63, 16, 'HTML', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(64, 16, 'CSS', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(65, 16, 'JavaScript', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(66, 17, 'Reseaux de neurones', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(67, 17, 'HTML', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(68, 17, 'CSS', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(69, 17, 'JavaScript', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(70, 18, 'TensorFlow', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(71, 18, 'HTML', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(72, 18, 'CSS', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(73, 18, 'JavaScript', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(74, 19, 'Dart', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(75, 19, 'Java', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(76, 19, 'Kotlin', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(77, 19, 'Swift', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(78, 20, 'Developpement multiplateforme', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(79, 20, 'Langage de programmation complexe', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(80, 20, 'Pas de support pour les widgets', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(81, 20, 'Pas de communaute active', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(82, 21, 'La protection des systèmes informatiques contre les cyberattaques', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(83, 21, 'Un type de programmation', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(84, 21, 'Une methode de stockage de donnees', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(85, 21, 'Un langage de programmation', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(86, 22, 'Wireshark', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(87, 22, 'HTML', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(88, 22, 'CSS', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(89, 22, 'JavaScript', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(90, 23, 'Un registre decentralise et immuable', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(91, 23, 'Un type de programmation', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(92, 23, 'Une methode de stockage de donnees', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(93, 23, 'Un langage de programmation', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(94, 24, 'Securite et transparence', 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(95, 24, 'Langage de programmation complexe', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(96, 24, 'Pas de support pour les transactions', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(97, 24, 'Pas de communaute active', 0, '2025-05-04 22:36:16', '2025-05-04 22:36:16');

-- --------------------------------------------------------

--
-- Table structure for table `quiz_questions`
--

DROP TABLE IF EXISTS `quiz_questions`;
CREATE TABLE IF NOT EXISTS `quiz_questions` (
  `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT,
  `course_part_id` bigint UNSIGNED NOT NULL,
  `label` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'Label of the question, e.g., "Question 1"',
  `has_multiple_answers` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'Does this question allow multiple answers?',
  `order` tinyint NOT NULL DEFAULT '0' COMMENT 'Order of the question in the quiz',
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `quiz_questions_course_part_id_foreign` (`course_part_id`)
) ENGINE=MyISAM AUTO_INCREMENT=25 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `quiz_questions`
--

INSERT INTO `quiz_questions` (`id`, `course_part_id`, `label`, `has_multiple_answers`, `order`, `created_at`, `updated_at`) VALUES
(1, 2, 'Combien de types de langages de programmation existe-t-il ?', 0, 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(2, 2, 'Quel est le langage de programmation le plus populaire ?', 0, 2, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(3, 4, 'Quel est l\'environnement de developpement le plus populaire ?', 0, 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(4, 4, 'Quel est le meilleur langage de programmation pour les debutants ?', 0, 2, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(5, 7, 'Quel est le framework JavaScript le plus populaire ?', 0, 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(6, 7, 'Quelle methode est utilisee pour securiser les applications web ?', 0, 2, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(7, 9, 'Quelle est la meilleure pratique pour securiser les mots de passe ?', 0, 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(8, 9, 'Quel est l\'un des outils les plus populaires pour le developpement web ?', 0, 2, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(9, 12, 'Qu\'est-ce que la science des donnees ?', 0, 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(10, 12, 'Quel est l\'un des outils les plus populaires en science des donnees ?', 0, 2, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(11, 15, 'Qu\'est-ce que le machine learning ?', 0, 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(12, 15, 'Quel est l\'un des langages les plus populaires pour le machine learning ?', 0, 2, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(13, 17, 'Quel est l\'un des algorithmes de machine learning les plus populaires ?', 0, 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(14, 17, 'Quel est l\'un des outils les plus populaires pour le machine learning ?', 0, 2, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(15, 20, 'Qu\'est-ce que l\'intelligence artificielle ?', 0, 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(16, 20, 'Quel est l\'un des langages les plus populaires pour l\'intelligence artificielle ?', 0, 2, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(17, 22, 'Quel est l\'un des algorithmes d\'intelligence artificielle les plus populaires ?', 0, 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(18, 22, 'Quel est l\'un des outils les plus populaires pour l\'intelligence artificielle ?', 0, 2, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(19, 26, 'Quel est le langage de programmation utilise avec Flutter ?', 0, 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(20, 26, 'Quel est l\'un des avantages de Flutter ?', 0, 2, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(21, 29, 'Qu\'est-ce que la cybersecurite ?', 0, 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(22, 29, 'Quel est l\'un des outils les plus populaires en cybersecurite ?', 0, 2, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(23, 32, 'Qu\'est-ce que la blockchain ?', 0, 1, '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(24, 32, 'Quel est l\'un des avantages de la blockchain ?', 0, 2, '2025-05-04 22:36:16', '2025-05-04 22:36:16');

-- --------------------------------------------------------

--
-- Table structure for table `sessions`
--

DROP TABLE IF EXISTS `sessions`;
CREATE TABLE IF NOT EXISTS `sessions` (
  `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_id` bigint UNSIGNED NOT NULL,
  `closed_at` timestamp NULL DEFAULT NULL COMMENT 'Timestamp when the session was closed',
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `sessions_user_id_foreign` (`user_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
CREATE TABLE IF NOT EXISTS `users` (
  `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT,
  `email` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `firstname` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `lastname` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `role` tinyint NOT NULL DEFAULT '1' COMMENT '1 = learner, 2 = teacher, 99 = admin',
  `distinction` varchar(191) COLLATE utf8mb4_unicode_ci DEFAULT NULL COMMENT 'Distinction of the user, if applicable',
  `password` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `users_email_unique` (`email`)
) ENGINE=MyISAM AUTO_INCREMENT=26 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `email`, `firstname`, `lastname`, `role`, `distinction`, `password`, `created_at`, `updated_at`) VALUES
(1, 'john@doe.com', 'John', 'Doe', 2, 'PhD. Ing.', '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(2, 'jane@smith.com', 'Jane', 'Smith', 2, 'PhD.', '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(3, 'alice@johnson.com', 'Alice', 'Johnson', 2, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(4, 'bob@brown.com', 'Bob', 'Brown', 1, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(5, 'davis@charlie.com', 'Charlie', 'Davis', 1, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(6, 'tmiller@example.net', 'Odie', 'Kulas', 1, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(7, 'ernestina91@example.org', 'Hubert', 'Block', 1, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(8, 'bechtelar.hardy@example.org', 'Amiya', 'Kshlerin', 1, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(9, 'abner03@example.com', 'Mae', 'Funk', 2, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(10, 'gleason.amira@example.net', 'Maribel', 'Runte', 2, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(11, 'grimes.mireille@example.org', 'Leanna', 'Simonis', 1, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(12, 'salvatore42@example.com', 'Hugh', 'Wolff', 2, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(13, 'hillary.cummerata@example.net', 'Delta', 'Haley', 2, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(14, 'torphy.scot@example.com', 'Estevan', 'Spencer', 2, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(15, 'glenda16@example.net', 'Bernadette', 'Bahringer', 2, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(16, 'bette.zulauf@example.com', 'Dora', 'Bernier', 2, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(17, 'rosamond49@example.net', 'Larissa', 'Cormier', 1, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(18, 'luettgen.immanuel@example.net', 'Jada', 'O\'Reilly', 2, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(19, 'garth93@example.com', 'Patricia', 'Heaney', 1, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(20, 'dubuque.libbie@example.org', 'Woodrow', 'Macejkovic', 2, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(21, 'mercedes.toy@example.net', 'Floyd', 'Hickle', 2, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(22, 'hamill.willis@example.org', 'Kayleigh', 'Halvorson', 2, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(23, 'cortney64@example.org', 'Ladarius', 'Dickens', 1, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(24, 'enienow@example.org', 'Niko', 'Bartoletti', 1, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16'),
(25, 'eleonore.cormier@example.com', 'Alexis', 'Rempel', 1, NULL, '6951367962714', '2025-05-04 22:36:16', '2025-05-04 22:36:16');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
