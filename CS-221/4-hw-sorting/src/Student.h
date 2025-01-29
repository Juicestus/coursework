#pragma once
#include <string>
#include <list>

/**
 * *** DO NOT EDIT THIS CLASS ***
 * Assume that the id field is unique for each student.
 */
class Student {
    unsigned int id;
    float gpa;
    std::string name;

public:
    Student() {}
    Student(unsigned int id, float gpa, std::string name) : id(id), gpa(gpa), name(name) {}

    const unsigned int& getID() const {
        return id;
    }

    const float& getGPA() const {
        return gpa;
    }

    const std::string& getName() const {
        return name;
    }
};

class GPAComparator {
public:
    /**
     * Compares two students and returns
     * - True if the first has a higher gpa than the second.
     * - False if the second has a higher gpa than the first.
     * - True if the first and second have the same gpa and the first has a lower id.
     * - False otherwise.
     */
    [[nodiscard]] bool operator()(const Student& a, const Student& b) const {
        /* TODO */
    }
};

class KnownOrderComparator {

    std::list<Student*> _student_ranking;

public:
    KnownOrderComparator(std::list<Student*> StudentRanking) : _student_ranking(StudentRanking) {}

    /**
     * Compares two students and returns
     * - True if the first appears before the second in _student_ranking.
     * - False otherwise (including when the a and b are the same).
     *
     * Should compare IDs.
     */
    [[nodiscard]] bool operator()(const Student& a, const Student& b) const {
        /* TODO */
    }
};
