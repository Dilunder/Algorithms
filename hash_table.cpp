#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class StudentGroupTable {
private:
    vector<list<pair<long, long>>> buckets;
    long bucket_count;
    long student_count;
    long total_points;
    long max_points;

    long calculateBucketIndex(long student_id) const {
        return ((student_id * student_id) >> 11) % bucket_count;
    }

    void resizeIfNeeded() {
        const double load_factor = 0.5;
        if (static_cast<double>(student_count) / bucket_count < load_factor) {
            return;
        }

        long new_bucket_count = bucket_count * 2;
        vector<list<pair<long, long>>> new_buckets(new_bucket_count);

        for (const auto& chain : buckets) {
            for (const auto& student : chain) {
                long new_index = ((student.first * student.first) >> 11) % new_bucket_count;
                new_buckets[new_index].push_back(student);
            }
        }

        buckets = move(new_buckets);
        bucket_count = new_bucket_count;
    }

    void updateMaxPoints() {
        max_points = 0;
        for (const auto& chain : buckets) {
            for (const auto& student : chain) {
                if (student.second > max_points) {
                    max_points = student.second;
                }
            }
        }
    }

public:
    explicit StudentGroupTable(long initial_size = 250)
            : buckets(initial_size), bucket_count(initial_size),
              student_count(0), total_points(0), max_points(0) {}

    void addStudent(long student_id, long points) {
        long index = calculateBucketIndex(student_id);

        for (const auto& student : buckets[index]) {
            if (student.first == student_id) {
                return;
            }
        }

        buckets[index].emplace_back(student_id, points);
        student_count++;
        total_points += points;
        max_points = max(max_points, points);

        resizeIfNeeded();
    }

    void removeStudent(long student_id) {
        long index = calculateBucketIndex(student_id);
        auto& chain = buckets[index];

        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->first == student_id) {
                long points = it->second;
                chain.erase(it);
                student_count--;
                total_points -= points;

                if (points == max_points) {
                    updateMaxPoints();
                }
                return;
            }
        }
    }

    long getMaxPoints() const {
        return max_points;
    }

    long getAveragePoints() const {
        return student_count == 0 ? 0 : total_points / student_count;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int group_count, operation_count;
    cin >> group_count >> operation_count;

    vector<StudentGroupTable> groups(group_count);

    for (int i = 0; i < operation_count; ++i) {
        char operation;
        int group;
        cin >> operation >> group;
        group--;

        switch (operation) {
            case '+': {
                long student_id, points;
                cin >> student_id >> points;
                groups[group].addStudent(student_id, points);
                break;
            }
            case '-': {
                long student_id;
                cin >> student_id;
                groups[group].removeStudent(student_id);
                break;
            }
            case 'm':
                cout << groups[group].getMaxPoints() << '\n';
                break;
            case 'a':
                cout << groups[group].getAveragePoints() << '\n';
                break;
        }
    }

    return 0;
}