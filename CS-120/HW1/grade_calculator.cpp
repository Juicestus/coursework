// These headers define some of the classes and functions we need
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// ONLY MAKE CHANGES WHERE THERE IS A TODO

// These using declarations let us refer to things more simply
// e.g. instead of "std::cin" we can just write "cin"
using std::cin, std::cout, std::endl;
using std::string, std::getline;

// These methods are defined below the main function

// print instructions for inputting grades
void print_instructions();

// pretty print a summary of the grades
void print_results(double exam_average,
                   double hw_average,
                   double lw_average,
                   double reading,
                   double engagement,
                   double weighted_total,
                   char final_letter_grade);

// YOU ARE NOT EXPECTED TO UNDERSTAND THIS ONE... YET
// extract the category and score from the line
// and store the values in the provided variables
// if line := "exam 95", then category := "exam" and score := 95
// if the line is invalid, then category := "ignore"
void get_category_and_score(const string& line,
                            string* category,
                            double* score);

struct Avg {
    double sum;
    int n;
    Avg() : sum(0), n(0) {};
    void add(double val) { 
        sum += val; 
        n++; 
    }
    double avg() { 
        if (n > 0) return sum / n; 
        return 0;
    }
};

int main() {
    print_instructions();

    Avg exam, hw, lw, read, eng;
    double final = 0;

    string line;
    // read one line from standard input (discards the ending newline character)
    getline(cin, line);
    // read lines until an empty line is read
    while (!line.empty()) {
        string category;
        double score;
        get_category_and_score(line, &category, &score);

        // process the grade entry
        if (category == "exam") {
            exam.add(score);
        } else if (category == "final-exam") {
            final = score;
        } else if (category == "hw") {
            hw.add(score);
        } else if (category == "lw") {
            lw.add(score);
        } else if (category == "reading") {
            read.add(score);
        } else if (category == "engagement") {
            eng.add(score);
        } else {
            cout << "ignored invalid input" << endl;
        }

        // get the next line from standard input
        getline(cin, line);
    }

#define P15(X) { if (X > 0) X = std::min(X + 15, 100.0); }

    // TODO(student): compute component averages
    exam.add(final);
    double exam_average = std::max(exam.avg(), final);
    double hw_average = hw.avg();
    double lw_average = lw.avg() * 100.0;
    double reading = read.avg();
    P15(reading);
    double engagement = eng.avg();
    P15(engagement);

    // TODO(student): compute weighted total of components
    double weighted_total = .4 * hw_average + .1 * lw_average + .4 * exam_average + .05 * reading + .05 * engagement;

    // TODO(student): compute final letter grade
    char final_letter_grade;
    if (weighted_total < 60) final_letter_grade = 'F';
    else if (weighted_total < 70) final_letter_grade = 'D';
    else if (weighted_total < 80) final_letter_grade = 'C';
    else if (weighted_total < 90) final_letter_grade = 'B';
    else final_letter_grade = 'A';

    print_results(
        exam_average, hw_average, lw_average, reading, engagement,
        weighted_total, final_letter_grade);
}

// These methods are already implemented for you
// You should not need to modify them

void print_instructions() {
    cout << "enter grades as <category> <score>" << endl;
    cout << "  <category> := exam | final-exam | hw | lw | reading | engagement" << endl;
    cout << "     <score> := numeric value" << endl;
    cout << "enter an empty line to end input" << endl;
}

void get_category_and_score(
    const string& line,
    string* category,
    double* score) {
    // turn the string into an input stream
    std::istringstream sin(line);

    // read the category (as string) and score (as double) from the stream
    sin >> *category;
    sin >> *score;

    if (sin.fail()) {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

void print_results(
    double exam_average,
    double hw_average,
    double lw_average,
    double reading,
    double engagement,
    double weighted_total,
    char final_letter_grade) {
    cout << "summary:" << endl;
    cout << "      exam average: " << exam_average << endl;
    cout << "        hw average: " << hw_average << endl;
    cout << "        lw average: " << lw_average << endl;
    cout << "           reading: " << reading << endl;
    cout << "        engagement: " << engagement << endl;
    cout << "    ---------------" << endl;

    cout << "    weighted total: " << weighted_total << endl;

    cout << "final letter grade: " << final_letter_grade << endl;
}
