# Project Overview
This project leverages object-oriented programming to facilitate the enrollment of students to various courses and manage student and course records efficiently. Each course has a fixed capacity and once the 
capacity exceeds students wishing to register are already added to a waitlist. If a student drops out of a course, the students on the waitlist are automatically added. In addition, each course has pre-requisites.
The code ensures that no pre-requistes results in a cyclic denpendency. 

## Input Format
- The first line will contain an integer `Q`, representing the number of operations to be performed.
- For each operation:
  - If it is `add_student`, the next lines will include:
    - Student ID, Name, and Year of Study separated by spaces.
    - The number of completed courses.
    - A list of completed course codes separated by spaces.
  - If it is `add_course`, the next lines will include:
    - Course Code, Course Name, Number of Credits, Capacity, Time Slot.
    - The number of prerequisites.
    - A list of prerequisite course codes separated by spaces.
  - If it is `enroll`, the next line will include:
    - Student ID and Course Code separated by a space.
  - If it is `print`, the next line will include the course code.

- If it is `drop`, the next lines will include:
  - Student ID and Course Code.
  - If either the student or course does not exist, the system will reject the drop request and no waitlist processing is done.
