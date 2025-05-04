# Mini Learning Platform

## Description

This is a mini learning platform that allows users to create and manage courses, lessons, and quizzes.
It is built using C and a MySQL database.
The platform provides a console interface for users to interact with the system, allowing them
to create and manage their own courses and lessons.

## Libraries to install

You can install the required libraries using the following command:
  ```bash
  make dependencies
  ```

## Database

Be sure to have the `db-crendetentials.h` file in the `utils/database` directory.
If you don't have it, you can create it by copying the `db-credentials.h.example` file and filling in your database credentials.
To migrate your created database, you can import the `db.sql` file into your MySQL database.

## Usage
To compile the project, run the following command:
  ```bash
  make
  ```
After compiling, you can run the program using the following command:
  ```bash
  cd bin && ./mini_learning_platform
  ```

You can test the program by logging in with the following credentials:
- Instructor:
  - email: john@doe.com
  - Password: 123456
- Learner:
  - email: bob@brown.com
  - Password: 123456

Or you can create a new user by registering with your email and password.

## Features
- Authentication
- Course listing
- Course monitoring process
